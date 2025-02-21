#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

TitleScene::TitleScene() :
	title_image(NULL)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	// �w�i�摜�̓ǂݍ���
	/*ResourceManager* rm = ResourceManager::CreateInstance();
	title_image = rm->GetImages("Resource/Images/title.png")[0];*/

	//// BGM�̓ǂݍ���
	//title_image = rm->GetSounds("Resource/Sounds/start-music.mp3");
}

eSceneType TitleScene::Update(const float& delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::CreateInstance();

	// �C���Q�[���V�[���ɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	// �e�N���X�̕`�揈�����Ăяo��
	//__super::Draw();

	DrawFormatString(50, 50, GetColor(255, 255, 255), "�^�C�g�����");

	// UI�̕`��
	//DrawRotaGraph(320, 240, 1.0, 0.0, title_image, TRUE);
	DrawFormatString(10, 640, GetColor(255, 0, 0), "Space key pressed game start");
	SetFontSize(16);
}

void TitleScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}