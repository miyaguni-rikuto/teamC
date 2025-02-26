#pragma once
#include"../GameObject.h"

class Effect : public GameObject
{
private:
	float elapsed_time;					// �A�j���[�V��������
	int elapsed_count;					// �A�j���[�V�����Y��
	int death_count;						//������J�E���g
	float flip;							//���]���l
	float size;							//���]���l

public:
	Effect();
	virtual~Effect();

	virtual void  Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

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
};