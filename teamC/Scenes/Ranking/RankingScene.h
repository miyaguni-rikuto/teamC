#pragma once

#include "../SceneBase.h"
#include <vector>
#include <fstream>
#include <algorithm>

const int MAX_RANKING = 5;

class RankingScene : public SceneBase
{
private:
	std::vector<int> ranking;

public:
	RankingScene();
	virtual ~RankingScene();

	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual eSceneType GetNowSceneType() const override;

	static RankingScene& GetInstance();

	void LoadRanking();   // �����L���O��ǂݍ���
	void SaveRanking();   // �����L���O��ۑ�����
	void AddScore(int score);
};

