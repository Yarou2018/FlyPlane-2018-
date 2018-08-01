#include"Enemy.h"
#include"math.h"
#include"AudioEngine.h"
using namespace experimental;
//敌人载入（大敌人载入有动画）
bool Enemy::initWithEnemyType(const EnemyType& type) {
	//用成员变量保存类型，记住之后可以随时访问
	m_type = type;
	std::string frameName = "enemy1.png";
	m_speed = SPEED_SMALL_ENEMY * (RandomHelper::random_real(0.5,1.5));
	m_score = SCORE_SMALL_ENEMY;
	switch (m_type)
	{
	case EnemyType::MIDDLE_ENEMY:  
		frameName = "enemy2.png";
		m_speed = SPEED_MIDDLE_ENEMY * (RandomHelper::random_real(0.5, 1.5));
		m_score = SCORE_MIDDLE_ENEMY;
		break;
	case EnemyType::BIG_ENEMY:  
		frameName = "enemy3_n1.png";
		m_score = SCORE_BIG_ENEMY * (RandomHelper::random_real(0.5, 1.5));
		m_speed = SPEED_BIG_ENEMY;
		break;
	default:
		break;
	}
	//这里不要调用成了creatWithSpriteFrameName!
	if (!Sprite::initWithSpriteFrameName(frameName))
	{
		return false;
	}
	//大敌人的飞行动画
	//在执行动作时，停止其他动作
	if (m_type==EnemyType::BIG_ENEMY)
	{
		AudioEngine::play2d("big_spaceship_flying.mp3", false, VAL_MUSIC_SOUND);
		auto bigEnemyAni = CCAnimationCache::getInstance()->getAnimation(KEY_ANI_BIG_ENEMY_DOWN);
		auto bigEnemyAnimate = Animate::create(bigEnemyAni);
		runAction(bigEnemyAnimate);
	}
	return true;
}
//创建敌人
Enemy * Enemy::create(const EnemyType& type) {
	auto enemy = new Enemy();
	if (enemy&&enemy->initWithEnemyType(type))
	{
		enemy->autorelease();//放入自动计数池，当调用此方法时计数+1，结束后-1；
		switch (type)
		{
		case EnemyType::SMALL_ENEMY:
			enemy->m_life = LIFE_SMALL_ENEMY;
			enemy->m_type = EnemyType::SMALL_ENEMY;
			break;
		case EnemyType::MIDDLE_ENEMY:
			enemy->m_life = LIFE_MIDDLE_ENEMY;
			enemy->m_type = EnemyType::MIDDLE_ENEMY;
			break;
		case EnemyType::BIG_ENEMY:
			enemy->m_life = LIFE_BIG_ENEMY;
			enemy->m_type = EnemyType::BIG_ENEMY;
			break;
		default:
			break;
		}
		float minX = enemy->getContentSize().width / 2;
		float maxX = VISIBLE_SIZE.width - minX;
		//取余只能对整数，取min到max的随机数需要对(min-max+1)取余
		enemy->setPositionX(rand() % (int)(maxX - minX + 1) + minX);
		enemy->m_startX = enemy->getPositionX();
		enemy->move_random = (rand() % 4 == 3);
		enemy->setPositionY(VISIBLE_SIZE.height + enemy->getContentSize().height / 2);
		return enemy;
	}

	delete enemy;
	enemy = nullptr;
	return nullptr;
}
//敌人移动
void Enemy::move() {
	setPositionY(getPositionY() + m_speed);
	if (move_random)
	{
		setPositionX(m_startX + 50 * cos((VISIBLE_SIZE.height - getPositionY()) / 50));
	}

}
//敌人是否被击杀,返回值为获得分数
int Enemy::isDead() {
	if (m_life)
		return 0;
	else 
	return m_score;
}
//敌人是否被击中一次
bool Enemy::isShootedOnce() {
	if (!isDead())
	{
		this->m_life -= 1;
		isHit();
		return true;
	}
	else
		return false;
}
//敌人血量
int Enemy::getLife() {
	return m_life;
}
//敌人种类
EnemyType Enemy::getType() {
	return m_type;
}
//敌人击毁动画
void Enemy::downing() {
	Vector<SpriteFrame* > frames;
	auto aniEnemy = Animation::create();
	switch (m_type)
	{
	case EnemyType::SMALL_ENEMY:
		aniEnemy = CCAnimationCache::getInstance()->getAnimation(KEY_ANI_SMALL_ENEMY_DOWN);
		AudioEngine::play2d("enemy1_down.mp3", false, VAL_MUSIC_SOUND);
		break;
	case EnemyType::MIDDLE_ENEMY:
		aniEnemy = CCAnimationCache::getInstance()->getAnimation(KEY_ANI_MIDDLE_ENEMY_DOWN);
		AudioEngine::play2d("enemy2_down.mp3", false, VAL_MUSIC_SOUND);
		break;
	case EnemyType::BIG_ENEMY:
		aniEnemy = CCAnimationCache::getInstance()->getAnimation(KEY_ANI_BIG_ENEMY_DOWN);
		AudioEngine::play2d("enemy3_down.mp3", false, VAL_MUSIC_SOUND);
		break;
	default:
		break;
	}
	auto animateEnemyDown = Animate::create(aniEnemy);
	//序列执行函数
	/*auto seq = Sequence::create(animateEnemyDown, CallFuncN::create([](Node *node) {
	node->removeFromParentAndCleanup(true);
	}), nullptr);*/
	auto seq = Sequence::create(animateEnemyDown, RemoveSelf::create(), nullptr);
	//爆炸前停止其他所有动作
	runAction(seq);
}
//敌人被击中动画
void Enemy::isHit()
{
	Vector<SpriteFrame* > frames;
	auto aniEnemy = Animation::create();
	switch (m_type)
	{
	case EnemyType::MIDDLE_ENEMY:
		aniEnemy=CCAnimationCache::getInstance()->getAnimation(KEY_ANI_MIDDLE_ENEMY_HIT);
		break;
	case EnemyType::BIG_ENEMY:
		aniEnemy = CCAnimationCache::getInstance()->getAnimation(KEY_ANI_BIG_ENEMY_IHT);
		break;
	default:
		break;
	}	
	auto animateEnemyHit = Animate::create(aniEnemy);
	runAction(animateEnemyHit);
}