#include"OverScene.h"
#include"GameScene.h"
#include"AudioEngine.h"

using namespace experimental;
Scene* OverScene::creatScene(int score) {
	auto scene = new OverScene();
	//自动计数池
	if (scene&&scene->init(score))
	{
		scene->autorelease();
		return scene;
	}
	//创建不成功
	else
	{
		delete scene;
		scene = nullptr;
		return nullptr;
	}

}

bool OverScene::init(int score) {
	do
	{
		CC_BREAK_IF(!Scene::init());

		auto bg = Sprite::createWithSpriteFrameName("gameover.png");
		bg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		bg->setPosition(0, VISIBLE_ORIGIN.y + VISIBLE_SIZE.height);
		this->addChild(bg,BACKGROUND_ZORDER);
 
		

		//历史最高分标签		
		auto highScore = UserDefault::getInstance()->getIntegerForKey(KEY_HIGH_SCORE, 0);//不存在返回0
		auto lblHighScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", highScore));
		lblHighScore->setPosition(VISIBLE_ORIGIN + Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 5 * 4));	
		lblHighScore->setColor(CORLOR_SCORE);
		lblHighScore->setBMFontSize(36);
		this->addChild(lblHighScore, UI_ZORDER);
		//最高分更新
		if (highScore < score)
		{
			highScore = score;
			UserDefault::getInstance()->setIntegerForKey(KEY_HIGH_SCORE, highScore);

			auto seq = Sequence::create(
				//一秒时间将动画放大5倍
				ScaleTo::create(1, 5),
				CallFuncN::create([highScore](Node* node) {
				dynamic_cast<Label*>(node)->setString(StringUtils::format("%d", highScore));
			}),
			ScaleTo::create(1, 1),
			nullptr);
			lblHighScore->runAction(seq);
		}

		//添加分值标签
		auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", score));
		lblScore->setPosition(VISIBLE_ORIGIN + Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 3));
		this->addChild(lblScore, UI_ZORDER);
		lblScore->setColor(CORLOR_SCORE);
		lblScore->setBMFontSize(36);
		
		//重新开始
		auto spRestart = Sprite::createWithSpriteFrameName("btn_finish.png");
		auto itemRestart = MenuItemSprite::create(spRestart, spRestart, [](Ref*) {
			AudioEngine::play2d("button.mp3", false, VAL_MUSIC_SOUND);
			AudioEngine::stopAll();
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			
		});

		//重新开始标签
		itemRestart->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		itemRestart->setPosition(VISIBLE_ORIGIN.x + VISIBLE_SIZE.width -20,20);
		
		auto menu = Menu::create(itemRestart, nullptr);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, UI_ZORDER);
		return true;
	} while (0);

	return false;
}