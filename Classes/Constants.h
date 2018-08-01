
#define VISIBLE_SIZE Director::getInstance()->getVisibleSize()
#define VISIBLE_ORIGIN Director::getInstance()->getVisibleOrigin()

//标签定义
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

//速度
#define SPEED_BACKGROUND 0.3f
#define SPEED_BULLET 8.0f
#define SPEED_SMALL_ENEMY -2.0f 
#define SPEED_MIDDLE_ENEMY -1.0f
#define	SPEED_BIG_ENEMY -0.5f
#define SPEED_UFO -2.2f

//记时器
#define CREAT_BULLET_INTERVAL 0.2f
#define CREAT_ENEMY_INTERVAL 0.5f
#define CREAT_SMALLENEMY_INTERVAL 0.5f		//创建第一个小敌人
#define CREAT_MIDDLEENEMY_INTERVAL 3.0f		//创建第一个中敌人
#define CREAT_BIGENEMY_INTERVAL 18.0f		//创建第一个大敌人
#define CREAT_UFO_INTERVAL 8.0f				//创建第一个道具时间


//延时
#define DELAY_PRE_HERO_FLY 0.2f				//飞机飞行动画延时
#define DELAY_PRE_HERO_BLOWUP 0.04f			//飞机坠毁动画延时
#define DELAY_PRE_BULLET_CREAT 0.02f		//每颗子弹创建延时
#define DELAY_PRE_SMALLENEMY_CREAT 0.4f		//每个小敌人创建延时
#define DELAY_PRE_MIDDLEENEMY_CREAT 1.5f	//每个中敌人创建延时
#define DELAY_PRE_BIGENEMY_CREAT 2.0f		//每个大敌人创建延时
#define DELAY_PRE_BIGENEMY_FLY 0.2f			//大敌人飞行动画延时
#define DELAY_PRE_ENEMY_DOWN 0.05f			//每个敌人坠毁动画延时
#define DELAY_PRE_ENEMY_HIT 0.1f			//敌人被击动画延时
#define DELAY_PRE_UFO_CREAT	12.0f			//每个道具创建延时
//生命值
#define LIFE_SMALL_ENEMY 1
#define LIFE_MIDDLE_ENEMY 5
#define LIFE_BIG_ENEMY 15

//分值
#define SCORE_SMALL_ENEMY 1
#define SCORE_MIDDLE_ENEMY 3
#define SCORE_BIG_ENEMY 10


//双子弹最大发射次数
#define FULL_DOUBLE_BULLET_COUNT 30

//成绩字体颜色
#define CORLOR_SCORE Color3B::BLACK

//动画缓存键名
#define KET_ANI_HERO_FLY "HEROFLY"						//飞机飞行动画
#define KEY_ANI_HERO_BLOWUP "HEROBLOWUP"				//飞机爆炸动画
#define KET_ANI_BIGENEMY_FLY "BIGENEMYFLY"				//大敌人飞行动画
#define KEY_ANI_MIDDLE_ENEMY_HIT "MIDLLEENEMYHIT"		//中敌人被击动画
#define KEY_ANI_BIG_ENEMY_IHT "BIGENEMYHIT"				//大敌人被击动画
#define KEY_ANI_SMALL_ENEMY_DOWN "SMALLENEMYDOWN"		//小敌人爆炸动画
#define KEY_ANI_MIDDLE_ENEMY_DOWN "MIDDLEENEMYDOWN"		//中敌人爆炸动画
#define KEY_ANI_BIG_ENEMY_DOWN "BIGENEMYDOWN"			//大敌人爆炸动画

#define KEY_HIGH_SCORE "HIGHSCORE"						//最高分
#define VAL_MUSIC_SOUND 0.5f							//音效音量
#define VAL_MUSIC_BACKGROUND 1.0f						//背景音乐