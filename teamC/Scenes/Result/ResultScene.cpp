#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

void ResultScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	//result_image = rm->GetImageResource("Resource/Images/Resulet_image.png")[0];
	result_field = rm->GetImageResource("Resource/Images/Result_display.png")[0];
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

	//DrawFormatString(320, 220, GetColor(255,255,255), "�{�^������������");
	DrawFormatString(280, 150, GetColor(255,255,255), "%d��", 1000);

	//DrawFormatString(320, 300, GetColor(255, 255, 255), "�G���A������");
	DrawFormatString(280, 320, GetColor(255, 255, 255), "%d�l", 100);

	//DrawRotaGraphF(320,220,1.0,0.0,result_image,TRUE,FALSE);

	/*SetFontSize(60);

	DrawFormatString(180, 210, GetColor(255, 255, 255), "GAME OVER");*/

}

void ResultScene::Finalize()
{
	result_image = NULL;
	result_field = NULL;

	GameObjectManager *obm = GameObjectManager::GetInstance();

	obm->DestroyGameObject();
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}