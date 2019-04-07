#pragma once

#include <vector>
#include "../Types/Types.h"
#include "../Engine.h"
#include "../Image/IMP.h"
#include "../File/PakFile.h"
#include "../File/INIReader.h"
#include "../Types/Types.h"

class Element
{
public:
	Element();
	~Element();	
	void addChild(Element * child);
	void removeChild(Element * child);
	void removeAllChild();
	void changeParent(Element * p);
	void setChildActivated(Element * child, bool activated);

	//��������x,yλ��������Ԫ�ص�����
	void setChildRect(int setLevel = -1);
	unsigned int getResult();
	bool getResult(unsigned int ret);
	int index = -1;
	int type = -1;

protected:
	Engine * engine = NULL;

	static std::vector<Element *> runningElement;

public:

	unsigned char priority = 128;	//���ȼ���0���255��С��Ĭ��128
	ElementType elementType = etElement;
	int elementTypeData = 0;

	std::string name = "Element";

	Element * parent = NULL;
	std::vector<Element *> children = {};
	Time timer;						//��ʱ��
	unsigned int LastTime = 0;

	int dragType = -1;
	int dragIndex = -1;
	int dropIndex = -1;
	int dropType = -1;

public:
	virtual void initAllTime();
	virtual void initTime();
	virtual unsigned int getTime();
	virtual unsigned int getFrameTime();
	virtual void setPaused(bool paused);
public:

	bool visible = true;			//�Ƿ�ɼ���ֻ�пɼ�״̬�ſ���draw�ͼ��������
	bool activated = true;			//�Ƿ񼤻ֻ�д��ڼ���״̬ʱ�ſ���draw�ʹ����¼�

	bool drawFullScreen = false;	//ȫ����ͼԪ�أ�����ʱ��������ȫ��Ԫ�ؿ�ʼ�������������Ԫ��
	bool rectFullScreen = false;	//Ϊtrueʱ������rect���ƣ���ȫ����Χ�������¼�
	bool eventOccupied = false;		//Ϊtrueʱ����ռ�¼��������¼�������Ԫ�ز��ܴ����¼�
	bool coverMouse = true;			//Ϊtrueʱ���ڸ���꣬���������Ԫ���޷���ⴥ���������¼�
	bool needEvents = true;			//�Ƿ���Ҫ�����¼�
	bool onlyCheckRect = false;
	bool needArrangeChild = true;
	bool canDraw = true;

	bool canCallBack = false;		//����ֵ���ûص�����

	bool canDrag = false;			//�Ƿ������ק
	bool canDrop = false;			//�Ƿ���Խ��ܷ���


protected:

	int mouseLDownX = 0;
	int mouseLDownY = 0;
	unsigned int mouseLDownTime = 0;

	bool mouseLeftPressed = false;	//�������������λ��������ʱ��Ч�����������״̬����
	bool mouseMoveIn = false;		//������״̬����
	bool mouseLDownInRect = false;	//������������������

	bool nextFrame = false;

	static bool dragging;
	static int dragParam[2];
	static Element * dragItem;
	int dragX = 0;
	int dragY = 0;
	int dragRange = 1;

protected:
	void reArrangeChildren();
	virtual bool mouseInRect();
	//�Ƚ���ÿ��child�����¼�,�ٴ��������¼�
	void handleEvents(bool vis, bool * canCoverMouse);
	void checkDrag();
	void drawSelf();
	void drawAll();
	void update(bool r, bool events, bool vis, bool * canCoverMouse);
	void updateAll(bool * canCoverMouse);
	void frame();
	bool initial();
	void handleRun();
	void exit();
	void quit();
	bool running = false;
public:
	unsigned int run();
	unsigned int stop(int ret = erNone);
	unsigned int result = erNone;	//ĳЩ����µķ���ֵ
	Rect rect = { 0, 0, 0, 0 };		//Ԫ��ռ�ݵķ�Χ����������������

	void freeAll();
	virtual void freeResource() { result = erNone; };
	virtual void initFromIni(std::string fileName) {};
protected:
	virtual void onEvent() {};
	//�����¼����Ѵ�����true��δ������false��δ������¼���������������Ԫ�ؽ��д���
	virtual bool onHandleEvent(AEvent * e) { return false; };
	//�����봥�����¼�
	virtual void onMouseMoveIn() {};
	//����Ƴ��������¼�
	virtual void onMouseMoveOut() {};
	//���������´������¼�
	virtual void onMouseLeftDown() {};
	//������̧�𴥷����¼�
	virtual void onMouseLeftUp() {};
	//������¼�
	virtual void onClick() {};
	//��ק�����¼�
	virtual void onDrop(Element * src, int param1, int param2) {};
	//��ק�¼�
	virtual void onDrag(int * param1, int * param2) {};
	//���ÿؼ��̳����򴥷��¼�
	virtual void onSetChildRect() {};
	//������ק����קʱÿ֡�������
	virtual void onDragging() {};
	//��ק����ʱ���ã����ڴ˺�����ȡ����ק״̬����������¼�����
	virtual void onDragEnd(Element * dst) {};
	//����ק�Ļ���
	virtual void onDrawDrag() {};
	//���軭�Ķ���д������
	virtual void onDraw() {};
	//��ʼ��ʱ���õ��¼�
	virtual bool onInitial() { return true; };
	//�ڿ�ʼrun���ҳ�ʼ��֮�󴥷����¼�
	virtual void onRun() {};
	//�뿪ʱ�������¼�
	virtual void onExit() {};		
	//��ÿ֡����״̬�Ĵ����¼�
	virtual void onUpdate() {};

public:
	//����Ԫ�ػص�
	virtual void onChildCallBack(Element * child) {};
};
