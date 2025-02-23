#include "Table.h"
#include "../../Utility/ResourceManager.h"

Table::Table()
{

}

Table::~Table()
{

}

/// <summary>
/// ����������
/// </summary>
void Table::Initialize()
{
	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	//table_image = rm->GetImageResource("Resource/Images/table.png")[0];
	image = rm->GetImageResource("Resource/Images/table.png")[0];
	//image = table_image[10];

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
void Table::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void Table::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

/// <summary>
/// �I��������
/// </summary>
void Table::Finalize()
{
	// ���I�z��̉��
	image = NULL;
}

void Table::OnHitCollision(GameObject* partner)
{

}