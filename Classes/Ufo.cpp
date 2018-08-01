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
	//����ִ��һ���������У�1.������Ļһ�ξ���2.�ص���Ļ�ϱ�3.������Ļ�±߽�4.���ٵ���
	//setPositionY(getPositionY() + SPEED_UFO);
	auto move1 = MoveBy::create(0.5f, Vec2(0, -5));//��һ�ν�����Ļ
	auto move2 = MoveTo::create(10, Vec2(getPositionX(), -getContentSize().height / 2));
	auto sequence = Sequence::create(move1, move1->reverse(), move2,/*RemoveSelf::create(),*/ nullptr);
	runAction(sequence);
}
Ufo* Ufo::create(const UfoType& ufoType) {
	auto ufo = new Ufo();
	if (ufo&&ufo->initWithUfoType(ufoType))
	{
		ufo->autorelease();//�����Զ������أ������ô˷���ʱ����+1��������-1��
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
		//ȡ��ֻ�ܶ�������ȡmin��max���������Ҫ��(min-max+1)ȡ��
		ufo->setPositionX(rand() % (int)(maxX - minX + 1) + minX);
		ufo->setPositionY(VISIBLE_SIZE.height + ufo->getContentSize().height / 2);
		return ufo;
	}
	delete ufo;
	ufo = nullptr;
	return nullptr;
}