#include "Table.h"
#include "../../Utility/ResourceManager.h"
#include"../../Objects/GameObject.h"

Table::Table()
{

}

Table::~Table()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void Table::Initialize()
{
	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	//table_image = rm->GetImageResource("Resource/Images/table.png")[0];
	image = rm->GetImageResource("Resource/Images/table.png")[0];
	//image = table_image[10];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eTable;
	collision.hit_object_type.push_back(eEnemy);
	collision.box_size = (32.0f, 32.0f);

	// レイヤーの設定
	z_layer = 4;

	//可動性の設定
	is_mobility = false;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Table::Update(float delta_second)
{
	
	hit_flag = false;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void Table::Draw(const Vector2D& screen_offset) const
{
		__super::Draw(screen_offset);
}

/// <summary>
/// 終了時処理
/// </summary>
void Table::Finalize()
{
	// 動的配列の解放
	image = NULL;
}

void Table::OnHitCollision(GameObject* partner)
{

}