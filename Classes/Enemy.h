#pragma once
#include"cocos2d.h"
#include"Constants.h"

USING_NS_CC;
//ö����,������ȫ����
enum class EnemyType {
	SMALL_ENEMY,
	MIDDLE_ENEMY,
	BIG_ENEMY
};
class Enemy: public Sprite {
public:
	Enemy(): m_type(EnemyType::SMALL_ENEMY), m_speed(0),m_life(0),m_score(0), m_startX(0), move_random(0) {}
	bool initWithEnemyType(const EnemyType&) ;
	static Enemy* create(const EnemyType&);
	//����ֵΪ��ɱ�ɻ���õķ���
	int isDead();
	bool isShootedOnce();
	void move();
	int getLife();
	EnemyType getType();
	void downing();
	//�ƶ��ٶ�
	CC_SYNTHESIZE(float, m_speed, Speed);
	CC_SYNTHESIZE(int, m_life, Life);
	CC_SYNTHESIZE(int, m_score, Score);
	void isHit();
private:
	EnemyType m_type;
	float m_startX;
	bool move_random;
};
