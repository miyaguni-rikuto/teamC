#include "ScoreManager.h"
#include "InputManager.h"
#include <cstdio>
#include <fstream>

#define SCORE_X 390

ScoreManager::ScoreManager() : button_count(0), enemy_count(0), score(0)
{
}

ScoreManager& ScoreManager::GetInstance() {
    static ScoreManager instance;
    return instance;
}

//void ScoreManager::SetCount(COUNTDATA data, int val)
//{
//    switch (data) {
//    case BUTTON_COUNT:
//        button_count = val;
//        break;
//    case ENEMY_COUNT:
//        enemy_count = val;
//        break;
//    }
//}
//
void ScoreManager::AddCount(int val)
{
    enemy_count++;
    score += val;
   /* switch (data) {
    case BUTTON_COUNT:
        button_count += val;
        break;
    case ENEMY_COUNT:
        enemy_count += val;
        break;
    }*/
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
    
    InputManager* input = InputManager::GetInstance();

        //button_count++;
        score += val;  // スコアを100追加
    
}

void ScoreManager::ResetScore()
{
    score = 0;
    button_count = 0;
    enemy_count = 0;
}

void ScoreManager::SaveScore() {
    std::ofstream file("score.dat", std::ios::out);
    if (file.is_open()) {
        file << score << " " << button_count << " " << enemy_count;
        file.close();
    }
}

void ScoreManager::LoadScore() {
    std::ifstream file("score.dat", std::ios::in);
    if (file.is_open()) {
        file >> score >> button_count >> enemy_count;
        file.close();
    }
}