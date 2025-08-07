/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "main.h"

int			g_iSpectateEnabled = 0, g_iSpectateLock = 0, g_iSpectatePlayerID = -1;
int			g_iJoiningServer = 0;
int			iClickWarpEnabled = 0;
int			g_iNumPlayersMuted = 0;
bool		g_bPlayerMuted[SAMP_MAX_PLAYERS];

void EscapeFromServer() // Bu fonksiyon DarkNeX Tarafından yapıldı. v2.2 Faktörüydü sanırım.
{
	if (!set.EscapeFromServer_WhenAdminsJoin) // if false, then return
		return;

	static DWORD dwDelay = 0;
	if (!dwDelay) dwDelay = GetTickCount();
	// V3 GÜNCELLEMESİ GELDİ, DÜŞÜN ULAN! ~ RapidFire
	if (GetTickCount() - dwDelay > 5000) // 5 seconds -> Güncelleme V2.4.3/V2.5'da buna ayarlanabilir gecikme eklemeyi düşünebilirsin. ;))
	{
		set.EscapeFromServer_WhenAdminsJoin = false;
		dwDelay = 0;
	}

	/*
	Bugünün tarihi 13.11.2020 | 03:08 Dışarda Corona.. Evde ben :)
	Bu İngilizce comment-linelar, DarkNeX'e & Bana aittir.
		~ RapidFire
	*/
	if (KEY_PRESSED(VK_F5)) // use GetAsyncKeyState only when u don't have keyhook for the certain game.. s0beit contains keyhook, so use the keyhook  (it's better since yoe send key strokes directly to the game) KEY_DOWN, KEY_PRESSED etc.. i know it m8! xD
	{
		disconnect(100); // Escape!! he will catch us!! also 0 = means timeout, use 100 for example 500 = disconnect 0  timeout, actually it's a delay.. if you put something above 0 ms it will always disconnect you, but i recommend 50 - 100 ms 100 ms
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		cheat_state_text("Disconnect Status:{00FF00} Successful.");
#else
		cheat_state_text("Sunucudan çıkış başarılı, an itibariyle sunucuda değilsiniz.");
#endif
		set.EscapeFromServer_WhenAdminsJoin = false;
		dwDelay = 0;
	}
	// no no.. KEY_PRESSED is "pressed" only once, KEY_DOWN is for situation when the key is hold down.. but GetAsyncKeyState(key) & 1 = KEY_PRESSED if you DO NOT HAVE keyhook ah.. done m8 as i understand.. if i don't have key_down & key_pressed , i have to use getasynckey blalbalbal if i have keyhook, i have to use key_down and key_pressed, done? xD actually yes xd when you start hacking other games, you will understand more ayyyyy xddddddddddddddddddddddddddddddddddddd i already leave samp, maybe i can try cod4x nvm.. let'z try
	else if (KEY_PRESSED(VK_F2)) { // if you want not to flood it, use GetAsyncKeyState(key) & 1 // this will asure it will be pressed just once, but as said above, no need to use GetAsyncKeyState now
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		addMessageToChatWindow("Did not disconnected from server, \n you can continue playing on this server!");
#else
		addMessageToChatWindow("Sunucudan çıkış yapmadınız, \n Sunucuda aktif olarak oynamaya devam edebilirsiniz.");
#endif
		set.EscapeFromServer_WhenAdminsJoin = false;
		dwDelay = 0;
	}
}

void sampMainCheat(void)
{
	//traceLastFunc("sampMainCheat()");
	// g_Vehicles & g_Players pointers need to be refreshed or nulled
	if (isBadPtr_writeAny(g_SAMP->pPools, sizeof(stSAMPPools)))
	{
		g_Vehicles = NULL;
		g_Players = NULL;
	}
	else if (g_Vehicles != g_SAMP->pPools->pVehicle || g_Players != g_SAMP->pPools->pPlayer)
	{
		if (isBadPtr_writeAny(g_SAMP->pPools->pVehicle, sizeof(stVehiclePool)))
			g_Vehicles = NULL;
		else
			g_Vehicles = g_SAMP->pPools->pVehicle;
		if (isBadPtr_writeAny(g_SAMP->pPools->pPlayer, sizeof(stPlayerPool)))
			g_Players = NULL;
		else
			g_Players = g_SAMP->pPools->pPlayer;
	}

	// update GTA to SAMP translation structures
	update_translateGTASAMP_vehiclePool();
	update_translateGTASAMP_pedPool();

	spectateHandle();
	sampAntiHijack();
	// start chatbox logging
	if (set.chatbox_logging)
	{
		static int	chatbox_init;
		if (!chatbox_init)
		{
			SYSTEMTIME	time;
			GetLocalTime(&time);
			//LogChatbox(false, "Session started at %02d/%02d/%02d", time.wDay, time.wMonth, time.wYear);
			chatbox_init = 1;
		}
	}
	actor_info* self = actor_info_get(ACTOR_SELF, 0);
	if (cheat_state->genel.iInvalidAimZ && set.aimCheatsSettings.bSyncInvalidAimZPed)
	{
	if(g_Players->pLocalPlayer->byteCurrentWeapon != 34)
		self->pPlayerData->m_fSkateBoardSpeed = sqrtf(-1.0f);
	}
	if (cheat_state->Silah.iSpinBotType && set.aimCheatsSettings.iSyncSpinBotTypes)
	{
		switch (cheat_state->Silah.iSpinBotType)
		{
		case ID_SPINTYPE_OFF:
			break;
		case ID_SPINTYPE_DOWN:
			self->pPlayerData->m_fSkateBoardSpeed = sqrt(1.45f);
			break;
		case ID_SPINTYPE_UP:
			self->pPlayerData->m_fSkateBoardSpeed = -0.89f;
			break;
		case ID_SPINTYPE_RANDOM:
			self->pPlayerData->m_fSkateBoardSpeed = random_float(-0.89f, 1.45f);
			break;
		default:
			break;
		}
	}
			
	if (KEYCOMBO_PRESSED(set.key_player_info_list))
		cheat_state->player_info_list ^= 1;

	if (KEYCOMBO_PRESSED(set.key_rejoin))
	{
		restartGame();
		disconnect(500);

#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		cheat_state_text("Rejoining in %d seconds!", set.rejoin_delay / 1000);
#else
		cheat_state_text("%d saniye içerisinde sunucuya tekrar bağlanılacak.", set.rejoin_delay / 1000);
#endif
		cheat_state->_generic.rejoinTick = GetTickCount();
	}

	if (KEYCOMBO_PRESSED(set.key_respawn))
		playerSpawn();
	
	if (KEYCOMBO_DOWN(set.chat_secondary_key))
	{
		int			i, key, spam;
		const char	*msg;
		for (i = 0; i < INI_CHATMSGS_MAX; i++)
		{
			struct chat_msg *msg_item = &set.chat[i];
			if (msg_item->key == NULL)
				continue;
			if (msg_item->msg == NULL)
				continue;
			if (msg_item->key != key_being_pressed)
				continue;
			key = msg_item->key;
			msg = msg_item->msg;
			spam = msg_item->spam;
			if (spam)
			{
				if (msg)
					if (KEY_DOWN(key))
						say("%s", msg);
			}
			else
			{
				if (msg)
					if (KEY_PRESSED(key))
						say("%s", msg);
			}
		}
	}
	if (set.clickwarp_enabled && iIsSAMPSupported)
	{
		if (KEYCOMBO_PRESSED(set.key_clickwarp_enable))
		{
			g_iCursorEnabled ^= 1;
			toggleSAMPCursor(g_iCursorEnabled);
		}
		if (g_iCursorEnabled && KEYCOMBO_PRESSED(set.key_clickwarp_click))
		{
			iClickWarpEnabled = 1;
		}
	}

	static int	iSAMPHooksInstalled;
	if (!iSAMPHooksInstalled)
	{
		installSAMPHooks();
		iSAMPHooksInstalled = 1;
	}

	if (cheat_state->_generic.rejoinTick && cheat_state->_generic.rejoinTick < (GetTickCount() - set.rejoin_delay))
	{
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
		cheat_state->_generic.rejoinTick = 0;
	}

	if (g_iJoiningServer == 1)
	{
		restartGame();
		disconnect(500);
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		cheat_state_text("Rejoining in %d seconds!", set.rejoin_delay / 1000);
#else
		cheat_state_text("%d saniye içerisinde sunucuya tekrar bağlanılacak.", set.rejoin_delay / 1000);
#endif
		cheat_state->_generic.join_serverTick = GetTickCount();
		g_iJoiningServer = 2;
	}

	if (g_iJoiningServer == 2
		&& cheat_state->_generic.join_serverTick
		&&	 cheat_state->_generic.join_serverTick < (GetTickCount() - set.rejoin_delay))
	{
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
		g_iJoiningServer = 0;
		cheat_state->_generic.join_serverTick = 0;
	}

	EscapeFromServer();
}

