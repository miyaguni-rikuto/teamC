#pragma once
#include <math.h>
#include <chrono>
#include <thread>
#include "DxLib.h"

class Fps {
	int mStartTime;         // 計測開始時間
	int mCount;             // カウンター

	static const int N = 60; // 計測するサンプル数
	static const int FPS = 60; // 設定されたFPS

public:
	float mFps;             // FPS値
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { // 1フレーム目の開始時間を記録
			mStartTime = GetNowCount();
		}
		if (mCount == N) { // 60フレーム経過後にFPSを計算
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw() {
		// FPSを画面に表示（現在コメントアウト）
		// DrawFormatString(0, 0, GetColor(255, 255, 255), "fps : %.1f", mFps);
	}

	void Wait() {
		int tookTime = GetNowCount() - mStartTime; // 経過時間を取得
		int waitTime = mCount * 1000 / FPS - tookTime; // 必要な待機時間を計算

		if (waitTime > 0) {
			std::chrono::milliseconds dura(waitTime);
			std::this_thread::sleep_for(dura);
			// Sleep(waitTime); // 待機処理（代替）
		}
	}
};
