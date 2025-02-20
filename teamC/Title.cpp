#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"



Title::Title()
{
	// ������

}

Title::~Title()
{
	
}

AbstractScene* Title::Update()
{

	// A�{�^���������ꂽ��Q�[�����C���֑J��
	if (PAD_INPUT::OnRelease(XINPUT_BUTTON_A))
	{
		
		return new GameMain();
		
	}
	return this;
}

void Title::Draw() const
{
	DrawFormatString(0, 120, (255, 255, 255), "title");
	
}