#pragma once

#include <DxLib.h>

class ScoreManager
{
public:
		
private:
	int score;
	int button_count, enemy_count;
	

private:
	void Draw();
	ScoreManager();
	~ScoreManager() {}

	bool ButtonState;
public:
	static ScoreManager& GetInstance();
	int GetCount();
	int GetScore();
	void AddCount(int val);
	void DrawCount();
	void UpdateButtonCount(int val);
	void ResetScore();

};

