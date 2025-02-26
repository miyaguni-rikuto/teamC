#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"

void HelpScene::Initialize()
{

}

eSceneType HelpScene::Update(float delta_second)
{

	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed ||
		input->GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
	{
		return eSceneType::eTitle;
	}

	Draw();

	return GetNowSceneType();
}

void HelpScene::Draw() const
{
	DrawFormatString(50, 50, GetColor(255, 255, 255), "ヘルプ画面です。");
	DrawFormatString(50, 150, GetColor(255, 255, 255), "スペースキーを押してタイトル画面に戻る");
}

void HelpScene::Finalize()
{

}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
