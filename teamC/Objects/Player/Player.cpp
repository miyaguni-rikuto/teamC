#include "Player.h"
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
	is_mobility = true;

	//image = NULL;//move_animation[0];

	////エラーチェック
	//if (move_animation[0] == -1)
	//{
	//	throw("\n");
	//}
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
		//image = move_animation[0];
	}

	is_grounded = false;
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	//デバッグ用
	float left = location.x - PLAYER_CENTER_OFFSET + screen_offset.x;
	float top = location.y - PLAYER_CENTER_OFFSET + screen_offset.y;
	float right = location.x + PLAYER_CENTER_OFFSET + screen_offset.x;
	float bottom = location.y + PLAYER_CENTER_OFFSET + screen_offset.y;

	DrawBox(left, top, right, bottom, GetColor(255, 255, 255), TRUE);
	// デバッグ用：入力状態を表示
	InputManager* input = InputManager::GetInstance();
	if (input->GetKeyState(KEY_INPUT_LEFT))
	{
		DrawString(10, 10, "LEFT KEY PRESSED", GetColor(255, 0, 0));
	}
	if (input->GetKeyState(KEY_INPUT_RIGHT))
	{
		DrawString(10, 30, "RIGHT KEY PRESSED", GetColor(0, 255, 0));
	}
}

void Player::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	dying_animation.clear();
}


/// <summary>
/// プレイヤーの状態を取得する
/// </summary>
/// <returns>プレイヤーの状態</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
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
	if (input->GetKeyState(KEY_INPUT_RIGHT))
	{
		target_velocity_x = max_speed;
		now_direction_state = eDirectionState::RIGHT;
		player_state = ePlayerState::MOVE;
	}
	//左移動
	else if (input->GetKeyState(KEY_INPUT_LEFT))
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
	
	

	//次と前の位置の値を持つ変数
	Vector2D next_location = location + (p_velocity * delta_second);
	old_location = location;

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
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 8.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;
	//	if (animation_count >= 4)
	//	{
	//		animation_count = 0;
	//	}
	//	// 画像の設定
	//	image = move_animation[animation_num[animation_count]];
	//}
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
	//if (owner_scene != nullptr)
	//{
	//	//owner_scene->screen_offset = offset;
	//}
}

//ステージをスクロールさせる
void Player::ApplyScreenScroll(float velocity_x, float delta_second)
{
	//float current_offset_x = 0.0f;
	//if (owner_scene != nullptr)
	//{
	//	//current_offset_x = owner_scene->GetScreenOffset().x;
	//}

	//float scroll_amount = velocity_x * delta_second;

	//Vector2D new_offset(current_offset_x + scroll_amount, 0.0f);
	//SetScreenOffset(new_offset);
}

void Player::OnHitCollision(GameObjectManager* hit_Object)
{
	player_state = ePlayerState::DIE;
}