#include"GameScene.h"
#include "OverScene.h"
#include "AudioEngine.h"
#include"time.h"

using namespace experimental;

Scene* GameScene::createScene() {
	return GameScene::create();
}
bool GameScene::init() {
	//1.�ȵ��ø����init
	if (!Scene::init())
	{
		return false;
	}
	//���������
	srand((unsigned int)time(NULL));

	//ע����̼���
	auto backKeyListener = EventListenerKeyboard::create();
	backKeyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backKeyListener, this);

	AudioEngine::play2d("game_music.mp3", true, VAL_MUSIC_BACKGROUND);//�ļ������Ƿ�ѭ��������

	////////////����
	//��������
	//auto bg = Sprite::create("shoot_background.png");

	auto bg1 = Sprite::createWithSpriteFrameName("background.png");
	//����ê��λ������������½�
	bg1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);//����Ҳ����(0,0)�������½�(1,1)�������Ͻ�
	//��λ
	//��������ͼ2������������
	auto bg2 = Sprite::createWithSpriteFrameName("background.png");
	bg2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bg2->setPositionY(bg1->getContentSize().height);

	//��Ӿ���
	this->addChild(bg1, BACKGROUND_ZORDER, BACKGROUND_TAG_1);
	this->addChild(bg2, BACKGROUND_ZORDER, BACKGROUND_TAG_2);

	//���������
	bg1->getTexture()->setAliasTexParameters();//���������ʾ�󣩲����������
	bg2->getTexture()->setAliasTexParameters();

	/////////////�ɻ�
	m_hero = Hero::create();
	this->addChild(m_hero, FOREGROUND_ZORDER, HERO_TAG);
	//��Ӵ���ʱ��Ĵ���
	//1.����һ��ʱ���������
	auto listener = EventListenerTouchOneByOne::create();

	//2.�ֽ�ʱ�䣬�����߼�
	//a������ʼʱ
	//lambda���ʽ��[]���ֱ�ʾ���ƶ��ⲿ�����ķ��ʣ�����һ��һ���Ĵ��ݣ�Ĭ����ֵ����
	//Ҳ������"="�Ⱥţ���ʾ�ⲿ���б�������ֵ���ݣ����Է��ʣ��������޸�
	//������дһ��[&]��ַ������ʾ�ⲿ���б��������ô��ݣ����Է��ʣ������޸�
	listener->onTouchBegan = [=](Touch* t, Event* e) {//"="��ʾ�������еı��������԰�ֵ���ݽ���
		Vec2 touchPos = t->getLocation();//��ȡ������λ��
		m_offset = m_hero->getPosition() - touchPos;
		bool isContains = m_hero->getBoundingBox().containsPoint(touchPos);//�жϷɻ��Ƿ�����˴�����
		//�������ͣ״̬��ֹͣ�ɻ��ƶ�
		//���ش������Ƿ��ڷɻ���
		return isContains && !Director::getInstance()->isPaused();
	};
	//b�����������ƶ�
	listener->onTouchMoved = [=](Touch* t, Event* e) {
		Vec2 touchPos = t->getLocation();
		//�ƶ�ʱ�߽��ж�
		auto maxX = VISIBLE_SIZE.width - m_hero->getContentSize().width / 2;//��
		auto minX = m_hero->getContentSize().width / 2;//��
		auto maxY = VISIBLE_SIZE.height - m_hero->getContentSize().height;//��
		auto minY = m_hero->getContentSize().height / 2;//��
		m_hero->setPositionX(MIN(MAX(t->getLocation().x + m_offset.x, minX), maxX));//����λ�������ұ߽���
		m_hero->setPositionY(MIN(MAX(t->getLocation().y + m_offset.y, minY), maxY));//����λ�������±߽磨���пռ䣩��

	};
	//c.��������
	listener->onTouchEnded = [=](Touch* t, Event* e) {
	};
	//3.ע��������ַ�����
	//ͨ�������Ļ滭���ȼ������������ȼ���������ȴ��룩���Զ�ע���¼�
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_hero);//(��������hero��)

	///////UI


	auto pause = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	//�Ʒֱ�ǩ
	//����
	auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", this->m_totalScore));

	//����ê�㵽��ߣ�����߽�̶�
	lblScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	////����

	lblScore->setPosition(20, VISIBLE_SIZE.height - lblScore->getContentSize().height);
	this->addChild(lblScore, UI_ZORDER, LABEL_SCORE_TAG);
	lblScore->setColor(CORLOR_SCORE);//���Զ���(R,G,B)
	//ը���˵���
	auto spBomb = Sprite::createWithSpriteFrameName("bomb.png");
	//�˵���
	//���ը��ʱ������е���
	auto itemBomb = MenuItemSprite::create(spBomb, spBomb, [=](Ref*) {
		//��ͣʱ�޷�ʹ��ը��
		if (Director::getInstance()->isPaused())
		{
			return;
		}
		
		if (m_bombCount > 0)
		{
			AudioEngine::play2d("use_bomb.mp3", false, VAL_MUSIC_BACKGROUND);
			//ɱ�����е��˲��ӷ�
			for (auto enemy : m_enemies)
			{
				enemy->downing();
				enemy->setLife(0);
				this->m_totalScore += enemy->isDead();	
			}
			this->m_enemies.clear();
			lblScore->setString(StringUtils::format("%d", this->m_totalScore));
			this->m_bombCount--;
			this->changeBomb();
		}
	});


	//ը��������
	auto lblBombConter = Label::createWithBMFont("font.fnt", StringUtils::format("X%d", this->m_bombCount));
	lblBombConter->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	itemBomb->setPosition(itemBomb->getContentSize()/2);
	lblBombConter->setPosition(itemBomb->getPosition().x+itemBomb->getContentSize().width/2, itemBomb->getPosition().y);
	this->addChild(lblBombConter, UI_ZORDER, LABEL_BOMBCONTER_TAG);
	lblBombConter->setColor(Color3B::RED);//���Զ���(R,G,B)

	//�����˵���ִ�в˵���
	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	

	//��ͣ�˵�
	//��������,���ھ���˵���
	auto spPauseNoremal = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto spPauseSelected = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	auto spResumeNormal = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto spResumeSelected = Sprite::createWithSpriteFrameName("game_resume_pressed.png");
	auto itemPause = MenuItemSprite::create(spPauseNoremal, spPauseSelected);
	auto itemResume = MenuItemSprite::create(spResumeNormal, spResumeSelected);
	//�л�
	//Toggle�˵������Զ������л���ӵ�������Ĳ˵����������һ�ε��ֻ��ʾһ��
	auto toggle = MenuItemToggle::createWithCallback([](Ref *sender) {
		//��ȡ��ǰѡ������±꣨��0��ʼ��
		int index = dynamic_cast<MenuItemToggle*>(sender)->getSelectedIndex();
		if (index)
		{
			AudioEngine::play2d("button.mp3", false, VAL_MUSIC_SOUND);
			Director::getInstance()->pause();
			AudioEngine::pauseAll();
		}
		else
		{
			AudioEngine::play2d("button.mp3", false, VAL_MUSIC_SOUND);
			Director::getInstance()->resume();
			AudioEngine::resumeAll();
		}
	},itemPause,itemResume,nullptr);
	menu->addChild(itemBomb, UI_ZORDER, ITEM_BOMB_TAG);
	toggle->setPosition(VISIBLE_SIZE - toggle->getContentSize());
	menu->addChild(toggle);
	//��Ӳ˵�
	this->addChild(menu, UI_ZORDER, MENU_TAG);
	
	//�޲�����ÿ�����һ��Update����
	scheduleUpdate();

	//ʹ�ü�ʱ���������ַɻ�
	schedule(schedule_selector(GameScene::createSmallEnemy), CREAT_SMALLENEMY_INTERVAL, CC_REPEAT_FOREVER, DELAY_PRE_SMALLENEMY_CREAT);
	schedule(schedule_selector(GameScene::createMiddleEnemy), CREAT_MIDDLEENEMY_INTERVAL, CC_REPEAT_FOREVER, DELAY_PRE_MIDDLEENEMY_CREAT);
	schedule(schedule_selector(GameScene::createBigEnemy), CREAT_BIGENEMY_INTERVAL, CC_REPEAT_FOREVER, DELAY_PRE_BIGENEMY_CREAT);

	//ʹ�ü�ʱ�������ӵ�
	schedule(schedule_selector(GameScene::createBullet), CREAT_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createUfo), CREAT_UFO_INTERVAL, CC_REPEAT_FOREVER, DELAY_PRE_UFO_CREAT);
	return true;
}
void GameScene::update(float delta) {
	//////����
	auto bg1 = this->getChildByTag(BACKGROUND_TAG_1);
	bg1->setPositionY(bg1->getPositionY() - SPEED_BACKGROUND);
	auto bg2 = this->getChildByTag(BACKGROUND_TAG_2);
	auto hero = this->getChildByTag(HERO_TAG);
	auto ufo = this->getChildByTag(UFO_TAG);
	//�ñ���ͼ2���汳��ͼ1
	bg2->setPositionY(bg1->getPositionY() + bg1->getContentSize().height);
	//��ͼ������򳬳��ײ�ʱ����ͼһ�ƶ����ײ���ͼ��ʼ�ո���ͼһ
	if (bg2->getPositionY() < 0)
	{
		bg1->setPositionY(0);
	}

	//////�ӵ�

	//����Ҫɾ�����ӵ����븨������
	Vector<Sprite *> removableBullets;
	//�����ӵ�����
	for (auto bullet : m_bullets)
	{
		if (isTracked)
		{
			Enemy* Target = nullptr;

			float minDistance = 9999;//��С����
			float angle = 0.0f;
			for (auto enemy : m_enemies)
			{
				Vec2 dis = enemy->getPosition() - bullet->getPosition();
				float distance = dis.getLength();//��ǰ����
				if (distance < minDistance)
				{
					minDistance = distance;
					Target = enemy;
					angle = dis.getAngle();

				}
			}
			float radian = angle * 3.14159 / 180.0;
			if (Target&&m_trackBulletsCount > 0&&angle>0)
			{
				float q2x = hero->getPositionX() + (Target->getPositionX() - hero->getPositionX()) / 2.0;
				Vec2 q2 = ccp(q2x, 10 + hero->getPositionY() + cos(radian)*q2x);
				ccBezierConfig bezier;
				bezier.controlPoint_1 = Point(Target->getPosition());
				bezier.controlPoint_2 = q2;
				bezier.endPosition = Point(Target->getPosition());
				BezierTo* bezierTo = BezierTo::create(20.0f,bezier);
				bullet->runAction(bezierTo);
			}
			else
				bullet->setPositionY(bullet->getPositionY() + SPEED_BULLET);
		}
		else
			bullet->setPositionY(bullet->getPositionY() + SPEED_BULLET);
		//�ӵ����Ͻ�ʱ����
		if (bullet->getPositionY() >= VISIBLE_SIZE.height)
		{
			this->removeChild(bullet);
			//�����ڱ�������ʱ���޸ļ��ϵĳ�Ա���������Խ����ǰ���Ч���ӵ���ŵ���ʱ�����У��ȱ�������֮���ٴӼ������Ƴ�
			removableBullets.pushBack(bullet);
		}

	}

	Vector<Enemy*> removableEnemys;
	///////����
	//�ƶ�
	for (auto enemy : m_enemies)
	{
		enemy->move();
		if (enemy->getPositionY() + enemy->getContentSize().height / 2 < 0)
		{
			this->removeChild(enemy);
			removableEnemys.pushBack(enemy);
		}
	}

	//��ײ���
	for (auto enemy : m_enemies)
	{
		for (auto bullet : m_bullets)
		{
			//�л��Ļ���������û�����ӵ��Ļ��������ཻ
			if (enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
			{
				enemy->isShootedOnce();
				removableBullets.pushBack(bullet);
				//���˱����
				if (enemy->isDead())
				{
					removableEnemys.pushBack(enemy);
					m_totalScore += enemy->isDead();
					if (isTracked)
					{
						m_trackBulletsCount--;
						log("%d", m_trackBulletsCount);
						if (m_trackBulletsCount < 0)
						{
							this->isTracked = false;
						}
					}
				}
			}
		}
	}

	//�ı����(��Ҫ����ת����getChild��������ΪNode*)
	auto Score = dynamic_cast<Label*> (this->getChildByTag(LABEL_SCORE_TAG));
	//ֻ�����ַ�����Ϊ����
	Score->setString(StringUtils::format("%d", m_totalScore));

	for (auto enemy : m_enemies)		//�ɻ�ײ������
	{
		if (m_hero->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
		{

			AudioEngine::play2d("game_over.mp3", false, VAL_MUSIC_BACKGROUND);
			//��ըǰ���������ӵ�
			for (auto bullet : m_bullets)
			{
				removableBullets.pushBack(bullet);
			}
			//1.ִ�б�ը����
			m_hero->blowup();
			//2.���ó�Ա����m_isOverΪTRUE
			//3.ֹͣ���ж�ʱ��
			this->unscheduleAllSelectors();
			//4.��ת����
			auto scene = OverScene::creatScene(m_totalScore);
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			break;
		}
	}

	Vector<Ufo*> removableUfos;
	for (auto ufo : m_ufos)	
	{
		ufo->move();
		//���ߺͷɻ���ײ���
		if (hero&&hero->getBoundingBox().intersectsRect(ufo->getBoundingBox()))
		{
			removableUfos.pushBack(ufo);
			if (ufo->getType() == UfoType::UFO_1)
			{
				//�����˫�ӵ��ķ������
				AudioEngine::play2d("get_double_laser.mp3", false, VAL_MUSIC_BACKGROUND);
				this->m_doubleBulletsCount = FULL_DOUBLE_BULLET_COUNT;
			}
			//����ը������
			else if(ufo->getType() == UfoType::UFO_2)
			{
				AudioEngine::play2d("get_bomb.mp3", false, VAL_MUSIC_BACKGROUND);
				if (this->m_bombCount < 3)
				{

					m_bombCount++;
					this->changeBomb();
				}
			}
			else if (ufo->getType() == UfoType::UFO_3)
			{
				AudioEngine::play2d("get_bomb.mp3", false, VAL_MUSIC_BACKGROUND);
				this->m_trackBulletsCount += 20;
				this->isTracked = true;
			}
		}
		if (ufo->getPositionY() + ufo->getContentSize().height / 2 < 0)
		{
			this->removeChild(ufo);
			removableUfos.pushBack(ufo);
		}
	}


	//�Ƴ������ӵ�
	for (auto bullet : removableBullets)
	{
		this->removeChild(bullet);		//1.�ӳ������Ƴ������ٱ�����
		m_bullets.eraseObject(bullet);	//2.�Ӽ������Ƴ������ٲ�������
	}
	//�Ƴ����õĵл�
	for (auto enemy : removableEnemys)
	{
		enemy->downing();
		this->m_enemies.eraseObject(enemy);
	}
	for (auto ufo : removableUfos)
	{
		this->removeChild(ufo);
		this->m_ufos.eraseObject(ufo);
	}
}

//�����ӵ�
void GameScene::createBullet(float) {
	auto m_hero = getChildByTag(HERO_TAG);
	if (m_hero)
	{
		AudioEngine::play2d("bullet.mp3", false, VAL_MUSIC_SOUND);
		if (m_doubleBulletsCount > 0)
		{
			//����˫�ӵ�
			auto bulletL = Sprite::createWithSpriteFrameName("bullet2.png");
			bulletL->setPositionX(m_hero->getPosition().x - m_hero->getContentSize().width / 3);
			bulletL->setPositionY(m_hero->getPosition().y + bulletL->getContentSize().height / 2);
			this->addChild(bulletL, FOREGROUND_ZORDER, BULLET_TAG);
			m_bullets.pushBack(bulletL);

			auto bulletR = Sprite::createWithSpriteFrameName("bullet2.png");

			bulletR->setPositionX(m_hero->getPosition().x + m_hero->getContentSize().width / 3);
			bulletR->setPositionY(m_hero->getPosition().y  + bulletR->getContentSize().height / 2);
			this->addChild(bulletR, FOREGROUND_ZORDER, BULLET_TAG);
			m_bullets.pushBack(bulletR);
			m_doubleBulletsCount--;

		}
		else
		{
			//��������
			auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");


			bullet->setPositionX(m_hero->getPosition().x);
			bullet->setPositionY(m_hero->getPosition().y + m_hero->getContentSize().height / 2 + bullet->getContentSize().height / 2);
			this->addChild(bullet, FOREGROUND_ZORDER, BULLET_TAG);
			m_bullets.pushBack(bullet);

		}
	}
}
//��������
void GameScene::createEnemy(EnemyType enemyType) {
	auto enemy = Enemy::create(enemyType);
	this->addChild(enemy, FOREGROUND_ZORDER, ENEMY_TAG);
	this->m_enemies.pushBack(enemy);
}


//�������ַɻ���ͨ����ʱ�����볡��
void GameScene::createSmallEnemy(float) {
	GameScene::createEnemy(EnemyType::SMALL_ENEMY);
}
void GameScene::createMiddleEnemy(float) {
	GameScene::createEnemy(EnemyType::MIDDLE_ENEMY);
}
void GameScene::createBigEnemy(float){
	GameScene::createEnemy(EnemyType::BIG_ENEMY);
}
void GameScene::changeBomb()
{
	auto menu = this->getChildByTag(MENU_TAG);
	auto itemBomb = menu->getChildByTag(ITEM_BOMB_TAG);
	auto lblBomb = this->getChildByTag(LABEL_BOMBCONTER_TAG);
	dynamic_cast<Label*>(lblBomb)->setString(StringUtils::format("X%d", this->m_bombCount));
}
//��������
void GameScene::createUfo(float) {
	UfoType ufoType;
	switch (rand()%3)
	{
	case 0:ufoType = UfoType::UFO_1;
		break;
	case 1:ufoType = UfoType::UFO_2;
		break;
	case 2:ufoType = UfoType::UFO_3;
		break;
	default:
		break;
	}
	auto ufo = Ufo::create(ufoType);
	this->addChild(ufo, FOREGROUND_ZORDER, UFO_TAG);
	this->m_ufos.pushBack(ufo);
}
//չʾ����
void GameScene::deplayScore() {
	auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", this->m_totalScore));
	////����

	lblScore->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 + 150);
	this->addChild(lblScore, UI_ZORDER, LABEL_SCORE_TAG);
	lblScore->setColor(CORLOR_SCORE);//���Զ���(R,G,B)
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}