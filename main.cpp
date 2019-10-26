#include <thread>
#include "CameraPlayer.h"
#include "MusicPlayer.h"
#include "SectionPlayer.h"


using namespace std;

void camera_thread_func()
{
	CameraPlayer* cameraPlayer = new CameraPlayer();

	delete cameraPlayer;
}

void music_thread_func()
{
	MucisPlayer* musicPlayer = new MucisPlayer();

	delete musicPlayer;
}

void section_thread_func()
{
	SectionPlayer* sectionPlayer = new SectionPlayer();

	delete sectionPlayer;
}

int main()  
{  
	thread camera_thread(camera_thread_func);
	thread music_thread(music_thread_func);
	thread section_thread(section_thread_func);
	
	camera_thread.join();
	music_thread.join();
	section_thread.join();

	return 0;
}  