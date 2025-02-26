#include "Effect.h"
#include "../../Utility/ResourceManager.h"
#include "../GameObjectManager.h"


Effect::Effect() :
	elapsed_time(0.0f),
	elapsed_count(0),
	size(0.0f),
	death_count(0)
{

}

Effect::~Effect()
{

}
void Effect::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();

	//�摜��P�̂œǂ݂�
	int random = GetRand(1);
	
	if (random == 0)
	{
		image = rm->GetImageResource("Resource/Images/hibana.png")[0];
		flip = 1.0f;
	}
	else if (random == 1)
	{
		image = rm->GetImageResource("Resource/Images/hinaba2.png")[0];
		flip = -1.0f;
	}

	if (image == -1)
	{
		// �摜�ǂݍ��ݎ��s�̏ꍇ�̏���
		throw ("move_animation.png���ǂݍ��߂܂���ł���\n");

	}

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	is_mobility = true;

}
void Effect::Update(float delta_second)
{
	//�A�j���[�V�����̎擾
	Movement(delta_second);

	//�O�J�E���g�����Ə�����
	if (death_count > 3)
	{
		GameObjectManager *obm = GameObjectManager::GetInstance();
		obm->DestroyGameObject(this);
	}
}

void Effect::Draw(const Vector2D& screen_offset)const
{
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, size, 0.0, image, TRUE, filp_flag);
}

void Effect::Finalize()
{
	
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Effect::Movement(float delta_second)
{
	// �ړ����̃A�j���[�V����
	elapsed_time += delta_second;
	if (elapsed_time >= (1.0f / 8.0f))
	{
		elapsed_time = 0.0f;
		elapsed_count++;
		if (elapsed_count >= 2)
		{
			elapsed_count = 0;
			death_count++;
		}

		size += 0.15f;

		location.x += 5.5f * flip;
		location.y -= 5.0f;
	}
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Effect::AnimationControl(float delta_second)
{

}