#include "main.h"
extern struct gui *menu_titlebar_background;
extern struct gui *menu_background;
extern struct gui *menu_selected_item_bar;
extern struct gui *menu_selected_item_text;

extern struct gui *gta_hp_bar;
extern struct gui *gta_money_hud;

TwBar *twBar_MainMenu;
TwBar *twBar_GeneralCheats;
TwBar *twBar_CarCheats;
TwBar *twBar_FloodCheats;
TwBar *twBar_AimFuncs;
TwBar *twBar_TrollFuncs;
TwBar *twBar_FakeKill;
TwBar *twBar_RakNetCheats;
TwBar* twBar_weaponCheats;
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
TwBar *twBar_Bots;
#endif
TwBar *twBar_Interface;

void runNewMenu()
{
	if (KEY_PRESSED(set.ATB_key))
	{
		if (gta_menu_active()) return;
		if (g_SAMP != NULL) if (g_Scoreboard->iIsEnabled) return;

		cheat_state->_generic.bShowRapidManager ^= 1;
		if (cheat_state->_generic.bShowRapidManager)
			toggleATBCursor(true);
		else
			toggleATBCursor(false);
	}
}
DWORD dwLastUpdate_MenuPopulator;
void menuPopulator()
{
	if (dwLastUpdate_MenuPopulator < (GetTickCount() - 200))
	{
		dwLastUpdate_MenuPopulator = GetTickCount();
	}
}
DWORD menuUpdateHook_origfunc = 0x50B8F0;
void _declspec(naked) menuUpdateHook()
{
	_asm call menuUpdateHook_origfunc
	_asm pushad
	menuPopulator();
	_asm popad
	_asm retn
}
void TW_CALL newcheatsMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_GeneralCheats))
		TwMaximizeBar(twBar_GeneralCheats);
	else
		TwMinimizeBar(twBar_GeneralCheats);
}
void TW_CALL carcheatsMenuLinker(void*)
{
	if (TwIsBarMinimized(twBar_CarCheats))
		TwMaximizeBar(twBar_CarCheats);
	else
		TwMinimizeBar(twBar_CarCheats);
}

void TW_CALL newAimFuncsMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_AimFuncs))
		TwMaximizeBar(twBar_AimFuncs);
	else
		TwMinimizeBar(twBar_AimFuncs);
}
void TW_CALL newInterfaceMenuLinker(void*)
{
	if (TwIsBarMinimized(twBar_Interface))
		TwMaximizeBar(twBar_Interface);
	else
		TwMinimizeBar(twBar_Interface);
}
void TW_CALL newWeaponFuncsLinker(void*)
{
	if (TwIsBarMinimized(twBar_weaponCheats))
		TwMaximizeBar(twBar_weaponCheats);
	else
		TwMinimizeBar(twBar_weaponCheats);
}
void TW_CALL newTrollFuncMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_TrollFuncs))
		TwMaximizeBar(twBar_TrollFuncs);
	else
		TwMinimizeBar(twBar_TrollFuncs);
}
void TW_CALL floodcheatsMenuLinker(void*)
{
	if (TwIsBarMinimized(twBar_FloodCheats))
		TwMaximizeBar(twBar_FloodCheats);
	else
		TwMinimizeBar(twBar_FloodCheats);
}
void TW_CALL newFakeKillMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_FakeKill))
		TwMaximizeBar(twBar_FakeKill);
	else
		TwMinimizeBar(twBar_FakeKill);
}
void TW_CALL rakNetFunctionsMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_RakNetCheats))
		TwMaximizeBar(twBar_RakNetCheats);
	else
		TwMinimizeBar(twBar_RakNetCheats);
}

//void TW_CALL newPacketLoggerMenuLinker(void*)
//{
//	if (TwIsBarMinimized(twBar_PacketLoggers))
//		TwMaximizeBar(twBar_PacketLoggers);
//	else
//		TwMinimizeBar(twBar_PacketLoggers);
//}
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
void TW_CALL botsMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_Bots))
		TwMaximizeBar(twBar_Bots);
	else
		TwMinimizeBar(twBar_Bots);
}
#endif

void TW_CALL interfaceMenu_GetInterfaceColor(void *value, void *clientData)
{
	int iColorID = (int)clientData;

	switch (iColorID)
	{
	case 1:
		*(DWORD*)value = D3DCOLOR_ARGB(menu_titlebar_background->alpha, menu_titlebar_background->red, menu_titlebar_background->green, menu_titlebar_background->blue);
		break;

	case 2:
		*(DWORD*)value = D3DCOLOR_ARGB(menu_background->alpha, menu_background->red, menu_background->green, menu_background->blue);
		break;

	case 3:
		*(DWORD*)value = D3DCOLOR_ARGB(menu_selected_item_bar->alpha, menu_selected_item_bar->red, menu_selected_item_bar->green, menu_selected_item_bar->blue);
		break;

	case 4:
		*(DWORD*)value = D3DCOLOR_ARGB(menu_selected_item_text->alpha, menu_selected_item_text->red, menu_selected_item_text->green, menu_selected_item_text->blue);
		break;

	case 5:
		*(DWORD*)value = D3DCOLOR_ARGB(gta_hp_bar->alpha, gta_hp_bar->red, gta_hp_bar->green, gta_hp_bar->blue);
		break;

	case 6:
		*(DWORD*)value = D3DCOLOR_ARGB(gta_money_hud->alpha, gta_money_hud->red, gta_money_hud->green, gta_money_hud->blue);
		break;

	case 7:
		*(DWORD*)value = sampGetRadarColor(1); // sampGetRadarColor
		break;

	case 8:
		*(DWORD*)value = sampGetRadarColor(2);
		break;

	case 9:
		*(DWORD*)value = sampGetRadarColor(3);
		break;
	}
}

