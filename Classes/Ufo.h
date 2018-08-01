#pragma once
#include"cocos2d.h"
#include"Constants.h"
USING_NS_CC;
enum class UfoType {
	UFO_1,
	UFO_2,
	UFO_3
};
class Ufo :public Sprite {
public:
	Ufo() : m_type(UfoType::UFO_1), m_speed(0) , visited(false){}
	bool initWithUfoType(const UfoType&);
	static Ufo* create(const UfoType&);
	void move();
	//void isGotten();
	CC_SYNTHESIZE(float, m_speed, Speed);
	CC_SYNTHESIZE(UfoType, m_type, Type);
	CC_SYNTHESIZE(int, m_ufo2_count, Ufo2Count);
private:
	bool visited;//下落过一次，见到过
};