#pragma once
#include"cocos2d.h"

USING_NS_CC;

#include"Constants.h"

class Enemy :public Sprite {
public:
	static Enemy* createEnergy();
	bool init();

};