#include "ResultScene.h"
#include "../Ranking/RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/ScoreManager.h"
#include "DxLib.h"

void ResultScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	//result_image = rm->GetImageResource("Resource/Images/Resulet_image.png")[0];
	result_field = rm->GetImageResource("Resource/Images/Result_Field.png")[0];
	replay_image = rm->GetImageResource("Resource/Images/Restart.png")[0];
	title_image = rm->GetImageResource("Resource/Images/Titleexit.png")[0];

	select = false;

	// スコアとボタン回数を取得
	ScoreManager& sm = ScoreManager::GetInstance();
	score = sm.GetScore(); // スコア取得
	enemy_count = sm.GetCount(); //客を帰した数の取得
}

eSceneType ResultScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyState(KEY_INPUT_LEFT) == eInputState::Pressed ||
		input->GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Pressed)
	{
		select = false;
	}

	if (input->GetKeyState(KEY_INPUT_RIGHT) == eInputState::Pressed ||
		input->GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Pressed)
	{
		select = true;
	}

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed ||
		input->GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
	{
		return eSceneType::eTitle;
	}

	Draw();

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
	__super::Draw();

	DrawRotaGraph(320, 220, 1.5, 0.0, result_field, TRUE, FALSE);

	DrawFormatString(190, 80, GetColor(255,255,255), "今回のスコア");
	DrawFormatString(230, 150, GetColor(255,255,255), "SCORE:%d", score);

	DrawFormatString(190, 250, GetColor(255, 255, 255), "帰した客の数");
	DrawFormatString(280, 320, GetColor(255, 255, 255), "%d人", enemy_count);

	//リスタート画像
	DrawRotaGraph(240, 440, 1.0, 0.0, replay_image, TRUE, FALSE);

	//タイトルに戻る画像
	DrawRotaGraph(410, 440, 1.0, 0.0, title_image, TRUE, FALSE);

	if (select)
	{
		DrawBoxAA(346, 408, 474, 472, GetColor(255, 0, 0), FALSE, 1.5f);
	}
	else
	{
		DrawBoxAA(176, 408, 304, 472, GetColor(255, 0, 0), FALSE, 1.5f);
	}

	//DrawRotaGraphF(320,220,1.0,0.0,result_image,TRUE,FALSE);

	/*SetFontSize(60);

	DrawFormatString(180, 210, GetColor(255, 255, 255), "GAME OVER");*/

}

void ResultScene::Finalize()
{
	GameObjectManager *objm = GameObjectManager::GetInstance();
	objm->Finalize();

	result_image = NULL;
	result_field = NULL;

	RankingScene::GetInstance().AddScore(score);

	//GameObjectManager *obm = GameObjectManager::GetInstance();

	//obm->DestroyGameObject();
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}