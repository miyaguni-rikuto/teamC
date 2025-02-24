#pragma once

#include <DxLib.h>

enum SCOREDATA {
	HIGH_SCORE,
	CURRENT_SCORE
};

class ScoreManager
{
	public:
    ScoreManager();
private:
	int g_number[10];

	int high_score, score;

private:
	void Draw();

public:
	void SetScore(SCOREDATA data, int val);
	int GetScore(SCOREDATA data);
	void AddScore(int val);
	void DrawScore();
};

