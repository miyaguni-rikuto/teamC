#pragma once
#include "../SceneBase.h"
#include "../../Objects/GameObjectManager.h"

class InGameScene : public SceneBase
{
private:
	class GameObjectManager* objm;
	class Player* player;
	class Enemy* enemy;
	std::vector<std::vector<int>> stage_data;			//“®“I“ñŸŒ³”z—ñ
	int count;
	std::vector<Enemy*> game_enemy_list;

	int sky_image;	//‹ó‚Ì”wŒi‰æ‘œ
	int leaf_image[3];	//‘‚Ì”wŒi‰æ‘œŠi”\”z—ñ
	int cloud_image[6];
	int enemy_count[3];		//ŠeƒŒ[ƒ“‚Ì“G”
	int mountain_image[6];
	int coin_image[1];
	int time_remaining = 4;  // ‰ŠúŠÔ4•b
	float time_counter = 0.0f;
	int enemy_timer = 0;
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

	int mainbgm;//ƒQ[ƒ€ƒƒCƒ“‚ÌBG‚l

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;
	void testCheckLane();

private:
	void LoadStageMapCSV();
	void DrawBackGroundCSV() const;
	void DeleteObject();
};