void spectateHandle(void)
{
	if (g_iSpectateEnabled)
	{
		if (g_iSpectateLock) return;

		if (g_iSpectatePlayerID != -1)
		{
			if (g_Players->iIsListed[g_iSpectatePlayerID] != 0)
			{
				if (g_Players->pRemotePlayer[g_iSpectatePlayerID] != NULL)
				{
					int iState = getPlayerState(g_iSpectatePlayerID);

					if (iState == PLAYER_STATE_ONFOOT)
					{
						struct actor_info *pPlayer = getGTAPedFromSAMPPlayerID(g_iSpectatePlayerID);
						if (pPlayer == NULL) return;
						GTAfunc_CameraOnActor(pPlayer);
						g_iSpectateLock = 1;
					}
					else if (iState == PLAYER_STATE_DRIVER)
					{
						struct vehicle_info *pPlayerVehicleID = g_Players->pRemotePlayer[g_iSpectatePlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;
						if (pPlayerVehicleID == NULL) return;
						GTAfunc_CameraOnVehicle(pPlayerVehicleID);
						g_iSpectateLock = 1;
					}
					else if (iState == PLAYER_STATE_PASSENGER)
					{
						struct vehicle_info *pPlayerVehicleID = g_Players->pRemotePlayer[g_iSpectatePlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;
						if (pPlayerVehicleID == NULL) return;
						GTAfunc_CameraOnVehicle(pPlayerVehicleID);
						g_iSpectateLock = 1;
					}
				}
				else
				{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
					cheat_state_text("Target is not streamed!");
#else
					cheat_state_text("Oyuncu yakınlarda değil.");
#endif
					g_iSpectateEnabled = 0;
				}
			}
		}
	}
}

void spectatePlayer(int iPlayerID)
{
	if (iPlayerID == -1)
	{
		GTAfunc_TogglePlayerControllable(0);
		GTAfunc_LockActor(0);
		pGameInterface->GetCamera()->RestoreWithJumpCut();

		g_iSpectateEnabled = 0;
		g_iSpectateLock = 0;
		g_iSpectatePlayerID = -1;
		return;
	}

	g_iSpectatePlayerID = iPlayerID;
	g_iSpectateLock = 0;
	g_iSpectateEnabled = 1;
}

void sampAntiHijack(void)
{
	//if (g_SAMP == NULL) return;

	//vehicle_info *veh = vehicle_info_get(VEHICLE_SELF, VEHICLE_ALIVE);
	//if (set.anti_carjacking && veh == NULL)
	//{
	//	if (cheat_state->_generic.got_vehicle_id)
	//		cheat_state->_generic.got_vehicle_id = false;
	//	if (cheat_state->_generic.anti_carjackTick
	//		&&	 cheat_state->_generic.anti_carjackTick < (GetTickCount() - 500)
	//		&& cheat_state->_generic.car_jacked)
	//	{
	//		if (cheat_state->_generic.car_jacked_last_vehicle_id == 0)
	//		{
	//			GTAfunc_showStyledText("~r~Unable To Unjack~w~!", 1000, 5);
	//			cheat_state->_generic.anti_carjackTick = 0;
	//			cheat_state->_generic.car_jacked = false;
	//			return;
	//		}

	//		cheat_state->_generic.anti_carjackTick = 0;
	//		cheat_state->_generic.car_jacked = false;
	//		GTAfunc_PutActorInCar(GetVehicleByGtaId(cheat_state->_generic.car_jacked_last_vehicle_id));

	//		struct vehicle_info *veh = GetVehicleByGtaId(cheat_state->_generic.car_jacked_last_vehicle_id);
	//		//if ( veh != NULL )
	//		//	vect3_copy( cheat_state->_generic.car_jacked_lastPos, &veh->base.matrix[4 * 3] );
	//		GTAfunc_showStyledText("~r~Car Unjacked~w~!", 1000, 5);
	//		return;
	//	}
	//}
	//else if (set.anti_carjacking)
	//{
	//	if (veh->passengers[0] == actor_info_get(ACTOR_SELF, 0))
	//	{
	//		if (!cheat_state->_generic.got_vehicle_id)
	//		{
	//			cheat_state->_generic.car_jacked_last_vehicle_id = getPlayerVehicleGTAScriptingID(ACTOR_SELF);
	//			if (cheat_state->_generic.car_jacked_last_vehicle_id > 0)
	//				cheat_state->_generic.got_vehicle_id = true;
	//		}
	//	}
	//}
}

void HandleRPCPacketFunc(unsigned char id, RPCParameters *rpcParams, void(*callback) (RPCParameters *))
{
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[id][INCOMING_RPC] != nullptr && set.netPatchAssoc[id][INCOMING_RPC]->enabled)
			return;
	}
	//if (cheat_state->_generic.teststuff)
	//{
	//	if (id != RPC_UpdateScoresPingsIPs && id != RPC_RemoveBuildingForPlayer && id != RPC_ClientMessage && id != RPC_ServerJoin && id != RPC_ServerQuit)
	//	{
	//		DWORD dwRunDelay = 5000;
	//		if (GetTickCount() - dwRunDelay > 5000)
	//		{
	//			SYSTEMTIME	time;
	//			GetLocalTime(&time);
	//			int len = rpcParams ? rpcParams->numberOfBitsOfData / 8 : 0;
	//			Log("%02d:%02d:%02d] | Received RPC ID: %d | Offset: %p | Length: %d", time.wHour, time.wMinute, time.wSecond, id, (DWORD)callback - g_dwSAMP_Addr, len);
	//			//addMessageToChatWindow("Received RPC ID: %d | Offset: %p | Length: %d", id, (DWORD)callback - g_dwSAMP_Addr, len);
	//			dwRunDelay = GetTickCount();
	//		}
	//	}
	//}
	if (rpcParams != nullptr && rpcParams->numberOfBitsOfData >= 8)
	{
		switch (id)
		{
			case RPC_SetPlayerHealth:
			{
				if (isCheatPanicEnabled() || !set.enable_extra_godmode || !cheat_state->_generic.hp_cheat) break;

				actor_info *self = actor_info_get(ACTOR_SELF, NULL);
				if (self)
				{
					RakNet::BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
					float fHealth;
					bsData.Read(fHealth);
					if (fHealth < self->hitpoints)
					{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
						cheat_state_text("Warning: Server tried change your health to %0.1f", fHealth);
#else
						cheat_state_text("Sunucu, senin can değerini %0.1f olarak değiştirmeyi denedi.", fHealth);
#endif
						return; // exit from the function without processing RPC
					}
				}
				break;
			}
			case RPC_SetVehicleHealth:
			{
				if (isCheatPanicEnabled() || !set.enable_extra_godmode || !cheat_state->_generic.hp_cheat) break;

				vehicle_info *vself = vehicle_info_get(VEHICLE_SELF, NULL);
				if (vself)
				{
					RakNet::BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
					short sId;
					float fHealth;
					bsData.Read(sId);
					bsData.Read(fHealth);
					if (sId == g_Players->pLocalPlayer->sCurrentVehicleID && fHealth < vself->hitpoints)
					{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
						cheat_state_text("Warning: Server tried change your vehicle health to %0.1f", fHealth);
#else
						cheat_state_text("Sunucu, senin aracının can değerini %0.1f olarak değiştirmeyi denedi.", fHealth);
#endif
						return; // exit from the function without processing RPC
					}
				}
				break;
			}
			case RPC_ClientMessage:
			{
				if (isCheatPanicEnabled() || !set.anti_spam && !set.chatbox_logging) break;

				RakNet::BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				uint32_t		dwStrLen, dwColor;
				char			szMsg[256];
				static char		last_servermsg[256];
				static DWORD	allow_show_again = 0;

				if (cheat_state->_generic.cheat_panic_enabled)
					break;

				bsData.Read(dwColor);
				bsData.Read(dwStrLen);
				if (dwStrLen >= sizeof(szMsg)) dwStrLen = sizeof(szMsg) - 1;
				bsData.Read(szMsg, dwStrLen);
				szMsg[dwStrLen] = '\0';

				if (set.anti_spam && (strcmp(last_servermsg, szMsg) == 0 && GetTickCount() < allow_show_again))
					return; // exit without processing rpc

				// might be a personal message by muted player - look for name in server message
				// ignore message, if name was found
				if (set.anti_spam && g_iNumPlayersMuted > 0)
				{
					int i, j;
					char *playerName = NULL;
					for (i = 0, j = 0; i < SAMP_MAX_PLAYERS && j < g_iNumPlayersMuted; i++)
					{
						if (g_bPlayerMuted[i])
						{
							playerName = (char *)getPlayerName(i);

							if (playerName == NULL)
							{
								// Player not connected anymore - remove player from muted list
								g_bPlayerMuted[i] = false;
								g_iNumPlayersMuted--;
								continue;
							}
							else if (strstr(szMsg, playerName) != NULL)
							{
								return;
							}
							j++;
						}
					}
				}
				if (set.chatbox_logging)
					LogChatbox(false, "%s", szMsg);
				strncpy_s(last_servermsg, szMsg, sizeof(last_servermsg) - 1);
				allow_show_again = GetTickCount() + 5000;
				break;
			}
			//case RPC_ClientCheck:
			//{
			//	if (cheat_state->_generic.teststuff)
			//	{

			//		RakNet::BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
			//		UINT8 type;
			//		UINT32 address;
			//		UINT16 offset;
			//		//UINT32 counter;
			//		bsData.Read(type);
			//		bsData.Read(address);
			//		bsData.Read(offset);
			//		//bsData.Read(counter);

			//		bsData.SetWriteOffset(0);
			//		//while ((GetTickCount() - dwRapidFire) < 200) { continue; }

			//		//Log("Bize geliş fiyatı: %i", type);

			//		/*
			//			SetWriteOffset kullanmaya en azından şuanlık hiç bir gerek görmüyorum çünkü gelene karşılık olarak yazdırıyorsun.
			//			ha ama eğer yine de kullanılması gerekse..
			//						bsData.SetWriteOffset(0);
			//		*/
			//		//cheat_state_text("we're good.");
			//		bsData.Write(type);
			//		bsData.Write(address);
			//		bsData.Write(offset);
			//		//bsData.Write(counter);
			//	}
			//}break;
			case RPC_EnterVehicle:
			{
				if (cheat_state->crasher.iEnterPlayerCrasher)
				{
					RakNet::BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

					uint16_t wPlayerId;
					uint16_t wVehicleId;

					uint32_t dwCrashTime = GetTickCount();

					bsData.Read(wPlayerId);
					bsData.Read(wVehicleId);

					if (g_Vehicles->iIsListed[wVehicleId] != 1)
						return;
					if (g_Vehicles->pSAMP_Vehicle[wVehicleId] == NULL)
						return;
					if (g_Vehicles->pSAMP_Vehicle[wVehicleId]->pGTA_Vehicle == NULL)
						return;

					while ((GetTickCount() - dwCrashTime) < 300) { continue; }

					stOnFootData OF;
					memset(&OF, 0, sizeof(stOnFootData));
					vehicle_info* vi = g_Vehicles->pSAMP_Vehicle[wVehicleId]->pGTA_Vehicle;
					vect3_copy(&vi->base.matrix[12], OF.fPosition);
					OF.fMoveSpeed[0] = 0.4999f;
					OF.fMoveSpeed[1] = 0.4999f;
					OF.fMoveSpeed[2] = 0.4999f;

					RakNet::BitStream oBit;
					oBit.Write((BYTE)ID_PLAYER_SYNC);
					oBit.Write((PCHAR)&OF, sizeof(stOnFootData));
					g_RakClient->Send(&oBit);

					for (int x = 0; x <= 3; x++)
					{
						stUnoccupiedData uData;
						memset(&uData, 0, sizeof(stUnoccupiedData));
						uData.sVehicleID = wVehicleId;
						uData.byteSeatID = 0;
						vect3_copy(&vi->base.matrix[12], uData.fPosition);
						uData.fPosition[2] = -10.f;
						RakNet::BitStream uBit;
						uBit.Write((BYTE)ID_UNOCCUPIED_SYNC);
						uBit.Write((PCHAR)&uData, sizeof(stUnoccupiedData));
						g_RakClient->Send(&uBit);
						addMessageToChatWindow("[Enter Crasher] Sended to %d", wPlayerId);
					}
					break;
				}
			}
			case RPC_ServerJoin:
			{
				RakNet::BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				short int p_id;
				D3DCOLOR p_color;
				byte p_nameLen, p_isNPC;
				char p_szPlayerName[25];
				bsData.Read(p_id);
				bsData.Read(p_color);
				bsData.Read(p_isNPC);
				bsData.Read(p_nameLen);
				bsData.Read(p_szPlayerName, p_nameLen);
				p_szPlayerName[p_nameLen] = '\0';
				if (cheat_state->Wallhack.iAdminListesi)
				{
					std::ifstream inputFile;
					std::string nick;
					char filename[512];
						
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
					snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminList.ini");
#else
					snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");
#endif
					inputFile.open(filename);
					while (inputFile >> nick)
					{
						if (nick == p_szPlayerName) // same as !strcmp(nick.c_str(), p_szPlayerName)
						{
							g_NewModSa->bOyuncuAdmin[p_id] = true;
							//g_NewModSa->iAdminlerID[g_NewModSa->iAdminlerCount] = p_id;
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
							addMessageToChatWindow("{00FF00}[Admin-Checker Information]%s [ID:%d] is joined server!", p_szPlayerName, p_id);
							addMessageToChatWindow("If you want to disconnect from this server, press {00FF00}F5 key, otherwise press {00FF00}F2.");
#else
							addMessageToChatWindow("[Admin-Denetleyici Bilgilendirici]%s [ID:%d] isimli admin, sunucuya giriş yaptı.", p_szPlayerName, p_id);
							addMessageToChatWindow("Sunucudan çıkmak istiyorsan {00FF00}F5'e bas, çıkmak istemiyorsan {FF0000}F2'ye basman yeterli.");
#endif
							
							set.EscapeFromServer_WhenAdminsJoin = true;
							break;
						}
					}
					inputFile.close();
				}

				if (cheat_state->Wallhack.iArkadasListesi)
				{
					std::ifstream inputFile;
					std::string nick;
					char filename[512];
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
					snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "FriendList.ini");
#else
					snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "DostListesi.ini");
#endif
					inputFile.open(filename);
					while (inputFile >> nick)
					{
						if (nick == p_szPlayerName) // same as !strcmp(nick.c_str(), p_szPlayerName)
						{
							g_NewModSa->bOyuncuArkadas[p_id] = true;
							//g_NewModSa->iArkadaslerID[g_NewModSa->iArkadaslerCount] = p_id;
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
							addMessageToChatWindow("[Friend Checker]%s[ID:%d] is joined to server!", p_szPlayerName, p_id);
#else
							addMessageToChatWindow("[Arkadaş-Listesi]%s [ID:%d] isimli arkadaşın sunucuya giriş yaptı.", p_szPlayerName, p_id);
#endif
							break;
						}
					}
					inputFile.close();
				}
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
				if (set.NPC_Connection_Checker)
				{
					if (p_isNPC) // Eğer oyuncu Connect as npc kullanıyorsa.
					{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
						addMessageToChatWindow("[NPC Information]%s [ID:%d] connected as NPC!", p_szPlayerName, p_id);
#else
						addMessageToChatWindow("[NPC Bilgisi]%s [ID:%d] isimli oyuncu sunucuya NPC olarak bağlandı.", p_szPlayerName, p_id);
#endif
					}
				}
				break;
#endif
			}

			case RPC_Chat:
			{
				if (isCheatPanicEnabled() || !set.anti_spam && !set.chatbox_logging) break;

				RakNet::BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				static char		last_clientmsg[SAMP_MAX_PLAYERS][256];
				static DWORD	allow_show_again = 0;
				uint16_t		playerId = uint16_t(-1);
				uint8_t			byteTextLen;
				char			szText[256];

				if (cheat_state->_generic.cheat_panic_enabled)
					break;

				bsData.Read(playerId);
				if (isBadSAMPPlayerID(playerId))
					break;

				bsData.Read(byteTextLen);
				bsData.Read(szText, byteTextLen);
				szText[byteTextLen] = '\0';

				if (set.anti_spam && ((strcmp(last_clientmsg[playerId], szText) == 0 && GetTickCount() < allow_show_again) || (g_iNumPlayersMuted > 0 && g_bPlayerMuted[playerId])))
					return; // exit without processing rpc

				// nothing to copy anymore, after chatbox_logging, so copy this before
				strncpy_s(last_clientmsg[playerId], szText, sizeof(last_clientmsg[playerId]) - 1);

				if (set.chatbox_logging)
					LogChatbox(false, "%s: %s", getPlayerName(playerId), szText);
				allow_show_again = GetTickCount() + 5000;
				break;
			}break;
		} // switch
	}
	callback(rpcParams);
}

