#include"cocos2d.h"
#include"Constants.h"
USING_NS_CC;

class Hero :public Sprite {
public:
	bool init();
	static Hero* create();
	void blowup();

};