#pragma once
#include "../SceneBase.h"

enum eSelectMenu
{
	eNONE,
	ePLAY,
	eHELP,
	eRank,
	eEXIT
};

class TitleScene : public SceneBase
{
public:
	std::vector<int> UI_num;
	std::vector<int> UI_string;
	std::vector<int> UI_coin;

	int pickup_color;
	int dropoff_color;
	int num_image;
	int string_image[26];
	eSelectMenu select_menu;

	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
	void SetUpSelectMenuType();
	void SetDownSelectMenuType();
};

