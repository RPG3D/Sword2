#pragma once
#include "GameElement.h"
#include "../GameTypes.h"
#include "Magic.h"
#include "Effect.h"
#include <deque>

enum NPCKind
{
	nkNormal = 0,
	nkBattle = 1,
	nkPlayer = 2,
	nkPartner = 3,
	nkAnimal = 4,
	nkEvent = 5,
};

enum NPCRelation
{
	nrFriendly = 0,
	nrHostile = 1,
	nrNeutral = 2
};

enum PathFinder
{
	pfSingle = 0,
	pfBest = 1,
};

enum NPCLum
{
	nlNone = 0,
	nlRed = 1,
	nlGreen = 2,
	nlBlue = 3,
	nlGray = 4,
	nlAlpha = 5 // >= 5
};

enum NPCActionType
{
	naNone = 0,
	naStroll = 1,
	naGo = 2
};

struct NPCAction
{
	std::string imageFile = "";
	std::string shadowFile = "";
	std::string soundFile = "";
	IMPImage * image = NULL;
	IMPImage * shadow = NULL;
};

enum ActionCount
{
	acStand = 0,			//վ������
	acStand1 = 1,			//վ������2
	acWalk = 2,				//���߶���
	acRun = 3,				//���ܶ���
	acJump = 4,				//��Ծ����
	acAttack = 5,			//��������
	acAttack1 = 6,			//��������2
	acAttack2 = 7,			//��������3
	acMagic = 8,			//ʩ������
	acHurt = 9,				//���˶���
	acSit = 10,				//��������
	acDeath = 11,			//��������
	acSpecial = 12,			//���⶯�������¼�����ʱ������
	acSitting = 13,			//�������¶���

	acAStand = 20,			//�ֽ�վ������
	acAWalk = 21,			//�ֽ����ܶ���
	acARun = 22,			//�ֽ��ܲ�����
	acAJump = 23,			//�ֽ���Ծ����
	acSpecialAttack = 24,	//�书ָ���Ĺ�������
	acHide = 0xFF,
};

enum SitState
{
	ssSitting = 0,
	ssSat = 1,
};

enum JumpState
{
	jsUp,
	jsJumping,
	jsDown,
};

enum StepState
{
	ssIn,
	ssOut,
};

struct NPCRes
{
	NPCAction stand;
	NPCAction stand1;
	NPCAction walk;
	NPCAction run;
	NPCAction jump;
	NPCAction attack;
	NPCAction attack1;
	NPCAction attack2;
	NPCAction magic;
	NPCAction hurt;
	NPCAction death;
	NPCAction sit;
	NPCAction special;
	NPCAction specialAttack;
	NPCAction astand;
	NPCAction awalk;
	NPCAction arun;
	NPCAction ajump;
};

