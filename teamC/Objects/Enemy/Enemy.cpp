#include "Enemy.h"
#include "../../Objects/GameObject.h"
#include"../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/ScoreManager.h"
#include"../../Utility/Application.h"
#include "../Effect/Effect.h"
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
	hit_point(3),
	is_destroy(false),
	hit_flag(false),
	hit_table_flag(false),
	hit_enemy_flag(false),
	is_delete_flg(false),
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
	
	

	image = rm->GetImageResource("Resource/Images/Enemy/Enemy.png")[0];

	if (image == -1)
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
	collision.now_lane = eNULL;


	Enemy_state = eEnemyState::WALK;
	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	is_mobility = true;

}
 void Enemy::Update(float delta_second)
{
	 InputManager* input = InputManager::GetInstance();

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

	//�v���C���[�ƃ��[����������table�ɓ������Ă�����
	if (same_lane==true && hit_table_flag == true)
    {
		//�{�^���������ꂽ��HP�����
		if (input->GetButtonState(XINPUT_BUTTON_A) == Pressed)
		{
			GameObjectManager* obm = GameObjectManager::GetInstance();
			obm->CreateGameObject<Effect>(Vector2D(this->location.x + 16, location.y + 55.0f));

			hit_point--;
			ScoreManager::GetInstance().UpdateButtonCount(50);
		}
		
		//HP��0�ɂȂ��������
		if (hit_point == 0)
		{
			GameObjectManager* obm = GameObjectManager::GetInstance();
			is_delete_flg = true;
			obm->DestroyGameObject(this);
			ScoreManager::GetInstance().AddCount(100);
		}
    }

	hit_table_flag = false;
	hit_enemy_flag = false;

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
	if (hit_object->GetCollision().object_type == eTable)
	{
		hit_table_flag = true;
	}

	if (hit_object->GetCollision().object_type == eEnemy)
	{
		if (this->location.y < hit_object->GetLocation().y)
		{
			hit_enemy_flag = true;
		}
	}
}


void Enemy::CheckLane(bool a)
{
	same_lane = a;
}

void Enemy::SetLane(eNowLane a)
{
	this->collision.now_lane = a;
}
bool Enemy::GetDeleteFlag()
{
	return this->is_delete_flg;
}
/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Enemy::Movement(float delta_second)
{
	//���͏�Ԃ��擾
	//InputManager* input = InputManager::GetInstance();

	if (hit_table_flag == true)
	{
			k_velocity.y = 0.0f;
	}
	else
	{
		if (hit_enemy_flag == false)
		{
			k_velocity.y += 5.0f;
			if (location.x >= 400)
			{
				Finalize();
			}

			location.x += k_velocity.x * delta_second;
			location.y += k_velocity.y * delta_second;
		}
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
