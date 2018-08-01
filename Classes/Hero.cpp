#include"Hero.h"
//��ʼ��
bool Hero::init() {
	if (!Sprite::initWithSpriteFrameName("hero1.png"))
	{
		return false;
	}
	return true;
}
//����
Hero* Hero::create() {
	//�����ɻ�
	auto hero = new Hero();
	if (hero&&hero->init())
	{
		hero->setPositionX(VISIBLE_ORIGIN.x + VISIBLE_SIZE.width / 2);
		hero->setPositionY(VISIBLE_ORIGIN.y + hero->getContentSize().height);
		hero->getTexture()->setAliasTexParameters();
		//���ɻ���ӷ��ж���
		//1.�ӻ�����ȡ������
		auto heroAni = CCAnimationCache::getInstance()->getAnimation(KET_ANI_HERO_FLY);

		//2.��������װΪ����������ֻ��ִ�ж�����
		auto heroAnimate = Animate::create(heroAni);

		//3.�������ж���
		hero->runAction(heroAnimate);
		return hero;
	}
	delete hero;
	hero = nullptr;
	return nullptr;
}
//�ɻ�׹��
void Hero::blowup() {
	auto animHeroBlowup = CCAnimationCache::getInstance()->getAnimation(KEY_ANI_HERO_BLOWUP);
	auto animateHeroBlowup = Animate::create(animHeroBlowup);
	runAction(animateHeroBlowup);
}
