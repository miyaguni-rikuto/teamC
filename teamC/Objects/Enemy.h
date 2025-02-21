#pragma once
#include"GameObjectManager.h"
class Enemy
{
private:
	int type;
	int image;

	float speed;
	int count;
	Vector2D  location;   
	Vector2D box_size;   
	Enemy** p_enemy;

public:
	Enemy(int ytpe, int handle);
	~Enemy();

	void Initialize();            //����������
	void Updata(float speed);     //�X�V����
	void Draw()const;             //�`�揈��
	void Finalize();              //�I��������

	int GetType()const;           //�^�C�v�擾
	Vector2D GetLocation()const;  //�ʒu���̎擾
	Vector2D GetBoxSize()const;   //�����蔻��̑傫�����擾
};