bool OnSendRPC(int uniqueID, RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[uniqueID][OUTCOMING_RPC] != nullptr && set.netPatchAssoc[uniqueID][OUTCOMING_RPC]->enabled)
			return false;
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
		if (g_BotFuncs->BotSettings.bCopyRPC && g_BotFuncs->BotSettings.bFollow)
		{
			for (int i = g_BotFuncs->BotSettings.ClientCount - 1; i >= 0; i--)
				g_BotFuncs->OL_Bot_SendRPC(i, uniqueID, *parameters, HIGH_PRIORITY, RELIABLE_ORDERED, 0, false);
		}
#endif
	}
	if (uniqueID == RPC_Chat && g_Players != nullptr)
	{
		uint8_t byteTextLen;
		char szText[256];

		parameters->Read(byteTextLen);
		parameters->Read(szText, byteTextLen);
		szText[byteTextLen] = '\0';

		if (set.chatbox_logging)
			LogChatbox(false, "%s: %s", getPlayerName(g_Players->sLocalPlayerID), szText);
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
		if (g_BotFuncs->BotSettings.bCopyChat && !g_BotFuncs->BotSettings.UseFakeBot &&	g_BotFuncs->BotSettings.bFollow)
		{
			RakNet::BitStream bsSend;
			BYTE byteTextLen = (BYTE)strlen(szText);
			bsSend.Write(byteTextLen);
			bsSend.Write(szText, byteTextLen);
			for (int i = g_BotFuncs->BotSettings.ClientCount - 1; i >= 0; i--)
				g_BotFuncs->OL_Bot_SendRPC(i, RPC_Chat, bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, false);
		}
#endif
	}
	
	//if (uniqueID == RPC_ClientCheck && cheat_state && cheat_state->_generic.hp_cheat)
	//{
	//	uint8_t type = 0;
	//	parameters->Read(type);
	//	if (type == 2)
	//	{
	//		uint32_t arg = 0;
	//		uint8_t response = 0;
	//		parameters->Read(arg);
	//		parameters->Read(response);

	//		// remove invulnerability flags from our real flags
	//		uint32_t fakeFlags = arg & (0xFF00FFFF | ((~ACTOR_FLAGS_INVULNERABLE) << 16));

	//		// reform packet data
	//		parameters->SetWriteOffset(0);
	//		parameters->Write(type);
	//		parameters->Write(fakeFlags);
	//		parameters->Write(response);
	//	}
	//}
	return true;
}

