#pragma once

#include <DxLib.h>

enum COUNTDATA {
	BUTTON_COUNT,
	ENEMY_COUNT
};

class ScoreManager
{
	public:
    //ScoreManager();
private:
	int g_number[10];

	int score;
	int button_count, enemy_count;

private:
	void Draw();
	ScoreManager();
	~ScoreManager() {}

	bool ButtonState;
public:
	static ScoreManager& GetInstance();
	void SetCount(COUNTDATA data, int val);
	int GetCount(COUNTDATA data);
	void AddCount(int val);
	void DrawCount();
	void UpdateButtonCount(int val);
	void ResetScore();
};

