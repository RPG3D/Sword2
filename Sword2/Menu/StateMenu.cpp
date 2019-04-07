#include "StateMenu.h"
#include "../GameManager/GameManager.h"

StateMenu::StateMenu()
{
	init();
	visible = false;
}

StateMenu::~StateMenu()
{
	freeResource();
}

void StateMenu::updateLabel()
{
	labLevel->setStr(convert::GBKToUnicode(convert::formatString("%d", gm->player.level)));
	labExp->setStr(convert::GBKToUnicode(convert::formatString("%d", gm->player.exp)));
	labExpUp->setStr(convert::GBKToUnicode(convert::formatString("%d", gm->player.levelUpExp)));
	labAttack->setStr(convert::GBKToUnicode(convert::formatString("%d", gm->player.info.attack)));
	labDefend->setStr(convert::GBKToUnicode(convert::formatString("%d", gm->player.info.defend)));
	labEvade->setStr(convert::GBKToUnicode(convert::formatString("%d", gm->player.info.evade)));
	labLife->setStr(convert::GBKToUnicode(convert::formatString("%d/%d", gm->player.life, gm->player.info.lifeMax)));
	labThew->setStr(convert::GBKToUnicode(convert::formatString("%d/%d", gm->player.thew, gm->player.info.thewMax)));
	labMana->setStr(convert::GBKToUnicode(convert::formatString("%d/%d", gm->player.mana, gm->player.info.manaMax)));
}


void StateMenu::init()
{
	freeResource();
	initFromIni("ini\\ui\\state\\window.ini");
	image = addImageContainer("ini\\ui\\state\\Image.ini");
	title = addImageContainer("ini\\ui\\state\\Title.ini");
	labLevel = addLabel("ini\\ui\\state\\Lab�ȼ�.ini");
	labExp = addLabel("ini\\ui\\state\\Lab����.ini");
	labExpUp = addLabel("ini\\ui\\state\\Lab����.ini");
	labAttack = addLabel("ini\\ui\\state\\Lab����.ini");
	labDefend = addLabel("ini\\ui\\state\\Lab����.ini");
	labEvade = addLabel("ini\\ui\\state\\Lab����.ini");
	labLife = addLabel("ini\\ui\\state\\Lab����.ini");
	labThew = addLabel("ini\\ui\\state\\Lab����.ini");
	labMana = addLabel("ini\\ui\\state\\Lab����.ini");
	setChildRect();
}

void StateMenu::onEvent()
{
	updateLabel();
}

void StateMenu::freeResource()
{
	if (impImage != NULL)
	{
		IMP::clearIMPImage(impImage);
		delete impImage;
		impImage = NULL;
	}
	freeCom(image);
	freeCom(title);
	freeCom(labAttack);
	freeCom(labDefend);
	freeCom(labEvade);
	freeCom(labLevel);
	freeCom(labExp);
	freeCom(labExpUp);
	freeCom(labLife);
	freeCom(labMana);
	freeCom(labThew);

}

