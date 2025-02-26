#pragma once
#include"../GameObject.h"

class Effect : public GameObject
{
private:
	float elapsed_time;					// アニメーション時間
	int elapsed_count;					// アニメーション添字
	int death_count;						//消えるカウント
	float flip;							//反転数値
	float size;							//反転数値

public:
	Effect();
	virtual~Effect();

	virtual void  Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);
};