#include<windows.h>
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
#include <vector>
#include <Digitalv.h>
#include "Global.h"
// ==========================================



#define MUSIC_PLAYER_ID_0 0
#define MUSIC_PLAYER_DEFAULT_VOLUME		800
#define MUSIC_PLAYER_LOW_VOLUME			300
#define MUSIC_PLAYER_VOLUME_ADJUST_STEP	100
// ==========================================



using namespace std;

class MucisPlayer
{
public:
	MucisPlayer()
	{
		MCI_OPEN_PARMS mciOpen; 
		MCIERROR mciError; 

		vector<wstring> musicFileName;
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 2\\09. Winnie-The-Pooh And The Honey Tree  (1966) - Winnie-The-Pooh.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 2\\15. New York World's Fair (1964) - It's A Small World .mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 1\\02. Reflection [Mulan (1998)].mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 1\\06. Just Around the Riverbend [Pocahontas (1995)].mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 1\\09. Beauty and the Beast [Beauty and the Beast (1991)].mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 2\\01. Tarzan (1999) - You'll Be In My Heart.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 2\\05. Pocahontas (1995) - Colors Of The Wind.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 2\\12. Cinderella  (1950) - A Dream Is A Wish Your Heart Makes.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 2\\20. Snow White (1937) - Some Day My Prince Will Come .mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 3\\01. Return To Never Land (2002) - I'll Try.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 3\\02. Toy Story 2 (1999) - When She Loved Me.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 1\\08. A Whole New World [Aladdin (1992)].mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 2\\06. The Lion King (1994) - Hakuna Matata.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 3\\08. Beauty And The Beast (1991) - Gaston.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 3\\10. The Little Mermaid (1989) - Part Of Your World.mp3");
		musicFileName.push_back(L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Disney's Greatest\\Volume 3\\20. Mickey Mouse Club (1955-59) - Mickey Mouse Club, Alma Mater.mp3");
		
		mciOpen.lpstrDeviceType = L"mpegvideo"; 

		UINT DeviceID = MUSIC_PLAYER_ID_0; 
		MCI_PLAY_PARMS mciPlay; 
		

		MCI_STATUS_PARMS mciStatus;  
		mciStatus.dwItem = MCI_STATUS_MODE;  

		// volume param.
		MCI_DGV_SETAUDIO_PARMS	mciSetAudioPara;
		mciSetAudioPara.dwCallback	= NULL;
		mciSetAudioPara.dwItem	= MCI_DGV_SETAUDIO_VOLUME;
		mciSetAudioPara.dwValue	= MUSIC_PLAYER_DEFAULT_VOLUME;

		bool first_play = true;

		int music_id = 0;
		while(true && !can_exit)
		{
			if(!can_play_background_music)
			{
				Sleep(1000);
				continue;
			}

			if(first_play)
			{
				Sleep(3000);
				first_play = false;
			}

			mciSendCommand(DeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatus);  

			if(mciStatus.dwReturn == MCI_MODE_PLAY)
			{
				if(record_voice_playing)
				{
					// set down music volume
					if(mciSetAudioPara.dwValue > MUSIC_PLAYER_LOW_VOLUME)
					{
						mciSetAudioPara.dwValue -= MUSIC_PLAYER_VOLUME_ADJUST_STEP;
						mciSendCommand(DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE |  MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciSetAudioPara);
						Sleep(1000);
						continue;
					}		
				}
				else
				{
					// set down music volume
					if(mciSetAudioPara.dwValue < MUSIC_PLAYER_DEFAULT_VOLUME)
					{
						mciSetAudioPara.dwValue += MUSIC_PLAYER_VOLUME_ADJUST_STEP;
						mciSendCommand(DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE |  MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciSetAudioPara);
						Sleep(1000);
						continue;
					}		
				}
			}
			else
			{
				LPCWSTR a = (musicFileName[music_id]).c_str();
				mciOpen.lpstrElementName = a; 
				mciError = mciSendCommand((UINT)MUSIC_PLAYER_ID_0,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&mciOpen); 
				if(mciError) 
				{ 
					printf("send MCI_OPEN command failed\n"); 
					return; 
				}

				DeviceID = mciOpen.wDeviceID ; 


				// set up music volume 
				mciSendCommand(DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE |  MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciSetAudioPara);  

				mciError = mciSendCommand(DeviceID, MCI_PLAY,0 ,(DWORD)&mciPlay); 
				if(mciError) 
				{ 
					printf("send MCI_PLAY command failed\n"); 
					return; 
				}

				//printf("Current Music ID: %d\n", music_id);
				music_id++;
				if(music_id >= (int)musicFileName.size())
					music_id = 0;
			}

			Sleep(5000);
		}
	}
};



