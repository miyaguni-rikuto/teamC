#pragma once
#include "../SceneBase.h"

class ResultScene : public SceneBase
{
private:
	int result_image = NULL;	//�w�i�摜
	int result_field = NULL;	//�e�L�X�g�t�B�[���h�摜
	int replay_image = NULL;	//�e�L�X�g�t�B�[���h�摜
	int title_image = NULL;	//�e�L�X�g�t�B�[���h�摜
	bool select;

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
};

