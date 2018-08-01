
#define VISIBLE_SIZE Director::getInstance()->getVisibleSize()
#define VISIBLE_ORIGIN Director::getInstance()->getVisibleOrigin()

//��ǩ����
#define BACKGROUND_TAG_1 1
#define BACKGROUND_TAG_2 2
#define HERO_TAG 3
#define BULLET_TAG 4
#define ENEMY_TAG 5
/*#define ANIMATIATION_TAG 6*/
#define UFO_TAG 6
#define LABEL_SCORE_TAG 11
#define LABEL_BOMBCONTER_TAG 12
#define MENU_TAG 13
#define ITEM_BOMB_TAG 14
#define GAMEOVER_TAG 15
#define ENERGY_TAG 16


//ZORDER
#define BACKGROUND_ZORDER -1
#define DEFAULT_ZORDER 0
#define FOREGROUND_ZORDER 1
#define UI_ZORDER 99

//�ٶ�
#define SPEED_BACKGROUND 0.3f
#define SPEED_BULLET 8.0f
#define SPEED_SMALL_ENEMY -2.0f 
#define SPEED_MIDDLE_ENEMY -1.0f
#define	SPEED_BIG_ENEMY -0.5f
#define SPEED_UFO -2.2f

//��ʱ��
#define CREAT_BULLET_INTERVAL 0.2f
#define CREAT_ENEMY_INTERVAL 0.5f
#define CREAT_SMALLENEMY_INTERVAL 0.5f		//������һ��С����
#define CREAT_MIDDLEENEMY_INTERVAL 3.0f		//������һ���е���
#define CREAT_BIGENEMY_INTERVAL 18.0f		//������һ�������
#define CREAT_UFO_INTERVAL 8.0f				//������һ������ʱ��


//��ʱ
#define DELAY_PRE_HERO_FLY 0.2f				//�ɻ����ж�����ʱ
#define DELAY_PRE_HERO_BLOWUP 0.04f			//�ɻ�׹�ٶ�����ʱ
#define DELAY_PRE_BULLET_CREAT 0.02f		//ÿ���ӵ�������ʱ
#define DELAY_PRE_SMALLENEMY_CREAT 0.4f		//ÿ��С���˴�����ʱ
#define DELAY_PRE_MIDDLEENEMY_CREAT 1.5f	//ÿ���е��˴�����ʱ
#define DELAY_PRE_BIGENEMY_CREAT 2.0f		//ÿ������˴�����ʱ
#define DELAY_PRE_BIGENEMY_FLY 0.2f			//����˷��ж�����ʱ
#define DELAY_PRE_ENEMY_DOWN 0.05f			//ÿ������׹�ٶ�����ʱ
#define DELAY_PRE_ENEMY_HIT 0.1f			//���˱���������ʱ
#define DELAY_PRE_UFO_CREAT	12.0f			//ÿ�����ߴ�����ʱ
//����ֵ
#define LIFE_SMALL_ENEMY 1
#define LIFE_MIDDLE_ENEMY 5
#define LIFE_BIG_ENEMY 15

//��ֵ
#define SCORE_SMALL_ENEMY 1
#define SCORE_MIDDLE_ENEMY 3
#define SCORE_BIG_ENEMY 10


//˫�ӵ���������
#define FULL_DOUBLE_BULLET_COUNT 30

//�ɼ�������ɫ
#define CORLOR_SCORE Color3B::BLACK

//�����������
#define KET_ANI_HERO_FLY "HEROFLY"						//�ɻ����ж���
#define KEY_ANI_HERO_BLOWUP "HEROBLOWUP"				//�ɻ���ը����
#define KET_ANI_BIGENEMY_FLY "BIGENEMYFLY"				//����˷��ж���
#define KEY_ANI_MIDDLE_ENEMY_HIT "MIDLLEENEMYHIT"		//�е��˱�������
#define KEY_ANI_BIG_ENEMY_IHT "BIGENEMYHIT"				//����˱�������
#define KEY_ANI_SMALL_ENEMY_DOWN "SMALLENEMYDOWN"		//С���˱�ը����
#define KEY_ANI_MIDDLE_ENEMY_DOWN "MIDDLEENEMYDOWN"		//�е��˱�ը����
#define KEY_ANI_BIG_ENEMY_DOWN "BIGENEMYDOWN"			//����˱�ը����

#define KEY_HIGH_SCORE "HIGHSCORE"						//��߷�
#define VAL_MUSIC_SOUND 0.5f							//��Ч����
#define VAL_MUSIC_BACKGROUND 1.0f						//��������