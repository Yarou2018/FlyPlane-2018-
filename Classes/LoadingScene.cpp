#include "LoadingScene.h"
#include"GameScene.h"
#include"AudioEngine.h"

using namespace experimental;

LoadingScene* LoadingScene::createScene() {
	return LoadingScene::create();
}
bool LoadingScene::init() {
	do
	{
		CC_BREAK_IF(!Scene::init());

		
		//��ͨ�����ؾ��鼯�ļ��������鶼���浽���鼯������
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
		
		//ҳ������
		auto bg = Sprite::createWithSpriteFrameName("background.png");
		bg->setPosition(VISIBLE_ORIGIN+VISIBLE_SIZE / 2);
		this->addChild(bg,BACKGROUND_ZORDER);
		//����
		auto title = Sprite::createWithSpriteFrameName("shoot_copyright.png");
		title->setPosition(VISIBLE_ORIGIN + VISIBLE_SIZE / 2 + Vec2(0, 100));
		this->addChild(title);
		//���ض���
		auto  loading = Sprite::create();
		loading->setPosition(VISIBLE_ORIGIN + VISIBLE_SIZE / 2+Vec2(0, -100));
		this->addChild(loading);

		auto ani = Animation::create();
		for (auto i = 0; i < 4; i++)
		{
			auto png = StringUtils::format("game_loading%d.png", i + 1);
			ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
		ani->setDelayPerUnit(0.2f);
		ani->setLoops(2);
		auto seq = Sequence::create(Animate::create(ani), CallFunc::create([]() {
			//������ת(���س�������Ϸ����)
			auto gameScene = GameScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1,gameScene));
		}), nullptr );
		loading->runAction(seq);

		//�������������뻺��
		//���ɻ���Ӷ���
		//1.��������
		//a.������������
		Animation* aniHeroFly = Animation::create();
		//b.��Ӷ���֡	���Ӿ���֡�����и������ֲ��ҳ����ģ�
		aniHeroFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
		aniHeroFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
		//c.���ö����л�ʱ��	
		aniHeroFly->setDelayPerUnit(DELAY_PRE_HERO_FLY);
		//d.����ѭ������
		aniHeroFly->setLoops(CC_REPEAT_FOREVER);
		//e.���붯������
		AnimationCache::getInstance()->addAnimation(aniHeroFly, KET_ANI_HERO_FLY);

		//����˷���
		auto aniBigEnemy = Animation::create();
		aniBigEnemy->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		aniBigEnemy->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		aniBigEnemy->setDelayPerUnit(DELAY_PRE_BIGENEMY_FLY);
		aniBigEnemy->setLoops(CC_REPEAT_FOREVER);
		AnimationCache::getInstance()->addAnimation(aniBigEnemy, KET_ANI_BIGENEMY_FLY);

		//С���˱�ը����
		auto aniSmallEnemyDown = Animation::create();
		for (auto i = 0; i < 4; i++)
		{
			//�ַ����������format�ṩ�˱������ַ�����ƴ��
			auto frameNumOfName = StringUtils::format("enemy1_down%d.png", i + 1);
			aniSmallEnemyDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameNumOfName));
		}
		aniSmallEnemyDown->setDelayPerUnit(DELAY_PRE_ENEMY_DOWN);
		AnimationCache::getInstance()->addAnimation(aniSmallEnemyDown, KEY_ANI_SMALL_ENEMY_DOWN);

		//�е��˱�ը����
		auto aniMiddleEnemyDown = Animation::create();
		for (auto i = 0; i < 4; i++)
		{
			auto frameNumOfName = StringUtils::format("enemy2_down%d.png", i + 1);
			aniMiddleEnemyDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameNumOfName));
		}
		aniMiddleEnemyDown->setDelayPerUnit(DELAY_PRE_ENEMY_DOWN);
		AnimationCache::getInstance()->addAnimation(aniMiddleEnemyDown, KEY_ANI_MIDDLE_ENEMY_DOWN);

		//����˱�ը����
		auto aniBigEnemyDown = Animation::create();
		for (auto i = 0; i < 6; i++)
		{
			auto frameName = StringUtils::format("enemy3_down%d.png", i + 1);
			aniBigEnemyDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		aniBigEnemyDown->setDelayPerUnit(DELAY_PRE_ENEMY_DOWN);
		AnimationCache::getInstance()->addAnimation(aniBigEnemyDown, KEY_ANI_BIG_ENEMY_DOWN);

		//�е��˱�������
		auto aniMiddlenEmyHit = Animation::create();
		aniMiddlenEmyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
		aniMiddlenEmyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));
		aniMiddlenEmyHit->setDelayPerUnit(DELAY_PRE_ENEMY_HIT);
		AnimationCache::getInstance()->addAnimation(aniMiddlenEmyHit, KEY_ANI_MIDDLE_ENEMY_HIT);

		//����˱�������
		auto aniBigeEnemyHit = Animation::create();
		aniBigeEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png"));
		aniBigeEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		aniBigeEnemyHit->setDelayPerUnit(DELAY_PRE_ENEMY_HIT);
		AnimationCache::getInstance()->addAnimation(aniBigeEnemyHit, KEY_ANI_BIG_ENEMY_IHT);

		auto aniHeroBlowup = Animation::create();
		for (auto i = 0; i < 4; i++)
		{
			auto frameNumOfName = StringUtils::format("hero_blowup_n%d.png", i + 1);
			aniHeroBlowup->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameNumOfName));
		}
		aniHeroBlowup->setDelayPerUnit(DELAY_PRE_HERO_BLOWUP);
		AnimationCache::getInstance()->addAnimation(aniHeroBlowup, KEY_ANI_HERO_BLOWUP);

		//Ԥ���������ļ�
		AudioEngine::preload("achievement.mp3");
		AudioEngine::preload("big_spaceship_flying.mp3");
		AudioEngine::preload("bullet.mp3");
		AudioEngine::preload("button.mp3");
		AudioEngine::preload("enemy1_down.mp3");
		AudioEngine::preload("enemy2_down.mp3");
		AudioEngine::preload("enemy3_down.mp3");
		AudioEngine::preload("game_music.mp3");
		AudioEngine::preload("game_over.mp3");
		AudioEngine::preload("get_bomb.mp3");
		AudioEngine::preload("get_double_laser.mp3");
		AudioEngine::preload("out_porp.mp3");
		AudioEngine::preload("use_bomb.mp3");

		return true;
	} while (0);

	return false;
}