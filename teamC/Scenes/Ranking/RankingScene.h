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

	// 現在のシーンタイプ情報を取得する
	virtual eSceneType GetNowSceneType() const override;

	static RankingScene& GetInstance();

	void LoadRanking();   // ランキングを読み込む
	void SaveRanking();   // ランキングを保存する
	void AddScore(int score);
};

