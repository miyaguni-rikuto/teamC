#include"DxLib.h"
#include"SceneManager.h"
#include"FPS.h"
#include"Title.h"
#include"PadInput.h"
#include"GameMain.h"
#include "FpsControl.h"

#define FRAMERATE 60.0 //�t���[�����[�g

#define HEIGHT 720
#define WIDTH 1280 
#define REFRESHRATE 32

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("Russian Rolette");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	SetGraphMode(WIDTH, HEIGHT, REFRESHRATE);	//��ʃT�C�Y�̐ݒ�

	// 垂直同期を切る
	SetWaitVSyncFlag(0);

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager* sceneMng;

	try
	{
		sceneMng = new SceneManager((AbstractScene*)new Title/*GameMain*/());

	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//�t�@�C���I�[�v��
		fopen_s(&fp, "ErrLog.txt", "a");
		//�G���[�f�[�^�̏�������
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s������܂���B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}
	//FpsController FPSC(FRAMERATE, 800);

	// �Q�[�����[�v
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {
		//フレームレート制御
		FpsControll_Update();


		ClearDrawScreen();		// ��ʂ̏�����
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();

		//フレームレート表示
		FpsControll_Draw();
		//待機
		FpsControll_Wait();
		//FPSC.All();
		//FPSC.Disp();

		//�����I��
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK))
		{
			break;
		}

		ScreenFlip();			// ����ʂ̓�e��\��ʂɔ��f
	}
	return 0;
}