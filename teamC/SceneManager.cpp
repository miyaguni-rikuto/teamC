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

		// エラーログファイルを開く
		fopen_s(&fp, "ErrLog.txt", "a");
		// エラーデータの書き込み
		fprintf_s(fp, "%02d年 %02d月 %02d日 %02d時 %02d分 %02d秒 : %sが発生しました。\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return nullptr;
	}

	// シーンが変更された場合、古いシーンを削除
	if (NextScene != mScene)
	{
		delete mScene;
		mScene = NextScene;
	}

	return mScene;
}

void SceneManager::Draw() const {
	// 現在のシーンを描画
	mScene->Draw();
}