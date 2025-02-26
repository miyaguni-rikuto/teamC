#include "Enemy.h"
#include "../../Objects/GameObject.h"
#include"../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/ScoreManager.h"
#include"../../Utility/Application.h"
#include "../Effect/Effect.h"
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
	hit_point(3),
	is_destroy(false),
	hit_flag(false),
	hit_table_flag(false),
	hit_enemy_flag(false),
	is_delete_flg(false),
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
	
	

	image = rm->GetImageResource("Resource/Images/Enemy/Enemy.png")[0];

	if (image == -1)
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
	collision.now_lane = eNULL;


	Enemy_state = eEnemyState::WALK;
	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	is_mobility = true;

}
 void Enemy::Update(float delta_second)
{
	 InputManager* input = InputManager::GetInstance();

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

	//プレイヤーとレーンが同じでtableに当たっていたら
	if (same_lane==true && hit_table_flag == true)
    {
		//ボタンが押されたらHPを削る
		if (input->GetButtonState(XINPUT_BUTTON_A) == Pressed)
		{
			GameObjectManager* obm = GameObjectManager::GetInstance();
			obm->CreateGameObject<Effect>(Vector2D(this->location.x + 16, location.y + 55.0f));

			hit_point--;
			ScoreManager::GetInstance().UpdateButtonCount(50);
		}
		
		//HPが0になったら消す
		if (hit_point == 0)
		{
			GameObjectManager* obm = GameObjectManager::GetInstance();
			is_delete_flg = true;
			obm->DestroyGameObject(this);
			ScoreManager::GetInstance().AddCount(100);
		}
    }

	hit_table_flag = false;
	hit_enemy_flag = false;

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
	if (hit_object->GetCollision().object_type == eTable)
	{
		hit_table_flag = true;
	}

	if (hit_object->GetCollision().object_type == eEnemy)
	{
		if (this->location.y < hit_object->GetLocation().y)
		{
			hit_enemy_flag = true;
		}
	}
}


void Enemy::CheckLane(bool a)
{
	same_lane = a;
}

void Enemy::SetLane(eNowLane a)
{
	this->collision.now_lane = a;
}
bool Enemy::GetDeleteFlag()
{
	return this->is_delete_flg;
}
/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Enemy::Movement(float delta_second)
{
	//入力状態を取得
	//InputManager* input = InputManager::GetInstance();

	if (hit_table_flag == true)
	{
			k_velocity.y = 0.0f;
	}
	else
	{
		if (hit_enemy_flag == false)
		{
			k_velocity.y += 5.0f;
			if (location.x >= 400)
			{
				Finalize();
			}

			location.x += k_velocity.x * delta_second;
			location.y += k_velocity.y * delta_second;
		}
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
