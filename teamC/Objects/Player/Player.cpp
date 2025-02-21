#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

/*
UTF-8にするファイル:
Player.cpp
InGameScene.cpp
Collision.cpp
Collision.h
Floor.cpp
*/


#define SCREEN_CENTER_X (320.0f) //x座標の画面の中心
#define PLAYER_CENTER_OFFSET (16.0f) //プレイヤーが中心になるようにするオフセット

#define D_PLAYER_SPEED	(50.0f)
#define MAP_GRAVITY    (9.18f)

Player* Player::instance = nullptr;

Player::Player() :
	move_animation(),
	dying_animation(),
	p_velocity(0.0f),
	player_state(ePlayerState::MOVE),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	food_count(0),
	animation_time(0.0f),
	animation_count(0),
	is_power_up(false),
	is_destroy(false),
	acceleration_rate(70.0f),
	deceleration_rate(250.0f),
	max_speed(200.0f),
	scroll_velocity(0.0f),
	screen_scroll_speed(300.0f),
	is_grounded(false)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	image = move_animation[0];

	//エラーチェック
	if (move_animation[0] == -1)
	{
		throw("\n");
	}
}

void Player::Update(float delta_second)
{
	
	//入力状態の取得
	Movement(delta_second);
	//アニメーションの取得
	if (player_state == MOVE)
	{
		AnimationControl(delta_second);
	}
	//止まってるとき
	else
	{
		image = move_animation[0];
	}

	is_grounded = false;
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	dying_animation.clear();
}



/// <summary>
/// 餌を食べた数取得
/// </summary>
/// <returns>餌を食べた数</returns>
int Player::GetFoodCount() const
{
	return food_count;
}

/// <summary>
/// プレイヤーの状態を取得する
/// </summary>
/// <returns>プレイヤーの状態</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

/// <summary>
/// プレイヤーがパワーアップしてるか確認する
/// </summary>
/// <returns>プレイヤーの状態</returns>
bool Player::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// パワーダウンさせる
/// </summary>
void Player::SetPowerDown()
{
	is_power_up = false;
}

bool Player::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::Movement(float delta_second)
{
	//入力状態を取得
	InputManager* input = InputManager::GetInstance();

	//初期速度の変数
	float target_velocity_x = 0.0f;

	//右移動
	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		target_velocity_x = max_speed;
		now_direction_state = eDirectionState::RIGHT;
		player_state = ePlayerState::MOVE;
	}
	//左移動
	else if (input->GetKey(KEY_INPUT_LEFT))
	{
		target_velocity_x = max_speed;
		now_direction_state = eDirectionState::LEFT;
		player_state = ePlayerState::MOVE;
	}
	else
	{
		player_state = ePlayerState::IDLE;
		target_velocity_x = 0.0f;
	}
	// 速度の更新（加速度を考慮）
	if (p_velocity.x < target_velocity_x)
	{
		p_velocity.x += acceleration_rate * delta_second;
		if (p_velocity.x > target_velocity_x)
		{
			p_velocity.x = target_velocity_x;
		}
	}
	else if (p_velocity.x > target_velocity_x)
	{
		p_velocity.x -= deceleration_rate * delta_second;
		if (p_velocity.x < target_velocity_x)
		{
			p_velocity.x = target_velocity_x;
		}
	}
	

	//次と前の位置の値を持つ変数
	Vector2D next_location = location + (p_velocity * delta_second);
	old_location = location;


	//現在の画面オフセットを計算
	float current_offset_x = 0.0f;
	if (owner_scene != nullptr)
	{
		//current_offset_x = owner_scene->GetScreenOffset().x;
	}

	//プレイヤーが移動できる座標範囲制限
	float screen_limit_left = 0.0f + -current_offset_x + PLAYER_CENTER_OFFSET;
	float screen_limit_right = SCREEN_CENTER_X + -current_offset_x + PLAYER_CENTER_OFFSET;

	if (next_location.x < screen_limit_left)
	{
		next_location.x = screen_limit_left;
	}
	else if (next_location.x > screen_limit_right)
	{
		next_location.x = screen_limit_right;
	}

	//ステージスクロールする分の変数
	float target_scroll_amount = 0.0f;

	//プレイヤーが画面中心 かつ 右へ移動していればステージをスクロールする
	if (abs(location.x - screen_limit_right) <= D_OBJECT_SIZE && p_velocity.x > 0)
	{
		target_scroll_amount = p_velocity.x;
	}
	else
	{
		target_scroll_amount = 0;
	}


	//ステージスクロールが必要であれば実装する
	if (target_scroll_amount != 0)
	{
		scroll_velocity = -target_scroll_amount;
	}
	else
	{
		scroll_velocity = 0.0f;
	}

	ApplyScreenScroll(scroll_velocity, delta_second);

	//プレイヤー座標を更新
	location.x = next_location.x;
	location.y = next_location.y;
}



/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// 画像の設定
		image = move_animation[animation_num[animation_count]];
	}
}

//プレイヤーのインスタンス取得
Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

//画面オフセットを設置
void Player::SetScreenOffset(const Vector2D& offset)
{
	if (owner_scene != nullptr)
	{
		//owner_scene->screen_offset = offset;
	}
}

//ステージをスクロールさせる
void Player::ApplyScreenScroll(float velocity_x, float delta_second)
{
	float current_offset_x = 0.0f;
	if (owner_scene != nullptr)
	{
		//current_offset_x = owner_scene->GetScreenOffset().x;
	}

	float scroll_amount = velocity_x * delta_second;

	Vector2D new_offset(current_offset_x + scroll_amount, 0.0f);
	SetScreenOffset(new_offset);
}

void Player::OnHitCollision(GameObjectManager* hit_Object)
{
	player_state = ePlayerState::DIE;
}