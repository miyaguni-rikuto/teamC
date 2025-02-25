#pragma once
#include "../SceneBase.h"

class ResultScene : public SceneBase
{
private:
	int result_image = NULL;	//背景画像
	int result_field = NULL;	//テキストフィールド画像
	int replay_image = NULL;	//テキストフィールド画像
	int title_image = NULL;	//テキストフィールド画像
	bool select;

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
};

