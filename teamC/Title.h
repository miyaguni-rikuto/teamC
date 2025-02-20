#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene
{
private:
    int Select;     // 選択中のメニュー
    int OldKey;     // 前回のキー入力状態
    int NowKey;     // 現在のキー入力状態
    int KeyFlg;     // キー入力フラグ

    bool Once;      // Lスティックでカーソルを連続移動しないためのフラグ

public:
    // コンストラクタ
    Title();

    // デストラクタ
    ~Title();

    // 描画以外の更新処理
    AbstractScene* Update() override;

    // 描画処理
    void Draw() const override;
};