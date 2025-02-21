#pragma once
#include "GameObject.h"

class BackImageBase : public GameObject
{
public:

protected:
	std::vector<int> destroy_animation;		//�A�j���[�V�����摜

public:
	BackImageBase();
	~BackImageBase();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset">�I�t�Z�b�g�l</param>
	virtual void Draw(const Vector2D& screen_offset) const;
	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize();

public:
	virtual void OnHitCollision(GameObject*) override;
};