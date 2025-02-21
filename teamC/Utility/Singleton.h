#pragma once

template <class T>

class Singleton
{
protected:

	//�R���X�g���N�^��private�ɂ��邱�ƂŁA
	//���N���X�̃����o�֐��ł����C���X�^���X�𐶐��ł��Ȃ��悤�ɂ���
	Singleton() = default;

	//�R�s�[�K�[�h
	//�N���X�O�ŃC���X�^���X�𐶐����ēn�����Ƃ��ł��Ȃ��悤�ɂ���
	Singleton(Singleton& v) = delete;
	Singleton& operator = (const Singleton& v) = delete;
	//�`�R�s�[�K�[�h

public:
	~Singleton() = default;

	/// <summary>
	/// �C���X�^���X�폜����
	/// </summary>
	//static void DeleteInstance();

public:
	static T* CreateInstance()
	{
		//�w�肵���N���X�𐶐�����
		//static�̓v���O�������I������܂ŏ���������������
		static T new_instance;

		return &new_instance;
	}
};