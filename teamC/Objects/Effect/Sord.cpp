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

	collision.object_type = eObjectType::eSord;
	//����̉摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImageResource("Resource/item/Enemy_sword.png")[0];

	if (image == -1)
	{
		// �摜�ǂݍ��ݎ��s�̏ꍇ�̏���
		throw ("Resource/item/Enemy_sword.png���ǂݍ��߂܂���ł���\n");

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
