#pragma once
#include"cocos2d.h"
#include"Constants.h"
#include"AudioEngine.h"
USING_NS_CC;

class LoadingScene :public Scene {
public:
	static LoadingScene* createScene();
	bool init() override;
	CREATE_FUNC(LoadingScene);
};