#pragma once
#include "GameObject.h"

class BackImageBase : public GameObject
{
public:

protected:
	std::vector<int> destroy_animation;		//アニメーション画像

public:
	BackImageBase();
	~BackImageBase();

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
	virtual void OnHitCollision(GameObject*) override;
};