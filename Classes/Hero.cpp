#include"Hero.h"
//初始化
bool Hero::init() {
	if (!Sprite::initWithSpriteFrameName("hero1.png"))
	{
		return false;
	}
	return true;
}
//创建
Hero* Hero::create() {
	//创建飞机
	auto hero = new Hero();
	if (hero&&hero->init())
	{
		hero->setPositionX(VISIBLE_ORIGIN.x + VISIBLE_SIZE.width / 2);
		hero->setPositionY(VISIBLE_ORIGIN.y + hero->getContentSize().height);
		hero->getTexture()->setAliasTexParameters();
		//给飞机添加飞行动画
		//1.从缓存中取出动画
		auto heroAni = CCAnimationCache::getInstance()->getAnimation(KET_ANI_HERO_FLY);

		//2.将动画封装为动作（精灵只能执行动作）
		auto heroAnimate = Animate::create(heroAni);

		//3.精灵运行动作
		hero->runAction(heroAnimate);
		return hero;
	}
	delete hero;
	hero = nullptr;
	return nullptr;
}
//飞机坠毁
void Hero::blowup() {
	auto animHeroBlowup = CCAnimationCache::getInstance()->getAnimation(KEY_ANI_HERO_BLOWUP);
	auto animateHeroBlowup = Animate::create(animHeroBlowup);
	runAction(animateHeroBlowup);
}
