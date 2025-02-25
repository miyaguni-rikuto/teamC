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
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �^�C�g���V�[���ɑJ�ڂ���
	if (input->GetKeyState(KEY_INPUT_SPACE) == Pressed)
	{
		return eSceneType::eTitle;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START) == Pressed)
	{
		return eSceneType::eTitle;
	}

	// �e�N���X�̍X�V�������Ăяo��
	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	// �e�N���X�̕`�揈�����Ăяo��
	//__super::Draw();

	DrawFormatString(50, 50, GetColor(255, 255, 255), "�����L���O�ł�");

	// UI�̕`��
	//DrawRotaGraph(320, 240, 1.0, 0.0, title_image, TRUE);
	DrawFormatString(10, 640, GetColor(255, 0, 0), "Space key pressed back title");
	SetFontSize(16);
}

void RankingScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}