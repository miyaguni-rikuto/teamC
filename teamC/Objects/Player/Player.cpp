#include "Player.h"
#include "../../Utility/ResourceManager.h"
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
	hammer_animation(),
	hammerdown_animation(),
	dying_animation(),
	p_velocity(0.0f),
	player_state(ePlayerState::MOVE),
	/*now_direction_state(eDirectionState::LEFT),*/
	now_direction_state(eDirectionState::NONE),
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
	is_grounded(false),
	Is_hammering(false),
	hammer_timer(0.0f)
{

}

Player::~Player()
{

}

void Player::Initialize()
{

	//画像読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	

	//画像を単体で読み込む
	int move_image = LoadGraph("Resource/Images/Player/kajiyasan2_syoumen.png");
		
	// エラーチェック
	if (move_image == -1)
	{
		// 画像読み込み失敗の場合の処理
		throw ("move_animation.pngが読み込めませんでした\n");
		
	}
	
	move_animation.push_back(move_image);  // 画像をアニメーションリストに追加

	// ハンマーアクションの画像も読み込む
	int hammer_swing_up = LoadGraph("Resource/Images/Player/kajisan_kamae.png");
	int hammer_swing_down = LoadGraph("Resource/Images/Player/kajisan_hriososi.png");

	if (hammer_swing_up == -1 || hammer_swing_down == -1)
	{
		throw ("ハンマーの画像が読み込めませんでした\n");
	}

	hammer_animation.push_back(hammer_swing_up);  // ハンマー振り上げアニメーションの画像を追加
	hammerdown_animation.push_back(hammer_swing_down);  // ハンマー振り下ろしアニメーションの画像を追加

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

	//SetHammerAnimation(, );
}

void Player::Update(float delta_second)
{
	
	//入力状態の取得
	Movement(delta_second);
	//アニメーションの取得
	//if (player_state == MOVE)
	//{
	//	AnimationControl(delta_second);
	//}
	////止まってるとき
	//else
	//{
	//	//image = move_animation[0];
	//}

	is_grounded = false;

	InputManager* input = InputManager::GetInstance();

	//ハンマーのアクション中なら時間を減らして終了判定
	if (Is_hammering)
	{
		hammer_timer -= delta_second;
		if (hammer_timer <= 0.0f)
		{
			Is_hammering = false;	//ハンマー振り終了
		}
		return;
	}

	//Aボタンをを押したらアクション開始
	if (input->GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
	{
		Is_hammering = true;
		hammer_timer = hammer_duration;
	}
	//通常の移動処理
	Movement(delta_second);
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	
	// デバッグ用：入力状態を表示
	//InputManager* input = InputManager::GetInstance();
	
	//デバッグ用
	float left = location.x - PLAYER_CENTER_OFFSET + screen_offset.x;
	float top = location.y - PLAYER_CENTER_OFFSET + screen_offset.y;
	float right = location.x + PLAYER_CENTER_OFFSET + screen_offset.x;
	float bottom = location.y + PLAYER_CENTER_OFFSET + screen_offset.y;

	DrawBox(left, top, right, bottom, GetColor(255, 255, 255), TRUE);
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
	float acceleration = acceleration_rate * delta_second;
	float deceleration = deceleration_rate * delta_second;

	//右移動
	if (input->GetButtonState(KEY_INPUT_RIGHT) || input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Held)
	{
		//target_velocity_x = max_speed;
		now_direction_state = eDirectionState::RIGHT;
		//player_state = ePlayerState::MOVE;
	}
	//左移動
	else if (input->GetButtonState(KEY_INPUT_LEFT) || input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Held)
	{
		//target_velocity_x = max_speed;
		now_direction_state = eDirectionState::LEFT;
		//player_state = ePlayerState::MOVE;
	}
	else
	{
		now_direction_state = eDirectionState::NONE;
	}
	if (input->GetButtonState(KEY_INPUT_A) || input->GetButtonState(XINPUT_BUTTON_A) == eInputState::Held)
	{	
		DrawString(10, 50, "A BUTTON PRESSED", GetColor(0, 0, 255));
	}

	switch (now_direction_state)
	{
	case Player::UP:
		break;
	case Player::RIGHT:
		p_velocity.x = 2.0f;
		if (input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::None)now_direction_state = NONE;
		break;
	case Player::DOWN:
		break;
	case Player::LEFT:
		p_velocity.x = -2.0f;
		if (input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::None)now_direction_state = NONE;
		break;
	case Player::NONE:
		p_velocity = 0.0f;
		//右移動
		if (input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT))
		{
			//target_velocity_x = max_speed;
			now_direction_state = eDirectionState::RIGHT;
			//player_state = ePlayerState::MOVE;
		}
		//左移動
		else if (input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Held)
		{
			//target_velocity_x = max_speed;
			now_direction_state = eDirectionState::LEFT;
			//player_state = ePlayerState::MOVE;
		}
		break;
	default:
		break;
	}


	location.x += p_velocity.x;
	location.y += p_velocity.y;
}



/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::AnimationControl(float delta_second)
{
	animation_time += delta_second;

	//ハンマーの状態
	if (Is_hammering)
	{

		//ハンマーが振りかぶったアニメーション
		if (hammer_timer < hammer_duration / 2.0f)
		{
			animation_count = 0;	//振りかぶった状態のフレーム
		}

		//ハンマーを振り下ろしたアニメーション
		else if (hammer_timer < hammer_duration)
		{
			animation_count = 1;	//振り下ろし状態のフレーム
		}
		else 
		{
			Is_hammering = false;
			animation_count = 0;
		}
	}
	//通常時のアニメーション
	else if (player_state == ePlayerState::MOVE)
	{
		animation_count = (animation_count + 1 % move_animation.size());//移動アニメーションの切り替え
	}
	else if (player_state == ePlayerState::DIE)
	{
		animation_count = (animation_count + 1 % dying_animation.size());//死亡アニメーション
	}

	//アニメーション
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
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

void Player::SetHammerAnimation(int swing_up, int swing_down)
{
	hammer_animation.clear();
	hammer_animation.push_back(swing_up);  // 振りかぶった時の画像
	hammerdown_animation.clear();
	hammerdown_animation.push_back(swing_down);  // 振りおろした時の画像
}