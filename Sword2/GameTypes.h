#pragma once
#include <string>
#include <deque>
#include "Image/IMP.h"

#pragma warning(disable:26495)

#define TILE_WIDTH 64
#define TILE_HEIGHT 32

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

#define CONFIG_INI "config.ini"
#define DEFAULT_FOLDER "save\\game\\"
#define SAVE_FOLDER "save\\rpg%d\\"
#define SHOT_FOLDER "save\\shot\\"
#define SHOT_BMP "rpg%d.bmp"
#define GLOBAL_INI "game.ini"
#define PLAYER_INI "player.ini"
#define PARTNER_INI "partner.ini"
#define MEMO_INI "memo.txt"
#define TRAPS_INI "traps.ini"
#define MAP_FOLDER "map\\"
#define VIDEO_FOLDER "video\\"
#define SOUND_FOLDER "sound\\"
#define MUSIC_FOLDER "music\\"
#define MPC_FOLDER "mpc\\"
#define INI_FOLDER "ini\\"

#define SCRIPT_FOLDER "script\\"
#define LEVEL_FOLDER "ini\\level\\"

#define HEAD_FOLDER "mpc\\portrait\\"

#define NPC_INI_FOLDER "ini\\npc\\"
#define NPC_RES_INI_FOLDER "ini\\npcres\\"
#define NPC_RES_FOLDER "mpc\\character\\"

#define OBJECT_INI_FOLDER "ini\\obj\\"
#define OBJECT_RES_INI_FOLDER  "ini\\objres\\"
#define OBJECT_RES_FOLDER  "mpc\\object\\"

#define SCRIPT_COMMON_FOLDER "script\\common\\"
#define SCRIPT_GOODS_FOLDER "script\\goods\\"
#define SCRIPT_MAP_FOLDER "script\\map\\"

#define MAP_FOLDER "map\\"
#define VARIABLE_INI "variable.ini"
#define VARIABLE_SECTION "Variable"

#define TALK_FILE "talk.txt"

#define BMP16Head "BM16"
#define BMP16HeadLen 4

#define MENU_ITEM_COUNT 9

//��Ʒ����������
#define GOODS_COUNT 81
#define GOODS_TOOLBAR_COUNT 3
#define GOODS_BODY_COUNT 7
#define GOODS_RES_FOLDER "mpc\\goods\\"
#define GOODS_INI "goods.ini"
#define GOODS_INI_FOLDER "ini\\goods\\"

#define BUYSELL_GOODS_COUNT 81
#define BUYSELL_FOLDER "ini\\buy\\"


//ħ������������
#define MAGIC_COUNT 36
#define MAGIC_TOOLBAR_COUNT 5
#define MAGIC_PRACTISE_COUNT 1
#define MAGIC_RES_FOLDER "mpc\\magic\\"
#define MAGIC_INI "magic.ini"
#define INI_MAGIC_FOLDER "ini\\magic\\"
#define MAGIC_MAX_LEVEL 10

#define EFFECT_INI "proj.ini"
#define EFFECT_RES_FOLDER "mpc\\effect\\"

//���������������ֵԽ��˥��Խ��
#define SOUND_FACTOR 0.3f
//������Զ����
#define SOUND_FAREST 10000.0f
//NPC��OBJECT���������Ĳ��ż��
#define SOUND_RAND_INTERVAL 6000

//ʩ��������ʼ���ӳ�ʩ���书�����Ƿż���ʱʹ�ø��ӳ�
#define PLAYER_MAGIC_DELAY 300
//ÿ֡ʱ�䣨ԭ�书Ч������ʱ��Ϊ֡�����ڽ���תΪ����ʱʹ�øú꣩
#define EFFECT_FRAME_TIME (1000.0/60.0)
//ÿ��֮֡�����ļ��ʱ��
#define MAX_FRAME_TIME 40
//��Ϸ�����ٶȲ���
#define SPEED_TIME 0.004
//NPC�й���ʱ�䣨���룩
#define NPC_WALK_INTERVAL 5000
//NPC�й����������������������ʱ�䷶Χ�����룩
#define NPC_WALK_INTERVAL_RANGE 10000
//NPC�й����i��
#define NPC_WALK_STEP 3
//������Ѱ·��NPC�ڹ�������ʱ������ƶ��i�����i������ʱ�Ż��ٴθı�Ŀ���ƶ�
#define NPC_STEP_MAX_COUNT 5
//NPC�����ⷶΧ�������˷�Χ����Ѱ��
#define NPC_FOLLOW_RADIUS 1