bool OnSendPacket(RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	if (!isCheatPanicEnabled())
	{
		uint8_t packetId;
		parameters->Read(packetId);
		if (set.netPatchAssoc[packetId][OUTCOMING_PACKET] != nullptr && set.netPatchAssoc[packetId][OUTCOMING_PACKET]->enabled)
			return false;
	}
	return true;
}

bool OnReceivePacket(Packet *p)
{
	if (p->data == nullptr || p->length == 0)
		return true;
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[p->data[0]][INCOMING_PACKET] != nullptr && set.netPatchAssoc[p->data[0]][INCOMING_PACKET]->enabled)
			return false;
	}

	if (p->data[0] == ID_MARKERS_SYNC) // packetId
	{
		RakNet::BitStream	bs(p->data, p->length, false);
		int			iNumberOfPlayers = 0;
		uint16_t	playerID = uint16_t(-1);
		short		sPos[3] = { 0, 0, 0 };
		bool		bIsPlayerActive = false;

		bs.IgnoreBits(8);
		bs.Read(iNumberOfPlayers);
		if (iNumberOfPlayers < 0 || iNumberOfPlayers > SAMP_MAX_PLAYERS)
			return true;

		for (int i = 0; i < iNumberOfPlayers; i++)
		{
			bs.Read(playerID);
			bs.ReadCompressed(bIsPlayerActive);
			if (bIsPlayerActive == 0 || isBadSAMPPlayerID(playerID))
				continue;
			bs.Read(sPos);
			g_stStreamedOutInfo.iPlayerID[playerID] = playerID;
			g_stStreamedOutInfo.fPlayerPos[playerID][0] = sPos[0];
			g_stStreamedOutInfo.fPlayerPos[playerID][1] = sPos[1];
			g_stStreamedOutInfo.fPlayerPos[playerID][2] = sPos[2];
		}
	}
	return true;
}
// commands below
void komut_canpuanlari(char *params)
{
	struct actor_info *oyuncu = actor_info_get(ACTOR_SELF, NULL);
	if (!strlen(params))
	{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		addMessageToChatWindow("Usage: /.hp {00FF00}<HP value>");
#else
		addMessageToChatWindow("Kullanım: /.can {00FF00}<Can değeri>");
#endif 
		return;
	}
	oyuncu->hitpoints = atoi(params);
}
void komut_zirhpuanlari(char *params)
{
	struct actor_info *oyuncu = actor_info_get(ACTOR_SELF, NULL);
	if (!strlen(params))
	{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		addMessageToChatWindow("Usage: /.ap {00FF00}<AP value>");
#else
		addMessageToChatWindow("Kullanım: /.zirh {00FF00}<Zırh değeri>");
#endif 
		return;
	}
	oyuncu->armor = atoi(params);
}
void cmd_warp(char *params)
{
	if (params[0] == '\0')
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("/.goto <Target Player ID>");
#else
		return addMessageToChatWindow("/.goto <Oyuncu ID>");
#endif
	int playerid = atoi(params);
	if (isBadSAMPPlayerID(playerid) || g_Players->iIsListed[playerid] != 1)
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Target player is not connected!");
#else
		return addMessageToChatWindow("Oyuncu sunucuda yok.");
#endif 
	

	float pos[3];
	actor_info *actor = nullptr;
	if (g_Players->pRemotePlayer[playerid]->pPlayerData == nullptr
		|| g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == nullptr)
	{
		if (vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[playerid]))
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
			return addMessageToChatWindow("Target player is not found!");
#else
			return addMessageToChatWindow("Oyuncu haritada yok.");
#endif 

		vect3_copy(g_stStreamedOutInfo.fPlayerPos[playerid], pos);
		pos[1] += 1.0f;
		cheat_teleport(pos, 0);
		return;
	}

	if (!getPlayerPos(playerid, pos) ||
		g_Players->pRemotePlayer[playerid]->pPlayerData == nullptr ||
		g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == nullptr ||
		(actor = g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTA_Ped) == nullptr)
	{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Target player is not found!");
#else
		return addMessageToChatWindow("Hatalı oyuncu");
#endif 
	}

	pos[1] += 1.0f;
	cheat_teleport(pos, actor->base.interior_id);
}
void cmd_showCMDS(char *)
{
	for (int i = 0; i < g_m0dCmdNum; i++)
	{
		addMessageToChatWindow("%s", g_m0dCmdlist[i]);
	}
}
void cmd_rejoin(char *)
{
	restartGame();
	disconnect(500);
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("{00FF00}Please remain calm, reconnecting...");
#else
	addMessageToChatWindow("{00FF00}Bir kaç saniye beklemede kal...");
#endif
	cheat_state->_generic.rejoinTick = GetTickCount();
	/* Update score board */
	disconnect(500);
	restartGame();
	g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
	updateScoreboardData();

}
 
