#include "Script.h"
#include "../GameManager/GameManager.h"

Script::Script(const std::string & n)
{
	name = n;
	loadLib();
	registerFunc();
	runScript(n);
}

Script::Script()
{
	loadLib();
	registerFunc();
}

Script::~Script()
{
	lua_close(luaState);
	luaState = NULL;
}

int Script::runScript(char * s, int len)
{
	if (s != NULL && len > 0)
	{
		printf("RunScript:\n%s\n", s);
		luaL_loadbuffer(luaState, s, len, name.c_str());
		return lua_pcall(luaState, 0, 1, 0);
	}
	return -1;
}

int Script::runScript(const std::string & fileName)
{
	char * s = NULL;
	int len = PakFile::readFile(fileName, &s);
	if (s != NULL && len > 0)
	{
		name = fileName;
		int ret = runScript(s, len);
		delete[] s;
		return ret;
	}
	return -1;
}

void Script::registerFunc()
{
#ifdef regFunc
#undef regFunc
#endif // regFunc
#define regFunc(func) lua_register(luaState, #func, lua_##func);

	regFunc(printf);

	regFunc(Assign);
	regFunc(GetVar);
	regFunc(Add);

	regFunc(Talk);
	regFunc(Say);

	regFunc(FadeIn);
	regFunc(FadeOut);
	regFunc(SetFadeLum);
	regFunc(SetMainLum);
	regFunc(PlayMusic);
	regFunc(StopMusic);
#ifdef PlaySound
#undef PlaySound
#endif
	regFunc(PlaySound);
	regFunc(RunScript);
	regFunc(MoveScreen);
	regFunc(Sleep);
	regFunc(PlayMovie);
	regFunc(StopMovie);

	regFunc(LoadMap);
	regFunc(LoadGame);
	regFunc(SetMapPos);
	regFunc(SetMapTrap);
	regFunc(SaveMapTrap);
	regFunc(SetMapTime);

	regFunc(LoadObj);
	regFunc(SaveObj);
	regFunc(AddObj);
	regFunc(DelObj);
	regFunc(SetObjPos);
	regFunc(SetObjKind);
	regFunc(SetObjScript);
	regFunc(ClearBody);
	regFunc(OpenBox);
	regFunc(CloseBox);

	regFunc(LoadNpc);
	regFunc(SaveNpc);
	regFunc(AddNpc);
	regFunc(DelNpc);
	regFunc(SetNpcRes);
	regFunc(SetNpcScript);
	regFunc(SetNpcDeathScript);
	regFunc(NpcGoto);
	regFunc(NpcGotoEx);
	regFunc(NpcGotoDir);
	regFunc(FollowNpc);
	regFunc(FollowPlayer);
	regFunc(EnableNpcAI);
	regFunc(DisableNpcAI);
	regFunc(NpcAttack);
	regFunc(SetNpcPos);
	regFunc(SetNpcDir);
	regFunc(SetNpcKind);
	regFunc(SetNpcLevel);
	regFunc(SetNpcAction);
	regFunc(SetNpcRelation);
	regFunc(SetNpcActionType);
	regFunc(SetNpcActionFile);
	regFunc(NpcSpecialAction);

	regFunc(LoadPlayer);
	regFunc(SavePlayer);
	regFunc(SetPlayerPos);
	regFunc(SetPlayerDir);
	regFunc(SetPlayerScn);
	regFunc(SetPlayerLum);
	regFunc(SetLevelFile);
	regFunc(SetMagicLevel);
	regFunc(SetPlayerLevel);
	regFunc(SetPlayerState);
	regFunc(EnableRun);
	regFunc(DisableRun);
	regFunc(EnableJump);
	regFunc(DisableJump);
	regFunc(EnableFight);
	regFunc(DisableFight);
	regFunc(PlayerGoto);
	regFunc(PlayerGotoEx);
	regFunc(PlayerRunTo);
	regFunc(PlayerJumpTo);
	regFunc(PlayerGotoDir);

	regFunc(AddLife);
	regFunc(AddLifeMax);
	regFunc(AddThew);
	regFunc(AddThewMax);
	regFunc(AddMana);
	regFunc(AddManaMax);
	regFunc(AddAttack);
	regFunc(AddDefend);
	regFunc(AddEvade);
	regFunc(AddExp);
	regFunc(AddMoney);
	regFunc(AddRandMoney);
	regFunc(AddGoods);
	regFunc(AddRandGoods);
	regFunc(AddMagic);
	regFunc(DelGoods);
	regFunc(DelMagic);
	regFunc(AddMagicExp);
	regFunc(FullLife);
	regFunc(FullThew);
	regFunc(FullMana);
	regFunc(UpdateState);
	regFunc(SaveGoods);
	regFunc(LoadGoods);
	regFunc(ClearGoods);
	regFunc(GetGoodsNum);
	regFunc(GetMoneyNum);
	regFunc(SetMoneyNum);

	regFunc(ShowMessage);
	regFunc(AddToMemo);
	regFunc(ClearMemo);
	regFunc(BuyGoods);
	regFunc(SellGoods);
	regFunc(ReturnToTitle);
	regFunc(EnableInput);
	regFunc(DisableInput);
	regFunc(HideInterface);
	regFunc(HideBottomWnd);
	regFunc(ShowBottomWnd);
	regFunc(HideMouseCursor);
	regFunc(ShowMouseCursor);
	regFunc(ShowSnow);
	regFunc(ShowRandomSnow);
	regFunc(ShowRain);
}