#ifdef pi
#undef pi
#endif // pi
#define pi 3.1415926

//�书���ӳ�ʱ��

//�����ͷ��м���ÿ��effect��ʩ�ż��
#define MAGIC_CONTINUOUS_INTERVAL 20
//Բ�μ��ܵ�effect����
#define MAGIC_CIRCLE_COUNT 32
//Բ�μ��ܵ�����Ƕ�
#define MAGIC_CIRCLE_ANGLE_SPACE (2 * pi / MAGIC_CIRCLE_COUNT)
//���μ���ʩ���ӳٵȲ���
#define MAGIC_HEART_DELAY 10
#define MAGIC_HEART_DECAY 0.1
//��������ÿ��effect��ʩ�ż��
#define MAGIC_CIRCLE_HELIX_INTERVAL 10
//���漼�ܸ���Ŀ����(ms)
#define MAGIC_FOLLOW_DELAY 0
//���漼����ѰĿ�귶Χ
#define MAGIC_FOLLOW_RADIUS 10
//Ͷ������������ߵ�ϵ��������Ŀ�����Զ������Ͷ�����߶ȣ�
#define MAGIC_THROW_HEIGHT 7.0

enum TileObstacle
{
	toTrans = 0x40,
	toJumpTrans = 0x60,
	toObstacle = 0x80,
	toJumpOpaque = 0xA0,
};

enum DragType
{
	dtGoods = 1,
	dtMagic = 2,
	dtSell = 3,
	dtBuy = 4,
};

struct DataTile
{
	std::vector<int> objIndex = {};
	std::vector<int> npcIndex = {};
	std::vector<int> stepIndex = {};
};

struct DataMap
{
	std::vector<std::vector<DataTile>> tile;
};

struct EffectTile
{
	std::vector<int> index = {};
};

struct EffectMap
{
	std::vector<std::vector<EffectTile>> tile;
};

struct Point
{
	int x;
	int y;
};

struct PointEx
{
	double x;
	double y;
};

struct pathList
{
	std::vector<Point> point = {};
};

enum GameState
{
	gsNone,
	gsRunning,
	gsMenu,
	gsScript
};

#define MAP_HEADSTR "MAP File Ver2.0"
#define MAP_HEADSTR_LEN 16
#define MAP_NULL 16
#define MAP_PATH 32 
#define MAP_NULL_2 108
#define MAP_HEAD_LEN MAP_HEADSTR_LEN + MAP_NULL + MAP_PATH + 20 + MAP_NULL_2

struct MapHead
{
	char head[MAP_HEADSTR_LEN];
	char dataNil[MAP_NULL];
	char path[MAP_PATH];
	int dataLen = 0;
	int width = 0;
	int height = 0;
	int infoLen = 0x40;
	int nameLen = 0x20;
	char dataNil2[MAP_NULL_2];
};

//#define MAP_MPC_PATH 32
#define MAP_MPC_COUNT 255

struct MpcInfo
{
	char * name = NULL;
	int index = 0;
	int dynamic = 0;
	int obstacle = 0;
	int nil = 0;
};

struct MapMpcPath
{
	MpcInfo mpc[MAP_MPC_COUNT];
};

struct MapTileLayer
{
	unsigned char frame = 0;
	unsigned char mpc = 0;
};

#define MAP_TILE_LAYER 3

struct MapTile
{
	MapTileLayer layer[MAP_TILE_LAYER];
	unsigned char obstacle = 0;
	unsigned char trap = 0;
	unsigned char end[2] = { 0x00, 0x1F };
};

struct MapData
{
	MapHead head;
	MapMpcPath mpc;
	std::vector<std::vector<MapTile>> tile = {};
};

struct Mpc
{
	IMPImage * img = NULL;
};

struct MapMpc
{
	Mpc mpc[MAP_MPC_COUNT];
};
