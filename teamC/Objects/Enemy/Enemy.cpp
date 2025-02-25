#include "Enemy.h"
#include"../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include"../../Utility/Application.h"
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
	is_destroy(false),
	hit_flag(false),
	k_velocity(1.0f)
{

}

Enemy::~Enemy()
{

}
void Enemy::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//�摜��P�̂œǂ݂�
	int move_image = LoadGraph("Resource/Images/Enemy/Enemy.png");

	if (move_image == -1)
	{
		// �摜�ǂݍ��ݎ��s�̏ꍇ�̏���
		throw ("move_animation.png���ǂݍ��߂܂���ł���\n");

	}


		//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::eTable);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = (32.0f, 32.0f);


	Enemy_state = eEnemyState::WALK;
	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	is_mobility = true;

	


}
 void Enemy::Update(float delta_second)
{
	//�����蔻��̈ʒu���擾����

	//�����蔻��̈ʒu���X�V

	//���͏�Ԃ̎擾
	Movement(delta_second);
	//�A�j���[�V�����̎擾
	if (Enemy_state == WALK)
	{
		AnimationControl (delta_second);
	}
	//�~�܂��Ă��鎞
	else
	{

	}
}
void Enemy::Draw(const Vector2D& screen_offset)const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
	//DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "Enemy");
}
void Enemy::Finalize()
{
	//���I�z��̊J��
	move_animation.clear();
	dying_animation.clear();
}
/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Enemy::OnHitCollision(GameObject* hit_object)
{
	hit_flag = true;
}
/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Enemy::Movement(float delta_second)
{
	//���͏�Ԃ��擾
	InputManager* input = InputManager::GetInstance();

	if (!hit_flag)
	{
		k_velocity.y += 5.0f;
		if (location.x >= 400)
		{
			Finalize();
		}


		location.x += k_velocity.x * delta_second;
		location.y += k_velocity.y * delta_second;
	}
	else
	{
		k_velocity.y = 0.0f;
	}


}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Enemy::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 8.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;
	//	if (animation_count >= 2)
	//	{
	//		animation_count = 0;
	//	}
	//	// �摜�̐ݒ�
	//	image = move_animation[animation_num[animation_count]];
	//}
}

//�v���C���[�̃C���X�^���X�擾
Enemy* Enemy::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Enemy();
	}
	return instance;
}
