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
/// ����������
/// </summary>
void BackImageBase::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void BackImageBase::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void BackImageBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

/// <summary>
/// �I��������
/// </summary>
void BackImageBase::Finalize()
{

}

void BackImageBase::OnHitCollision(GameObject* partner)
{

}
