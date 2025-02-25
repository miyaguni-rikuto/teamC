#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

RankingScene::RankingScene()
{

}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{
	
}

eSceneType RankingScene::Update(float delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// タイトルシーンに遷移する
	if (input->GetKeyState(KEY_INPUT_SPACE) == Pressed)
	{
		return eSceneType::eTitle;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START) == Pressed)
	{
		return eSceneType::eTitle;
	}

	// 親クラスの更新処理を呼び出す
	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	// 親クラスの描画処理を呼び出す
	//__super::Draw();

	DrawFormatString(50, 50, GetColor(255, 255, 255), "ランキングです");

	// UIの描画
	//DrawRotaGraph(320, 240, 1.0, 0.0, title_image, TRUE);
	DrawFormatString(10, 640, GetColor(255, 0, 0), "Space key pressed back title");
	SetFontSize(16);
}

void RankingScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}