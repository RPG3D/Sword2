#pragma once
#include "../GameTypes.h"
#include "File/PakFile.h"
#include "Engine/Engine.h"
#include "Element/Element.h"
#include <deque>

/*
λ�ã�10���ƣ�	��С��bytes��	˵��
00 - 15	16	MAP File Ver2.0
16 - 31	16	null
32 - 63	32	mpc�ļ�·�������31�ֽ� + 1��null��
64 - 67	4	��ͼ�� * ��ͼ�� * 10
68 - 71	4	��ͼ��
72 - 75	4	��ͼ��
76 - 79	4	�Ʋ���ÿ��MPC����Ϣ���ȣ�һ��Ϊ0x40(��ȷ��)
80 - 83	4	�Ʋ���ÿ��MPC���ļ������ȣ�һ��Ϊ0x20(��ȷ��)
84 - 191	108	null
192 - 16511	64 * 255 = 16320	"255��mpc�ļ���Ϣ��һ��ÿ��64�ֽڡ�������Щ�ط���̫ȷ����û��֤��mpc�ļ���һ��ռ32���ֽڣ����ļ���+null�ĸ�ʽ�������Ӧ����������1��2��3.�����������У����������ã� 00-��̬ 01-ѭ��
�ϰ����ã�00 - �� 01 - ͸�� 02 - ʵ��"
16512 - �ļ�ĩ	��ͼ�� * ��ͼ�� * 10	"������ͼ�飨10bytes���������
��0��0������1��0������2��0����������
��0��1������1��1������2��1������������0��2������1��2������2��2����������
2bytes: ͼ���һ��[�ڼ�֡][�ڼ���mpc�ļ�]
2bytes��ͼ��ڶ���[�ڼ�֡][�ڼ���mpc�ļ�]
2bytes��ͼ�������[�ڼ�֡][�ڼ���mpc�ļ�]
1byte ���ϰ��� 0x80 - ��   0xA0 - ���ϣ�ֻ��������  0x40 - ͸��ֻ���Էɹ����ܣ� 0x60 - ��͸�����Էɹ����ܺ�������
1byte ������ : 01 - 19������������
2bytes : 0x00 0x1F"
*/



struct LinePathPoint
{
	Point point = { 0, 0 };
	PointEx pointEx = { 0, 0 };
};

struct PathTile
{
	int index = -1;
	Point from = { 0, 0 };
};

struct PathMap
{
	int w = 0;
	int h = 0;
	std::vector<std::vector<PathTile>> map;
};

#define MAX_STEP 255

class Map:
	public Element
{
public:
	Map();
	~Map();

	MapData * data = NULL;
	MapMpc * mapMpc = NULL;

	bool load(const std::string & fileName);
	bool load(char * d, int len);

	static Point getElementPosition(Point pos, Point cenTile, Point cenScreen, PointEx offset);
	static Point getMousePosition(Point mouse, Point cenTile, Point cenScreen, PointEx offset);
	static Point getTilePosition(Point tile, Point cenTile, Point cenScreen = { 0, 0 }, PointEx offset = { 0, 0 });
	static Point getTileCenter(Point tile, Point cenTile, Point cenScreen, PointEx offset);
	static double getTileDistance(Point from, PointEx fromOffset, Point to, PointEx toOffset);

	void loadMapMpc();
	std::deque<Point> getPath(Point from, Point to);
	//�õ�����toΪradius�i����Χ�ĵ�
	std::deque<Point> getRadiusPath(Point from, Point to, int radius);
	//��õ���·������
	std::deque<Point> getStepPath(Point from, Point to, int stepCount);
	//��ĳ�㷽���ƶ�һ����·��
	std::deque<Point> getStep(Point from, Point to);
	//�õ���ֹ֮������е�
	std::deque<Point> getPassPath(Point from, Point to, Point flyDirection, Point dest);
	//�õ���ֹ֮������е�(��ƫ��)
	std::deque<Point> getPassPathEx(Point from, PointEx fromOffset, Point to, PointEx toOffset, Point flyDirection);

	Point getJumpPath(Point from, Point to);
	bool canView(Point from, Point to);

	int getTrapIndex(Point pos);
	std::string getTrapName(Point pos);
	bool haveTraps(Point pos);
	bool canWalk(Point pos);
	bool canJump(Point pos);
	bool canFly(Point pos);
	bool canViewTile(Point pos);
	bool canPass(Point pos);

	static Point getSubPoint(Point from, int direction);
	static std::vector<Point> getSubPointEx(Point from, int direction);

	static int calDistance(Point from, Point to);

	DataMap dataMap;

	void drawMap();

	void createDataMap();

	void deleteObjecFromDataMap(Point pos, int idx);
	void addObjectToDtataMap(Point pos, int idx);
	void changeObjectataMap(Point pos, int idx, int newIdx);

	void deleteStepFromDataMap(Point pos, int idx);
	void addStepToDataMap(Point pos, int idx);
	void changeStepDataMap(Point pos, int idx, int newIdx);

	void deleteNPCFromDataMap(Point pos, int idx);
	void addNPCToDataMap(Point pos, int idx);
	void changeNPCDataMap(Point pos, int idx, int newIdx);

	virtual void freeResource();
	void freeMpc();
	void freeData();
	void drawTile(int layer, Point tile, Point cenTile, Point cenScreen, PointEx offset);

	bool isInMap(Point pos);
private:
	double calFlyDirection(Point flyDirection);

	LinePathPoint getLineSubStepEx(Point from, PointEx fromOffset, double angle);
	std::vector<Point> getLineSubStep(Point from, Point to, double angle);
	std::vector<Point> getSubStep(PathMap * pathMap, Point from, Point to, int stepIndex);
	bool isInMap(PathMap * pathMap, Point pos);
	bool cmpMapHead(MapData * md);

};

