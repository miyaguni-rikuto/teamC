#include "ScoreManager.h"
#include "InputManager.h"
#include <cstdio>
#include <fstream>


ScoreManager::ScoreManager() : button_count(0), enemy_count(0), score(0)
{
}

ScoreManager& ScoreManager::GetInstance() {
    static ScoreManager instance;
    return instance;
}


void ScoreManager::AddCount(int val)
{
    enemy_count++;
    score += val;
  
}

int ScoreManager::GetCount()
{
    return enemy_count;
}

int ScoreManager::GetScore() {
    return score;
}

void ScoreManager::DrawCount()
{
    char buf[16];

    sprintf_s(buf, "客:%d人", enemy_count);
    DrawString(350, 10, buf, GetColor(255, 255, 255));

    sprintf_s(buf, "SCORE:%d", score);
    DrawString(50, 10, buf, GetColor(255, 255, 255));
    
}

void ScoreManager::UpdateButtonCount(int val) {
    
        score += val;  // スコアを100追加
    
}

void ScoreManager::ResetScore()
{
    score = 0;
    button_count = 0;
    enemy_count = 0;
}