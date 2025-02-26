#include "Effect.h"
#include "../../Utility/ResourceManager.h"
#include "../GameObjectManager.h"


Effect::Effect() :
	elapsed_time(0.0f),
	elapsed_count(0),
	size(0.0f),
	death_count(0)
{

}

Effect::~Effect()
{

}
void Effect::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像を単体で読みむ
	int random = GetRand(1);
	
	if (random == 0)
	{
		image = rm->GetImageResource("Resource/Images/hibana.png")[0];
		flip = 1.0f;
	}
	else if (random == 1)
	{
		image = rm->GetImageResource("Resource/Images/hinaba2.png")[0];
		flip = -1.0f;
	}

	if (image == -1)
	{
		// 画像読み込み失敗の場合の処理
		throw ("move_animation.pngが読み込めませんでした\n");

	}

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	is_mobility = true;

}
void Effect::Update(float delta_second)
{
	//アニメーションの取得
	Movement(delta_second);

	//三カウントされると消える
	if (death_count > 3)
	{
		GameObjectManager *obm = GameObjectManager::GetInstance();
		obm->DestroyGameObject(this);
	}
}

void Effect::Draw(const Vector2D& screen_offset)const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, size, 0.0, image, TRUE, filp_flag);
}

void Effect::Finalize()
{
	
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Effect::Movement(float delta_second)
{
	// 移動中のアニメーション
	elapsed_time += delta_second;
	if (elapsed_time >= (1.0f / 8.0f))
	{
		elapsed_time = 0.0f;
		elapsed_count++;
		if (elapsed_count >= 2)
		{
			elapsed_count = 0;
			death_count++;
		}

		size += 0.15f;

		location.x += 5.5f * flip;
		location.y -= 5.0f;
	}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Effect::AnimationControl(float delta_second)
{

}