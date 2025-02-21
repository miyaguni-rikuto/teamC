#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy((int type, int handle) : type(type), image(handle), speed(0.0f), count(0),
	location(0.0f), box_size(0.0f), p_enemy(nullptr))
{

}
Enemy::~Enemy()
{

}
void Enemy::Initialize()
{
//出現させるX座標パターンを取得
	
		float random_x = (float)(GetRand(4)* 105 + 40);

		//生成位置の設定
		location = Vector2D(random_x, -50.0f);


		//当たり判定の設定
		box_size = Vector2D(31.0f, 60.0f);

		//速さの設定
		speed = (float)(this->type * 2);

		p_enemy = new Enemy * [10];

}
 void Enemy::Updata()
{
	 //位置情報に移動量を加算する


	 location += Vector2D(0.0f, this->speed + speed - 6);

}
 void Enemy::Draw()
{
	 DrawRotaGraphF(location.x, location.y, 1.0f, 0.0, image, TRUE);

	 {


	 }
}
void Enemy::Finalize()
{

}
int Enemy::GetType()const
{
	return type;
}
Vector2D Enemy::GetBoxSize()const
{
	return box_size;
}
Vector2D Enemy::GetLocation()const
{
	return location;
}