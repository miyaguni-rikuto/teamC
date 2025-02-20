#pragma once
#include <math.h>
#include <chrono>
#include <thread>
#include "DxLib.h"

class Fps {
	int mStartTime;         // �v���J�n����
	int mCount;             // �J�E���^�[

	static const int N = 60; // �v������T���v����
	static const int FPS = 60; // �ݒ肳�ꂽFPS

public:
	float mFps;             // FPS�l
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { // 1�t���[���ڂ̊J�n���Ԃ��L�^
			mStartTime = GetNowCount();
		}
		if (mCount == N) { // 60�t���[���o�ߌ��FPS���v�Z
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw() {
		// FPS����ʂɕ\���i���݃R�����g�A�E�g�j
		// DrawFormatString(0, 0, GetColor(255, 255, 255), "fps : %.1f", mFps);
	}

	void Wait() {
		int tookTime = GetNowCount() - mStartTime; // �o�ߎ��Ԃ��擾
		int waitTime = mCount * 1000 / FPS - tookTime; // �K�v�ȑҋ@���Ԃ��v�Z

		if (waitTime > 0) {
			std::chrono::milliseconds dura(waitTime);
			std::this_thread::sleep_for(dura);
			// Sleep(waitTime); // �ҋ@�����i��ցj
		}
	}
};
