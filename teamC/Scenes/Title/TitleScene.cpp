#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

void TitleScene::Initialize()
{
	__super::Initialize();

	select_menu = eNONE;

	pickup_color = GetColor(255, 0, 0);
	dropoff_color = GetColor(255, 255, 255);
}

eSceneType TitleScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	//下キーが押された場合
	if (input->GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed)
	{
		SetDownSelectMenuType();
	}

	//上キーが押された場合
	if (input->GetKeyState(KEY_INPUT_UP) == eInputState::Pressed)
	{
		SetUpSelectMenuType();
	}

	//決定処理
	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		switch (select_menu)
		{
		case ePLAY:
			return eSceneType::eInGame;
			break;

		case eHELP:
			return eSceneType::eHelp;
			break;

		case eRank:
			return eSceneType::eRanking;
			break;

		case eEXIT:
			return eSceneType::eExit;
			break;

		default:
			return eSceneType::eTitle;
			break;
		}
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	//タイトル背景画像の描画;

	SetFontSize(60);

	DrawFormatString(155, 100, GetColor(255, 255, 255), "TITLE NAME");

	SetFontSize(40);
	
	//選択されているメニューによって色を変える
	switch (select_menu)
	{
	case eNONE:
		DrawFormatString(210, 200, dropoff_color, "PLAY STSRT");
		DrawFormatString(210, 250, dropoff_color, "HELP");
		DrawFormatString(210, 300, dropoff_color, "RANKING");
		DrawFormatString(210, 350, dropoff_color, "EXIT");
		break;

	case ePLAY:
		DrawFormatString(210, 200, pickup_color, "PLAY STSRT");
		DrawFormatString(210, 250, dropoff_color, "HELP");
		DrawFormatString(210, 300, dropoff_color, "RANKING");
		DrawFormatString(210, 350, dropoff_color, "EXIT");
		break;

	case eHELP:
		DrawFormatString(210, 200, dropoff_color, "PLAY STSRT");
		DrawFormatString(210, 250, pickup_color, "HELP");
		DrawFormatString(210, 300, dropoff_color, "RANKING");
		DrawFormatString(210, 350, dropoff_color, "EXIT");
		break;

	case eRanking:
		DrawFormatString(210, 200, dropoff_color, "PLAY STSRT");
		DrawFormatString(210, 250, dropoff_color, "HELP");
		DrawFormatString(210, 300, pickup_color, "RANKING");
		DrawFormatString(210, 350, dropoff_color, "EXIT");
		break;

	case eEXIT:
		DrawFormatString(210, 200, dropoff_color, "PLAY STSRT");
		DrawFormatString(210, 250, dropoff_color, "HELP");
		DrawFormatString(210, 300, dropoff_color, "RANKING");
		DrawFormatString(210, 350, pickup_color, "EXIT");
		break;
	default:
		break;
	}

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

//カーソル上昇処理
void TitleScene::SetDownSelectMenuType()
{
	switch (select_menu)
	{
	case eNONE:
		select_menu = ePLAY;
		break;

	case ePLAY:
		select_menu = eHELP;
		break;

	case eHELP:
		select_menu = eRank;
		break;

	case eRank:
		select_menu = eEXIT;
		break;

	case eEXIT:

		break;
	default:
		break;
	}
}

//カーソル下降処理
void TitleScene::SetUpSelectMenuType()
{
	switch (select_menu)
	{
	case eNONE:
		break;

	case ePLAY:
		break;

	case eHELP:
		select_menu = ePLAY;
		break;

	case eRank:
		select_menu = eHELP;
		break;

	case eEXIT:
		select_menu = eRank;
		break;

	default:
		break;
	}
}