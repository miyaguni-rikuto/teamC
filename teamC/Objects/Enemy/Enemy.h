#pragma once
#include"../GameObject.h"

// �v���C���[���
enum eEnemyState
{
	// �ҋ@���
	WALK,		// �ړ����
	// ���S���
};
class Enemy : public GameObject
{
private:
	// �i�s�������
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};
private:
	std::vector<int> move_animation;		// �ړ��̃A�j���[�V�����摜
	std::vector<int> dying_animation;
	Vector2D old_location;					// �O���location
	Vector2D k_velocity;// �ړ���
	eEnemyState Enemy_state;				// �v���C���[���
	eDirectionState now_direction_state;	// ���ݐi�s�������
	eDirectionState next_direction_state;	// ����i�s�������
	float animation_time;					// �A�j���[�V��������
	int animation_count;					// �A�j���[�V�����Y��
	bool is_destroy;						// ���񂾏�ԂɂȂ������H
	bool hit_flag;						//�I�u�W�F�N�g�ɓ������Ă��邩�ǂ���
	static Enemy* instance;                //�v���C���[�̃C���X�^���X
	bool is_delete_flg;
	int hit_point;

	
	bool same_lane;

	
	// �ړ��A�j���[�V�����̏���
	const int animation_num[4] = { 0, 1, 2, 1, };


public:
	Enemy();
	virtual~Enemy();

	virtual void  Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	void CheckLane(bool a);
	void SetLane(eNowLane a);
	bool GetDeleteFlag();

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

public:

	/// <summary>
	/// �v���C���[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	//eKuriboState GetKuriboState() const;

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);

public:
	//�C���X�^���X�擾
	static Enemy* GetInstance();
};

