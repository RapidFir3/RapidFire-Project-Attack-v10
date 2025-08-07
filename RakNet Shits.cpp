#include "main.h"

void RF_FakeKick()
{
	if (cheat_state->RakNet.iFakeKick)
	{
	//	addMessageToChatWindow("You are kicked from server By Fake Kick function.");
		if (g_RakClient) g_RakClient->SendEnterVehicleNotification(0xFFFF, 0);
	}
}
void RF_FakeLeave()
{
	if (cheat_state->RakNet.iFakeLeave)
	{
		//addMessageToChatWindow("You have disconnected from server by Fake Leave function.");
		disconnect(500);
	}
}
void RF_FakeTimeout()
{
	if (cheat_state->RakNet.iFakeTimeout)
	{
		//addMessageToChatWindow("You have disconnected from server by Fake Timeout function.");
		disconnect(0);
	}
}
void RF_ZeroPingExploit(void)
{
	if (cheat_state->RakNet.iZeroPingExploit)
	{
		static DWORD Delay = 0;
		//if (GetTickCount() - Delay > 2000)
		{
			RakNet::BitStream outBitStream;
			outBitStream.Write((unsigned char)ID_CONNECTED_PONG);
			RakNetTime timeMS = RakNet::GetTime();
			outBitStream.Write((unsigned int)-1);
			outBitStream.Write(timeMS);
			g_RakClient->Send(&outBitStream, SYSTEM_PRIORITY, UNRELIABLE, 0);
			Delay = GetTickCount();
			//cheat_state_text("ping data sent!");
		}
	}
}
void RN_Fonksiyonlari(void)
{
	RF_FakeKick();
	RF_FakeLeave();
	RF_FakeTimeout();
	RF_ZeroPingExploit();

}