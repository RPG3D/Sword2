#pragma once
#include "File/INIReader.h"
#include "File/PakFile.h"
#include "../GameTypes.h"
#include "libconvert/libconvert.h"

class Traps
{
public:
	Traps();
	~Traps();

	std::string get(const std::string & mapName, int index);
	void set(const std::string & mapName, int index, const std::string & value);
	void load();
	void save();
	void freeResource();

private:
	INIReader * ini = NULL;

};

