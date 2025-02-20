#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "Title.h"

GameMain::GameMain() {}

GameMain::~GameMain() {}

AbstractScene* GameMain::Update()
{
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_X))
    {
        return new Title();
    }
    return this;
}

void GameMain::Draw() const 
{
    DrawFormatString(0, 120, (255, 255, 255), "main87654");
}