#include"cocos2d.h"
#include "Enemy.h"
#include "Hero.h"
#include"Ufo.h"
#include"Constants.h"
USING_NS_CC;//�ؼ��֣������ռ�

class GameScene : public Scene {
public:
	GameScene() :m_offset(Vec2::ZERO), m_totalScore(0),m_doubleBulletsCount(0), m_trackBulletsCount(0),m_ufo_type(0), m_bombCount(2), isTracked(false){}

	static Scene* createScene();

	bool init() override;				//�麯����д
	
	CREATE_FUNC(GameScene)

	void update(float) override;

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
	Vec2 m_offset;						//��¼��������ɻ�λ�õ�ƫ����

	void createBullet(float);

	Vector <Sprite*> m_bullets;			//�����Ч�ӵ�
	Vector <Enemy* > m_enemies;			//�����Ч����
	Vector <Ufo* > m_ufos;				//�����Ч����

	void createEnemy(const EnemyType);

	void createSmallEnemy(float);

	void createMiddleEnemy(float);

	void createBigEnemy(float);

	void createUfo(float);				//�����������
			

	Hero* m_hero;

	int m_totalScore;					//��¼�ܷ֣���Ҫ��ʼ��

	//void gameOver();
	int m_doubleBulletsCount;
	int m_trackBulletsCount;
	int m_ufo_type;
	int m_bombCount;					//ը����Ŀ
	bool isTracked;						//�Ƿ����
	void changeBomb();
	void deplayScore();					//����ʱչʾ����
};