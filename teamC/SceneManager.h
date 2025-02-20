#pragma once
#include "AbstractScene.h"

class SceneManager :
    public AbstractScene
{
private:
    AbstractScene* mScene;
public:

    // �R���X�g���N�^
    SceneManager(AbstractScene* scene) : mScene(scene) {};

    // �f�X�g���N�^
    ~SceneManager()
    {
        delete mScene;
    }

    // �`��ȊO�̍X�V����
    AbstractScene* Update() override;

    // �`�揈��
    void Draw() const override;
};