void TW_CALL cmd_chatac(void*)
{
	cheat_state_text("ld_beat:up");
	// INPUT structure for key press
	INPUT input = { 0 };
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = VK_F6;
	// Send key press
	SendInput(1, &input, sizeof(INPUT));
	// Wait for the specified delay
	Sleep(50);
	input.ki.wVk = GTA_KEY_A;
	Sleep(50);
	input.ki.wVk = GTA_KEY_N;
	Sleep(50);
	input.ki.wVk = GTA_KEY_A;
	Sleep(50);
	input.ki.wVk = GTA_KEY_N;
	Sleep(50);
	input.ki.wVk = 0x31;
	Sleep(50);
	input.ki.wVk = 0x33;
	Sleep(50);
	input.ki.wVk = 0x33;
	Sleep(50);
	input.ki.wVk = 0x37;
	SendInput(1, &input, sizeof(INPUT));
	// INPUT structure for key release
	input.ki.dwFlags = KEYEVENTF_KEYUP;

	// Send key release
	SendInput(1, &input, sizeof(INPUT));
}
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
void TW_CALL botsMenu_addBot(void *)
{
	g_BotFuncs->OL_Add_Bot();
}
void TW_CALL botsMenu_delBot(void *)
{
	g_BotFuncs->OL_Delete_Bot();
}
void TW_CALL botsaySomething(void*)
{
	g_BotFuncs->OL_Bot_Say(set.Bots.iBotID_for_Message, set.Bots.BotMessage);
}
void TW_CALL botsMenu_SpawnAll(void*)
{
	for (int i = g_BotFuncs->BotSettings.ClientCount-1; i >= 0; i--)
		g_BotFuncs->OL_Spawn_Bot(i);
}
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
void TW_CALL zombieConnection(void*)
{
	for(int x = g_BotFuncs->BotSettings.ClientCount-1;x>=0;x--)
	g_BotEntity->ConnectAsZombie(x);
}
void TW_CALL ClientZombieConnection(void*)
{
	RakNet::BitStream bs;
	PlayerID playerId = g_RakClient->GetInterface()->GetPlayerID();
	char newRandomNumber[20] = { 0 };

	CSHA1 sha1;
	sha1.Reset();
	sha1.Update((unsigned char*)&playerId.binaryAddress, sizeof(playerId.binaryAddress));
	sha1.Update((unsigned char*)&playerId.port, sizeof(playerId.port));
	sha1.Update((unsigned char*)&(newRandomNumber), 20);
	sha1.Final();

	byte* hash = sha1.GetHash();

	bs.Write((BYTE)ID_SECURED_CONNECTION_CONFIRMATION);
	bs.Write((char*)hash, 20);
	bs.Write("12345678901234567890123456789012", 32);
	g_RakClient->Send(&bs, PacketPriority::SYSTEM_PRIORITY, PacketReliability::RELIABLE, 0);
}
#endif
#endif
void TW_CALL AreYouRageCheater(void*)
{
	set.silentAim.uiMinHitChanceValue = 100;
	cheat_state->Silah.iSpinBotType = ID_SPINTYPE_DOWN;
	set.aimCheatsSettings.iSyncSpinBotTypes = ID_SPINTYPE_DOWN;
	set.silentAim.bFriendFilter = true;
	set.silentAim.bAFKFilter = true;
	set.silentAim.bAliveFilter = true;
	set.silentAim.bVisibleFilter = false;
	//addMessageToChatWindow("Projenin Aimbot Faktörleri Rage olacak þekilde ayarlandý, Ýyi eðlenceler!{00FF00} %s", getPlayerName(g_Players->sLocalPlayerID));
}
void TW_CALL killAllKnife(void*)
{
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i))
		{
			g_RakClient->SendDamage(i, 0, 4, 3);
			g_RakClient->SendDamage(i, 1833.331542, 4, 3);
		}
	}
}
void TW_CALL AreYouLegitCheater(void*)
{ 
	set.silentAim.uiMinHitChanceValue = random(15,50);
	set.silentAim.bFriendFilter = true;
	set.silentAim.bAFKFilter = true;
	set.silentAim.bAliveFilter = true;
	set.silentAim.bVisibleFilter = true;
	//addMessageToChatWindow("Projenin Aimbot Faktörleri Legit olacak þekilde ayarlandý, Ýyi eðlenceler,{00FF00} %s", getPlayerName(g_Players->sLocalPlayerID));
}
void TW_CALL killAllVehicleHit(void*)
{
	for (int x = 0; x < SAMP_MAX_PLAYERS; x++)
	{
		if (IsPlayerStreamed(x))
		{
			g_RakClient->SendGiveDamage(x, 9.9f, 49, 3);
		}
	}
}
void TW_CALL killAllSplat(void*)
{
	for (int x = 0; x < SAMP_MAX_PLAYERS; x++)
	{
		if (IsPlayerStreamed(x))
		{
			g_RakClient->SendGiveDamage(x, 165.0f, 54, 3);
		}
	}
}
void TW_CALL takeDamage(void*)
{
	for (int x = 0; x < SAMP_MAX_PLAYERS; x++)
	{
		if (IsPlayerStreamed(x))
		{
			g_RakClient->TakeDamage(x, 0.0f, WEAPONTYPE_KNIFE, 3);
			g_RakClient->TakeDamage(x, 1833.33154296875, WEAPONTYPE_KNIFE, 3);
		}
	}
}
void TW_CALL killAllServer(void*)
{
	//pPedSelf->GiveWeapon(WEAPONTYPE_KNIFE, 1);
	for (int x = 0; x < SAMP_MAX_PLAYERS; x++)
	{
		if (IsPlayerConnected(x))
		{
			g_RakClient->SendGiveDamage(x, 0.0f, WEAPONTYPE_KNIFE, 3);
			g_RakClient->SendGiveDamage(x, 1833.33154296875, WEAPONTYPE_KNIFE, 3);
		}
	}
}
void TW_CALL fkick(void*)
{
	if (g_RakClient) g_RakClient->SendEnterVehicleNotification(0xFFFF, 0);
	//addMessageToChatWindow("Sunucudan baþarýyla çýkýþ yaptýn. \n Not: Kick/Ban sebebiyle çýkýþ yaptýn.");
}
void TW_CALL fleave(void*)
{
	disconnect(500);
	//addMessageToChatWindow("Sunucudan baþarýyla çýkýþ yaptýn.");
}
void TW_CALL ftimeout(void*)
{
	disconnect(0);
	//addMessageToChatWindow("Sunucudan baþarýyla çýkýþ yaptýn. \n Not: Timeout/Crash sebebiyle çýkýþ yaptýn.");
}
void TW_CALL skyCrasher(void*)
{
	RakNet::BitStream CrashServer;
	CrashServer.Write((BYTE)ID_PLAYER_SYNC); // 207 crash
	CrashServer.Write(NAN);
	g_RakClient->Send(&CrashServer, SYSTEM_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void TW_CALL weaponMenu_GiveWeaponWithAmmo(void*)
{
	pPedSelf->GiveWeapon((eWeaponType)set.WeaponCheats.GiveWeapon_WeaponID, set.WeaponCheats.GiveWeapon_Ammo_Amount);
}
void TW_CALL reconnect(void*)
{
	if (GetTickCount() - set.rejoin_delay > cheat_state->_generic.rejoinTick)
	{
		restartGame();
		disconnect(500);
	//	cheat_state_text("Sunucuya tekrar baðlanýlýyor...");
		cheat_state->_generic.rejoinTick = GetTickCount();
	}
}
void TW_CALL dostEkle(void*)
{
	if (isBadSAMPPlayerID(set.friendFilters.iAddDeleteFriendID) || g_Players->iIsListed[set.friendFilters.iAddDeleteFriendID] != 1)
		return addMessageToChatWindow("Oyuncu ID'si Hatalý.");

	std::ofstream outputFile;
	char filename[512];
	std::string nick;
	std::string del;
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "DostListesi.ini");
	outputFile.open(filename, std::fstream::out | std::fstream::app);

	if (g_Players->pRemotePlayer[set.friendFilters.iAddDeleteFriendID]->strPlayerName.c_str()) // Default : if (g_Players->pRemotePlayer[playerid]->iNameAllocated <= 0xF)
	{
		nick = g_Players->pRemotePlayer[set.friendFilters.iAddDeleteFriendID]->strPlayerName.c_str(); //  Default : nick = g_Players->pRemotePlayer[playerid]->szPlayerName;
	}
	outputFile << nick << "\n";
	outputFile.close();
	addMessageToChatWindow("%s[ID:%d] isimli oyuncu {00FF00}Arkadaþlar listesine eklendi.", nick.c_str(), set.friendFilters.iAddDeleteFriendID);
	/* Eðer girilen nick listede varsa listeden silsin o nicki. */
}
void TW_CALL adminEkle(void*)
{
	if (isBadSAMPPlayerID(set.friendFilters.iAddDeleteAdminID) || g_Players->iIsListed[set.friendFilters.iAddDeleteAdminID] != 1)
		return addMessageToChatWindow("Oyuncu ID'si Hatalý.");

	std::ofstream outputFile;
	char filename[512];
	std::string nick;
	std::string del;
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");
	outputFile.open(filename, std::fstream::out | std::fstream::app);
	if (g_Players->pRemotePlayer[set.friendFilters.iAddDeleteAdminID]->strPlayerName.c_str()) // Default : if (g_Players->pRemotePlayer[playerid]->iNameAllocated <= 0xF)
	{
		nick = g_Players->pRemotePlayer[set.friendFilters.iAddDeleteAdminID]->strPlayerName; //  Default : nick = g_Players->pRemotePlayer[playerid]->szPlayerName;
	}
	outputFile << nick << "\n";
	outputFile.close(); // close it.
	addMessageToChatWindow("%s [ID:%d] isimli oyuncu {00FF00}Adminler listesine eklendi. ", nick.c_str(), set.friendFilters.iAddDeleteAdminID);
}
void TW_CALL adminSil(void*)
{
	if (isBadSAMPPlayerID(set.friendFilters.iAddDeleteAdminID) || g_Players->iIsListed[set.friendFilters.iAddDeleteAdminID] != 1)
		return addMessageToChatWindow("Oyuncu ID'si Hatalý.");

	char filename[512];
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");

	std::vector<std::string> nicklist;
	std::ifstream inputFile; // ERROR -> Redefiniton!! good xd
	std::string nick;

	// That should be it. Let's test. wait

	inputFile.open(filename);
	while (inputFile >> nick)
	{
		if (!strcmp(nick.c_str(), getPlayerName(set.friendFilters.iAddDeleteAdminID)))
			continue;

		nicklist.push_back(nick);
	}

	inputFile.close();

	std::ofstream outputFile; // good song xd xD
	outputFile.open(filename, std::ios::trunc);

	for (int i = 0; i < (int)nicklist.size(); i++)
	{
		nick = nicklist[i];
		outputFile << nick << "\n";
	}

	outputFile.close();
	addMessageToChatWindow("%s [ID:%d] isimli oyuncu Adminler Listesinden {FF0000}SÝLÝNDÝ.", getPlayerName(set.friendFilters.iAddDeleteAdminID), set.friendFilters.iAddDeleteAdminID);
	/* Eðer girilen nick listede varsa listeden silsin o nicki. */
}
void TW_CALL dostSil(void*)
{
	if (isBadSAMPPlayerID(set.friendFilters.iAddDeleteFriendID) || g_Players->iIsListed[set.friendFilters.iAddDeleteFriendID] != 1)
		return addMessageToChatWindow("Oyuncu ID'si Hatalý.");

	char filename[512];
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "DostListesi.ini");

	std::vector<std::string> nicklist;
	std::ifstream inputFile; // ERROR -> Redefiniton!! good xd
	std::string nick;

	inputFile.open(filename);
	while (inputFile >> nick)
	{
		if (!strcmp(nick.c_str(), getPlayerName(set.friendFilters.iAddDeleteFriendID)))
			continue;

		nicklist.push_back(nick);
	}

	inputFile.close();

	std::ofstream outputFile; // good song xd xD
	outputFile.open(filename, std::ios::trunc);

	for (int i = 0; i < (int)nicklist.size(); i++)
	{
		nick = nicklist[i];
		outputFile << nick << "\n";
	}

	outputFile.close();
	addMessageToChatWindow("%s [ID: %d] Nick nameli oyuncu {00FF00} Arkadaþlar listesinden SÝLÝNDÝ.", getPlayerName(set.friendFilters.iAddDeleteFriendID), set.friendFilters.iAddDeleteFriendID);
	/* Eðer girilen nick listede varsa listeden silsin o nicki. */
}

void TW_CALL interfaceMenu_SetInterfaceColor(const void *value, void *clientData)
{
	int iColorID = (int)clientData;
	DWORD dwColor = *(DWORD*)value;

	BYTE byteA, byteR, byteG, byteB;

	byteA = dwColor >> 24; byteR = (dwColor >> 16) & 0xFF;
	byteG = (dwColor >> 8) & 0xFF; byteB = dwColor & 0xFF;

	if (iColorID == 1)
	{
		menu_titlebar_background->alpha = byteA; menu_titlebar_background->red = byteR;
		menu_titlebar_background->green = byteG; menu_titlebar_background->blue = byteB;
	}
	else if (iColorID == 2)
	{
		menu_background->alpha = byteA; menu_background->red = byteR;
		menu_background->green = byteG; menu_background->blue = byteB;
	}
	else if (iColorID == 3)
	{
		menu_selected_item_bar->alpha = byteA; menu_selected_item_bar->red = byteR;
		menu_selected_item_bar->green = byteG; menu_selected_item_bar->blue = byteB;
	}
	else if (iColorID == 4)
	{
		menu_selected_item_text->alpha = byteA; menu_selected_item_text->red = byteR;
		menu_selected_item_text->green = byteG; menu_selected_item_text->blue = byteB;
	}
	else if (iColorID == 5)
	{
		gta_hp_bar->alpha = byteA; gta_hp_bar->red = byteR;
		gta_hp_bar->green = byteG; gta_hp_bar->blue = byteB;
	}
	else if (iColorID == 6)
	{
		gta_money_hud->alpha = byteA; gta_money_hud->red = byteR;
		gta_money_hud->green = byteG; gta_money_hud->blue = byteB;
	}

	else if (iColorID == 7)
		sampSetRadarColor(1, byteA | (byteB << 8) | (byteG << 16) | (byteR << 24));

	else if (iColorID == 8)
		sampSetRadarColor(2, byteA | (byteB << 8) | (byteG << 16) | (byteR << 24));

	else if (iColorID == 9)
		sampSetRadarColor(3, byteA | (byteB << 8) | (byteG << 16) | (byteR << 24));

	if (iColorID == 5 || iColorID == 6)
		UpdateHUDColors(); // UpdateHUDColors
}

