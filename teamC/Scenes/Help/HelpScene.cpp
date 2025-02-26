#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Vector2D.h"

void HelpScene::Initialize()
{
	// �w�i�摜�̓ǂݍ���
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
	//�^�C�g���w�i�摜�̕`��;
	DrawGraph(0, 0, help_back_image, TRUE);

	SetFontSize(20);

	DrawFormatString(150, 50, GetColor(255, 255, 255), "�Q�[���̊T�v");
	DrawFormatString(50, 100, GetColor(255, 255, 255), "�E�ォ��f�ނ������Ă��鏤�l��");
	DrawFormatString(50, 150, GetColor(255, 255, 255), "�������[����5�l���ԑO�Ɍ�������Ă����悤");
	DrawFormatString(150, 200, GetColor(255, 255, 255), "������@");
	DrawFormatString(50, 250, GetColor(255, 255, 255), "�E�\���{�^���Ńv���C���[�̍��E�ړ�");
	DrawFormatString(75, 280, GetColor(255, 255, 255), "A�{�^���Ńn���}�[��U�艺�낷");
	DrawFormatString(100, 450, GetColor(255, 255, 255), "�X�y�[�X�L�[�������ă^�C�g����ʂɖ߂�");
}

void HelpScene::Finalize()
{

}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
