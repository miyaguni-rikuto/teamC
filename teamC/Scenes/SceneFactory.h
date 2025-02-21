#pragma once
#include "SceneBase.h"
#include "Title/TitleScene.h"
#include "InGame/InGameScene.h"
#include "ResultScene.h"

class SceneFactory
{
public:
	static SceneBase* CreateScene(eSceneType type)
	{
		switch (type)
		{
		case eSceneType::eTitle:
			return dynamic_cast<SceneBase*>(new TitleScene());

		case eSceneType::eInGame:
			return dynamic_cast<SceneBase*>(new InGameScene());


		case eSceneType::eResult:
			return dynamic_cast<SceneBase*>(new ResultScene());

		default:
			return nullptr;

		}
	}
};
