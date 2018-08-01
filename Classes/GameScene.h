#include"cocos2d.h"
#include "Enemy.h"
#include "Hero.h"
#include"Ufo.h"
#include"Constants.h"
USING_NS_CC;//关键字：命名空间

class GameScene : public Scene {
public:
	GameScene() :m_offset(Vec2::ZERO), m_totalScore(0),m_doubleBulletsCount(0), m_trackBulletsCount(0),m_ufo_type(0), m_bombCount(2), isTracked(false){}

	static Scene* createScene();

	bool init() override;				//虚函数重写
	
	CREATE_FUNC(GameScene)

	void update(float) override;

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
	Vec2 m_offset;						//记录触摸点与飞机位置的偏移量

	void createBullet(float);

	Vector <Sprite*> m_bullets;			//存放有效子弹
	Vector <Enemy* > m_enemies;			//存放有效敌人
	Vector <Ufo* > m_ufos;				//存放有效道具

	void createEnemy(const EnemyType);

	void createSmallEnemy(float);

	void createMiddleEnemy(float);

	void createBigEnemy(float);

	void createUfo(float);				//随机创建道具
			

	Hero* m_hero;

	int m_totalScore;					//记录总分，需要初始化

	//void gameOver();
	int m_doubleBulletsCount;
	int m_trackBulletsCount;
	int m_ufo_type;
	int m_bombCount;					//炸弹数目
	bool isTracked;						//是否跟踪
	void changeBomb();
	void deplayScore();					//结束时展示分数
};