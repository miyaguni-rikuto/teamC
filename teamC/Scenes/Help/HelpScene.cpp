#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Vector2D.h"

void HelpScene::Initialize()
{
	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	help_back_image = rm->GetImageResource("Resource/Images/Help.png")[0];
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
	//タイトル背景画像の描画;
	DrawGraph(0, 0, help_back_image, TRUE);

	SetFontSize(20);

	DrawFormatString(150, 50, GetColor(255, 255, 255), "ゲームの概要");
	DrawFormatString(50, 100, GetColor(255, 255, 255), "・上から素材を持ってくる商人が");
	DrawFormatString(50, 150, GetColor(255, 255, 255), "同じレーンに5人並ぶ前に剣を作ってあげよう");
	DrawFormatString(150, 200, GetColor(255, 255, 255), "操作方法");
	DrawFormatString(50, 250, GetColor(255, 255, 255), "・十字ボタンでプレイヤーの左右移動");
	DrawFormatString(75, 280, GetColor(255, 255, 255), "Aボタンでハンマーを振り下ろす");
	DrawFormatString(100, 450, GetColor(255, 255, 255), "スペースキーを押してタイトル画面に戻る");
}

void HelpScene::Finalize()
{

}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
