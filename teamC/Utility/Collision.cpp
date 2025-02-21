#include "Collision.h"
#include <math.h>

///// <summary>
///// 適用オブジェクトか確認する処理
///// </summary>
///// <param name="hit_object">相手のオブジェクトタイプ</param>
///// <returns>適用するオブジェクトなら、true</returns>
bool Collision::IsCheckHitTarget(eObjectType hit_object) const
{
	// 適用するオブジェクトタイプなら、true
	for (eObjectType type : hit_object_type)
	{
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

//
///// <summary>
///// 矩形と矩形の当たり判定確認処理
///// </summary>
///// <param name="c1">矩形の情報1</param>
///// <param name="c2">矩形の情報2</param>
///// <returns>当たっているなら、true</returns>
bool IsCheckCollision(Collision& b1, Collision& b2)
{
	Vector2D ob1, ob2, diff, size;
	Vector2D object_center[2];

	ob1 = b1.box_location[0];
	ob2 = b2.box_location[0];

	object_center[0].x = b1.box_size.x / 2;
	object_center[0].y = b1.box_size.y / 2;
	object_center[1].x = b2.box_size.x / 2;
	object_center[1].y = b2.box_size.y / 2;

	diff.x = ob1.x - ob2.x;
	diff.y = ob1.y - ob2.y;

	if (diff.x < 0)
	{
		diff.x *= -1;
	}

	if (diff.y < 0)
	{
		diff.y *= -1;
	}

	size.x = (b1.box_size.x + b2.box_size.x) / 2;
	size.y = (b1.box_size.y + b2.box_size.y) / 2;

	if (diff.x <= size.x && diff.y <= size.y)
	{
		return true;
	}

	return false;
}