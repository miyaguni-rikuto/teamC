#include "Sord.h"
#include "../../Objects/GameObject.h"
#include"../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/ScoreManager.h"
#include"../../Utility/Application.h"
#include"DxLib.h"
Sord::Sord()
{
}

Sord::~Sord()
{
}

void Sord::Initialize()
{
	//武器の画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImageResource("Resource/item/Enemy_sword.png")[0];

	if (image == -1)
	{
		// 画像読み込み失敗の場合の処理
		throw ("Resource/item/Enemy_sword.pngが読み込めませんでした\n");

	}
}

void Sord::Update(float delta_second)
{
}

void Sord::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Sord::Finalize()
{
}

void Sord::OnHitCollision(GameObject* target)
{
}
