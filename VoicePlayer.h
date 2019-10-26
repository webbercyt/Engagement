#include <iostream>
#include <windows.h>
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
#include "Global.h"


#define MUSIC_PLAYER_ID_1	1
// ==========================================

using namespace std;

class VoicePlayer
{
public:
	// set up music player
	MCI_OPEN_PARMS mciOpen; 
	MCIERROR mciError; 
	UINT DeviceID; 
	MCI_PLAY_PARMS mciPlay; 
	MCI_STATUS_PARMS mciStatus;  	

	VoicePlayer()
	{
		DeviceID = MUSIC_PLAYER_ID_1; 
		mciStatus.dwItem = MCI_STATUS_MODE;	
		mciOpen.lpstrDeviceType = L"mpegvideo"; 
	}

	void play(wstring filename)
	{
		if(record_voice_playing)
			return;

		record_voice_playing = true;			

		mciSendCommand(DeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatus);
		if(mciStatus.dwReturn == MCI_MODE_PLAY)
				return;

		mciOpen.lpstrElementName = filename.c_str();
		mciError = mciSendCommand((UINT)MUSIC_PLAYER_ID_1,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&mciOpen); 
		if(mciError) 
		{ 
			printf("send MCI_OPEN command failed\n"); 
			return; 
		}

		DeviceID = mciOpen.wDeviceID ; 

		mciError = mciSendCommand(DeviceID, MCI_PLAY,0 ,(DWORD)&mciPlay); 
		if(mciError) 
		{ 
			printf("send MCI_PLAY command failed\n"); 
			return; 
		}

		while(true)
		{
			if(record_voice_playing)
			{
				mciSendCommand(DeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatus);
				if(mciStatus.dwReturn == MCI_MODE_STOP)
				{
					record_voice_playing = false;
					mciSendCommand (DeviceID, MCI_CLOSE, NULL, NULL);
					break;
				}
			}

			Sleep(3000);
		}
	}
};