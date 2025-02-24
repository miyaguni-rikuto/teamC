#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

void ResultScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	//result_image = rm->GetImageResource("Resource/Images/Resulet_image.png")[0];
	result_field = rm->GetImageResource("Resource/Images/Result_Field.png")[0];
}

eSceneType ResultScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return eSceneType::eTitle;
	}

	Draw();

	return __super::Update(delta_second);

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
	DrawRotaGraphF(320, 220, 1.5, 0.0, result_field, TRUE, FALSE);

	__super::Draw();

	//DrawRotaGraphF(320,220,1.0,0.0,result_image,TRUE,FALSE);

	/*SetFontSize(60);

	DrawFormatString(180, 210, GetColor(255, 255, 255), "GAME OVER");*/

}

void ResultScene::Finalize()
{
	result_image = NULL;
	result_field = NULL;
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}