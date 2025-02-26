#pragma once
#include "Vector2D.h"
#include <vector>

//�I�u�W�F�N�g�̃^�C�v
enum eObjectType
{
	eNone,
	ePlayer,
	eEnemy,
	eTable,
	eSord
};

//���݂̃��[���ʒu
enum eNowLane
{
	eNULL,
	eLEFT,
	eMID,
	eRIGHT
};

enum eSide
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

class Collision
{
public:
	bool is_blocking;
	eNowLane now_lane;
	Vector2D box_size;
	Vector2D pivot;
	eObjectType object_type;
	std::vector<eObjectType> hit_object_type;

	bool IsCheckHitTarget(eObjectType object_type) const;
	bool IsCheckHitCollision(Collision target1, Collision target2);
};

