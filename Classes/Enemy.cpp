#include"Enemy.h"
#include"math.h"
#include"AudioEngine.h"
using namespace experimental;
//�������루����������ж�����
bool Enemy::initWithEnemyType(const EnemyType& type) {
	//�ó�Ա�����������ͣ���ס֮�������ʱ����
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
	//���ﲻҪ���ó���creatWithSpriteFrameName!
	if (!Sprite::initWithSpriteFrameName(frameName))
	{
		return false;
	}
	//����˵ķ��ж���
	//��ִ�ж���ʱ��ֹͣ��������
	if (m_type==EnemyType::BIG_ENEMY)
	{
		AudioEngine::play2d("big_spaceship_flying.mp3", false, VAL_MUSIC_SOUND);
		auto bigEnemyAni = CCAnimationCache::getInstance()->getAnimation(KEY_ANI_BIG_ENEMY_DOWN);
		auto bigEnemyAnimate = Animate::create(bigEnemyAni);
		runAction(bigEnemyAnimate);
	}
	return true;
}
//��������
Enemy * Enemy::create(const EnemyType& type) {
	auto enemy = new Enemy();
	if (enemy&&enemy->initWithEnemyType(type))
	{
		enemy->autorelease();//�����Զ������أ������ô˷���ʱ����+1��������-1��
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
		//ȡ��ֻ�ܶ�������ȡmin��max���������Ҫ��(min-max+1)ȡ��
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
//�����ƶ�
void Enemy::move() {
	setPositionY(getPositionY() + m_speed);
	if (move_random)
	{
		setPositionX(m_startX + 50 * cos((VISIBLE_SIZE.height - getPositionY()) / 50));
	}

}
//�����Ƿ񱻻�ɱ,����ֵΪ��÷���
int Enemy::isDead() {
	if (m_life)
		return 0;
	else 
	return m_score;
}
//�����Ƿ񱻻���һ��
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
//����Ѫ��
int Enemy::getLife() {
	return m_life;
}
//��������
EnemyType Enemy::getType() {
	return m_type;
}
//���˻��ٶ���
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
	//����ִ�к���
	/*auto seq = Sequence::create(animateEnemyDown, CallFuncN::create([](Node *node) {
	node->removeFromParentAndCleanup(true);
	}), nullptr);*/
	auto seq = Sequence::create(animateEnemyDown, RemoveSelf::create(), nullptr);
	//��ըǰֹͣ�������ж���
	runAction(seq);
}
//���˱����ж���
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