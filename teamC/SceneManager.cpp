#include "DxLib.h"
#include "SceneManager.h"
#include "FPS.h"

AbstractScene* SceneManager::Update()
{
	AbstractScene* NextScene;
	try
	{
		NextScene = mScene->Update();
	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);

		// �G���[���O�t�@�C�����J��
		fopen_s(&fp, "ErrLog.txt", "a");
		// �G���[�f�[�^�̏�������
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s���������܂����B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return nullptr;
	}

	// �V�[�����ύX���ꂽ�ꍇ�A�Â��V�[�����폜
	if (NextScene != mScene)
	{
		delete mScene;
		mScene = NextScene;
	}

	return mScene;
}

void SceneManager::Draw() const {
	// ���݂̃V�[����`��
	mScene->Draw();
}