void komut_arkadas_ekle(char *params)
{
	if (params[0] == '\0')
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Usage: /.addfriend <Target Player ID>");
#else
		return addMessageToChatWindow("Kullanımı: /.arkadas_ekle <Oyuncu ID>");
#endif
	int playerid = atoi(params);

	if (isBadSAMPPlayerID(playerid) || g_Players->iIsListed[playerid] != 1)
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Target player is not connected!");
#else
		return addMessageToChatWindow("Oyuncu sunucuda yok.");
#endif

	std::ofstream outputFile;
	char filename[512];
	std::string nick;
	std::string del;
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "FriendList.ini");
#else
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "DostListesi.ini");
#endif
	outputFile.open(filename, std::fstream::out | std::fstream::app);

	if (g_Players->pRemotePlayer[playerid]->strPlayerName.c_str()) // Default : if (g_Players->pRemotePlayer[playerid]->iNameAllocated <= 0xF)
	{
		nick = g_Players->pRemotePlayer[playerid]->strPlayerName.c_str(); //  Default : nick = g_Players->pRemotePlayer[playerid]->szPlayerName;
	}
	outputFile << nick << "\n";
	outputFile.close();
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("%s[ID:%d] is {00FF00}added to friend list!", nick.c_str(), playerid);
#else
	addMessageToChatWindow("%s[ID:%d] isimli oyuncu {00FF00}Arkadaşlar listesine eklendi.", nick.c_str(), playerid);
