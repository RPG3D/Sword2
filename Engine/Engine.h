/*
	Engineģ����λ��EngineBaseģ���ϲ�����棬����Ϸʵ�ʵ��á�
	EngineBase��װ��SDL��FMOD��FFMPEG��ģ�飬ʵ��������󲿷ֵĵײ㹦�ܡ�
	Engineģ���Ƕ�EngineBase���ٷ�װ���ṩ������Ҫ�ĳ��ýӿں�һЩEngineBase
	ûд��ר�ýӿڣ����罫������������Ϊ�������֡���Ч���Ի��ȣ���
*/

#pragma once

#include "EngineBase.h"

enum MusicType
{
	mtNONE = 0,
	mtMUSIC = 1,
	mtSOUND = 2,
	mtTALK = 4
};

class Engine
{

private:
	static Engine engine;
	static Engine * this_;

	EngineBase* engineBase;

	Time time;

	int width = 800;
	int height = 600;

	bool fullScreen = false;

public:
	Engine();
	~Engine();

	static Engine* getInstance();

	//��ʼ������
	int init(std::string & windowCaption, int windowWidth, int windowHeight, bool isFullScreen);
	//�ͷ�����
	void destroyEngine();
	//��ȡ���ڳߴ�
	void getWindowSize(int* w, int* h);
	//���ô��ڳߴ�
	void setWindowSize(int w, int h);
	//��ȡ�Ƿ�ȫ��
	bool getWindowFullScreen();
	//�����Ƿ�ȫ��
	bool setWindowFullScreen(bool full);
	//����ȫ����ʾģʽ���Ƿ�ı�ֱ���
	bool setWindowDisplayMode(bool dm);

	//���������ʽ
	void setMouseFromImpImage(IMPImage* impImage);

	void setMouseHardware(bool hdCursor);
	bool getMouseHardware();
	void showMouse();
	void hideMouse();
	
	//ʱ���붨ʱ���ӳ���
	//�ײ�������ڴ����¼�ʱ��ͣ��ʱ������ʱ�ƶ����壬�ı䴰���С���¼���ʹ������������
	//getAbsoluteTime()�ӳ��������¼������ʱ�䡣
	//getTime()�������������������ģ�����ͣʱ��

	//�õ�����ʱ��
	unsigned int getAbsoluteTime();
	//��ʼ��engine���ö�ʱ��
	unsigned int initTime();
	//�õ�engine���ö�ʱ����ʱ��
	unsigned int getTime();	
	//��ͣengine���ö�ʱ��
	void setTimePaused(bool paused);
	//��engine���ö�ʱ��Ϊ��׼����ʼ��������ʱ��
	unsigned int initTime(Time * t);
	//��engine���ö�ʱ��Ϊ��׼���õ�������ʱ����ʱ��
	unsigned int getTime(Time * t);
	//��engine���ö�ʱ��Ϊ��׼����ͣ������ʱ��
	void setTimePaused(Time * t, bool paused);
	//���ö�ʱ��ʱ��
	unsigned int setTime(Time * t, unsigned int time);
	//ϵͳ��ʱ�����룩
	void delay(unsigned int t);

	//�õ�֡��
	int getFPS();
	void drawFPS();

	//��ͼ�ӳ���
	_image loadImageFromFile(const std::string & fileName);
	_image loadImageFromMem(char * data, int size);
	int saveImageToFile(_image image, int w, int h, const std::string & fileName);
	int saveImageToFile(_image image, const std::string & fileName);
	int saveImageToMem(_image image, int w, int h, char ** data);
	int saveImageToMem(_image image, char ** data);
	bool pointInImage(_image image, int x, int y);
	_image createNewImageFromImage(_image image);
	void drawImage(_image image, int x, int y);
	void drawImage(_image image, Rect* src, Rect* dst);
	void drawImageWithAlpha(_image image, int x, int y, unsigned char alpha);
	void drawImageWithAlpha(_image image, Rect *src, Rect * dst, unsigned char alpha);
	void drawImageWithColor(_image image, int x, int y, unsigned char r, unsigned char g, unsigned char b);
	void drawImageWithColor(_image image, Rect* src, Rect* dst, unsigned char r, unsigned char g, unsigned char b);
	void setImageColorMode(_image image, unsigned char r, unsigned char g, unsigned char b);
	void setImageAlpha(_image image, unsigned char a);
	void freeImage(_image image);
	int getImageSize(_image image, int * w, int * h);

	//��������ͼ�ӳ���
	_image createBMP16(int w, int h, char * data, int size);
	_image beginSaveScreen();
	_image endSaveScreen();
	int saveImageToBMP16(_image image, int w, int h, char ** s);

	//������ͼ��
	_image createRaindrop();
	_image createSnowflake();
	
	//��������
	void setFontName(const std::string& fontName);
	void setFontFromMem(void * data, int size);
	_image createText(const std::string& text, int size, unsigned int color);
	void drawText(const std::string& text, int x, int y, int size, unsigned int color);
	_image createUnicodeText(const std::wstring& text, int size, unsigned int color);
	void drawUnicodeText(const std::wstring& text, int x, int y, int size, unsigned int color);

	//�����ַ�����ͼƬ�ӳ���
	_image beginDrawTalk(int w, int h);
	_image endDrawTalk();
	void drawSolidUnicodeText(const std::wstring& text, int x, int y, int size, unsigned int color);