class NPC :
	public GameElement
{
public:
	NPC();
	~NPC();

	unsigned int getUpdateTime();
	unsigned int updateTime = 0;

	GameElement * destGE = nullptr;
	GameElement * attackTarget = nullptr;

	bool attackDone = false;
	bool haveDest = false;
	Point gotoExDest = { 0, 0 };
	int nowAction = acStand;
	bool selected = false;
	int npcIndex = 1;
	std::string followNPC = "";

	Point attackDest = { 0, 0 };
	void calOffset(int nowTime, int totalTime);
	int getInvertDirection(int dir);
	int calDirection(Point dest);
	unsigned int calStepLastTime();
	static int calDirection(double angle);
	static int calDirection(Point src, Point dest);
	unsigned int walkTime = 0;
	Magic * npcMagic = NULL;
	Magic * npcMagic2 = NULL;
	bool magicUsed = true;

	std::string npcName = "";
	int kind = nkNormal;
	std::string npcIni = "";

	int currPos = 0;
	int action = naNone;
	int walkSpeed = 1;
	int standSpeed = 20;
	int pathFinder = pfSingle;
	int dialogRadius = 1;
	std::string scriptFile = "";

	int relation = nrFriendly;
	int life = 1000;
	int lifeMax = 1000;
	int thew = 100;
	int thewMax = 100;
	int mana = 100;
	int manaMax = 100;
	int attack = 0;
	int defend = 0;
	int evade = 0;
	int duck = 0;
	int exp = 0;

	int levelUpExp = 0;
	int level = 1;
	int attackLevel = 1;	//���ܵȼ�
	int magicLevel = 0;		//����
	int lum = nlNone;
	int visionRadius = 18;
	int attackRadius = 3;
	std::string bodyIni = "";
	std::string flyIni = "";
	std::string flyIni2 = "";
	std::string magicIni = "";
	std::string deathScript = "";

	virtual void addLife(int value);
	virtual void addThew(int value);
	virtual void addMana(int value);

	//�������Ա�ͺ���
	bool isSitting();
	bool isStanding();
	bool isAttacking();
	bool isMagicing();
	bool isRunning();
	bool isWalking();
	bool isJumping();
	bool isDying();
	bool isHurting();
	bool isDoingSpecialAction();
	bool canDoAction(NPCAction * act);
	bool canDoAction(int act);
	bool canView(Point dest);

	std::deque<Point> stepList = {};

	void setFight(int f);
	int fight = 0;
	unsigned int fightTime = 0;
	const unsigned int fightOverTime = 10000;

	virtual unsigned int eventRun();
	virtual void npcJumpTo(Point dest);
	virtual void npcRunTo(Point dest);
	virtual void npcGoto(Point dest);
	virtual void npcGotoEx(Point dest);
	virtual void npcGotoDir(int dir, int distance);
	virtual void npcAttack(Point dest, GameElement * target = nullptr);
	virtual void doSpecialAction(const std::string & fileName);
	virtual void setLevel(int lvl);

	virtual void deleteStep();

	virtual void beginStand();
	virtual void beginWalk(Point dest);
	virtual void beginHurt(Point dest);
	virtual void beginHurt();
	virtual void checkDie();
	virtual void beginDieScript();
	virtual void beginDie();
	virtual void beginAttack(Point dest, GameElement * target = nullptr);
	virtual void beginSpecial();

	virtual void beginSit();
	virtual void beginMagic(Point dest, GameElement * target = nullptr);
	virtual void beginJump(Point dest);
	virtual void beginRun(Point dest);

	virtual void beginRadiusStep(Point dest, int radius);
	virtual void changeRadiusStep(Point dest, int radius);

	virtual void beginRadiusWalk(Point dest, int radius);
	virtual void changeRadiusWalk(Point dest, int radius);

	bool isFollower();
	bool isFollowAttack(NPC * npc);
	virtual void beginFollowWalk(Point dest);
	virtual void beginFollowAttack(Point dest);
	virtual void changeFollowWalk(Point dest);
	virtual void changeFollowAttack(Point dest);

	virtual void hurt(Effect * e);
	virtual void directHurt(Effect * e);
	void addBody();

	virtual void doAttack(Point dest, GameElement * target);
	virtual void useMagic(Magic * m, Point dest, int level, GameElement * target);

	bool frozen = false;
	unsigned int frozenLastTime = 0;
	double jumpSpeed = 10;
	int runSpeed = 4;
	unsigned int jumpState = 0;
	unsigned int getActionTime(int act);
	unsigned int stepBeginTime = 0;
	unsigned int stepLastTime = 0;
	unsigned int stepState = 0;
	unsigned int sitState = 0;

	virtual void playSound(int act);

	//��ͼ����
	_image getActionImage(int * offsetx, int * offsety);
	_image getActionShadow(int * offsetx, int * offsety);
	void draw(Point cenTile, Point cenScreen, PointEx coffset);
	void drawNPCAlpha(Point cenTile, Point cenScreen, PointEx coffset);
	
	void limitDir(int * d);
	void limitDir();

	//ͼ����Դ����
	NPCRes res;
	virtual void initFromIni(INIReader * ini, const std::string & section);
	virtual void saveToIni(INIReader * ini, const std::string & section);
	virtual void loadAction(NPCAction * npcAction);
	virtual void reloadAction();
	virtual void initActionFromIni(NPCAction * npcAction, INIReader * iniReader, const std::string & section);
	virtual void loadSpecialAction(const std::string & fileName);
	virtual void initRes(const std::string & fileName);	
	virtual void loadActionFile(const std::string & fileName, int act);

	virtual void freeResource();

protected:
	virtual bool mouseInRect();

	virtual bool onHandleEvent(AEvent * e);

	void freeNPCRes();
	void freeNPCAction(NPCAction * act);
	virtual void freeActionImage(NPCAction * act);

	virtual void onUpdate();
	virtual void updateAction(unsigned int frameTime);
	virtual void onEvent();
};

