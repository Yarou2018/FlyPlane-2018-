#include"GameScene.h"
#include "OverScene.h"
#include "AudioEngine.h"
#include"time.h"

using namespace experimental;

Scene* GameScene::createScene() {
	return GameScene::create();
}
bool GameScene::init() {
	//1.先调用父类的init
	if (!Scene::init())
	{
		return false;
	}
	//随机数种子
	srand((unsigned int)time(NULL));

	//注册键盘监听
	auto backKeyListener = EventListenerKeyboard::create();
	backKeyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backKeyListener, this);

	AudioEngine::play2d("game_music.mp3", true, VAL_MUSIC_BACKGROUND);//文件名，是否循环，音量

	////////////背景
	//创建精灵
	//auto bg = Sprite::create("shoot_background.png");

	auto bg1 = Sprite::createWithSpriteFrameName("background.png");
	//设置锚点位置在自身的左下角
	bg1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);//参数也可以(0,0)代表左下角(1,1)代表右上角
	//定位
	//创建背景图2用于连续滚动
	auto bg2 = Sprite::createWithSpriteFrameName("background.png");
	bg2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bg2->setPositionY(bg1->getContentSize().height);

	//添加精灵
	this->addChild(bg1, BACKGROUND_ZORDER, BACKGROUND_TAG_1);
	this->addChild(bg2, BACKGROUND_ZORDER, BACKGROUND_TAG_2);

	//开启抗锯齿
	bg1->getTexture()->setAliasTexParameters();//获得纹理（显示后）并开启抗锯齿
	bg2->getTexture()->setAliasTexParameters();

	/////////////飞机
	m_hero = Hero::create();
	this->addChild(m_hero, FOREGROUND_ZORDER, HERO_TAG);
	//添加触摸时间的处理
	//1.创建一个时间监听对象
	auto listener = EventListenerTouchOneByOne::create();

	//2.分解时间，处理逻辑
	//a触摸开始时
	//lambda表达式的[]部分表示控制对外部变量的访问，可以一个一个的传递，默认是值传递
	//也可以用"="等号，表示外部所有变量都按值传递，可以访问，但不能修改
	//还可以写一个[&]地址符，表示外部所有变量按引用传递，可以访问，可以修改
	listener->onTouchBegan = [=](Touch* t, Event* e) {//"="表示外面所有的变量都可以按值传递进来
		Vec2 touchPos = t->getLocation();//获取触摸点位置
		m_offset = m_hero->getPosition() - touchPos;
		bool isContains = m_hero->getBoundingBox().containsPoint(touchPos);//判断飞机是否包含了触摸点
		//如果在暂停状态，停止飞机移动
		//返回触摸点是否在飞机上
		return isContains && !Director::getInstance()->isPaused();
	};
	//b持续触摸并移动
	listener->onTouchMoved = [=](Touch* t, Event* e) {
		Vec2 touchPos = t->getLocation();
		//移动时边界判断
		auto maxX = VISIBLE_SIZE.width - m_hero->getContentSize().width / 2;//右
		auto minX = m_hero->getContentSize().width / 2;//左
		auto maxY = VISIBLE_SIZE.height - m_hero->getContentSize().height;//上
		auto minY = m_hero->getContentSize().height / 2;//下
		m_hero->setPositionX(MIN(MAX(t->getLocation().x + m_offset.x, minX), maxX));//控制位置在左右边界内
		m_hero->setPositionY(MIN(MAX(t->getLocation().y + m_offset.y, minY), maxY));//控制位置在上下边界（留有空间）内

	};
	//c.触摸结束
	listener->onTouchEnded = [=](Touch* t, Event* e) {
	};
	//3.注册监听到分发器上
	//通过场景的绘画优先级决定传递优先级（后绘制先传入）会自动注销事件
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_hero);//(监听器和hero绑定)

	///////UI


	auto pause = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	//计分标签
	//字体
	auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", this->m_totalScore));

	//设置锚点到左边，将左边界固定
	lblScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	////分数

	lblScore->setPosition(20, VISIBLE_SIZE.height - lblScore->getContentSize().height);
	this->addChild(lblScore, UI_ZORDER, LABEL_SCORE_TAG);
	lblScore->setColor(CORLOR_SCORE);//或自定义(R,G,B)
	//炸弹菜单项
	auto spBomb = Sprite::createWithSpriteFrameName("bomb.png");
	//菜单项
	//点击炸弹时清空所有敌人
	auto itemBomb = MenuItemSprite::create(spBomb, spBomb, [=](Ref*) {
		//暂停时无法使用炸弹
		if (Director::getInstance()->isPaused())
		{
			return;
		}
		
		if (m_bombCount > 0)
		{
			AudioEngine::play2d("use_bomb.mp3", false, VAL_MUSIC_BACKGROUND);
			//杀死所有敌人并加分
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


	//炸弹计数器
	auto lblBombConter = Label::createWithBMFont("font.fnt", StringUtils::format("X%d", this->m_bombCount));
	lblBombConter->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	itemBomb->setPosition(itemBomb->getContentSize()/2);
	lblBombConter->setPosition(itemBomb->getPosition().x+itemBomb->getContentSize().width/2, itemBomb->getPosition().y);
	this->addChild(lblBombConter, UI_ZORDER, LABEL_BOMBCONTER_TAG);
	lblBombConter->setColor(Color3B::RED);//或自定义(R,G,B)

	//创建菜单，执行菜单项
	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	

	//暂停菜单
	//创建精灵,用于精灵菜单项
	auto spPauseNoremal = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto spPauseSelected = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	auto spResumeNormal = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto spResumeSelected = Sprite::createWithSpriteFrameName("game_resume_pressed.png");
	auto itemPause = MenuItemSprite::create(spPauseNoremal, spPauseSelected);
	auto itemResume = MenuItemSprite::create(spResumeNormal, spResumeSelected);
	//切换
	//Toggle菜单具有自动轮流切换添加到它上面的菜单项的能力，一次点击只显示一项
	auto toggle = MenuItemToggle::createWithCallback([](Ref *sender) {
		//获取当前选择项的下标（从0开始）
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
	//添加菜单
	this->addChild(menu, UI_ZORDER, MENU_TAG);
	
	//无参数，每桢调用一次Update函数
	scheduleUpdate();

	//使用计时器创建三种飞机
	schedule(schedule_selector(GameScene::createSmallEnemy), CREAT_SMALLENEMY_INTERVAL, CC_REPEAT_FOREVER, DELAY_PRE_SMALLENEMY_CREAT);
	schedule(schedule_selector(GameScene::createMiddleEnemy), CREAT_MIDDLEENEMY_INTERVAL, CC_REPEAT_FOREVER, DELAY_PRE_MIDDLEENEMY_CREAT);
	schedule(schedule_selector(GameScene::createBigEnemy), CREAT_BIGENEMY_INTERVAL, CC_REPEAT_FOREVER, DELAY_PRE_BIGENEMY_CREAT);

	//使用计时器创建子弹
	schedule(schedule_selector(GameScene::createBullet), CREAT_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createUfo), CREAT_UFO_INTERVAL, CC_REPEAT_FOREVER, DELAY_PRE_UFO_CREAT);
	return true;
}
void GameScene::update(float delta) {
	//////背景
	auto bg1 = this->getChildByTag(BACKGROUND_TAG_1);
	bg1->setPositionY(bg1->getPositionY() - SPEED_BACKGROUND);
	auto bg2 = this->getChildByTag(BACKGROUND_TAG_2);
	auto hero = this->getChildByTag(HERO_TAG);
	auto ufo = this->getChildByTag(UFO_TAG);
	//让背景图2跟随背景图1
	bg2->setPositionY(bg1->getPositionY() + bg1->getContentSize().height);
	//当图二到达或超出底部时，则将图一移动到底部，图二始终跟随图一
	if (bg2->getPositionY() < 0)
	{
		bg1->setPositionY(0);
	}

	//////子弹

	//将需要删除的子弹存入辅助容器
	Vector<Sprite *> removableBullets;
	//遍历子弹集合
	for (auto bullet : m_bullets)
	{
		if (isTracked)
		{
			Enemy* Target = nullptr;

			float minDistance = 9999;//最小距离
			float angle = 0.0f;
			for (auto enemy : m_enemies)
			{
				Vec2 dis = enemy->getPosition() - bullet->getPosition();
				float distance = dis.getLength();//当前距离
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
		//子弹出上界时消除
		if (bullet->getPositionY() >= VISIBLE_SIZE.height)
		{
			this->removeChild(bullet);
			//不能在遍历集合时，修改集合的成员数量，所以仅仅是把无效的子弹存放到临时集合中，等遍历结束之后再从集合中移除
			removableBullets.pushBack(bullet);
		}

	}

	Vector<Enemy*> removableEnemys;
	///////敌人
	//移动
	for (auto enemy : m_enemies)
	{
		enemy->move();
		if (enemy->getPositionY() + enemy->getContentSize().height / 2 < 0)
		{
			this->removeChild(enemy);
			removableEnemys.pushBack(enemy);
		}
	}

	//碰撞检测
	for (auto enemy : m_enemies)
	{
		for (auto bullet : m_bullets)
		{
			//敌机的绘制区域有没有与子弹的绘制区域相交
			if (enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
			{
				enemy->isShootedOnce();
				removableBullets.pushBack(bullet);
				//敌人被打掉
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

	//改变分数(需要类型转换，getChild返回类型为Node*)
	auto Score = dynamic_cast<Label*> (this->getChildByTag(LABEL_SCORE_TAG));
	//只接受字符串作为参数
	Score->setString(StringUtils::format("%d", m_totalScore));

	for (auto enemy : m_enemies)		//飞机撞到敌人
	{
		if (m_hero->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
		{

			AudioEngine::play2d("game_over.mp3", false, VAL_MUSIC_BACKGROUND);
			//爆炸前销毁所有子弹
			for (auto bullet : m_bullets)
			{
				removableBullets.pushBack(bullet);
			}
			//1.执行爆炸动画
			m_hero->blowup();
			//2.设置成员变量m_isOver为TRUE
			//3.停止所有定时器
			this->unscheduleAllSelectors();
			//4.跳转场景
			auto scene = OverScene::creatScene(m_totalScore);
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			break;
		}
	}

	Vector<Ufo*> removableUfos;
	for (auto ufo : m_ufos)	
	{
		ufo->move();
		//道具和飞机碰撞检测
		if (hero&&hero->getBoundingBox().intersectsRect(ufo->getBoundingBox()))
		{
			removableUfos.pushBack(ufo);
			if (ufo->getType() == UfoType::UFO_1)
			{
				//填充满双子弹的发射次数
				AudioEngine::play2d("get_double_laser.mp3", false, VAL_MUSIC_BACKGROUND);
				this->m_doubleBulletsCount = FULL_DOUBLE_BULLET_COUNT;
			}
			//碰到炸弹道具
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


	//移除无用子弹
	for (auto bullet : removableBullets)
	{
		this->removeChild(bullet);		//1.从场景中移除，不再被绘制
		m_bullets.eraseObject(bullet);	//2.从集合中移除，不再参与运算
	}
	//移除无用的敌机
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

//创建子弹
void GameScene::createBullet(float) {
	auto m_hero = getChildByTag(HERO_TAG);
	if (m_hero)
	{
		AudioEngine::play2d("bullet.mp3", false, VAL_MUSIC_SOUND);
		if (m_doubleBulletsCount > 0)
		{
			//创建双子弹
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
			//创建单发
			auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");


			bullet->setPositionX(m_hero->getPosition().x);
			bullet->setPositionY(m_hero->getPosition().y + m_hero->getContentSize().height / 2 + bullet->getContentSize().height / 2);
			this->addChild(bullet, FOREGROUND_ZORDER, BULLET_TAG);
			m_bullets.pushBack(bullet);

		}
	}
}
//创建敌人
void GameScene::createEnemy(EnemyType enemyType) {
	auto enemy = Enemy::create(enemyType);
	this->addChild(enemy, FOREGROUND_ZORDER, ENEMY_TAG);
	this->m_enemies.pushBack(enemy);
}


//创建三种飞机，通过计时器加入场景
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
//创建道具
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
//展示分数
void GameScene::deplayScore() {
	auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", this->m_totalScore));
	////分数

	lblScore->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 + 150);
	this->addChild(lblScore, UI_ZORDER, LABEL_SCORE_TAG);
	lblScore->setColor(CORLOR_SCORE);//或自定义(R,G,B)
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}