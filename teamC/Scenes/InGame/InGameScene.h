#pragma once
#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"

class InGameScene : public SceneBase
{
private:
	class GameObjectManager* objm;
	std::vector<std::vector<int>> stage_data;			//���I�񎟌��z��

	int sky_image;	//��̔w�i�摜
	int leaf_image[3];	//���̔w�i�摜�i�\�z��
	int cloud_image[6];
	int mountain_image[6];
	int coin_image[1];
	int time_remaining = 4;  // ��������4�b
	float time_counter = 0.0f;
	bool start_flg;
	bool pause_flg;
	//Player* p;


	std::vector<int> UI_num;
	std::vector<int> UI_string;
	std::vector<int>UI_time;
	int num_image;
	int num_time;
	int num_world;
	int time_set;
	int time_add;
	int now_count;

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;

private:
	void LoadStageMapCSV();
	void DrawBackGroundCSV() const;
	void DeleteObject();
};

