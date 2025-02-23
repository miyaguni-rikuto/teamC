#pragma once
#include"../GameObject.h"
#include"../GameObjectManager.h"

// プレイヤー状態
enum eEnemyState
{
	// 待機状態
	WALK,		// 移動状態
	// 死亡状態
};
class Enemy : public GameObject
{
private:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};
private:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> dying_animation;
	Vector2D old_location;					// 前回のlocation
	Vector2D k_velocity;// 移動量
	eEnemyState Enemy_state;				// プレイヤー状態
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	bool is_destroy;						// 死んだ状態になったか？
	static Enemy* instance;                //プレイヤーのインスタンス

	// 移動アニメーションの順番
	const int animation_num[4] = { 0, 1, 2, 1, };

	float acceleration_rate;		//加速度
	float deceleration_rate;		//減速度
	float max_speed;				//最高速度
	float scroll_velocity;			//スクロール加速度
	float screen_scroll_speed;		//スクロール速度
	bool is_grounded;				//地面にいるフラグ

public:
	Enemy();
	virtual~Enemy();

	virtual void  Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectManager* hit_object);

public:

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	//eKuriboState GetKuriboState() const;

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

public:
	//インスタンス取得
	static Enemy* GetInstance();
};