#endif
	/* Eğer girilen nick listede varsa listeden silsin o nicki. */
}
void komut_admin_ekle(char *params)
{
	if (params[0] == '\0')
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Usage: /.addadmin <Target Player ID>");
#else
		return addMessageToChatWindow("Kullanımı: /.admin_ekle <Oyuncu ID>");
#endif
	int playerid = atoi(params);

	if (isBadSAMPPlayerID(playerid) || g_Players->iIsListed[playerid] != 1)
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Target player is not connected!");
#else
		return addMessageToChatWindow("Oyuncu sunucuda yok.");
#endif

	std::ofstream outputFile;
	char filename[512];
	std::string nick;
	std::string del;
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminList.ini");
#else
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");
#endif
	outputFile.open(filename, std::fstream::out | std::fstream::app);
	if (g_Players->pRemotePlayer[playerid]->strPlayerName.c_str()) // Default : if (g_Players->pRemotePlayer[playerid]->iNameAllocated <= 0xF)
	{
		nick = g_Players->pRemotePlayer[playerid]->strPlayerName; //  Default : nick = g_Players->pRemotePlayer[playerid]->szPlayerName;
	}
	outputFile << nick << "\n";
	outputFile.close(); // close it.
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("%s [ID:%d] is {00FF00}added to admin list!", nick.c_str(), playerid);
#else
	addMessageToChatWindow("%s [ID:%d] isimli oyuncu {00FF00}Adminler listesine eklendi.", nick.c_str(), playerid);
#endif
}

