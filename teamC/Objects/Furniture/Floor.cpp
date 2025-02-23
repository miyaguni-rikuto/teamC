#include "Floor.h"
#include "../../Utility/ResourceManager.h"

Floor::Floor()
{

}

Floor::~Floor()
{

}

/// <summary>
/// ����������
/// </summary>
void Floor::Initialize()
{
	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	floor_image = rm->GetImageResource("Resource/Images/yuka.png", 16, 16, 1, 32, 32);
	table_image = rm->GetImageResource("Resource/Images/yuka2.png", 16, 16, 1, 32, 32);
	image = floor_image[7];
	image = table_image[10];

	//�����蔻��̐ݒ�
	/*collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = (32.0f, 32.0f);*/

	// ���C���[�̐ݒ�
	z_layer = 4;

	//�����̐ݒ�
	is_mobility = false;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Floor::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void Floor::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

/// <summary>
/// �I��������
/// </summary>
void Floor::Finalize()
{
	// ���I�z��̉��
	image = NULL;
}

void Floor::OnHitCollision(GameObject* partner)
{

}