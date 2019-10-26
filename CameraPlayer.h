#include <map>
#include <thread>

#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\aruco.hpp>
#include <opencv2\videoio.hpp>

#include "Global.h"
#include <iostream>
#include <windows.h>
// ==========================================



using namespace std;

class CameraPlayer
{
public:
	cv::String video_window_name;

	CameraPlayer()
	{
		video_window_name = "LOVE";

		// set up camera
		cv::VideoCapture cam(0);   //0 is the id of video device.0 if you have only one camera.
 
		if (!cam.isOpened()) { //check if video device has been initialised
			std::cout << "cannot open camera" << std::endl;
			return;
		}

		cv::Ptr<cv::aruco::DetectorParameters> detectorParams = cv::aruco::DetectorParameters::create();
		cv::Ptr<cv::aruco::Dictionary> dictionary = 
			cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME(0));

		while (true) {
			if(found_marker)
			{
				Sleep(5000);
				continue;
			}

			cv::Mat image;
			cam.read(image);

			vector< int > ids;
			vector< vector< cv::Point2f > > corners;
			vector< cv::Vec3d > rvecs, tvecs;

			// detect markers and estimate pose
			cv::aruco::detectMarkers(image, dictionary, corners, ids, detectorParams);

			

			if(ids.size() == 1)
			{	
				if(ids[0] == 0)
				{
						
				}
				else if(!record_voice_playing)
				{
					/*if(ids[0] == current_section)
					{
						current_section = DEFAUKT_SECTION_ID;
						continue;
					}*/	// don't know why, fix later

					if(next_section == ids[0])
					{
						if(!can_play_background_music)
							can_play_background_music = true;

						current_section = ids[0];
						next_section++;
					}
					else
						continue;

					//cv::destroyWindow(video_window_name);
					found_marker = true;
				}
			}


			/*imshow(video_window_name, image);
			cv::waitKey(1);*/

			if (cv::waitKey(30) >= 0)
			{
				can_exit = true;
				break;
			}
		}

		cam.release();
	}
};