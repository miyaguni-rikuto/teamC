#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

void TitleScene::Initialize()
{
	__super::Initialize();
}

eSceneType TitleScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return eSceneType::eInGame;
	}

	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	//ƒ^ƒCƒgƒ‹”wŒi‰æ‘œ‚Ì•`‰æ

	SetFontSize(60);

	DrawFormatString(155, 130, GetColor(255, 255, 255), "TITLE NAME");

	SetFontSize(40);
	DrawFormatString(210, 300, GetColor(255, 255, 255), "PUSH SPASE");


	__super::Draw();
}

void TitleScene::Finalize()
{
	__super::Finalize();
}
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}