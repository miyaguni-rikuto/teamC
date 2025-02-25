
#pragma once

#include "../GameObject.h"
#include"../GameObjectManager.h"

// プレイヤー状態
enum ePlayerState
{
	IDLE,		// 待機状態
	MOVE,		// 移動状態
	DIE,		// 死亡状態
};



/// <summary>
/// プレイヤークラス（マリオ）
/// </summary>
class Player : public GameObject
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

public:

private:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> hammer_animation;		// ハンマーを振りかぶった時
	std::vector<int> hammerdown_animation;		// ハンマーを振りおろした時
	std::vector<int> dying_animation;		// 死亡のアニメーション画像
	Vector2D old_location;					// 前回のlocation
	Vector2D p_velocity;						// 移動量
	ePlayerState player_state;				// プレイヤー状態
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態

	int current_lane = 1;
	float lane_positions[3]{ D_LEFT_LEAN,D_MID_LEAN,D_RIGHT_LEAN };
	

	int food_count;							// コインを取った枚数
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	bool is_power_up;						// パワー餌を食べたか？
	bool is_destroy;						// 死んだ状態になったか？
	static Player* instance;                //プレイヤーのインスタンス

	bool IsHammering() const { return Is_hammering; }

	int normal_image;
	bool Is_hammering;						//ハンマーを振っているかのフラグ
	float hammer_timer;						//ハンマーのアクションを開始
	const float hammer_duration=0.3f;			//ハンマーを振る時間

 	// 移動アニメーションの順番
	const int animation_num[4] = { 0, 1, 2, 1, };

	float acceleration_rate;		//加速度
	float deceleration_rate;		//減速度
	float max_speed;				//最高速度
	float scroll_velocity;			//スクロール加速度
	float screen_scroll_speed;		//スクロール速度
	bool is_grounded;				//地面にいるフラグ

public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	//ハンマーアニメーションの追加
	void SetHammerAnimation(int swing_up, int swing_down);


	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectManager* hit_object);


	/// <summary>
   /// ハンマーの衝突チェック処理
   /// </summary>
	void CheckHammerCollision();

	// <summary>
	/// エネミーとの衝突時に呼ばれる処理
	/// </summary>
	void OnHitEnemy(GameObject* enemy);

public:
	/// <summary>
	/// 餌を食べた数取得
	/// </summary>
	/// <returns>餌を食べた数</returns>
	int GetFoodCount() const;

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	ePlayerState GetPlayerState() const;

	/// <summary>
	/// プレイヤーがパワーアップしてるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	bool GetPowerUp() const;

	/// <summary>
	/// パワーダウンさせる
	/// </summary>
	void SetPowerDown();

	/// <summary>
	/// プレイヤーがパワーアップしてるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	bool GetDestroy() const;


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
	static Player* GetInstance();

	//画面オフセット設置
	void SetScreenOffset(const Vector2D& offset);

	

private:
	// ステージをスクロールする
	void ApplyScreenScroll(float next_location_x, float current_offset_x);

	
};
