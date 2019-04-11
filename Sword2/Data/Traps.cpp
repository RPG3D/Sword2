#include "Traps.h"
#include "../Config/Config.h"


Traps::Traps()
{
}


Traps::~Traps()
{
	freeResource();
}

void Traps::load()
{
	freeResource();
	std::string fileName = TRAPS_INI;
	fileName = DEFAULT_FOLDER + fileName;
	ini = new INIReader(Config::getInstance()->getAssetDir() + fileName);
}

void Traps::save()
{
	if (ini == NULL)
	{
		return;
	}
	std::string fileName = TRAPS_INI;
	fileName = DEFAULT_FOLDER + fileName;
	ini->saveToFile(Config::getInstance()->getAssetDir() + fileName);
}

void Traps::freeResource()
{
	if (ini != NULL)
	{
		delete ini;
		ini = NULL;
	}
}

std::string Traps::get(const std::string & mapName, int index)
{
	if (ini == NULL)
	{
		return "";
	}
	std::string name = convert::formatString("%d", index);
	return ini->Get(mapName, name, "");
}

void Traps::set(const std::string & mapName, int index, const std::string & value)
{
	if (ini == NULL)
	{
		std::string fileName = TRAPS_INI;
		fileName = DEFAULT_FOLDER + fileName;
		ini = new INIReader(Config::getInstance()->getAssetDir() + fileName);
	}
	std::string name = convert::formatString("%d", index);
	ini->Set(mapName, name, value);
}
