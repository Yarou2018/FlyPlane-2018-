#pragma once

#include"cocos2d.h"
USING_NS_CC;

#include"Constants.h"

class OverScene :public Scene {
public:
	static Scene* creatScene(int score);
	bool init(int score) ;
	//CREATE_FUNC(OverScene);
};
