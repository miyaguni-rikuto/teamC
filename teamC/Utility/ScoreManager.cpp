#include "ScoreManager.h"
#include <cstdio>

#define SCORE_X 390

ScoreManager::ScoreManager() : high_score(0), score(0)
{
    // �摜�̓ǂݍ���
    for (int i = 0; i < 10; i++) {
        char filename[256];
        sprintf_s(filename, "number.png", i);
        g_number[i] = LoadGraph(filename);
    }
}

void ScoreManager::SetScore(SCOREDATA data, int val)
{
    switch (data) {
    case HIGH_SCORE:
        high_score = val;
        break;
    case CURRENT_SCORE:
        score = val;
        break;
    }
}

void ScoreManager::AddScore(int val)
{
    score += val;
    if (score > high_score) {
        high_score = score;  // �n�C�X�R�A�X�V
    }
}

int ScoreManager::GetScore(SCOREDATA data)
{
    switch (data) {
    case HIGH_SCORE:
        return high_score;
    case CURRENT_SCORE:
        return score;
    }
    return -1;
}

void ScoreManager::DrawScore()
{
    char buf[16];

    // �n�C�X�R�A�`��
    sprintf_s(buf, "%d", high_score);
    DrawString(50, 50, "HIGHSCORE", GetColor(255, 255, 255));
    for (int i = 0; buf[i] != '\0'; ++i) {
        DrawGraph(SCORE_X + i * 20, 50, g_number[buf[i] - '0'], TRUE);
    }

    // ���݂̃X�R�A�`��
    sprintf_s(buf, "%d", score);
    DrawString(50, 50, "SCORE", GetColor(255, 255, 255));
    for (int i = 0; buf[i] != '\0'; ++i) {
        DrawGraph(SCORE_X + i * 20, 80, g_number[buf[i] - '0'], TRUE);
    }
}