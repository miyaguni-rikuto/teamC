#pragma once
#include"../../Objects/GameObject.h"

class Sord:public GameObject
{
private:
	std::vector<int> item_image;		// 武器画像
	int hit_point;
public:
	Sord();
	~Sord();


	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset">オフセット値</param>
	virtual void Draw(const Vector2D& screen_offset) const;
	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize();

public:
	virtual void OnHitCollision(GameObject* target) override;
private:

};