int Script::lua_printf(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		printf("lua_printf: %s\n", lua_tostring(l, 1));
	}
	else
	{
		printf("lua_printf: null str\n");
	}
	return 0;
}

int Script::lua_RunScript(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		std::string n = lua_tostring(l, 1);
		printf("lua_RunScript: %s\n", n.c_str());
		gm->runScript(n);
	}
	return 0;
}

int Script::lua_MoveScreen(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->moveScreen((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_Sleep(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->sleep((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_PlayMovie(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->playMovie(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_StopMovie(lua_State * l)
{
	gm->stopMovie();
	return 0;
}

int Script::lua_LoadMap(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->loadMapWithThread(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_LoadGame(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->loadGameWithThread((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_SetMapPos(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setMapPos((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetMapTrap(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setMapTrap((int)lua_tointeger(l, 1), lua_tostring(l, 2));
	}
	return 0;
}

int Script::lua_SaveMapTrap(lua_State * l)
{
	gm->saveMapTrap();
	return 0;
}

int Script::lua_SetMapTime(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setMapTime((unsigned char)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_LoadObj(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->loadObjectWithThread(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_SaveObj(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->saveObject(lua_tostring(l, 1));
	}
	else
	{
		gm->saveObject();
	}
	return 0;
}

int Script::lua_AddObj(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 4)
	{
		gm->addObject(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3), (int)lua_tointeger(l, 4));
	}
	else if(argc >= 3)
	{
		gm->addObject(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3), 0);
	}
	return 0;
}

int Script::lua_DelObj(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->deleteObject(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_SetObjPos(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->setObjectPosition(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	return 0;
}

int Script::lua_SetObjKind(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setObjectKind(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetObjScript(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setObjectScript(lua_tostring(l, 1), lua_tostring(l, 2));
	}
	return 0;
}

int Script::lua_ClearBody(lua_State * l)
{
	gm->clearBody();
	return 0;
}

int Script::lua_OpenBox(lua_State * l)
{
	gm->openBox();
	return 0;
}

int Script::lua_CloseBox(lua_State * l)
{
	gm->closeBox();
	return 0;
}

int Script::lua_LoadNpc(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->loadNPCWithThread(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_SaveNpc(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->saveNPC(lua_tostring(l, 1));
	}
	else
	{
		gm->saveNPC();
	}
	return 0;
}

int Script::lua_AddNpc(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 4)
	{
		gm->addNPC(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3), (int)lua_tointeger(l, 4));
	}
	else if (argc >= 3)
	{
		gm->addNPC(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3), 0);
	}
	return 0;
}

int Script::lua_DelNpc(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->deleteNPC(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_SetNpcRes(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->setNPCPosition(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	return 0;
}

int Script::lua_SetNpcScript(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setNPCScript(lua_tostring(l, 1), lua_tostring(l, 2));
	}
	return 0;
}

int Script::lua_SetNpcDeathScript(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setNPCDeathScript(lua_tostring(l, 1), lua_tostring(l, 2));
	}
	return 0;
}

int Script::lua_NpcGoto(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->npcGoto(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	else if (argc >= 2)
	{
		gm->playerGoto((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_NpcGotoEx(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->npcGotoEx(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	return 0;
}

int Script::lua_NpcGotoDir(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->npcGotoDir(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	return 0;
}

int Script::lua_FollowNpc(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->followNPC(lua_tostring(l, 1), lua_tostring(l, 2));
	}
	return 0;
}

int Script::lua_FollowPlayer(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->followPlayer(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_EnableNpcAI(lua_State * l)
{
	gm->enableNPCAI();
	return 0;
}

int Script::lua_DisableNpcAI(lua_State * l)
{
	gm->disableNPCAI();
	return 0;
}

int Script::lua_NpcAttack(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->npcAttack(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	return 0;
}

int Script::lua_SetNpcPos(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->setNPCPosition(lua_tostring(l, 1), (int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	return 0;
}

int Script::lua_SetNpcDir(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setNPCDir(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetNpcKind(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setNPCKind(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetNpcLevel(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setNPCLevel(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetNpcAction(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setNPCAction(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetNpcRelation(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setNPCRelation(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetNpcActionType(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setNPCActionType(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetNpcActionFile(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->setNPCActionFile(lua_tostring(l, 1), (int)lua_tointeger(l, 2), lua_tostring(l, 3));
	}
	return 0;
}

int Script::lua_NpcSpecialAction(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->npcSpecialAction(lua_tostring(l, 1), lua_tostring(l, 2));
	}
	return 0;
}

int Script::lua_LoadPlayer(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->loadPlayer(lua_tostring(l, 1));
	}
	else
	{
		gm->loadPlayer();
	}
	return 0;
}

int Script::lua_SavePlayer(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->savePlayer(lua_tostring(l, 1));
	}
	else
	{
		gm->savePlayer();
	}
	return 0;
}

int Script::lua_SetPlayerPos(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 3)
	{
		gm->setPlayerPosition((int)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	else if (argc >= 2)
	{
		gm->setPlayerPosition((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetPlayerDir(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setPlayerDir((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_SetPlayerScn(lua_State * l)
{
	gm->setPlayerScn();
	return 0;
}

int Script::lua_SetPlayerLum(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setPlayerLum((unsigned char)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_SetLevelFile(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setLevelFile(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_SetMagicLevel(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->setMagicLevel(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_SetPlayerLevel(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setPlayerLevel((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_SetPlayerState(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setPlayerState((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_EnableRun(lua_State * l)
{
	gm->enableRun();
	return 0;
}

int Script::lua_DisableRun(lua_State * l)
{
	gm->disableRun();
	return 0;
}

int Script::lua_EnableJump(lua_State * l)
{
	gm->enableJump();
	return 0;
}

int Script::lua_DisableJump(lua_State * l)
{
	gm->disableJump();
	return 0;
}

int Script::lua_EnableFight(lua_State * l)
{
	gm->enableFight();
	return 0;
}

int Script::lua_DisableFight(lua_State * l)
{
	gm->disableFight();
	return 0;
}

int Script::lua_PlayerGoto(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->playerGoto((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_PlayerGotoEx(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->playerGotoEx((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_PlayerRunTo(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->playerRunTo((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_PlayerJumpTo(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->playerJumpTo((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_PlayerGotoDir(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->playerGotoDir((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_AddLife(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addLife((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddLifeMax(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addLifeMax((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddThew(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addThew((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddThewMax(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addThewMax((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddMana(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addMana((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddManaMax(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addManaMax((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddAttack(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addAttack((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddDefend(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addDefend((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddEvade(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addEvade((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddExp(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addExp((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddMoney(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addMoney((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_AddRandMoney(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->addRandMoney((int)lua_tointeger(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_AddGoods(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addGoods(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_AddRandGoods(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addRandGoods(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_AddMagic(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addMagic(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_DelGoods(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->deleteGoods(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_DelMagic(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->deleteMagic(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_AddMagicExp(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->addMagicExp(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_FullLife(lua_State * l)
{
	gm->fullLife();
	return 0;
}

int Script::lua_FullThew(lua_State * l)
{
	gm->fullThew();
	return 0;
}

int Script::lua_FullMana(lua_State * l)
{
	gm->fullMana();
	return 0;
}

int Script::lua_UpdateState(lua_State * l)
{
	gm->updateState();
	return 0;
}

int Script::lua_SaveGoods(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->saveGoods(lua_tostring(l, 1));
	}
	else
	{
		gm->saveGoods();
	}
	return 0;
}

int Script::lua_LoadGoods(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->loadGoods(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_ClearGoods(lua_State * l)
{
	gm->clearGoods();
	return 0;
}

int Script::lua_GetGoodsNum(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->getGoodsNum(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_GetMoneyNum(lua_State * l)
{
	gm->getMoneyNum();
	return 0;
}

int Script::lua_SetMoneyNum(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setMoneyNum((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_ShowMessage(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->showMessage(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_AddToMemo(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->addToMemo(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_ClearMemo(lua_State * l)
{
	gm->clearMemo();
	return 0;
}

int Script::lua_BuyGoods(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->buyGoods(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_SellGoods(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->sellGoods(lua_tostring(l, 1));
	}
	else
	{
		gm->sellGoods();
	}
	return 0;
}

int Script::lua_ReturnToTitle(lua_State * l)
{
	gm->returnToTitle();
	return 0;
}

int Script::lua_EnableInput(lua_State * l)
{
	gm->enableInput();
	return 0;
}

int Script::lua_DisableInput(lua_State * l)
{
	gm->disableInput();
	return 0;
}

int Script::lua_HideInterface(lua_State * l)
{
	gm->hideInterface();
	return 0;
}

int Script::lua_HideBottomWnd(lua_State * l)
{
	gm->hideBottomWnd();
	return 0;
}

int Script::lua_ShowBottomWnd(lua_State * l)
{
	gm->showBottomWnd();
	return 0;
}

int Script::lua_HideMouseCursor(lua_State * l)
{
	gm->hideMouseCursor();
	return 0;
}

int Script::lua_ShowMouseCursor(lua_State * l)
{
	gm->showMouseCursor();
	return 0;
}

int Script::lua_ShowSnow(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->showSnow((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_ShowRandomSnow(lua_State * l)
{
	gm->showRandomSnow();
	return 0;
}

int Script::lua_ShowRain(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->showRain((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_GetVar(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		int value = gm->getVar(lua_tostring(l, 1));
		lua_pushnumber(l, value);
	}
	else
	{
		lua_pushnumber(l, 0);
	}
	return 1;
}

int Script::lua_Assign(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->assign(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_Add(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 2)
	{
		gm->add(lua_tostring(l, 1), (int)lua_tointeger(l, 2));
	}
	return 0;
}

int Script::lua_Talk(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->talk(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_Say(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->say(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_FadeIn(lua_State * l)
{
	gm->fadeIn();
	return 0;
}

int Script::lua_FadeOut(lua_State * l)
{
	gm->fadeOut();
	return 0;
}

int Script::lua_SetFadeLum(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setFadeLum((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_SetMainLum(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->setMainLum((int)lua_tointeger(l, 1));
	}
	return 0;
}

int Script::lua_PlayMusic(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->playMusic(lua_tostring(l, 1));
	}
	return 0;
}

int Script::lua_StopMusic(lua_State * l)
{
	gm->stopMusic();
	return 0;
}

int Script::lua_PlaySound(lua_State * l)
{
	int argc = lua_gettop(l);
	if (argc >= 1)
	{
		gm->playSound(lua_tostring(l, 1));
	}
	return 0;
}

void Script::loadLib()
{
	luaState = luaL_newstate();
	luaL_openlibs(luaState);
	luaopen_base(luaState);
	luaopen_table(luaState);
	luaopen_math(luaState);
	luaopen_string(luaState);
}
