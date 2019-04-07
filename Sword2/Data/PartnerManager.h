#pragma once
#include "NPC.h"
#include <vector>
#include "../GameTypes.h"

class PartnerManager
{
public:
	PartnerManager();
	~PartnerManager();

	//��ȡnpcʱ��ʱ��������partner
	virtual void loadPartner();
	virtual void addPartner();

	virtual void load();
	virtual void save();
	virtual void freeResource();

private:
	std::vector<NPC *> partnerList = {};

};

