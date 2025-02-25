#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

void ResultScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	//result_image = rm->GetImageResource("Resource/Images/Resulet_image.png")[0];
	result_field = rm->GetImageResource("Resource/Images/Result_display.png")[0];
	replay_image = rm->GetImageResource("Resource/Images/Restart.png")[0];
	title_image = rm->GetImageResource("Resource/Images/Titleexit.png")[0];
}

eSceneType ResultScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();



	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
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

	//DrawFormatString(320, 220, GetColor(255,255,255), "ボタンを押した回数");
	DrawFormatString(280, 150, GetColor(255,255,255), "%d回", 1000);

	//DrawFormatString(320, 300, GetColor(255, 255, 255), "敵を帰した数");
	DrawFormatString(280, 320, GetColor(255, 255, 255), "%d人", 100);

	//リスタート画像
	DrawRotaGraph(320, 220, 1.5, 0.0, replay_image, TRUE, FALSE);

	//タイトルに戻る画像
	DrawRotaGraph(320, 220, 1.5, 0.0, title_image, TRUE, FALSE);

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

	//GameObjectManager *obm = GameObjectManager::GetInstance();

	//obm->DestroyGameObject();
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}