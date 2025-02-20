#pragma once
#include "DxLib.h"

#define BUTTONS 16

// スティックの構造体
struct Stick
{
	short ThumbX; // 横方向の値
	short ThumbY; // 縦方向の値
};

class PAD_INPUT
{
private:
	static char NowKey[BUTTONS]; // 現在の入力キー状態
	static char OldKey[BUTTONS]; // 前回の入力キー状態
	static XINPUT_STATE Input; // パッドの入力情報
	static Stick Rstick; // 右スティックの状態
	static Stick Lstick; // 左スティックの状態
private:
	// コンストラクタ (インスタンス化を禁止)
	PAD_INPUT() = default;
public:
	// パッドの入力状態を更新
	static void UpdateKey()
	{
		// キー入力の取得
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input);
		for (int i = 0; i < BUTTONS; i++)
		{
			OldKey[i] = NowKey[i];
			NowKey[i] = Input.Buttons[i];
		}

		// 右スティックの状態を更新
		Rstick.ThumbX = Input.ThumbRX;
		Rstick.ThumbY = Input.ThumbRY;

		// 左スティックの状態を更新
		Lstick.ThumbX = Input.ThumbLX;
		Lstick.ThumbY = Input.ThumbLY;
	}

	// ボタンが押された瞬間の判定
	static bool OnButton(int button)
	{
		bool ret = (NowKey[button] == 1 && OldKey[button] == 0);
		return ret;
	}

	// ボタンが離された瞬間の判定
	static bool OnRelease(int button)
	{
		bool ret = (NowKey[button] == 0 && OldKey[button] == 1);
		return ret;
	}

	// 右スティックの状態を取得
	static Stick GetRStick()
	{
		return Rstick;
	}

	// 左スティックの状態を取得
	static Stick GetLStick()
	{
		return Lstick;
	}
};