	//���ڻ�����Ļ�ڸǣ�һ�������ҹ���ƻ��Լ��׵�������龰����ɫ����
	void setScreenMask(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void drawScreenMask();
	void drawScreenMask(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	//���ڴ�����ͨ����
	_image createMask(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	_image createLumMask();
	//������ͨ����
	void drawMask(_image mask);
	void drawMask(_image mask, Rect * dst);
	//���ƴ����ֵ�ͼƬ
	void drawImageWithMask(_image image, int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void drawImageWithMask(_image image, int x, int y, _image mask);
	void drawImageWithMask(_image image, Rect *src, Rect * dst, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void drawImageWithMask(_image image, Rect *src, Rect * dst, _image mask);
	
	void drawImageWithMaskEx(_image image, int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void drawImageWithMaskEx(_image image, int x, int y, _image mask);
	void drawImageWithMaskEx(_image image, Rect *src, Rect * dst, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void drawImageWithMaskEx(_image image, Rect *src, Rect * dst, _image mask);

	//ѹ����ѹ���ӳ���
	void * getMem(int size);
	void freeMem(void * mem);
	int getLZOOutLen(int inLen);

	//�¼��ӳ���
	int getEventCount();
	int getEvent(AEvent * event);
	void pushEvent(AEvent * event);
	int readEventList(EventList * eList);
	bool getKeyPress(KeyCode key);
	bool getMousePress(MouseButtonCode button);
	void getMouse(int * x, int * y);
	
	//��Ƶ�ӳ���
private:
	float bgmVolume = 1;
	float soundVolume = 1;
	float talkVolume = 1;

	_music bgm = NULL;
	_channel channelBGM = NULL;
	_music talk = NULL;
	_channel channelTalk = NULL;
public:

	//����ͨ�ýӿ�
	_music createMusic(char * data, int size, bool loop, bool music3d, unsigned char priority = 128);
	_music createMusic(const std::string & fileName, bool loop, bool music3d, unsigned char priority = 128);
	void freeMusic(_music music);
	void setMusicPosition(_channel channel, float x, float y);
	void setMusicVolume(_channel channel, float volume);
	_channel playMusic(_music music, float volume);
	_channel playMusic(_music music, float x, float y, float volume);
	void stopMusic(_channel channel);
	void pauseMusic(_channel channel);
	void resumeMusic(_channel channel);
	bool getMusicPlaying(_channel channel);
	bool soundAutoRelease(_music music, _channel channel);

	//����ר�ýӿ�

	//������Ч��Ĭ����������ȡ�Ͳ�������
	_music loadSound(char * data, int size);
	_music loadSound(const std::string & fileName);
	//��ȡѭ�����ŵ���Ч
	_music loadCircleSound(char * data, int size);
	_music loadCircleSound(const std::string & fileName);
	void setSoundVolume(float volume);
	float getSoundVolume();
	_channel playSound(_music music, float x, float y);
	_channel playSound(_music music);

	//���Ž����Զ��ͷ�
	_channel playSound(char * data, int size, float x = 0.0f, float y = 0.0f);

	//���ձ������ֵ�Ĭ����������ȡ�Ͳ�������
	_music loadBGM(char * data, int size);
	_music loadBGM(const std::string & fileName);
	void setBGMVolume(float volume);
	float getBGMVolume();
	_channel playBGM();
	void stopBGM();
	void pauseBGM();
	void resumeBGM();

	//���նԻ�������Ĭ����������ȡ�Ͳ�������
	_music loadTalk(char * data, int size);
	_music loadTalk(const std::string & fileName);
	void setTalkVolume(float volume);
	float getTalkVolume();
	_channel playtalk();
	void stopTalk();
	void pauseTalk();
	void resumeTalk();
	
public:
	//�����ļ����½���Ƶ����
	_video createNewVideo(const std::string& fileName);
	//������Ƶ��ʾ����rect = NULL ʱΪȫ��ģʽ
	void setVideoRect(_video v, Rect * rect);
	//�ͷ���Ƶ����
	void freeVideo(_video v);

	//������Ƶ״̬��������Ƶ��Ƶ�ȣ�Ӧ��ÿ��ѭ���е���
	bool updateVideo(_video v);
	//������Ƶͼ��
	void drawVideoFrame(_video v);

	//�˺����൱�����ε��ã�updateVideo(v);��drawVideoFrame(v);
	bool onVideoFrame(_video v); 

	//����Ƶ����Ϊ����״̬
	void runVideo(_video v);
	//��ͣ��Ƶ
	void pauseVideo(_video v);
	//�ָ���Ƶ
	void resumeVideo(_video v);
	//ֹͣ��Ƶ
	void stopVideo(_video v);
	//��ͷ������Ƶ
	void resetVideo(_video v);
	//������Ƶѭ�����ţ�loopΪѭ��������0Ϊ��ѭ����������ʾһֱѭ��
	void setVideoLoop(_video v, int loop);
	//��Ƶ�Ƿ�ֹͣ����
	bool getVideoStopped(_video v);

	double getVideoTime(_video v);
public:
	//����ÿһ֡������ִ�еĴ�����
	//ÿ֡��ʼǰ����
	void frameBegin();
	//ÿ֡���������
	void frameEnd();

};