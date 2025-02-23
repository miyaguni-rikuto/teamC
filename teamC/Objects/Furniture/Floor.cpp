#include "Floor.h"
#include "../../Utility/ResourceManager.h"

Floor::Floor()
{

}

Floor::~Floor()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void Floor::Initialize()
{
	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	floor_image = rm->GetImageResource("Resource/Images/yuka.png", 16, 16, 1, 32, 32);
	table_image = rm->GetImageResource("Resource/Images/yuka2.png", 16, 16, 1, 32, 32);
	image = floor_image[7];
	image = table_image[10];

	//当たり判定の設定
	/*collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = (32.0f, 32.0f);*/

	// レイヤーの設定
	z_layer = 4;

	//可動性の設定
	is_mobility = false;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Floor::Update(float delta_second)
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void Floor::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

/// <summary>
/// 終了時処理
/// </summary>
void Floor::Finalize()
{
	// 動的配列の解放
	image = NULL;
}

void Floor::OnHitCollision(GameObject* partner)
{

}