void initializeBarsMenu()
{
	if (memcmp_safe((uint8_t *)0x53EB0D, hex_to_bin("E8DECDFCFF"), 5))
	{
		CDetour api;
		if (api.Create((uint8_t *)((uint32_t)0x53EB0D), (uint8_t *)menuUpdateHook, DETOUR_TYPE_CALL_FUNC, 5) == 0)
			Log("Failed to hook menuUpdateHook.");
	}
	else
		Log("Failed to hook menuUpdateHook (memcmp)");

	TwDefine(" TW_HELP visible=false iconified=true ");
	TwDefine(" GLOBAL fontstyle=fixed ");
	TwDefine(" GLOBAL fontsize=3 ");
	char menuParameters[512];
 
	int iMainMenuPosX = pPresentParam.BackBufferWidth / 2 - 400 / 2;
	int iMainMenuPosY = pPresentParam.BackBufferHeight - 275;
	//int iMainMenuPosY = pPresentParam.BackBufferHeight / 2;

	/*sprintf(menuParameters, " Main_Menu label='~ Project Attack v2.3 Delays/Cheatz ~' color='238 130 238' position='%d %d' size='405 235' fontsize='4' iconpos='topright' iconmargin='8 24' valueswidth=150 ", iMainMenuPosX, iMainMenuPosY);*/
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISHNe

#if COMPILE_RINA_RP_CLANS == COMPILE_FOR_WILLSON
	sprintf(menuParameters, " Main_Menu label=' %s ' color='255 0 0' position='%d %d' size='405 235' fontsize='4' iconpos='topright' iconmargin='8 24' valueswidth=150 ", M0D_VERSION,iMainMenuPosX, iMainMenuPosY);
#else
	sprintf(menuParameters, " Main_Menu label=` %s ` color='0 0 0' position='%d %d' size='405 235' fontsize='4' iconpos='topright' iconmargin='8 24' valueswidth=150 ",M0D_VERSION,iMainMenuPosX, iMainMenuPosY);
#endif
	TwDefine(menuParameters);
	
	TwAddSeparator(twBar_MainMenu, NULL, NULL);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 150;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150;

	TwAddButton(twBar_MainMenu, "Cheat_Settings", newcheatsMenuLinker, NULL, " label='Cheat Stuffs' ");

	sprintf(menuParameters, " Cheat_Settings label='Cheat Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ",iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);
	
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (445 / 2) - 175;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 175;

	TwAddButton(twBar_MainMenu, "Car_Hacks", carcheatsMenuLinker, NULL, " label='Car Stuffs' ");

	sprintf(menuParameters, " Car_Hacks label='Car Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ",iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (125 / 2) - 150;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150;

	TwAddButton(twBar_MainMenu, "Aim_Funcs", newAimFuncsMenuLinker, NULL, " label='Aim Stuffs' ");

	sprintf(menuParameters, " Aim_Funcs label='Aim Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (250 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (350 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Weapon_Funcs", newWeaponFuncsLinker, NULL, " label='Weapon Stuffs' ");

	sprintf(menuParameters, " Weapon_Funcs label='Weapon Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Troll_Cheats", newTrollFuncMenuLinker, NULL, " label='Player Troll Stuffs' ");

	sprintf(menuParameters, " Troll_Cheats label='Player Troll Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ",iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Flood_Hacks", floodcheatsMenuLinker, NULL, " label='Chat Stuffs' ");

	sprintf(menuParameters, " Flood_Hacks label='Chat Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;


	//TwAddButton(twBar_MainMenu, "Fake_Kill", newFakeKillMenuLinker, NULL, " label='Fake Kill Settings' ");

	//sprintf(menuParameters, " Fake_Kill label='~ Fake Kill Settings ~' color='255 255 255' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	//TwDefine(menuParameters);

	//iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	//iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "RakNet_Funcs", rakNetFunctionsMenuLinker, NULL, " label='RakNet Stuffs' ");

	sprintf(menuParameters, " RakNet_Funcs label='RakNet Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;

	TwAddButton(twBar_MainMenu, "Interface", newInterfaceMenuLinker, NULL, " label='Interface Stuffs' ");

	sprintf(menuParameters, " Interface label='Interface Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;

#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
	TwAddButton(twBar_MainMenu, "Bot_Options", botsMenuLinker, NULL, " label='RakNet Bot Stuffs' ");

	sprintf(menuParameters, " Bot_Options label='RakNet Bot Stuffs' color='0 0 0' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;
#endif

#else

	sprintf(menuParameters, " Main_Menu label='~ Project Attack v4 ~' color='192 255 192' position='%d %d' size='405 235' fontsize='4' iconpos='topright' iconmargin='8 24' valueswidth=150 ", rand() % 255, rand() % 255, rand() % 255, iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	TwAddSeparator(twBar_MainMenu, NULL, NULL);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 150;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150;

	TwAddButton(twBar_MainMenu, "Cheat_Settings", newcheatsMenuLinker, NULL, " label='Cheats' ");

	sprintf(menuParameters, " Cheat_Settings label='~ Cheats ~' color='192 255 192' position='%d %d' size='405 235' fontsize='6' ", rand() % 255, rand() % 255, rand() % 255, iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Car_Hacks", carcheatsMenuLinker, NULL, " label='Car Cheats' ");

	sprintf(menuParameters, " Car_Hacks label='~ Car Cheats ~' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Aim_Funcs", newAimFuncsMenuLinker, NULL, " label='Aim Funcs/Settings' ");

	sprintf(menuParameters, " Aim_Funcs label='~ Aim Funcs/Settings ~' color='0 255 255' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Weapon_Funcs", newWeaponFuncsLinker, NULL, " label='Weapon Cheats' ");

	sprintf(menuParameters, " Weapon_Funcs label='~ Weapon Cheats ~' color='135 206 235' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Troll_Cheats", newTrollFuncMenuLinker, NULL, " label='Troll Funcs/Settings' ");

	sprintf(menuParameters, " Troll_Cheats label='~ Troll Funcs/Settings ~' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Flood_Hacks", floodcheatsMenuLinker, NULL, " label='Chat Operations Settings' ");

	sprintf(menuParameters, " Flood_Hacks label='~ Chat Operations Settings ~' color='34 156 255' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;


	TwAddButton(twBar_MainMenu, "Fake_Kill", newFakeKillMenuLinker, NULL, " label='Fake Kill Settings' ");

	sprintf(menuParameters, " Fake_Kill label='~ Fake Kill Settings ~' color='255 255 255' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "RakNet_Funcs", rakNetFunctionsMenuLinker, NULL, " label='RakNet Settings' ");

	sprintf(menuParameters, " RakNet_Funcs label='~ RakNet Settings ~' color='0 0 55' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;

#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
	TwAddButton(twBar_MainMenu, "Bot_Options", botsMenuLinker, NULL, " label='RakNet Bot Functions/Settings' ");

	sprintf(menuParameters, " Bot_Options label='~ RakNet Bot Functions/Settings ~' color='0 0 0' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;
#endif

#endif

	//TwAddButton(twBar_GeneralCheats, "Hile ipuclari", ipucuver, NULL, " label='Hile Tüyolari' ");
	TwType ActorFlyType = TwDefineEnum("FlyType", NULL, 0);
	TwAddVarRW(twBar_GeneralCheats, "Player Fly Type", ActorFlyType, &set.General.Actor_Fly_Type, " label='Player Fly Type:' enum='1 { Swim type }, 2 { Bossfly type }, 3 { Bike Driver type } ' ");
	TwAddVarRW(twBar_GeneralCheats, "Dost Etiketi yazi", TW_TYPE_CSSTRING(sizeof(set.D3DFeatures.friendtext)), &set.D3DFeatures.friendtext, " label='Friend 3D Text:' min=1 max=25 group='Visual Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "rainbowhudtitle", TW_TYPE_BOOLCPP, &set.D3DFeatures.Use_Rainbow_Title_for_NewHUD, "label='Rainbow Title:HUD' group='Visual Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "Sunucu bilgisi", TW_TYPE_BOOLCPP, &set.D3DFeatures.bServerInformations, "label='Server Information' group='Visual Settings' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Visual Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "Friend List X Pos", TW_TYPE_FLOAT, &set.D3DFeatures.fXPosFixForFriendList, " label='Dost List | X Position of List' min=-200.0f max=300.0 group='Visual Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "Admin List X Pos", TW_TYPE_FLOAT, &set.D3DFeatures.fXPosFixForAdminList, " label='Admin List | X Position of List' min=-200.0f max=300.0 group='Visual Settings' ");
	TwDefine(" 'Cheat_Settings'/'Visual Settings' opened=false ");

	
	TwAddVarRW(twBar_GeneralCheats, "IBC fOnFootZPos", TW_TYPE_FLOAT, &set.invalidBullets.fOnFootPosZ, " label='Invalid Bullets Crasher(s): OnFoot Z Position[-5.5 = BAN]' min=-6.0 max=15.0 group='Crasher Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "IBCs: Delay", TW_TYPE_INT32, &set.invalidBullets.dwDelayOfInvalidBullets, " label='Invalid Bullets Crasher: Delay(s)' step=25 min=50 max=500 group='Crasher Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "Send Give Damage", TW_TYPE_BOOLCPP, &set.invalidBullets.bSendGiveDamage, " label='Bypass Invalid Bullets Crasher | use RPC_GiveTakeDamage' group='Crasher Settings' ");
	TwDefine(" 'Cheat_Settings'/'Crasher Settings' opened=false ");
	TwType CrasherType = TwDefineEnum("CrasherType", NULL, 0);
	TwAddVarRW(twBar_GeneralCheats, "Invalid Bullets Crasher Type:", CrasherType, &cheat_state->crasher.uiInvalidBulletsCrasherType, " label='uiInvalidBulletsCrasherType' enum='0 { None }, 1 { High Speed }, 2 { Low Speed }, 3 { Negative }' group='Player Crashers' ");

	TwAddVarRW(twBar_GeneralCheats, "IBC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher1, " label='Invalid Bullets Crasher #1' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "IBC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher2, " label='Invalid Bullets Crasher #2' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "IBC #3", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher3, " label='Invalid Bullets Crasher #3' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "IBC #4", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher4, " label='Invalid Bullets Crasher #4' group='Player Crashers' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "RC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iRollCrasher1, " label='Roll Crasher #1' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "RC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iRollCrasher2, " label='Roll Crasher #2' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "RC #3", TW_TYPE_BOOLCPP, &cheat_state->crasher.iRollCrasher3, " label='Roll Crasher #3' group='Player Crashers' ");

	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "DC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iDirectionCrasher1, " label='Direction Crasher #1' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "DC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iDirectionCrasher2, " label='Direction Crasher #2' group='Player Crashers' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "Game Sound Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iGameSoundCrasher, " label='Game Sound Crasher' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "Enter Player Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iEnterPlayerCrasher, " label='Enter Vehicle Crasher' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "Remove Player Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicRemovePlayerCrasher, " label='Detonator Crasher' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "Tuning Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicTuningCrasher, " label='Tuning Crasher' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "Pass Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicPassengerCrasher, " label='Pass Crasher' group='Player Crashers' ");
	TwAddVarRW(twBar_GeneralCheats, "Quarter Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iQuarterCrasher, " label='Quarter Crasher' group='Player Crashers' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Player Crashers' ");
	TwDefine(" 'Cheat_Settings'/'Player Crashers' opened=false ");
	
	TwAddVarRW(twBar_GeneralCheats, "afk", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreAFKs, "label='Target: AFK Filter' group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "dead", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreDEADs, "label='Target: Dead Filter' group='General Settings of Cheats' ");
	TwAddSeparator(twBar_AimFuncs, NULL, NULL);
	TwAddVarRW(twBar_GeneralCheats, "Color", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameColor, "label='Target: Color Filter' group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "skin", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameSkinID, "label='Target: Skin Filter' group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "team", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameTeam, "label='Target: Team Filter' group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "friend", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreMyFriends, "label='Target: Friend Filter' group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "project user", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreProjectUsers, "label='Target: Project Users Filter' group='General Settings of Cheats' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='General Settings of Cheats' ");

	TwAddVarRW(twBar_GeneralCheats, "RapidFire: Delay", TW_TYPE_INT32, &set.WeaponCheats.dwRapidFireDelay, " label='RapidFire:Delay' min=10 max=2500 group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "Rainbow Kullan", TW_TYPE_BOOLCPP, &set.bUseRainbowColors, " label='Use Rainbow for some visuals' group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "Rainbow Delay", TW_TYPE_FLOAT, &set.rainbowdelay, " label='Rainbow: Delay' min=0.100 max=1000.0 group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "MapRun Speed", TW_TYPE_FLOAT, &set.General.MapRun_Speed, " label='MapRun Speed' min=0.5 max=10.0 group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "Unsynch Radius", TW_TYPE_INT32, &set.Unsynch_Radius, " label='Unsynch :Radius' min=20 max=500 group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "Speed Walk", TW_TYPE_FLOAT, &set.General.SpeedWalk_X, " label='Speed Walk : Speed' step=0.1 min=0.1 max=1.0 group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "God Fly: X", TW_TYPE_FLOAT, &set.General.fGodFlySpeed[0], " label='God Fly: X Axis Speed' step=0.1 min=0.1 max=5.0 group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "Unsynch senkronize", TW_TYPE_BOOLCPP, &set.See_How_UnSynch_Works, "label='Unsynch: Sync Position' group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "Dost Etiketi", TW_TYPE_BOOLCPP, &set.D3DFeatures.bDrawFriendTag, " label='Draw Friend Tag' group='General Settings of Cheats' ");
	TwAddVarRW(twBar_GeneralCheats, "Rapid Fire:Teleport sistemi", TW_TYPE_BOOLCPP, &set.WeaponCheats.bTeleportForRapidFire, " label='Rapid Fire: Teleport to Target Player' group='General Settings of Cheats' ");
	TwDefine(" 'Cheat_Settings'/'General Settings of Cheats' opened=false ");

	TwAddVarRW(twBar_GeneralCheats, "Double Gun #1 Delay", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun1_Delay, " label='Double Gun #1: Delay' min=250 max=2000 group='Double Gun: Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Delay", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_Delay, " label='Double Gun #2: Delay' min=250 max=2000 group='Double Gun: Settings' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Double Gun: Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Weapon Slot #1", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_WeaponSlot1, " label='Double Gun #2 Weapon Slot #1' min=0 max=6 group='Double Gun: Settings' ");
	TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Weapon Slot #2", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_WeaponSlot2, " label='Double Gun #2 Weapon Slot #2' min=0 max=6 group='Double Gun: Settings' ");
	TwDefine(" 'Cheat_Settings'/'Double Gun: Settings' opened=false ");

	//TwType gWeapon = TwDefineEnum("gWeapon", NULL, 0);
	//TwAddVarRW(twBar_GeneralCheats, "Weapon Name:", gWeapon, &set.WeaponCheats.GiveWeapon_WeaponID, " label='Weapon Name:' enum='0 {Yumruk}, 1 {Musta}, 2 {Golf Sopasi}, 3 {Jop}, 4 {Bicak}, 5 {Bat}, 6 {Kürek}, 7 {Bilardo Sopasi}, 8 {Katana}, 9 {Testere}, 10 {Dildo #1}, 11 {Dildo #2}, 12 {Vibratör #1}, 13 {Vibratör #2}, 14 {Çiçek}, 15 {Cane}, 16 {Bomba}, 17 {Gaz Bombasi}, 18 {Molotof}, 22 {Colt45}, 23 {Susturuculu Colt45}, 24 {Deagle}, 25 {Shotgun}, 26 {Sawn Off Shotgun}, 27 {Combat Shotgun}, 28 {Uzi}, 29 {MP5}, 30 {AK47}, 31 {M4}, 32 {TEC9}, 33 {Cuntgun}, 34 {Sniper}, 35 {Roket}, 36 {Isi Duyarli Roket}, 37 {Alev Püskürtücü}, 38 {Minigun}' group='Give Weapon' ");
	//TwAddVarRW(twBar_GeneralCheats, "Weapon Ammo:", TW_TYPE_INT32, &set.WeaponCheats.GiveWeapon_Ammo_Amount, " label='Weapon Ammo:' step=100 min=1 max=10000 group='Give Weapon' ");
	//TwAddButton(twBar_GeneralCheats, "Get Gun", weaponMenu_GiveWeaponWithAmmo, NULL, " label='Get Gun' group='Give Weapon' ");
	//TwDefine(" 'Cheat_Settings'/'Give Weapon' opened=false ");


	TwAddVarRW(twBar_GeneralCheats, "Admin Ekle ID", TW_TYPE_INT32, &set.friendFilters.iAddDeleteAdminID, " label=`Add Admin ID:` step=1 min=1 max=1000 group='Admin List: Add/Remove' ");
	TwAddButton(twBar_GeneralCheats, "Seçili ID Admin Ekle", adminEkle, NULL, " label=`Add Selected ID as Admin` group='Admin List: Add/Remove' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Admin List: Add/Remove' ");
	TwAddButton(twBar_GeneralCheats, "Seçili ID Admin Sil", adminSil, NULL, " label=`Remove Selected ID from Admin List` group='Admin List: Add/Remove' ");
	TwDefine(" 'Cheat_Settings'/'Admin List: Add/Remove' opened=false ");

	TwAddVarRW(twBar_GeneralCheats, "Dost Ekle ID", TW_TYPE_INT32, &set.friendFilters.iAddDeleteFriendID, " label=`Add Friend ID:` step=1 min=1 max=1000 group='Friend List: Add/Remove' ");
	TwAddButton(twBar_GeneralCheats, "Seçili ID Dost Ekle", dostEkle, NULL, " label=`Add Selected ID as Friend` group='Friend List: Add/Remove' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Friend List: Add/Remove' ");
	TwAddButton(twBar_GeneralCheats, "Seçili ID Dosttan Sil", dostSil, NULL, " label=`Remove Selected ID from Friend List` group='Friend List: Add/Remove' ");
	TwDefine(" 'Cheat_Settings'/'Friend List: Add/Remove' opened=false ");

	//TwAddVarRW(twBar_GeneralCheats, "Rainbow", TW_TYPE_BOOLCPP, &set.renderPlayerTagSettings.bRainbow, "label='Rainbow Kullan' group='Render Player Tag: Ayarlar' ");
	//TwAddVarRW(twBar_GeneralCheats, "status tag", TW_TYPE_BOOLCPP, &set.statusTag, "label='Player Status Kullan' group='Render Player Tag: Ayarlar' ");
	//TwAddVarRW(twBar_GeneralCheats, "Weapon name tag", TW_TYPE_BOOLCPP, &set.seeWeaponTags, "label='Weapon Name Kullan' group='Render Player Tag: Ayarlar' ");
	//
	TwAddVarRW(twBar_GeneralCheats, "Triangle Tracer", TW_TYPE_BOOLCPP, &cheat_state->Wallhack.iTriangleESP, "label='Triangle Tracer' ");
	TwAddVarRW(twBar_GeneralCheats, "Pentagram Tracer", TW_TYPE_BOOLCPP, &cheat_state->Wallhack.iPentagramESP, "label='Pentagram Tracer' ");

	TwAddVarRW(twBar_CarCheats, "Car Remote Control", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCarRemoteControl, " label='Car Remote Control' group='Car Remote Control' ");
	TwAddVarRW(twBar_CarCheats, "Car Remote Control With Driver", TW_TYPE_BOOLCPP, &set.CarCheats.car_remote_control_with_driver, " label='Car Remote Control With Driver' group='Car Remote Control' ");
	TwAddVarRW(twBar_CarCheats, "Car Remote Control Without Driver", TW_TYPE_BOOLCPP, &set.CarCheats.car_remote_control_without_driver, " label='Car Remote Control Without Driver' group='Car Remote Control' ");
	TwDefine(" 'Car_Hacks'/'Car Remote Control' opened=false ");
	
	TwAddVarRW(twBar_CarCheats, "Car Lag X Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[0], " label='Car Lag: X+ Coords' min=-10 max=150  group='Car Lagger: Coordinate Settings' ");
	TwAddVarRW(twBar_CarCheats, "Car Lag Y Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[1], " label='Car Lag: Y+ Coords' min=-10 max=150  group='Car Lagger: Coordinate Settings' ");
	TwAddVarRW(twBar_CarCheats, "Car Lag Z Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[2], " label='Car Lag: Z+ Coords' min=-15 max=50   group='Car Lagger: Coordinate Settings' ");
	TwAddSeparator(twBar_CarCheats, NULL, "group='Car Lagger: Coordinate Settings' ");
	TwDefine(" 'Car_Hacks'/'Car Lagger: Coordinate Settings' opened=false ");

	TwAddVarRW(twBar_CarCheats, "Car Sun Angle", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Angle, " label='Car Sun: Angle' step=10.0 min=0.0 max=180.00  ");
	TwAddVarRW(twBar_CarCheats, "Car Sun Z Height", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Z_Position_Height, " label='Car Sun: Z+ Height' step=10.0 min=0.0 max=100.00  ");
	TwAddVarRW(twBar_CarCheats, "Car Sun Abs Speed", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Abs_Speed, " label='Car Sun: Speed' step=10.0 min=0.0 max=100.00  ");
	TwAddVarRW(twBar_CarCheats, "Car Sun Degree To Radian Value", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Degree_To_Radian_Value, " label='Car Sun: Radian Value' step=10.0 min=5.0 max=200.00  ");
	TwAddSeparator(twBar_CarCheats, NULL, "");

	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Use Random Z Height", TW_TYPE_BOOLCPP, &set.CarCheats.bCarCircle_Use_Random_Z_Height, " label='Car Circle #2: Use Random Z Height'   ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Minimum Random Value", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Z_Height_Minimum_Value, " label='Car Circle #2:Random Z Minimum Value:' step=6.0 min=7.0 max=50.00   ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Maximum Random Value", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Z_Height_Maximum_Value, " label='Car Circle #2:Random Z Maximum Value:' step=6.0 min=7.0 max=50.00   ");
	TwAddSeparator(twBar_CarCheats, NULL, "");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Use Random Radius", TW_TYPE_BOOLCPP, &set.CarCheats.bCarCircle_Use_Random_Radius, " label='Car Circle #2:Use Random Radius'   ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Minimum Random Value for Radius", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Radius_Minimum_Value, " label='Car Circle #2:Random Radius Minimum Value:' step=6.0 min=7.0 max=90.00   ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Maximum Random Value for Radius", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Radius_Maximum_Value, " label='Car Circle #2:Random Radius Maximum Value:' step=6.0 min=7.0 max=90.00   ");
	TwAddSeparator(twBar_CarCheats, NULL, "");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Radius", TW_TYPE_FLOAT, &set.CarCheats.CarCircle3_Radius, " label='Car Circle #2:Radius' step=6.0 min=7.0 max=150.00   ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Z Height", TW_TYPE_FLOAT, &set.CarCheats.CarCircle_Z_Height, " label='Car Circle #2:Z Axis' step=6.0 min=2.0 max=70.00   ");
	TwAddSeparator(twBar_CarCheats, NULL, "");

	TwAddVarRW(twBar_CarCheats, "Car Floating #3:X Max Random Value", TW_TYPE_INT32, &set.CarCheats.fCarFloating3_Random_Value[0], " label='Floating Cars #3:X Axis Random Minimum Value:' step=10 min=15 max=350 group='Floating Cars #3: Settings' ");
	TwAddVarRW(twBar_CarCheats, "Car Floating #3:Y Max Random Value", TW_TYPE_INT32, &set.CarCheats.fCarFloating3_Random_Value[1], " label='Floating Cars #3:Y Axis Random Minimum Value:' step=10 min=15 max=350 group='Floating Cars #3: Settings' ");
	TwAddVarRW(twBar_CarCheats, "Car Floating #3:Z Height", TW_TYPE_FLOAT, &set.CarCheats.fCarFloating3_Z_Height, " label='Floating Cars #3:Z Height' step=6.0 min=3.0 max=70.00 group='Floating Cars #3: Settings' ");
	TwDefine(" 'Car_Hacks'/'Floating Cars #3: Settings' opened=false ");

	TwAddVarRW(twBar_CarCheats, "Crazy Car #1 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar1_Delay, " label='Crazy Car #1: Delay' step=100 min=100 max=4500 group='Crazy Car: Settings' ");
	TwAddVarRW(twBar_CarCheats, "Crazy Car #2 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar2_Delay, " label='Crazy Car #2: Delay' step=100 min=100 max=4500 group='Crazy Car: Settings' ");
	TwAddVarRW(twBar_CarCheats, "Crazy Car #3 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar3_Delay, " label='Crazy Car #3: Delay' step=100 min=100 max=4500 group='Crazy Car: Settings' ");
	TwAddVarRW(twBar_CarCheats, "Crazy Car #4 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar4_Delay, " label='Crazy Car #4: Delay' step=100 min=100 max=4500 group='Crazy Car: Settings' ");
	TwDefine(" 'Car_Hacks'/'Crazy Car: Settings' opened=false ");
	TwAddVarRW(twBar_CarCheats, "Car Lagger", TW_TYPE_BOOLCPP, &cheat_state->Arac.iCarLagger, " label='Car Lagger' ");

	//TwAddSeparator(twBar_CarCheats, NULL, "group='Car Colorleri #1-#4: Ayarlar' ");

	/*
		Added Delay settings for Crazy Car #1, #2, #3, #4.
		iTroll Places is changed.. It is on F2 menu -> Troll Cheats menu anymore.
	*/

	/*
	<- Aim Functions & Aim Fonksiyonlarý ->
	*/
	TwAddButton(twBar_AimFuncs, "Rage Hacking", AreYouRageCheater, NULL, " label='Click to set RAGE settings!' ");
	TwAddButton(twBar_AimFuncs, "Legit Hacking", AreYouLegitCheater, NULL, " label='Click to set Legit settings!' ");
	TwAddSeparator(twBar_AimFuncs, NULL, NULL);
	TwType AimBotType = TwDefineEnum("AimBotType", NULL, 0); 
	TwAddVarRW(twBar_AimFuncs, "AimBot Lock To:", AimBotType, &set.AutoAimPozisyon, " label='Skin Aimbot: Target Body Pos' enum='0 {OFF: Head}, 1 {Pelvis #1}, 2 {Pelvis #2}, 3 {Spine #1}, 4 {Upper Torso}, 5 {Neck}, 6 {Right Upper Torso}, 8 {Right Shoulder}' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim2", TW_TYPE_BOOLCPP, &cheat_state->Silah.bSilentAimV2, " label='Real Silent Aimbot' ");

	TwAddVarRW(twBar_AimFuncs, "SilentAim", TW_TYPE_BOOLCPP, &cheat_state->Silent.bSilent, " label='Silent Aimbot' ");
	TwAddVarRW(twBar_AimFuncs, "Shoot Through Walls", TW_TYPE_BOOLCPP, &cheat_state->Silah.iShooting_Through_Walls, " label='Shoot Through Walls' ");
	TwAddSeparator(twBar_AimFuncs, NULL, NULL);
	TwAddVarRW(twBar_AimFuncs, "Only headshots", TW_TYPE_BOOLCPP, &set.silentAim.bOnlyHeadShots, " label='Silent Aimbot: Only Headshots' ");
	TwAddVarRW(twBar_AimFuncs, "Silent Aimbot: Do Not Send Damage RPC", TW_TYPE_BOOLCPP, &set.silentAim.bDoNotSendDamageRPC, " label='Silent Aimbot: Do Not Send Damage RPC' ");
	TwAddVarRW(twBar_AimFuncs, "Silent Aimbot: Do Not Use Local Pos", TW_TYPE_BOOLCPP, &set.silentAim.bDoNotUseLocalPlayerPos, " label='Silent Aimbot: Do Not Use Local Pos' ");
	TwAddVarRW(twBar_AimFuncs, "Silent Aimbot: Use Aim Sync Support", TW_TYPE_BOOLCPP, &set.silentAim.bUseAimSyncSupport, " label='Silent Aimbot: Use Aim Sync Support' ");
	TwAddVarRW(twBar_AimFuncs, "Use Centers", TW_TYPE_BOOLCPP, &set.silentAim.bUseHitCenter, " label='Silent Aimbot: Use Centers' ");
	TwAddSeparator(twBar_AimFuncs, NULL, NULL);
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Hit Chance", TW_TYPE_INT32, &set.silentAim.uiMinHitChanceValue, " label='Silent Aimbot: Hit Chance' min=5 max=100 ");
	TwAddSeparator(twBar_AimFuncs, NULL, NULL);
	TwType targetType = TwDefineEnum("targetType", NULL, 0);
	TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: Hedef Çizim Türü", targetType, &set.silentAim.targetType, " label='Silent Aimbot: Target Draw Type' enum='0 { Text }, 1 { None }' ");
	//TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Circle Radius", TW_TYPE_FLOAT, &set.silentAim.fCircleRadius, " label='SilentAim:Daire Büyüklügü' min=5.0 max=500.0 group='Silent Aimbot: Target Information #1' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " ");

	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Draw Target Bones", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDrawTargetBones, " label='Silent Aimbot: Target Bone' ");
	TwType colorType1 = TwDefineEnum("ColorType1", NULL, 0);
	TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: Bone Çizimi", colorType1, &set.silentAim.iDrawBoneColor, " label='Target Bone:Color' enum='0 { Use Player Color }, 1 { Red }, 2 { Green }, 3 { Blue }, 4 { Black }, 5 { White }, 6 { Gold }, 7 { Silver }, 8 { Midnight }, 9 { Aqua }, 10 { Maroon }, 11 { Rainbow }' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " ");

	TwType colorType2 = TwDefineEnum("ColorType2", NULL, 0);
	TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: ESP: Aç ", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDrawTargetBox, " label='Silent Aimbot:Target ESP Box' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: Box Çizimi", colorType1, &set.silentAim.iDrawBoxColor, " label='Target Box:Color' enum='0 { Use Player Color }, 1 { Red }, 2 { Green }, 3 { Blue }, 4 { Black }, 5 { White }, 6 { Gold }, 7 { Silver }, 8 { Midnight }, 9 { Aqua }, 10 { Maroon }, 11 { Rainbow }' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " ");

	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Out Of Range", TW_TYPE_BOOLCPP, &set.silentAim.bOutOfRange, " label='Silent Aimbot: Range Filter' group='Silent Aimbot: Target Filters' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aimbot: Target Filters' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Same Team Filter", TW_TYPE_BOOLCPP, &set.silentAim.bTeamFilter, " label='Silent Aimbot: Team Filter' group='Silent Aimbot: Target Filters' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Nick Name Color Filter", TW_TYPE_BOOLCPP, &set.silentAim.bColorFilter, " label='Silent Aimbot: Nick Color Filter' group='Silent Aimbot: Target Filters' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Skin Filter", TW_TYPE_BOOLCPP, &set.silentAim.bSkinFilter, " label='Silent Aimbot: Skin Filter' group='Silent Aimbot: Target Filters' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aimbot: Target Filters' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Visible Target Filter", TW_TYPE_BOOLCPP, &set.silentAim.bVisibleFilter, " label='Silent Aimbot: Visible Target Filter' group='Silent Aimbot: Target Filters' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> AFK Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAFKFilter, " label='Silent Aimbot: AFK Filter' group='Silent Aimbot: Target Filters' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Alive Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAliveFilter, " label='Silent Aimbot: Dead Filter' group='Silent Aimbot: Target Filters' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aimbot: Target Filters' ");
	// NPC Filterne gerek yok...
	//TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore NPCs Filter", TW_TYPE_BOOLCPP, &cheat_state->Silah.iSAim_IgnoreNPCs, " label='Silent Aimbot: NPC Filter' group='Silent Aimbot: Target Filters' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore Admins[IN ADMINS LIST] Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAdminFilter, " label='Silent Aimbot: Admin Filter' group='Silent Aimbot: Target Filters' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore Friends[IN FRIENDS LIST] Filter", TW_TYPE_BOOLCPP, &set.silentAim.bFriendFilter, " label='Silent Aimbot: Friend Filter' group='Silent Aimbot: Target Filters' ");
	TwDefine(" 'Aim_Funcs'/'Silent Aimbot: Target Filters' opened=true ");
	
	TwType spinType = TwDefineEnum("spinSettings", NULL, 0);
	TwAddVarRW(twBar_AimFuncs, "SpinBot Type", spinType, &cheat_state->Silah.iSpinBotType, " label='Spinbot Type:' enum='0 { Off }, 1 { Look Down }, 2 { Look Up }, 3 { Random Looking }' group='Spinbot' ");
	TwDefine(" 'Aim_Funcs'/'Spinbot' opened=false ");

	TwAddVarRW(twBar_AimFuncs, "SyncSpinBot", TW_TYPE_BOOLCPP, &set.aimCheatsSettings.iSyncSpinBotTypes, " label='SpinBot:Sync' group='Aim Sync' ");
	TwAddVarRW(twBar_AimFuncs, "InvalidAimZ:Sync", TW_TYPE_BOOLCPP, &set.aimCheatsSettings.bSyncInvalidAimZPed, " label='Aim Z:Sync' group='Aim Sync' ");
	TwDefine(" 'Aim_Funcs'/'Aim Sync' opened=false ");
	
	TwAddVarRW(twBar_weaponCheats, "Silah Hilesi Atlatma Yöntemi #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon, " label='Bypass Weapon Cheat' ");
	TwAddSeparator(twBar_weaponCheats, NULL, ""); 
	TwAddVarRW(twBar_weaponCheats, "Bullet bugger", TW_TYPE_BOOLCPP, &cheat_state->Silah.bBulletBugger, " label='Bullet Bugger' ");
	TwAddVarRW(twBar_weaponCheats, "DamageCheat", TW_TYPE_BOOLCPP, &cheat_state->Silah.damage, NULL);
	TwAddVarRW(twBar_weaponCheats, "RapidFire", TW_TYPE_BOOLCPP, &cheat_state->Silah.iRapidFire, " label='Rapid Fire' ");
	TwAddVarRW(twBar_weaponCheats, "RTD", TW_TYPE_BOOLCPP, &cheat_state->Silah.iReturnTheDamage, " label='Return the Damage' ");
	TwAddVarRW(twBar_weaponCheats, "No Reload", TW_TYPE_BOOLCPP, &cheat_state->Silah.iNoReloadBug, " label='No Reload' ");
	TwAddVarRW(twBar_weaponCheats, "Oto 2-2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAuto2_2, " label='Auto 2-2(SawnOff)' ");
	TwAddVarRW(twBar_weaponCheats, "No Recoil", TW_TYPE_BOOLCPP, &cheat_state->Silah.iNoRecoil, " label=' No Recoil' ");
	TwAddSeparator(twBar_weaponCheats, NULL, NULL);
	TwAddVarRW(twBar_weaponCheats, "Oto C bug #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAutoCbug1, " label='Auto C-Bug #1'");
	TwAddVarRW(twBar_weaponCheats, "Oto C bug #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAutoCbug2, " label='Auto C-Bug #2'");
	TwAddSeparator(twBar_weaponCheats, NULL, NULL);
	TwAddVarRW(twBar_weaponCheats, "Double Silah #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDoubleGun1, " label='Double Gun #1' ");
	TwAddVarRW(twBar_weaponCheats, "Çifte Silah #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDoubleGun2, " label='Double Gun #2' ");
	TwAddSeparator(twBar_weaponCheats, NULL, NULL);
	TwAddVarRW(twBar_weaponCheats, "Silah Katlayici kullan", TW_TYPE_BOOLCPP, &cheat_state->Silah.bWeaponDamageMultiplier, " label='Enable Damage Multiplier'");
	TwAddVarRW(twBar_weaponCheats, "Silah Hasar Katlayici", TW_TYPE_INT32, &set.WeaponCheats.Weapon_Damage, " label='Weapon Damage Multiplier Time:'");
	//DETECTOR_PROJECTVERSION_ID
	TwType iTrollType = TwDefineEnum("iTrollType", NULL, 0); // cheat_state->Troll.iInvisible5
	TwAddVarRW(twBar_TrollFuncs, "iTroll Type", iTrollType, &cheat_state->Troll.iTroll, " label='iTroll Türü:' enum='0 { iTroll KAPALI }, 1 { Yerin Altina Sok }, 2 { Speed Ver }, 3 { Patlat Ve Uçur #1 }, 4 { Patlat ve Uçur #2 }, 5 { 360 Derece Döndür }, 6 { Ters Çevir }, 7 { Patlat }, 8 { Çekiciye Teleport Et }, 9 { Ziplat }, 10 { Haritanin Ortasina Teleport Et }, 11 { Denize Teleport Et }, 12 { Durdur }, 13 { Çukura Teleport Et }, 14 { HP Ayarla }, 15 { Rastgele HP Ayarla }, 16 { Rastgele Eksen Degeri }, 17 { Rastgele Koordinat }, 18 { Hileli Z Koordinati + Patlama }, 19 { Arabadan At }' ");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
	TwAddVarRW(twBar_TrollFuncs, "iTroll: HP degeri", TW_TYPE_FLOAT, &set.itrollSettings.fSetHP, " label='iTroll:Set Car HP' min=1.0 max=1000.0 ");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
	TwAddVarRW(twBar_TrollFuncs, "Invisible Bike", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisibleBike, " label='Invisible Bike' ");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
	//TwAddVarRW(twBar_TrollFuncs, "Invisible Cars", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCarInvisible, " label='Görünmezlik[Car]' ");
	TwAddVarRW(twBar_TrollFuncs, "Delete Cars #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iRemoveCars, " label='Delete Cars #1' ");
	TwAddVarRW(twBar_TrollFuncs, "Delete Cars #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iRemoveCars2, " label='Delete Cars #2' ");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
	TwAddVarRW(twBar_TrollFuncs, "Kickup", TW_TYPE_BOOLCPP, &cheat_state->Troll.iKickup, " label='Car Kicker' ");
	TwAddVarRW(twBar_TrollFuncs, "Vehicle Deformer", TW_TYPE_BOOLCPP, &cheat_state->Arac.iVehicleDeformer, " label='Vehicle Deformer' ");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
	TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Enable", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCircleTroll, " label='Circle Troll' ");
	TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Target ID", TW_TYPE_INT32, &set.TrollCheats.CircleTrollTargetID, " label='Circle Troll: Target ID' min=0 max=1000 ");
	TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Spin Speed", TW_TYPE_INT32, &set.TrollCheats.CircleTroll_Spin_Speed, " label='Circle Troll: Spin Speed' min=0 max=100");
	TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Circle Radius", TW_TYPE_INT32, &set.TrollCheats.CircleTroll_Circle_Radius, " label='Circle Troll: Circle Radius' min=1 max=100");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
	TwAddVarRW(twBar_TrollFuncs, "Player Copier: Enable", TW_TYPE_BOOLCPP, &cheat_state->Troll.iPlayerCopier, " label='Player Copier'");
	TwAddVarRW(twBar_TrollFuncs, "Player Copier: Target ID", TW_TYPE_INT32, &set.TrollCheats.iPlayerCopier_TargetID, " label='Player Copier: Target ID' min=0 max=1000 ");
	TwAddVarRW(twBar_TrollFuncs, "Player Copier: Sync Player Copier", TW_TYPE_BOOLCPP, &set.TrollCheats.bSyncPlayerCopier, " label='Player Copier: Sync Player Copier' ");


	TwAddVarRW(twBar_TrollFuncs, "Invisibility #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible1, " label='Invisibility #1' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible2, " label='Invisibility #2' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #3", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible3, " label='Invisibility #3' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #4", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible4, " label='Invisibility #4' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #5", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible5, " label='Invisibility #5' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #6", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible6, " label='Invisibility #6' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #7", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible7, " label='Invisibility #7' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #8", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible8, " label='Invisibility #8' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #9", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible9, " label='Invisibility #9' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #10", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible10, " label='Invisibility #10' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #11", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible11, " label='Invisibility #11' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #12", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible12, " label='Invisibility #12' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #13", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible13, " label='Invisibility #13' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #14", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible14, " label='Invisibility #14' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #15", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible15, " label='Invisibility #15' group=`Invisibility's` ");
	TwAddVarRW(twBar_TrollFuncs, "Invisibility #16", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible16, " label='Invisibility #16' group=`Invisibility's` ");

	TwDefine(" 'Troll_Cheats'/`Invisibility's` opened=true ");

	TwAddVarRW(twBar_TrollFuncs, "Slapper #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iPlayerFucker, " label='Slapper #1' group='Slappers(Player Trollers)' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iHeadWalkSlapper, " label='Slapper #2' group='Slappers(Player Trollers)' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #3", TW_TYPE_BOOLCPP, &cheat_state->Troll.iQuaSlapper, " label='Slapper #3' group='Slappers(Player Trollers)' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #4", TW_TYPE_BOOLCPP, &cheat_state->Troll.iSpeedKicker, " label='Slapper #4' group='Slappers(Player Trollers)' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #5", TW_TYPE_BOOLCPP, &cheat_state->Troll.iActorShooter, " label='Slapper #5' group='Slappers(Player Trollers)' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #6", TW_TYPE_BOOLCPP, &cheat_state->Troll.iElevator, " label='Slapper #6' group='Slappers(Player Trollers)' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #7", TW_TYPE_BOOLCPP, &cheat_state->Troll.iJetpackElevator, " label='Slapper #7' group='Slappers(Player Trollers)' ");
	TwDefine(" 'Troll_Cheats'/'Slappers(Player Trollers)' opened=false ");

	TwAddVarRW(twBar_TrollFuncs, "Anti Aim", TW_TYPE_BOOLCPP, &cheat_state->Troll.bAntiAim, "label='Anti-Aim' ");

	TwAddVarRW(twBar_FloodCheats, "Spammer #1 Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.Project_Spammer1_Text)), &set.ChatHacks.Project_Spammer1_Text, " label='Flooder #1: Text' group='Spammer: Text Settings' ");
	//TwAddVarRW(twBar_FloodCheats, "Spammer #2 Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.Project_Spammer2_Text)), &set.ChatHacks.Project_Spammer2_Text, " label='Flooder #2 Text' group='Flooder Text Settings' ");
	TwDefine(" 'Flood_Hacks'/'Spammer: Text Settings' opened=false ");

	TwAddVarRW(twBar_FloodCheats, "Spammer #1 -> Run Delay", TW_TYPE_INT32, &set.ChatHacks.Project_Spammer1_Run_Delay, " label='Flooder #1: Delay' min=50 max=10000 group='Spammer: Delay Settings' ");
	//TwAddVarRW(twBar_FloodCheats, "Spammer #2 -> Run Delay", TW_TYPE_INT32, &set.ChatHacks.Project_Spammer2_Run_Delay, " label='Flooder #2 -> Run Delay' min=50 max=10000 group='Flooder Delay/Run Settings' ");
	TwDefine(" 'Flood_Hacks'/'Spammer: Delay Settings' opened=false ");

	TwType FlooderType = TwDefineEnum("FlooderType", NULL, 0);
	TwAddVarRW(twBar_FloodCheats, "Random Texts Flooder Type:", FlooderType, &set.ChatHacks.bSpammer1_Random_Texts_Random_Type, " label='Flooder #1: Generator Type' enum='1 { Only A-Z & a-z }, 2 { Only A-Z }, 3 { Only a-z }, 4 { Only 0-9 }, 5 { Only 0 & 1 }, 6 { Only Special Chars }' group='Spammer: Types & Settings' ");
	TwAddSeparator(twBar_FloodCheats, NULL, "group='Spammer: Types & Settings' ");
	TwAddVarRW(twBar_FloodCheats, "Use Left Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Left_Random_Texts, "label='Flooder #1: Generate from left side' group='Spammer: Types & Settings' ");
	TwAddVarRW(twBar_FloodCheats, "Use Right Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Right_Random_Texts, "label='Flooder #1: Generate from right side' group='Spammer: Types & Settings' ");
	TwAddVarRW(twBar_FloodCheats, "Use Both Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Both_Random_Texts, "label='Flooder #1: Generate for both sides' group='Spammer: Types & Settings' ");
	TwAddSeparator(twBar_FloodCheats, NULL, "group='Spammer: Types & Settings' ");
	TwAddVarRW(twBar_FloodCheats, "Left Random Text Lenght for Flooder #1", TW_TYPE_INT32, &set.ChatHacks.sSpammer1_Left_Random_Text_Lenght, " label='Flooder #1: Left generator length' min=1 max=9 group='Spammer: Types & Settings' ");
	TwAddVarRW(twBar_FloodCheats, "Right Random Text Lenght for Flooder #1", TW_TYPE_INT32, &set.ChatHacks.sSpammer1_Right_Random_Text_Lenght, " label='Flooder #1: Right generator length' min=1 max=9 group='Spammer: Types & Settings' ");
	TwDefine(" 'Flood_Hacks'/'Spammer: Types & Settings' opened=false ");

	TwAddVarRW(twBar_FloodCheats, "PM Flooder", TW_TYPE_BOOLCPP, &cheat_state->Flooderler.iPMCrashFlooder, "label='PM Flooder' group='PM Spammer:Settings' ");
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Target ID", TW_TYPE_INT32, &set.ChatHacks.iPMLagFloodID, " label='PM Spammer: Target ID' min=0 max=1000 group='PM Spammer:Settings' ");
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Delay", TW_TYPE_INT32, &set.ChatHacks.iPMLagger_Run_Delay, " label='PM Spammer: Delay' min=10 max=10000 group='PM Spammer:Settings' ");
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Length", TW_TYPE_INT32, &set.ChatHacks.iPMLaggerText_Lenght, " label='PM Spammer: Length' min=1 max=90 group='PM Spammer:Settings' ");
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: CMD Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.iPMLagFloodCommandText)), &set.ChatHacks.iPMLagFloodCommandText, " label='Whats the CMD of sending PM?' min=1 max=6 group='PM Spammer:Settings' ");
	TwDefine(" 'Flood_Hacks'/'PM Spammer:Settings' opened=false ");


	TwAddButton(twBar_RakNetCheats, "Reconnect", reconnect, NULL, " label='Reconnect' group='Connection Settings' ");
	TwAddButton(twBar_RakNetCheats, "Fake Leave", fleave, NULL, " label='Leave the server' group='Connection Settings' ");
	TwAddButton(twBar_RakNetCheats, "Fake Timeout", ftimeout, NULL, " label='Leave the server[Crash]' group='Connection Settings' ");
	TwAddButton(twBar_RakNetCheats, "Fake Kick/Ban", fkick, NULL, " label='Leave the server[Kick/Ban]' group='Connection Settings' ");
	TwAddVarRW(twBar_RakNetCheats, "NPC Connection Info", TW_TYPE_BOOLCPP, &set.NPC_Connection_Checker, "label='NPC Information' group='Connection Settings' ");
	TwDefine(" 'RakNet_Funcs'/'Connection Settings' opened=false ");
	TwAddVarRW(twBar_RakNetCheats, "Project Panel", TW_TYPE_BOOLCPP, &cheat_state->PrivateControlPanel.bEnablePanel, "label='Enable Project Panel' group='RakNet Exploits' ");
	TwAddVarRW(twBar_RakNetCheats, "Connect As NPC", TW_TYPE_BOOLCPP, &cheat_state->RakNet.iConnectAsNPC, "label='Connect As NPC' group='RakNet Exploits' ");
	TwAddButton(twBar_RakNetCheats, "Connect As Zombie", ClientZombieConnection, NULL, " label='Connect As Zombie' group='RakNet Exploits' ");
	TwAddButton(twBar_RakNetCheats, "Knife Hack #1", killAllKnife, NULL, " label='Knife Kill All #1 | Interesting One' group='RakNet Exploits' ");
	TwAddButton(twBar_RakNetCheats, "Knife Hack #2", killAllSplat, NULL, " label='Splat Kill All(Test) | Bütün Sunucu' group='RakNet Exploits' ");
	TwAddButton(twBar_RakNetCheats, "Knife Hack #3", killAllVehicleHit, NULL, " label='Vehicle Hit Kill All | Bütün Sunucu' group='RakNet Exploits' ");
	TwAddButton(twBar_RakNetCheats, "Take Damage", takeDamage, NULL, " label='Take Damage #1' group='RakNet Exploits' ");
	TwAddButton(twBar_RakNetCheats, "Sky Crasher", skyCrasher, NULL, " label='Sky Crasher' group='RakNet Exploits' ");
	TwAddVarRW(twBar_RakNetCheats, "Zero Ping", TW_TYPE_BOOLCPP, &cheat_state->RakNet.iZeroPingExploit, "label='Zero Ping' group='RakNet Exploits' ");

	TwDefine(" 'RakNet_Funcs'/'RakNet Exploits' opened=false ");
	
	
	TwAddVarRW(twBar_RakNetCheats, "Use Fake GPCI", TW_TYPE_BOOLCPP, &set.bUse_Fake_GPCI, "label='Use Random GPCI' group='GPCI Settings' ");
	TwAddVarRW(twBar_RakNetCheats, "Information about fake gpci", TW_TYPE_BOOLCPP, &set.Information_About_My_Fake_GPCI, "label='Information about GPCI' group='GPCI Settings' ");
	TwDefine(" 'RakNet_Funcs'/'GPCI Settings' opened=true ");
	
	TwAddVarRW(twBar_RakNetCheats, "Aim", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingAimData, "label='Disable Sending Aim Data' group='The RakNet Packets: Turn OFF/ON' ");
	TwAddVarRW(twBar_RakNetCheats, "Bullet", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingBulletData, "label='Disable Sending Bullet Data' group='The RakNet Packets: Turn OFF/ON' ");
	TwAddVarRW(twBar_RakNetCheats, "Passenger", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingPassengerData, "label='Disable Sending Passenger Data' group='The RakNet Packets: Turn OFF/ON' ");

	TwAddVarRW(twBar_RakNetCheats, "Player", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingPlayerData, "label='Disable Sending OnFoot Data' group='The RakNet Packets: Turn OFF/ON' ");
	TwAddVarRW(twBar_RakNetCheats, "Trailer", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingTrailerData, "label='Disable Sending Trailer Data' group='The RakNet Packets: Turn OFF/ON' ");
	//TwAddVarRW(twBar_RakNetCheats, "Unoccupied", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingUnoccupiedData, "label='Disable Sending Unoccupied Data' group='Disable Sending Some Data Packets' ");
	TwAddVarRW(twBar_RakNetCheats, "Vehicle", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingVehicleData, "label='Disable Sending Vehicle Data' group='The RakNet Packets: Turn OFF/ON' ");
	TwAddVarRW(twBar_RakNetCheats, "Weapon", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingWeaponUpdateData, "label='Disable Sending Weapon Data' group='The RakNet Packets: Turn OFF/ON' ");
	//TwAddVarRW(twBar_RakNetCheats, "Spec", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSpectatorSyncData, "label='Disable Sending Spectator Sync Data' group='Disable Sending Some Data Packets' ");
	TwDefine(" 'RakNet_Funcs'/'The RakNet Packets: Turn OFF/ON' opened=false ");
	TwAddVarRW(twBar_RakNetCheats, "Enable Onfoot Logger", TW_TYPE_BOOLCPP, &cheat_state->Korumalar.iLogger, "label='OnFoot Packet logger' group='Packet Logger' ");
	TwAddVarRW(twBar_RakNetCheats, "Logger Target ID", TW_TYPE_INT32, &set.OnfootLoggerID, " label='Logger Target ID' min=0 max=1000 group='Packet Logger' ");
	TwDefine(" 'RakNet_Funcs'/'Packet Logger' opened=false ");


#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL && COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	if (g_BotFuncs)
	{
		TwAddButton(twBar_Bots, "Add bot", botsMenu_addBot, NULL, " label='Add Bot' ");
		TwAddButton(twBar_Bots, "Delete bot", botsMenu_delBot, NULL, " label='Delete Bot' ");
		TwAddButton(twBar_Bots, "Spawn ALL b0Tz", botsMenu_SpawnAll, NULL, " label='Spawn All Bots' ");
		TwAddVarRW(twBar_Bots, "Bot Class Flooder", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bClassFlooder, "label='Bot Class Flooder' ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Use Fake Bot", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.UseFakeBot, " label='Use Fake Bot' group='Fake Bot Settings' ");
		TwAddVarRW(twBar_Bots, "Fake Bot ID", TW_TYPE_INT32, &BotCheats->Target_PlayerID, " label='Fake Bot: Target ID' min=0 max=1000 group='Fake Bot Settings' ");
		TwDefine(" 'Bot_Options'/'Fake Bot Settings' opened=false ");
		////////////////////////////////////////////////////////////////////
		TwAddButton(twBar_Bots, "Connect as Zombie", zombieConnection, NULL, " label='Connect Bots as Zombie' group='Bot RakNet Stuffs:)' ");
		TwAddVarRW(twBar_Bots, "Connect as NPC", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bConnectAsNPC, " label='Connect Bots as NPC' group='Bot RakNet Stuffs:)' ");
		TwDefine(" 'Bot_Options'/'Bot RakNet Stuffs:)' opened=false ");
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Rand0m quats", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRandomQuaternions, " label='Bot Rand Quats' group='Bot OnFoot Functions' ");
		TwAddVarRW(twBar_Bots, "Bot TwistMode", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTwistMode, " label='Bot Twist Mode' group='Bot OnFoot Functions' ");
		TwAddVarRW(twBar_Bots, "Bot Upside Down", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUpsideDown, " label='Bot Head Walk' group='Bot OnFoot Functions' ");
		TwAddVarRW(twBar_Bots, "Bot Random Animations", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRandAnim, " label='Bot Random Animations' group='Bot OnFoot Functions'  ");
		TwDefine(" 'Bot_Options'/'Bot OnFoot Functions' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Tornado #1", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTornado, " label='Bot Tornado #1' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Tornado #2", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTornado2, " label='Bot Tornado #2' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Circle", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotCircle, "	label='Bot Circle' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Sun", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSun, " label='Bot Sun' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Shooter", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bShooter, " label='Bot Shooter' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Storm", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bStorm, " label='Bot Storm' group='Bot OnFoot Actions'  ");
		TwDefine(" 'Bot_Options'/'Bot OnFoot Actions' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Player Blocker", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotPlayerBlocker, " label='Bot Player Blocker' group='Bot Troll Actions' ");
		TwAddVarRW(twBar_Bots, "Bot Player Slapper", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSlapper, " label='Bot Player Slapper' group='Bot Troll Actions' ");
		TwAddVarRW(twBar_Bots, "Bot Player Elevator", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotElevator, " label='Bot Player Elevator' group='Bot Troll Actions' ");
		TwAddVarRW(twBar_Bots, "Bot Player Jetpack Elevator", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotJetpackElevator, " label='Bot Player Jetpack Elevator' group='Bot Troll Actions' ");
		TwAddVarRW(twBar_Bots, "Bot Player Fuck", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotFuck, " label='Bot Player Fucker' group='Bot Troll Actions' ");
		TwDefine(" 'Bot_Options'/'Bot Troll Actions' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot SpinBot", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bSpinBot, " label='Bot SpinBot' group='Bot Aim Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot SilentAim", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSilent, " label='Bot Silent' group='Bot Aim Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot ShakingCamera #1", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotShakingCamera, " label='Bot Derp Cam #1' group='Bot Aim Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot ShakingCamera #2", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotShakingCamera2, " label='Bot Derp Cam #2' group='Bot Aim Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot Invalid Aim Z", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotInvalidAimZ, " label='Bot Invalid Aim Z' group='Bot Aim Funcs' ");
		TwDefine(" 'Bot_Options'/'Bot Aim Funcs' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////BotCrasherType
		TwType botCrashers = TwDefineEnum("botCrashers", NULL, 0);
		TwAddVarRW(twBar_Bots, "Bot Crasher Type:", botCrashers, &set.Bots.BotCrasherType, " label='Bot Crasher Type:' enum='0 { Off }, 1 { Detonator Crasher }, 2 { Invalid Bullets Crasher }, 3 { Passenger Crasher }, 4 { Roll Crasher }, 5 { Invalid Negative Bullets Crasher #2 }, 6 { Tuning Crasher }, 7 { Negative Roll Crasher }' group='Bot Player Crashers' ");
		TwAddVarRW(twBar_Bots, "Bot Remove Player Crasher!", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRemovePlayerCrasher, " label='Bot Remove Player Crasher' group='Bot Player Crashers' ");
		TwAddVarRW(twBar_Bots, "Bot Roll Crasher", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRollCrasher, " label='Bot Roll Crasher' group='Bot Player Crashers' ");
		TwDefine(" 'Bot_Options'/'Bot Player Crashers' opened=false ");


		/*TwAddVarRW(twBar_Bots, "Bot Roll Crasher: Use Bot ID", TW_TYPE_BOOLCPP, &set.Bots.bUseRollCrasherBotID, " label='Bot Roll Crasher' group='Bot Player Crashers' ");
		TwAddVarRW(twBar_Bots, "Bot Roll CRASHERZ: Bot ID", TW_TYPE_INT32, &set.Bots.bUseRollCrasherBotID, " label='Fake Bot: Target ID' min=0 max=1000 group='Fake Bot Settings' ");
		TwDefine(" 'Bot_Options'/'Bot Player Crashers Settings' opened=false ");*/
		/*

		*/
		//////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////// which ver? CP health, etcc v1.5
		TwAddVarRW(twBar_Bots, "CP Health", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyHealth, " label='Copy My Health Value' group='Bot Copy Settings' ");
		TwAddVarRW(twBar_Bots, "CP Armor", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyArmor, " label='Copy My Armor Value' group='Bot Copy Settings' ");
		TwAddVarRW(twBar_Bots, "CP Weapon", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyWeapon, " label='Copy My Weapon ID' group='Bot Copy Settings' ");
		TwAddVarRW(twBar_Bots, "CP Words", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyChat, " label='Copy My Words' group='Bot Copy Settings' ");
		TwAddVarRW(twBar_Bots, "CP RPCs", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyRPC, " label='Copy RPCs[Commands/Die]' group='Bot Copy Settings' ");
		TwDefine(" 'Bot_Options'/'Bot Copy Settings' opened=false ");
		//TwAddVarRW(twBar_Bots, "CP Anim ID", TW_TYPE_INT16, &g_BotFuncs->BotSettings.sBotFollowAnimID, " label='Bot Follow Me Animation ID' min=0 max=885 group='Bot Copy Settings' ");
		////////////////////////////////////////////////////////////////////
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwType botFlooderType = TwDefineEnum("botFlooderType", NULL, 0);
		TwAddVarRW(twBar_Bots, "Bot PM Flooder", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bPMFlooder, " label='Bot PM Flooder' ");
		TwAddVarRW(twBar_Bots, "Bot PM Flooder ID", TW_TYPE_INT32, &set.Bots.botpmflooderhedef, "label='Spam ID:' min=0 max=1000 ");
		TwAddVarRW(twBar_Bots, "Random Texts Flooder Type:", FlooderType, &set.Bots.botpmfloodertype, " label='Bot PM Flooder: Generator Type' enum='1 { All Characters }, 2 { Only 0-1 }, 3 { Only 0-9 }, 4 { Your Text }' ");
		TwAddSeparator(twBar_Bots, NULL, "");
		
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Adjustable Nick", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableNick, " label='Use Adjustable Nick for bots? ");
		TwAddVarRW(twBar_Bots, "Bot Adjustable Tag", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableTag, " label='Use Adjustable Tag for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Use Split for NickName", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Split_For_NickName, " label='Use Adjustable Split for bots?' ");
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwAddVarRW(twBar_Bots, "Bot Use Count Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Bot_Count, " label='Use Bot Count method for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Use Random Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Random_Numbers, " label='Use Random numbers for bots?' ");
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Nick for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_AdjustableNick)), &set.Bots.RAKNET_BOT_AdjustableNick, " label='Bot Nick:' ");
		TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Tag for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName)), &set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName, " label='Bot Tag:' ");
		TwAddVarRW(twBar_Bots, "Do you want to use Split for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_NickName_Split)), &set.Bots.RAKNET_BOT_NickName_Split, " label='Bot Split Character:' ");

		TwAddVarRW(twBar_Bots, "Update Send Rate", TW_TYPE_INT32, &g_BotFuncs->BotSettings.UpdateSendRate, " label='Bots: Update Send Rate' step=1 min=1 max=50 group='Bot Settings' ");
		/* Bu gece 22.10.2019 -> 21:07 Aþaðýdaki yazýyý yorum satýrý yapmamýn sebebi milletin sik kafalý olmasýndan bir boku okuma alýþkanlýðý olmamasýndan dolayý... */
	
		/*TwAddVarRW(twBar_Bots, "Bot Adjustable Nick", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableNick, " label='Do you want to use Adjustable Nick for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Adjustable Tag", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableTag, " label='Do you want to use Adjustable Tag for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Use Split for NickName", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Split_For_NickName, " label='Do you want to use Adjustable Split for bots?' ");
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwAddVarRW(twBar_Bots, "Bot Use Count Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Bot_Count, " label='Do you want to use Bot Count method for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Use Random Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Random_Numbers, " label='Do you want to use Random numbers for bots?' ");
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Nick for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_AdjustableNick)), &set.Bots.RAKNET_BOT_AdjustableNick, " label='Bot Nick:' ");
		TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Tag for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName)), &set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName, " label='Bot Tag:' ");
		TwAddVarRW(twBar_Bots, "Do you want to use Split for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_NickName_Split)), &set.Bots.RAKNET_BOT_NickName_Split, " label='Bot Split Character:' ");*/

		TwType BotYaziTuru = TwDefineEnum("BotText", NULL, 0);
		TwAddVarRW(twBar_Bots, "Bot Flooder Type", BotYaziTuru, &set.Bots.Bot_ChatFlooder_Text_Type, " label='RAKNET Bot Chat Flood Type:' enum='1 {Use New Characters}, 2 {Only Binary Nums[0 & 1]}, 3{Only Numbers[0 & 9]}, 4 {Full Random}' group='Bot Chat Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot chat flood", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bChatFlooder, " label='Bot Chat Flood' group='Bot Chat Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot Chat Flooder Letter length", TW_TYPE_INT32, &set.Bots.RAKNET_BOT_Flooder_Letter_Length, " label='Bot Chat Flooder Character/Letter Length' min=0 max=9 group='Bot Chat Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot Flooder Text", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Chat_Text)), &set.Bots.RAKNET_BOT_Chat_Text, " label='Bot Flooder Text:' group='Bot Chat Funcs' ");
		TwDefine(" 'Bot_Options'/'Bot Chat Funcs' opened=false ");

	}
#endif
	/*
	TwAddVarRW(twBar_Interface, "Draw FPS", TW_TYPE_BOOLCPP, &set.hud_fps_draw, " label='FPS göster' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inv", TW_TYPE_BOOLCPP, &set.hud_indicator_inv, " label='Ölümsüzlük Yazisi' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_airbrk", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_airbrk, " label='Airbreak Yazisi' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_aim", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_aim, " label='Aim[RAGE] & Legit Yazisi' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_silent_aim", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_silent_aim, " label='Silent Aimbot Yazisi' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_pos", TW_TYPE_BOOLCPP, &set.hud_indicator_pos, " label='Pozisyon Göster' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_fly", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_fly, " label='Uçma Hilesi Yazisi' group='HUD' ");
	//TwAddVarRW(twBar_Interface, "welcome_to_project_attack_text", TW_TYPE_BOOLCPP, &set.welcome_to_project_attack_text, " label='Welcome To Project Attack TEXT' group='HUD Settings' ");
	/*
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_airbrk", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_airbrk, " label='HUD Indicator InVeh AirBrk' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_stick", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_stick, " label='HUD Indicator InVeh Stick' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_brkdance", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_brkdance, " label='HUD Indicator InVeh BrkDance' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_spider", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_spider, " label='HUD Indicator InVeh Spider' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_fly", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_fly, " label='HUD Indicator InVeh Fly' group='HUD' ");

	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_airbrk", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_airbrk, " label='HUD Indicator OnFoot AirBrk' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_stick", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_stick, " label='HUD Indicator OnFoot Stick' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_aim", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_aim, " label='HUD Indicator OnFoot Aim' group='HUD' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_fly", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_fly, " label='HUD Indicator OnFoot Fly' group='HUD' ");*/

	TwDefine(" 'Interface'/'HUD' opened=false ");
}
void toggleATBCursor(bool bToggle)
{
	uint32_t	func = g_dwSAMP_Addr + SAMP_FUNC_TOGGLECURSOR;
	uint32_t	funcunlock = g_dwSAMP_Addr + SAMP_FUNC_CURSORUNLOCKACTORCAM;

	uint32_t	obj = *(DWORD *)(g_dwSAMP_Addr + SAMP_MISC_INFO);

	if (bToggle)
	{
		_asm
		{
			mov ecx, obj;
			push 0;
			push 3;
			call func;
		}
	}
	else
	{
		_asm
		{
			mov ecx, obj;
			push 1;
			push 0;
			call func;
		}

		_asm
		{
			mov ecx, obj;
			call funcunlock;
		}
	}
}
