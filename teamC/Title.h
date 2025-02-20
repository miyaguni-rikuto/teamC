#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene
{
private:
    int Select;     // �I�𒆂̃��j���[
    int OldKey;     // �O��̃L�[���͏��
    int NowKey;     // ���݂̃L�[���͏��
    int KeyFlg;     // �L�[���̓t���O

    bool Once;      // L�X�e�B�b�N�ŃJ�[�\����A���ړ����Ȃ����߂̃t���O

public:
    // �R���X�g���N�^
    Title();

    // �f�X�g���N�^
    ~Title();

    // �`��ȊO�̍X�V����
    AbstractScene* Update() override;

    // �`�揈��
    void Draw() const override;
};