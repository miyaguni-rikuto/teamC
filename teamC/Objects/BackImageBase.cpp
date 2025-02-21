#include "BackImageBase.h"
#include "../Utility/ResourceManager.h"

#include "../Utility/Singleton.h"

#include "DxLib.h"

#define DEBUG

BackImageBase::BackImageBase()
{

}

BackImageBase::~BackImageBase()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void BackImageBase::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void BackImageBase::Update(float delta_second)
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void BackImageBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

/// <summary>
/// 終了時処理
/// </summary>
void BackImageBase::Finalize()
{

}

void BackImageBase::OnHitCollision(GameObject* partner)
{

}
