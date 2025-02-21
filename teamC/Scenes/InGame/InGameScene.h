#pragma once

#include "../SceneBase.h"
//#include "../../Objects/Player/Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"

class InGameScene : public SceneBase
{
private:
	//class Player* player;				// �v���C���[���
	//class EnemyBase* enemy;			//�@�G���
	int e_count;						//�G������
	std::vector<int> back_ground_image;		// �w�i�摜
	int back_ground_sound;					// BGM
	int score;							//�X�R�A
	bool pause_flag;					// �ꎞ��~�t���O
		
	Vector2D location;

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;

	/// <summary>
	/// �����蔻��m�F����
	/// </summary>
	/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
	/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
	virtual void HitCheckObject(GameObject* target, GameObject* partner) override;

	//private:
		/// <summary>
		// �X�e�[�W�}�b�v�i�ǁj�ǂݍ��ݏ���
		// </summary>
	void LoadStageMapCSV();

	/// <summary>
	/// �X�e�[�W�}�b�v�a�ǂݍ��ݏ���
	/// </summary>
	///void LoadStageMapFoodsCSV();
};