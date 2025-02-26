#pragma once
#include"../../Objects/GameObject.h"

class Sord:public GameObject
{
private:
	std::vector<int> item_image;		// ����摜
	int hit_point;
public:
	Sord();
	~Sord();


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
	virtual void OnHitCollision(GameObject* target) override;
private:

};
