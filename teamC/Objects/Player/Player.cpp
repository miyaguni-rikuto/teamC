#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

/*
UTF-8�ɂ���t�@�C��:
Player.cpp
InGameScene.cpp
Collision.cpp
Collision.h
Floor.cpp
*/


#define SCREEN_CENTER_X (320.0f) //x���W�̉�ʂ̒��S
#define PLAYER_CENTER_OFFSET (16.0f) //�v���C���[�����S�ɂȂ�悤�ɂ���I�t�Z�b�g

#define D_PLAYER_SPEED	(50.0f)
#define MAP_GRAVITY    (9.18f)

Player* Player::instance = nullptr;

Player::Player() :
	move_animation(),
	dying_animation(),
	p_velocity(0.0f),
	player_state(ePlayerState::MOVE),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	food_count(0),
	animation_time(0.0f),
	animation_count(0),
	is_power_up(false),
	is_destroy(false),
	acceleration_rate(70.0f),
	deceleration_rate(250.0f),
	max_speed(200.0f),
	scroll_velocity(0.0f),
	screen_scroll_speed(300.0f),
	is_grounded(false)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

	image = move_animation[0];

	//�G���[�`�F�b�N
	if (move_animation[0] == -1)
	{
		throw("\n");
	}
}

void Player::Update(float delta_second)
{
	
	//���͏�Ԃ̎擾
	Movement(delta_second);
	//�A�j���[�V�����̎擾
	if (player_state == MOVE)
	{
		AnimationControl(delta_second);
	}
	//�~�܂��Ă�Ƃ�
	else
	{
		image = move_animation[0];
	}

	is_grounded = false;
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	dying_animation.clear();
}



/// <summary>
/// �a��H�ׂ����擾
/// </summary>
/// <returns>�a��H�ׂ���</returns>
int Player::GetFoodCount() const
{
	return food_count;
}

/// <summary>
/// �v���C���[�̏�Ԃ��擾����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

/// <summary>
/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
bool Player::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// �p���[�_�E��������
/// </summary>
void Player::SetPowerDown()
{
	is_power_up = false;
}

bool Player::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::Movement(float delta_second)
{
	//���͏�Ԃ��擾
	InputManager* input = InputManager::GetInstance();

	//�������x�̕ϐ�
	float target_velocity_x = 0.0f;

	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		flip_flag = false;
		player_state = ePlayerState::MOVE;
		target_velocity_x = 5.0f; // �E�����̑��x
	}
	else if (input->GetKey(KEY_INPUT_LEFT))
	{
		flip_flag = true

		player_state = ePlayerState::MOVE;
		target_velocity_x = -5.0f; // �������̑��x
	}
	else
	{
		player_state = ePlayerState::IDLE;
	}

	//�W�����v����********************************************************
	static int jpcount = 0;

	//�n�ʂ��痣��Ă���Ώd�͂��v���C���[�ɗ^����
	if (!is_grounded)
	{
		p_velocity.y += MAP_GRAVITY;
	}
	//�n�ʂɗ����Ă��鎞�����W�����v����
	if (input->GetKey(KEY_INPUT_UP) && is_grounded)
	{
		p_velocity.y = -600.0f;	//�W�����v�X�s�[�h
		is_grounded = false;
	}
	else
	{
		jpcount = 0;
	}
	//*********************************************************************

	//���������������鏈��
	if (target_velocity_x != 0.0f)
	{
		//����
		if (p_velocity.x > 0 && target_velocity_x < 0 || p_velocity.x < 0 && target_velocity_x > 0)
		{
			p_velocity.x = 0.0f;
		}
		p_velocity.x += target_velocity_x * acceleration_rate * delta_second;

		//�ō����x
		if (p_velocity.x > max_speed)
		{
			p_velocity.x = max_speed;
		}
		else if (p_velocity.x < -max_speed)
		{
			p_velocity.x = -max_speed;
		}
	}
	else
	{
		//����
		if (abs(p_velocity.x) > 0)
		{
			float deceleration = deceleration_rate * delta_second;
			if (p_velocity.x > 0)
			{
				p_velocity.x = (p_velocity.x - deceleration) > 0 ? (p_velocity.x - deceleration) : 0;
			}
			else
			{
				p_velocity.x = (p_velocity.x + deceleration) < 0 ? (p_velocity.x + deceleration) : 0;
			}
		}
	}

	//���ƑO�̈ʒu�̒l�����ϐ�
	Vector2D next_location = location + (p_velocity * delta_second);
	old_location = location;


	//���݂̉�ʃI�t�Z�b�g���v�Z
	float current_offset_x = 0.0f;
	if (owner_scene != nullptr)
	{
		//current_offset_x = owner_scene->GetScreenOffset().x;
	}

	//�v���C���[���ړ��ł�����W�͈͐���
	float screen_limit_left = 0.0f + -current_offset_x + PLAYER_CENTER_OFFSET;
	float screen_limit_right = SCREEN_CENTER_X + -current_offset_x + PLAYER_CENTER_OFFSET;

	if (next_location.x < screen_limit_left)
	{
		next_location.x = screen_limit_left;
	}
	else if (next_location.x > screen_limit_right)
	{
		next_location.x = screen_limit_right;
	}

	//�X�e�[�W�X�N���[�����镪�̕ϐ�
	float target_scroll_amount = 0.0f;

	//�v���C���[����ʒ��S ���� �E�ֈړ����Ă���΃X�e�[�W���X�N���[������
	if (abs(location.x - screen_limit_right) <= D_OBJECT_SIZE && p_velocity.x > 0)
	{
		target_scroll_amount = p_velocity.x;
	}
	else
	{
		target_scroll_amount = 0;
	}


	//�X�e�[�W�X�N���[�����K�v�ł���Ύ�������
	if (target_scroll_amount != 0)
	{
		scroll_velocity = -target_scroll_amount;
	}
	else
	{
		scroll_velocity = 0.0f;
	}

	ApplyScreenScroll(scroll_velocity, delta_second);

	//�v���C���[���W���X�V
	location.x = next_location.x;
	location.y = next_location.y;
}



/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		image = move_animation[animation_num[animation_count]];
	}
}

//�v���C���[�̃C���X�^���X�擾
Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

//��ʃI�t�Z�b�g��ݒu
void Player::SetScreenOffset(const Vector2D& offset)
{
	if (owner_scene != nullptr)
	{
		//owner_scene->screen_offset = offset;
	}
}

//�X�e�[�W���X�N���[��������
void Player::ApplyScreenScroll(float velocity_x, float delta_second)
{
	float current_offset_x = 0.0f;
	if (owner_scene != nullptr)
	{
		//current_offset_x = owner_scene->GetScreenOffset().x;
	}

	float scroll_amount = velocity_x * delta_second;

	Vector2D new_offset(current_offset_x + scroll_amount, 0.0f);
	SetScreenOffset(new_offset);
}