#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"



Title::Title()
{
	// 初期化

}

Title::~Title()
{
	
}

AbstractScene* Title::Update()
{

	// Aボタンが押されたらゲームメインへ遷移
	if (PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
	{
		
		return new GameMain();
		
	}
	return this;
}

void Title::Draw() const
{
	DrawFormatString(0, 120, (255, 255, 255), "title");
	
}