#pragma once

#include "File/INIReader.h"
#include "../GameTypes.h"
#include "Engine.h"

class Config
{
public:
	Config();
	~Config();

	static Config * getInstance();

	bool fullScreen = false;
	bool playerAlpha = true;
	bool canChangeDisplayMode = false;

	void load();
	void save();
	float getMusicVolume();
	float getSoundVolume();
	float setMusicVolume(float volume);
	float setSoundVolume(float volume);

	void getWindowSize(int * w, int * h);

	std::string getAssetDir() const
	{
		return AssetDir;
	}

private:
	static Config config;
	static Config * this_;

	std::string AssetDir = "D:/Sword2Data/";

	int windowWidth = DEFAULT_WINDOW_WIDTH;
	int windowHeight = DEFAULT_WINDOW_HEIGHT;
};

