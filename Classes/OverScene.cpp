#include"OverScene.h"
#include"GameScene.h"
#include"AudioEngine.h"

using namespace experimental;
Scene* OverScene::creatScene(int score) {
	auto scene = new OverScene();
	//�Զ�������
	if (scene&&scene->init(score))
	{
		scene->autorelease();
		return scene;
	}
	//�������ɹ�
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
 
		

		//��ʷ��߷ֱ�ǩ		
		auto highScore = UserDefault::getInstance()->getIntegerForKey(KEY_HIGH_SCORE, 0);//�����ڷ���0
		auto lblHighScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", highScore));
		lblHighScore->setPosition(VISIBLE_ORIGIN + Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 5 * 4));	
		lblHighScore->setColor(CORLOR_SCORE);
		lblHighScore->setBMFontSize(36);
		this->addChild(lblHighScore, UI_ZORDER);
		//��߷ָ���
		if (highScore < score)
		{
			highScore = score;
			UserDefault::getInstance()->setIntegerForKey(KEY_HIGH_SCORE, highScore);

			auto seq = Sequence::create(
				//һ��ʱ�佫�����Ŵ�5��
				ScaleTo::create(1, 5),
				CallFuncN::create([highScore](Node* node) {
				dynamic_cast<Label*>(node)->setString(StringUtils::format("%d", highScore));
			}),
			ScaleTo::create(1, 1),
			nullptr);
			lblHighScore->runAction(seq);
		}

		//��ӷ�ֵ��ǩ
		auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", score));
		lblScore->setPosition(VISIBLE_ORIGIN + Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 3));
		this->addChild(lblScore, UI_ZORDER);
		lblScore->setColor(CORLOR_SCORE);
		lblScore->setBMFontSize(36);
		
		//���¿�ʼ
		auto spRestart = Sprite::createWithSpriteFrameName("btn_finish.png");
		auto itemRestart = MenuItemSprite::create(spRestart, spRestart, [](Ref*) {
			AudioEngine::play2d("button.mp3", false, VAL_MUSIC_SOUND);
			AudioEngine::stopAll();
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			
		});

		//���¿�ʼ��ǩ
		itemRestart->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		itemRestart->setPosition(VISIBLE_ORIGIN.x + VISIBLE_SIZE.width -20,20);
		
		auto menu = Menu::create(itemRestart, nullptr);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, UI_ZORDER);
		return true;
	} while (0);

	return false;
}