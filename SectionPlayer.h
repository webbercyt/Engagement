#include <map>
#include "Global.h"
#include "VoicePlayer.h"

class SectionPlayer
{
public:
	SectionPlayer()
	{
		map<int, wstring>	pageFileName;
		map<int, wstring>	voiceFileName;
		map<int, DWORD>		waitTime;
		VoicePlayer* voicePlayer = new VoicePlayer();

		// add page file 
		pageFileName.emplace(0, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S1\\index.html");
		pageFileName.emplace(1, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S2\\index.html");
		pageFileName.emplace(2, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S3\\index.html");
		pageFileName.emplace(3, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S4\\index.html");
		pageFileName.emplace(4, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S5\\index.html");
		pageFileName.emplace(5, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S6\\index.html");
		pageFileName.emplace(6, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S7\\index.html");
		pageFileName.emplace(7, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S8\\index.html");
		pageFileName.emplace(8, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S9\\index.html");
		pageFileName.emplace(9, L"open C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\html\\S10\\index.html");

		// add wait time
		//waitTime.emplace(0, 10000);

		// add voice file
		voiceFileName.emplace(0, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\1.mp3");
		voiceFileName.emplace(1, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\2.mp3");
		voiceFileName.emplace(2, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\3.mp3");
		voiceFileName.emplace(3, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\4.mp3");
		voiceFileName.emplace(4, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\5.mp3");
		voiceFileName.emplace(5, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\6.mp3");
		voiceFileName.emplace(6, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\7.mp3");
		voiceFileName.emplace(7, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\8.mp3");
		voiceFileName.emplace(8, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\9.mp3");
		voiceFileName.emplace(9, L"C:\\Users\\user\\Desktop\\Abigail's Files\\ArUco\\Record Voice\\10.mp3");


		STARTUPINFO si;
		memset(&si,0,sizeof(STARTUPINFO));
		si.cb=sizeof(STARTUPINFO);
		si.dwFlags=STARTF_USESHOWWINDOW;
		si.wShowWindow=SW_SHOWMAXIMIZED;
		PROCESS_INFORMATION pi;
		bool has_page = false; 

		while(true)
		{
			if(!found_marker)
			{
				Sleep(500);
				continue;
			}

			//printf("current_section = %d\n", current_section);

			if(has_page)
			{
				has_page = false;
				TerminateProcess(pi.hProcess, 1);
				CloseHandle(pi.hThread);
				CloseHandle(pi.hProcess);
			}

			Sleep(300);
			if(pageFileName.find(current_section) != pageFileName.end())
			{
				has_page = true;
			
				if(!CreateProcess(L"C:\\Program Files\\Internet Explorer\\iexplore.exe", LPWSTR(pageFileName[current_section].c_str()), 
					NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
					printf("Failed\n");
			}	

			if(voiceFileName.find(current_section) != voiceFileName.end())
				voicePlayer->play(voiceFileName[current_section]);

			/*if(waitTime.find(current_section) != waitTime.end())
				Sleep(waitTime[current_section]);
			else
				Sleep(3000);*/	

			found_marker = false;
		}
	}
};