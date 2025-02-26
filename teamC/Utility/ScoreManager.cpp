#include "ScoreManager.h"
#include "InputManager.h"
#include <cstdio>

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
//
//int ScoreManager::GetCount(COUNTDATA data)
//{
//    switch (data) {
//    case BUTTON_COUNT:
//        return button_count;
//    case ENEMY_COUNT:
//        return enemy_count;
//    }
//    return -1;
//}

void ScoreManager::DrawCount()
{
    char buf[16];

    sprintf_s(buf, "BUTTON:%d", button_count);
    DrawString(350, 10, buf, GetColor(255, 255, 255));

    sprintf_s(buf, "SCORE:%d", score);
    DrawString(50, 10, buf, GetColor(255, 255, 255));
    
}

void ScoreManager::UpdateButtonCount(int val) {
    
    InputManager* input = InputManager::GetInstance();

        button_count++;
        score += val;  // ÉXÉRÉAÇ100í«â¡
    
}

void ScoreManager::ResetScore()
{
    score = 0;
    button_count = 0;
    enemy_count = 0;
}