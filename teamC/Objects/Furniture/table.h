#pragma once
#include "../BackImageBase.h"

class Table : public BackImageBase
{
private:
	std::vector<int> table_image;		// �w�i�摜

public:
	Table();
	~Table();

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

};
