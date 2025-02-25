#include "DxLib.h"
#include "../../Objects/GameObject.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/Collision.h"
#include "Player.h"

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
	hammer_animation(),
	hammerdown_animation(),
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
	is_grounded(false),
	Is_hammering(false),
	hammer_timer(0.0f)

{
}

Player::~Player()
{

}

void Player::Initialize()
{

	//�摜�ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//�摜��P�̂œǂݍ���
	int move_image = LoadGraph("Resource/Images/Player/kajiyasan2_syoumen.png");
		
	// �G���[�`�F�b�N
	if (move_image == -1)
	{
		// �摜�ǂݍ��ݎ��s�̏ꍇ�̏���
		throw ("move_animation.png���ǂݍ��߂܂���ł���\n");
		
	}
	
	move_animation.push_back(move_image);  // �摜���A�j���[�V�������X�g�ɒǉ�

	// �n���}�[�A�N�V�����̉摜���ǂݍ���
	//int hammer_swing_up = LoadGraph("Resource/Images/Player/kajisan_kamae.png");
	tmp = rm->GetImageResource("Resource/Images/Player/kajisan_kamae.png");
	hammer_animation.push_back(tmp[0]);
	tmp = rm->GetImageResource("Resource/Images/Player/kajisan_hriososi.png");
	hammer_animation.push_back(tmp[0]);

	//int hammer_swing_down = LoadGraph("Resource/Images/Player/kajisan_hriososi.png");

	/*if (hammer_swing_up == -1 || hammer_swing_down == -1)
	{
		throw ("�n���}�[�̉摜���ǂݍ��߂܂���ł���\n");
	}*/

	//hammer_animation.push_back(hammer_swing_up);  // �n���}�[�U��グ�A�j���[�V�����̉摜��ǉ�
	//hammerdown_animation.push_back(hammer_swing_down);  // �n���}�[�U�艺�낵�A�j���[�V�����̉摜��ǉ�

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	is_mobility = true;

	image = hammer_animation[0];//move_animation[0];

	//SetHammerAnimation(, );
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

	InputManager* input = InputManager::GetInstance();

	//�n���}�[�̃A�N�V�������Ȃ玞�Ԃ����炵�ďI������
	if (Is_hammering)
	{
		hammer_timer -= delta_second;
		if (hammer_timer <= 0.0f)
		{
			Is_hammering = false;	//�n���}�[�U��I��
			image = hammer_animation[0];
		}
		return;
	}

	//A�{�^��������������A�N�V�����J�n
	if (input->GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
	{
		Is_hammering = true;
		hammer_timer = hammer_duration;
		image = hammer_animation[1];
	}
	//�ʏ�̈ړ�����
	//Movement(delta_second);
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	DrawFormatString(location.x + 10, location.y - 12, GetColor(255, 255, 255), "%d", current_lane);

	//DrawGraph(location.x, location.y, image,TRUE);

	// �f�o�b�O�p�F���͏�Ԃ�\��
	//InputManager* input = InputManager::GetInstance();
	
	//�f�o�b�O�p
	float left = location.x - PLAYER_CENTER_OFFSET + screen_offset.x;
	float top = location.y - PLAYER_CENTER_OFFSET + screen_offset.y;
	float right = location.x + PLAYER_CENTER_OFFSET + screen_offset.x;
	float bottom = location.y + PLAYER_CENTER_OFFSET + screen_offset.y;

	//DrawBox(left, top, right, bottom, GetColor(255, 255, 255), TRUE);
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
	// ���͏�Ԃ��擾
	InputManager* input = InputManager::GetInstance();

	// �E�ړ��i1���E�Ɉړ��j
	//if (input->GetButtonState(KEY_INPUT_RIGHT) == eInputState::Pressed ||
	//	input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Pressed)
	//{
	//	current_lane++;
	//	// ���݂̃��[�����E�[�łȂ��ꍇ�A���ԂɉE�Ɉړ�
	//	if (current_lane >= 2) // ���݉E�[�łȂ��Ȃ�
	//	{
	//		current_lane = 2;  // 1���E�Ɉړ�
	//	}
	//}
	//// ���ړ��i1�����Ɉړ��j
	//else if (input->GetButtonState(KEY_INPUT_LEFT) == eInputState::Pressed ||
	//	input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Pressed)
	//{
	//	current_lane--;
	//	// ���݂̃��[�������[�łȂ��ꍇ�A���Ԃɍ��Ɉړ�
	//	if (current_lane <= 0) // ���ݍ��[�łȂ��Ȃ�
	//	{
	//		current_lane = 0;  // 1�����Ɉړ�
	//	}
	//}
	// �E�ړ��i1���E�Ɉړ��j
	if (input->GetButtonState(KEY_INPUT_RIGHT) == eInputState::Pressed ||
		input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Pressed)
	{
		// �E�[�ɂ���Ƃ��͂��̂܂ܒ[�ɗ��܂�
		if (current_lane < 2)
		{
			current_lane++;  // �E�ɐi��
		}
	}
	// ���ړ��i1�����Ɉړ��j
	else if (input->GetButtonState(KEY_INPUT_LEFT) == eInputState::Pressed ||
		input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Pressed)
	{
		// ���[�ɂ���Ƃ��͂��̂܂ܒ[�ɗ��܂�
		if (current_lane > 0)
		{
			current_lane--;  // ���ɐi��
		}
	}

	// ���݂̃��[���Ɋ�Â��ăv���C���[�ʒu���X�V
	//location.x = lane_positions[current_lane];

	location.x = (210 * current_lane) + 110;

	// Y���̏����i���̂܂܁j
	location.y += p_velocity.y;
}
/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::AnimationControl(float delta_second)
{
	animation_time += delta_second;

	//�n���}�[�̏��
	if (Is_hammering)
	{

		//�n���}�[���U�肩�Ԃ����A�j���[�V����
		if (hammer_timer < hammer_duration / 2.0f)
		{
			animation_count = 0;	//�U�肩�Ԃ�����Ԃ̃t���[��
		}

		//�n���}�[��U�艺�낵���A�j���[�V����
		else if (hammer_timer < hammer_duration)
		{
			animation_count = 1;	//�U�艺�낵��Ԃ̃t���[��
		}
		else 
		{
			Is_hammering = false;
			animation_count = 0;
		}
	}
	//�ʏ펞�̃A�j���[�V����
	else if (player_state == ePlayerState::MOVE)
	{
		animation_count = (animation_count + 1 % move_animation.size());//�ړ��A�j���[�V�����̐؂�ւ�
	}
	else if (player_state == ePlayerState::DIE)
	{
		animation_count = (animation_count + 1 % dying_animation.size());//���S�A�j���[�V����
	}

	//�A�j���[�V����
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
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

void Player::SetHammerAnimation(int swing_up, int swing_down)
{
	hammer_animation.clear();
	hammer_animation.push_back(swing_up);  // �U�肩�Ԃ������̉摜
	hammerdown_animation.clear();
	hammerdown_animation.push_back(swing_down);  // �U�肨�낵�����̉摜
}