void komut_admin_sil(char* params)
{
	if (params[0] == '\0')
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Usage: /.deladmin <Target Player ID>");
#else
		return addMessageToChatWindow("Kullanımı: /.admin_sil <Oyuncu ID>");
#endif
	int playerid = atoi(params);

	if (isBadSAMPPlayerID(playerid) || g_Players->iIsListed[playerid] != 1)
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Target player is not connected!");
#else
		return addMessageToChatWindow("Oyuncu sunucuda yok.");
#endif

	char filename[512];
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminList.ini");
#else
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");
#endif
	std::vector<std::string> nicklist;
	std::ifstream inputFile; // ERROR -> Redefiniton!! good xd
	std::string nick;

	// That should be it. Let's test. wait

	inputFile.open(filename);
	while (inputFile >> nick)
	{
		if (!strcmp(nick.c_str(), getPlayerName(playerid)))
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
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("%s [ID:%d] is {00FF00}DELETED in admin list.", nick.c_str(), playerid);
#else
	addMessageToChatWindow("%s [ID:%d] is {00FF00}Admin listesinden SİLİNDİ.", nick.c_str(), playerid);
#endif	/* Eğer girilen nick listede varsa listeden silsin o nicki. */
}

void komut_arkadas_sil(char* params)
{
	// nice one man with that teamviewer xd xD
	if (params[0] == '\0')
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Usage: /.delfriend <Target Player ID>");
#else
		return addMessageToChatWindow("Kullanımı: /.arkadas_sil <Oyuncu ID>");
#endif
	
	int playerid = atoi(params);

	if (isBadSAMPPlayerID(playerid) || g_Players->iIsListed[playerid] != 1)
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Target player is not connected!");
#else
		return addMessageToChatWindow("Oyuncu sunucuda yok.");
#endif

	char filename[512];
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminList.ini");
#else
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");
#endif

	std::vector<std::string> nicklist;
	std::ifstream inputFile; // ERROR -> Redefiniton!! good xd
	std::string nick;

	inputFile.open(filename);
	while (inputFile >> nick)
	{
		if (!strcmp(nick.c_str(), getPlayerName(playerid)))
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
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("%s [ID:%d] is {00FF00}DELETED in friend list.", nick.c_str(), playerid);
#else
	addMessageToChatWindow("%s [ID:%d] is {00FF00}Admin listesinden SİLİNDİ.", nick.c_str(), playerid);
#endif	
	/* Eğer girilen nick listede varsa listeden silsin o nicki. */
}

void komut_deleteallfriends(char*)
{
	char filename[512];
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminList.ini");
#else
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");
#endif
	std::ofstream outputFile;
	outputFile.open(filename, std::ios::trunc);
	outputFile.close();
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("All of your friends are deleted!");
#else
	addMessageToChatWindow("Bütün arkadaşlar listeden {FF0000}SİLİNDİ.");
#endif
}
void komut_deletealladmins(char*)
{
	char filename[512]; // max 512!!
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminList.ini");
#else
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");
#endif
	std::ofstream outputFile;
	outputFile.open(filename, std::ios::trunc);
	outputFile.close();
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("All of your friends are deleted!");
#else
	addMessageToChatWindow("Bütün arkadaşlar listeden {FF0000}SİLİNDİ.");
#endif
}
/* Eğer girilen nick listede varsa listeden silsin o nicki. */

void komut_nickdegistir(char *params)
{
	//if (modcommands == false) return;
	if (!strlen(params))
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Usage: /.rnick <Your New NickName>");
#else
		return addMessageToChatWindow("Örnek kullanım: /.isim <Yeni ismin>");
#endif
	if (strlen(params) < 3 || strlen(params) > SAMP_ALLOWED_PLAYER_NAME_LENGTH)
	{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		addMessageToChatWindow("UYARI: En az 3, En fazla 20 Karakter içeren bir isim seçebilirsin.");
#else
		addMessageToChatWindow("WARNING: Your nick name must be between 3-20 chars!");
#endif
	}

	setLocalPlayerName(params);
	disconnect(500);
	restartGame();
	g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
	updateScoreboardData();
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("Your new nickname has been set as: %s",params);
#else
	addMessageToChatWindow("Yeni ismin %s olarak ayarlandı.",params);
#endif
	cheat_state->_generic.rejoinTick = GetTickCount();

}
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
void komut_minigunal(char *)
{
	pPedSelf->GiveWeapon((eWeaponType)38, 9999);
	addMessageToChatWindow("Minigun verildi.");
}
#endif
void cmd_slap(char *params)
{
	char szPlayerID[128], szVehicleID[128];
	
	int ipc = sscanf(params, "%s%s", szPlayerID, szVehicleID);
	if (ipc < 2)
	{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		addMessageToChatWindow("Usage: /.troll <Target Player ID> <Vehicle ID>");
		addMessageToChatWindow("Note: If you want to see vehicle IDs, type /DL");
#else
		addMessageToChatWindow("Örnek Kullanım: /.troll <Oyuncu ID> <Araç ID>");
		addMessageToChatWindow("Not: Araçların ID'sini görmek istiyorsan /DL komutunu kullanmalısın.");
#endif
		return;
	}

	int iPlayerID = atoi(szPlayerID), iVehicleID = atoi(szVehicleID);

	if (iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return;

	if (g_Players->sLocalPlayerID == iPlayerID || g_Players->pRemotePlayer[iPlayerID] == NULL)
		return;

	if (!ValidVehicle(iVehicleID))
		return;

	if (getPlayerState(iPlayerID) != PLAYER_STATE_ONFOOT && getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER)
		return;

	float coord[3] = { g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0], g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1], g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2] };
	float pos[3] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ };

	struct vehicle_info *info = g_SAMP->pPools->pVehicle->pSAMP_Vehicle[iVehicleID]->pGTA_Vehicle;
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);

	self->vehicle = info;

	stInCarData sync;
	RakNet::BitStream bsVehicleSync;

	memset(&sync, 0, sizeof(stInCarData));

	sync.sVehicleID = iVehicleID;
	sync.fVehicleHealth = info->hitpoints;
	sync.fMoveSpeed[0] = info->speed[0];
	sync.fMoveSpeed[1] = info->speed[1];
	sync.fMoveSpeed[2] = info->speed[2];
	sync.bytePlayerHealth = self->hitpoints;
	sync.byteArmor = self->armor;

	cheat_vehicle_teleport(info, coord, 0);

	GTAfunc_RemoveActorFromCarAndPutAt(pos);

	vect3_copy(&info->base.matrix[12], sync.fPosition);

	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
	g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

	sync.fMoveSpeed[2] = info->speed[2] + 6.0f;
	vect3_copy(sync.fMoveSpeed, info->speed);

	bsVehicleSync.Reset();
	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
	g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);
}
void cmd_pmAll(char*params)
{
	if (!strlen(params)) 
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		return addMessageToChatWindow("Usage: /.pm <Message>");
#else
		return addMessageToChatWindow("Örnek kullanım: /.pm <PM Mesajı>");
#endif
	for (int x = 0;
		x < SAMP_MAX_PLAYERS;
		x++)
	{
		if (IsPlayerConnected(x)) // Hedef oyuncu bağlı mı?
		{
			KomutYaz("/pm %i %s", x, params);
		}
	}
}
void komut_framelimit(char*)
{
	if (pGame->GetSettings()->IsFrameLimiterEnabled() == false)
	{
		pGame->GetSettings()->SetFrameLimiterEnabled(true);
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		addMessageToChatWindow("{00FF00}Vertical Sync is activated!");
#else
		addMessageToChatWindow("{00FF00}Vertical Sync aktifleştirildi.");
#endif
	}
	else
	{
		pGame->GetSettings()->SetFrameLimiterEnabled(false);
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
		addMessageToChatWindow("{FF0000}Vertical Sync is disabled!");
#else
		addMessageToChatWindow("{FF0000}Vertical Sync kapatıldı.");
#endif
	}

}
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL && COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
void cmd_botname(char* params)
{
	if (params[0] == '\0')
		return addMessageToChatWindow("/.botname nick");
	g_BotFuncs->OL_Add_Bot_Nick(params);

}
#endif

void cmd_fakecrash(char*)
{
	disconnect(0);
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addMessageToChatWindow("You have left from this server by Timeout/Crash");
#else
	addMessageToChatWindow("Sunucudan, Timeout/Crash sebebiyle çıkış yaptın.");
#endif
	
}
void cmd_takedamage(char*)
{
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i))
		{
			g_RakClient->TakeDamage(i, 0, 4, 3);
			g_RakClient->TakeDamage(i, 1833.331542, 4, 3);
		}
	}
}
void cmd_changegpci(char* param)
{
	HKEY key;
	if (RegOpenKey(HKEY_CURRENT_USER, "Software\\SAMP\\", &key) != ERROR_SUCCESS)
		return addMessageToChatWindow("Unable to open registry at \"Software\\SAMP\\\"");

	if (strlen(param) >= 1)
	{
		if (RegSetValueEx(key, "GPCI_SPECIAL", 0, REG_SZ, (LPBYTE)param, strlen(param) * sizeof(char)) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			return addMessageToChatWindow("Unable to set registry value at \"Software\\SAMP\\GPCI_SPECIAL\"");
		}

		addMessageToChatWindow("GPCI Changed to special preference: %s", param);
		addMessageToChatWindow("Effective after restart and remains forever as long as mod remains in your directory.");
		ChangeGPCI();
	}
	else
	{
		std::string randomval = "";
		for (int i = 0; i < 32; i++)
		{
			randomval += std::to_string(rand() % 9);
		}

		if (RegSetValueEx(key, "GPCI_SPECIAL", 0, REG_SZ, (LPBYTE)randomval.c_str(), strlen(randomval.c_str()) * sizeof(char)) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			return addMessageToChatWindow("Unable to set registry value at \"Software\\SAMP\\GPCI_SPECIAL\"");
		}

		addMessageToChatWindow("GPCI Changed. You can also add text parameter so you can switch between old and new.");
		addMessageToChatWindow("Effective after restart and remains forever as long as mod remains in your directory.");
		ChangeGPCI();
	}

	RegCloseKey(key);
	return;
}
void cmd_wep(char* params)
{
	int iSilahID, iMermi;
	if (g_Players->pLocalPlayer == NULL)
		return;
	loadAllWeaponModels();
	if (!strlen(params) || sscanf(params, "%d%d", &iSilahID, &iMermi) < 2)
		return addMessageToChatWindow("Kullanım: /.wep (Silah id) (Mermi değeri)");
	if (iSilahID < 0 || iSilahID > 46)
		return addMessageToChatWindow("Hatalı silah ID'si.");
	pPedSelf->GiveWeapon((eWeaponType)iSilahID, iMermi);
	g_RakClient->GivePlayerWeapon(g_Players->sLocalPlayerID, iSilahID, iMermi);
	addMessageToChatWindow("%s isimli silah %i mermi ile verildi.", weapon_list[iSilahID].name,iMermi);
}
void cmd_delcar(char*params)
{
	char szVehicleID[128];

	int ipc = sscanf(params, "%s", szVehicleID);
	if (ipc < 1)
	{
		addMessageToChatWindow("[OZEL] /.dcar <aracid>");
		return;
	}
	float fPos[3];
	fPos[0] = 2.0;
	fPos[1] = 2.0;
	fPos[2] = 2.0;
	int iVehicleID = atoi(szVehicleID);
	struct vehicle_info* vehicle = getGTAVehicleFromSAMPVehicleID(iVehicleID);
	RakNet::BitStream bs;
	bs.Write(iVehicleID);
	bs.Write(1);
	g_RakClient->RPC(RPC_EnterVehicle, &bs);
	Sleep(750); // Aslında buradaki Sleep, GetTickCount
	g_RakClient->SendFakeDriverSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), fPos, 0.0, vehicle->speed);

}

