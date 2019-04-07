#pragma once
#include "Element/Element.h"
#include "../GameTypes.h"
#include "math.h"

class GameElement:
	public Element
{
public:
	GameElement();
	~GameElement();

	int speed = 1;

	unsigned int actionBeginTime = 0;
	unsigned int actionLastTime = 0;

	int state = 0;

	//ʱ�����ű���
	float timeSlow = 1.0f;

	//��Χ����TILE_HEIGHT��TILE_WIDTHΪ��λ
	float radius = 0.4f;

	Point position = { 0, 0 };
	PointEx offset = { 0.0, 0.0 };
	int direction = 0;
	Point flyingDirection = { 0, 0 };

	void playSoundFile(const std::string & fileName, float x = 0.0f, float y = 0.0f);
	void getNewPosition(Point pos, PointEx off, Point * newPos, PointEx * newOff);
	void updateEffectPosition(unsigned int ftime, double flySpeed);
	void updateFlyingPosition(unsigned int ftime, double flySpeed);
	void updatePosition(unsigned int ftime);

	virtual unsigned int getFrameTime();
	virtual void beginNewState(int newState);

	//�õ����ǵ�ǰԪ�ص�����λ��,ʵ�������ĵ��·�����(TILE_HEIGHT/2)��
	//������Ԫ��λ�ö������ˣ����Լ����ײʱ������ֱ��ʹ��
	Point getPosition(Point cenTile, PointEx cenOffset);
	Point getPosition(GameElement * camera);

	bool checkCollide(GameElement * ge1, GameElement * ge2);
	bool checkCollide(GameElement * ge);

	virtual void onCollide(GameElement * ge) {};

	virtual void draw() {};

	unsigned int stateBeginTime = 0;
	//unsigned int LastTime = 0;

};

