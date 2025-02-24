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
	/*now_direction_state(eDirectionState::LEFT),*/
	now_direction_state(eDirectionState::NONE),
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
	is_mobility = true;

	//image = NULL;//move_animation[0];

	////�G���[�`�F�b�N
	//if (move_animation[0] == -1)
	//{
	//	throw("\n");
	//}
}

void Player::Update(float delta_second)
{
	
	//���͏�Ԃ̎擾
	Movement(delta_second);
	//�A�j���[�V�����̎擾
	//if (player_state == MOVE)
	//{
	//	AnimationControl(delta_second);
	//}
	////�~�܂��Ă�Ƃ�
	//else
	//{
	//	//image = move_animation[0];
	//}

	is_grounded = false;
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	
	// �f�o�b�O�p�F���͏�Ԃ�\��
	InputManager* input = InputManager::GetInstance();
	
	//�f�o�b�O�p
	float left = location.x - PLAYER_CENTER_OFFSET + screen_offset.x;
	float top = location.y - PLAYER_CENTER_OFFSET + screen_offset.y;
	float right = location.x + PLAYER_CENTER_OFFSET + screen_offset.x;
	float bottom = location.y + PLAYER_CENTER_OFFSET + screen_offset.y;

	DrawBox(left, top, right, bottom, GetColor(255, 255, 255), TRUE);
}

void Player::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	dying_animation.clear();
}


/// <summary>
/// �v���C���[�̏�Ԃ��擾����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
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
	float acceleration = acceleration_rate * delta_second;
	float deceleration = deceleration_rate * delta_second;

	//�E�ړ�
	if (input->GetButtonState(KEY_INPUT_RIGHT) || input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Held)
	{
		//target_velocity_x = max_speed;
		now_direction_state = eDirectionState::RIGHT;
		//player_state = ePlayerState::MOVE;
	}
	//���ړ�
	else if (input->GetButtonState(KEY_INPUT_LEFT) || input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Held)
	{
		//target_velocity_x = max_speed;
		now_direction_state = eDirectionState::LEFT;
		//player_state = ePlayerState::MOVE;
	}
	else
	{
		now_direction_state = eDirectionState::NONE;
	}
	if (input->GetButtonState(KEY_INPUT_A) || input->GetButtonState(XINPUT_BUTTON_A) == eInputState::Held)
	{	
		DrawString(10, 50, "A BUTTON PRESSED", GetColor(0, 0, 255));
	}

	switch (now_direction_state)
	{
	case Player::UP:
		break;
	case Player::RIGHT:
		p_velocity.x = 5.0f;
		if (input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::None)now_direction_state = NONE;
		break;
	case Player::DOWN:
		break;
	case Player::LEFT:
		p_velocity.x = -5.0f;
		if (input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::None)now_direction_state = NONE;
		break;
	case Player::NONE:
		p_velocity = 0.0f;
		//�E�ړ�
		if (input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT))
		{
			//target_velocity_x = max_speed;
			now_direction_state = eDirectionState::RIGHT;
			//player_state = ePlayerState::MOVE;
		}
		//���ړ�
		else if (input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Held)
		{
			//target_velocity_x = max_speed;
			now_direction_state = eDirectionState::LEFT;
			//player_state = ePlayerState::MOVE;
		}
		break;
	default:
		break;
	}


	location.x += p_velocity.x;
	location.y += p_velocity.y;
}



/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 8.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;
	//	if (animation_count >= 4)
	//	{
	//		animation_count = 0;
	//	}
	//	// �摜�̐ݒ�
	//	image = move_animation[animation_num[animation_count]];
	//}
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
	//if (owner_scene != nullptr)
	//{
	//	//owner_scene->screen_offset = offset;
	//}
}

//�X�e�[�W���X�N���[��������
void Player::ApplyScreenScroll(float velocity_x, float delta_second)
{
	//float current_offset_x = 0.0f;
	//if (owner_scene != nullptr)
	//{
	//	//current_offset_x = owner_scene->GetScreenOffset().x;
	//}

	//float scroll_amount = velocity_x * delta_second;

	//Vector2D new_offset(current_offset_x + scroll_amount, 0.0f);
	//SetScreenOffset(new_offset);
}

void Player::OnHitCollision(GameObjectManager* hit_Object)
{
	player_state = ePlayerState::DIE;
}