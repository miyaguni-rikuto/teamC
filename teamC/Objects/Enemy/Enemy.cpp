#include "Enemy.h"
#include"../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include"../../Utility/Application.h"
#include"DxLib.h"

#define D_ENEMY_SPEED (20.f)

Enemy* Enemy::instance = nullptr;

Enemy::Enemy() :
	move_animation(),
	dying_animation(),
	Enemy_state(WALK),
	now_direction_state(eDirectionState::NONE),
	next_direction_state(eDirectionState::LEFT),
	animation_time(0.0f),
	animation_count(0),
	is_destroy(false),
	hit_flag(false),
	k_velocity(1.0f)
{

}

Enemy::~Enemy()
{

}
void Enemy::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//画像を単体で読みむ
	int move_image = LoadGraph("Resource/Images/Enemy/Enemy.png");

	if (move_image == -1)
	{
		// 画像読み込み失敗の場合の処理
		throw ("move_animation.pngが読み込めませんでした\n");

	}


		//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::eTable);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = (32.0f, 32.0f);


	Enemy_state = eEnemyState::WALK;
	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	is_mobility = true;

	


}
 void Enemy::Update(float delta_second)
{
	//当たり判定の位置を取得する

	//当たり判定の位置を更新

	//入力状態の取得
	Movement(delta_second);
	//アニメーションの取得
	if (Enemy_state == WALK)
	{
		AnimationControl (delta_second);
	}
	//止まっている時
	else
	{

	}
}
void Enemy::Draw(const Vector2D& screen_offset)const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
	//DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "Enemy");
}
void Enemy::Finalize()
{
	//動的配列の開放
	move_animation.clear();
	dying_animation.clear();
}
/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Enemy::OnHitCollision(GameObject* hit_object)
{
	hit_flag = true;
}
/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Enemy::Movement(float delta_second)
{
	//入力状態を取得
	InputManager* input = InputManager::GetInstance();

	if (!hit_flag)
	{
		k_velocity.y += 5.0f;
		if (location.x >= 400)
		{
			Finalize();
		}


		location.x += k_velocity.x * delta_second;
		location.y += k_velocity.y * delta_second;
	}
	else
	{
		k_velocity.y = 0.0f;
	}


}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Enemy::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 8.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;
	//	if (animation_count >= 2)
	//	{
	//		animation_count = 0;
	//	}
	//	// 画像の設定
	//	image = move_animation[animation_num[animation_count]];
	//}
}

//プレイヤーのインスタンス取得
Enemy* Enemy::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Enemy();
	}
	return instance;
}