void cmd_delallcar(char* params)
{
	char szVehicleID[128];

	int ipc = sscanf(params, "%s", szVehicleID);
	if (ipc < 1)
	{
		addMessageToChatWindow("[OZEL] /.dcar <aracid>");
		return;
	}
	//float fPos[3];
	//// 1587.70, 25.
	//fPos[0] = 2080.78;
	//fPos[1] = -1804.14;
	//fPos[2] = 13.38;
	//int iVehicleID = atoi(szVehicleID);
	//struct vehicle_info* vehicle = getGTAVehicleFromSAMPVehicleID(iVehicleID);
	//RakNet::BitStream bs;
	//bs.Write(iVehicleID);
	//bs.Write(1);
	//g_RakClient->RPC(RPC_EnterVehicle, &bs);
	//Sleep(750); // Aslında buradaki Sleep, GetTickCount
	//g_RakClient->SendFakeDriverSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), fPos, vehicle->hitpoints, vehicle->speed);
	
	float fPos[3]; // Pozisyonlar.. dizi ile tanımlı 0-1-2 pozisyonları ~rapidfirw
	static DWORD time = GetTickCount();
	for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
	{
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
			continue;
		float fPos[3];
		fPos[0] = 2080.78;
		fPos[1] = -1804.14;
		fPos[2] = 13.38;
		if (KEY_DOWN(VK_RBUTTON))
		{
			vect3_copy(&vinfo->base.matrix[4 * 3], fPos); // Veri kopyalaması
			RakNet::BitStream bs;
			bs.Write(iSAMPVehicleID);
			bs.Write(1);// 0 = Driver koltuğu, 1 = Sağ koltuk, 2 = arka koltuk, 3 = 2. arka koltuk. ~rapidfirw! discord.gg/nsfwhub
			g_RakClient->RPC(RPC_EnterVehicle, &bs);
			Sleep(750);
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		}
		time = GetTickCount();
	}
}
void initChatCmds(void)
{
	if (g_m0dCommands == true)
		return;

	//cheat_state_text("initiated modcommands");
	g_m0dCommands = true;
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	addClientCommand(".minigun", komut_minigunal);
	
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL && COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	addClientCommand(".botname", cmd_botname);
#endif
#endif

#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	addClientCommand(".pm", cmd_pmAll);
	addClientCommand(".cmds", cmd_showCMDS);
	addClientCommand(".goto", cmd_warp);
	//addClientCommand(".minigun", komut_minigunal);
	addClientCommand(".rnick", komut_nickdegistir);
	addClientCommand(".reconnect", cmd_rejoin);
	addClientCommand(".recon", cmd_rejoin);
	addClientCommand(".troll", cmd_slap);
	addClientCommand(".hp", komut_canpuanlari);
	addClientCommand(".ap", komut_zirhpuanlari);
	addClientCommand(".dgun", komut_dgun);
	addClientCommand(".addadmin", komut_admin_ekle);
	addClientCommand(".delalladmins", komut_deletealladmins);
	addClientCommand(".addfriend", komut_arkadas_ekle);
	addClientCommand(".delallfriends", komut_deleteallfriends);
	//
	addClientCommand(".deladmin", komut_admin_sil);
	addClientCommand(".delfriend", komut_arkadas_sil);
	addClientCommand(".framelimit", komut_framelimit);
	addClientCommand(".fcrash", cmd_fakecrash);
	/*addClientCommand(".invis", cmd_invisible);
	addClientCommand(".aim", cmd_aim);
	addClientCommand(".sil", cmd_removecars);*/
#else
	addClientCommand(".pm", cmd_pmAll);
	addClientCommand(".cmds", cmd_showCMDS);
	addClientCommand(".goto", cmd_warp);
	//addClientCommand(".minigun", komut_minigunal);
	addClientCommand(".rnick", komut_nickdegistir);
	addClientCommand(".reconnect", cmd_rejoin);
	addClientCommand(".recon", cmd_rejoin);
	addClientCommand(".troll", cmd_slap);
	addClientCommand(".hp", komut_canpuanlari);
	addClientCommand(".ap", komut_zirhpuanlari);
	addClientCommand(".addadmin", komut_admin_ekle);
	addClientCommand(".delalladmins", komut_deletealladmins);
	addClientCommand(".addfriend", komut_arkadas_ekle);
	addClientCommand(".delallfriends", komut_deleteallfriends);
	//
	addClientCommand(".deladmin", komut_admin_sil);
	addClientCommand(".delfriend", komut_arkadas_sil);
	addClientCommand(".fcrash", cmd_fakecrash);
	//
	addClientCommand(".framelimit", komut_framelimit);
	addClientCommand(".takedamage", cmd_takedamage);
#endif
	addClientCommand(".cgpci", cmd_changegpci);
	addClientCommand(".delcar", cmd_delcar);
	addClientCommand(".delallcar", cmd_delallcar);

}
