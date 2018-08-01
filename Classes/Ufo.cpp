#include"Ufo.h"
bool Ufo::initWithUfoType(const UfoType& ufoType) {
	std::string frameName = "ufo1.png";
	m_speed = SPEED_UFO;
	if (ufoType == UfoType::UFO_2)
	{
		frameName = "ufo2.png";
	}
	if (ufoType == UfoType::UFO_3)
	{
		frameName = "game_resume_nor.png";
	}
	if (!Sprite::initWithSpriteFrameName(frameName))
	{
		return false;
	}
	return true;
}

	int randomhelper = RandomHelper::random_int(0, 1) + 1;



void Ufo::move()
{
	//道具执行一个动作序列：1.进入屏幕一段距离2.回到屏幕上边3.掉出屏幕下边界4.销毁道具
	//setPositionY(getPositionY() + SPEED_UFO);
	auto move1 = MoveBy::create(0.5f, Vec2(0, -5));//第一次进入屏幕
	auto move2 = MoveTo::create(10, Vec2(getPositionX(), -getContentSize().height / 2));
	auto sequence = Sequence::create(move1, move1->reverse(), move2,/*RemoveSelf::create(),*/ nullptr);
	runAction(sequence);
}
Ufo* Ufo::create(const UfoType& ufoType) {
	auto ufo = new Ufo();
	if (ufo&&ufo->initWithUfoType(ufoType))
	{
		ufo->autorelease();//放入自动计数池，当调用此方法时计数+1，结束后-1；
		switch (ufoType)
		{
		case UfoType::UFO_1:
			ufo->m_type = UfoType::UFO_1;
			break;
		case UfoType::UFO_2:
			ufo->m_type = UfoType::UFO_2;
			break;
		case UfoType::UFO_3:
			ufo->m_type = UfoType::UFO_3;
		default:
			break;
		}
		
		float minX = ufo->getContentSize().width / 2;
		float maxX = VISIBLE_SIZE.width - minX;
		//取余只能对整数，取min到max的随机数需要对(min-max+1)取余
		ufo->setPositionX(rand() % (int)(maxX - minX + 1) + minX);
		ufo->setPositionY(VISIBLE_SIZE.height + ufo->getContentSize().height / 2);
		return ufo;
	}
	delete ufo;
	ufo = nullptr;
	return nullptr;
}