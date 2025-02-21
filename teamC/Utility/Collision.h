#pragma once

#include "Vector2D.h"
#include <vector>

// �I�u�W�F�N�g�^�C�v
enum class eObjectType : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eGround,
	eBlock,
	eItem,
	eClay_pipe
};

struct HitCheck
{
	//�e�ӂɓ������Ă��邩�ǂ����𔻒肷��
	bool H_left;
	bool H_right;
	bool H_top;
	bool H_bottom;
};

// �����蔻����N���X
class Collision
{
public:
	//�{�b�N�X�̓����蔻��
	float B_left;		//x���W
	float B_right;		//x + width(x���W�ƕ��𑫂������l)
	float B_top;		//y���W
	float B_bottom;		//y + height(y���W�ƍ����𑫂������l)

public:
	bool						is_blocking;		// ���蔲���t���O
	eObjectType					object_type;		// ���g�̃I�u�W�F�N�g�^�C�v
	std::vector<eObjectType>	hit_object_type;	// �K�p����I�u�W�F�N�g�^�C�v
	Vector2D					location;			// ��`�̍��W
	Vector2D					box_size;			// ��`�̍��W
	Vector2D					box_location[2];			// ��`�̔��a
	Vector2D					center[2];			// �n�_�ƏI�_�i���΍��W�j
	HitCheck					hitCheck;			//�e�ӂ̓����蔻����

public:
	Collision() :
		is_blocking(false),
		object_type(eObjectType::eNone),
		hit_object_type(),
		location(0.0f, 0.0f),
		box_size(0.0f, 0.0f),
		B_left(0.0f),
		B_right(0.0f),
		B_top(0.0f),
		B_bottom(0.0f)
	{
		center[0] = 0.0f;
		center[1] = 0.0f;

		box_location[0] = 0.0f;
		box_location[1] = 0.0f;

		hitCheck.H_bottom = 0.0f;
		hitCheck.H_top = 0.0f;
		hitCheck.H_left = 0.0f;
		hitCheck.H_right = 0.0f;

	}
	~Collision()
	{
		hit_object_type.clear();
	}

public:
	// �����蔻��L���m�F����
	bool IsCheckHitTarget(eObjectType hit_object) const;

	////�I�u�W�F�N�g���ڐG���Ă��邩�ǂ���
	/*void HitCheckObject(GameObject* a, GameObject* b);*/

};

/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="c1">�`��̏��1</param
/// <param name="c2">�`��̏��2</param>
/// <returns>�������Ă���Ȃ�Atrue</returns>
bool IsCheckCollision(Collision& b1, Collision& b2);