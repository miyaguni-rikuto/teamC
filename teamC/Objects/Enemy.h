#pragma once
#include"GameObjectManager.h"
class Enemy
{
private:
	int type;
	int image;

	float speed;
	int count;
	Vector2D  location;   
	Vector2D box_size;   
	Enemy** p_enemy;

public:
	Enemy(int ytpe, int handle);
	~Enemy();

	void Initialize();            //初期化処理
	void Updata(float speed);     //更新処理
	void Draw()const;             //描画処理
	void Finalize();              //終了時処理

	int GetType()const;           //タイプ取得
	Vector2D GetLocation()const;  //位置情報の取得
	Vector2D GetBoxSize()const;   //当たり判定の大きさを取得
};

