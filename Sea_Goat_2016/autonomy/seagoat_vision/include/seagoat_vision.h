//#include "seagoat_vision.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>
#include <string.h>
#include "comms.h"

using namespace cv;
using namespace std;

//TARGET DEFINITIONS
#define INITIAL_GATE 0
#define MARKERS 1
#define RED_BUOY 2
#define YELLOW_BUOY 3
#define GREEN_BOUY 4
#define MANUVERING_GATE 5
#define BINS 6
#define TORPEDO 7
#define END_GATE 8

//PROTOCAL DEFINITIONS
#define RS232 0
// perhaps others eventually ... 

class vision {
	private:
		//Here goes the constants for: color thresholding, intrinsic camera matrix, object points, distortion Coeff
		VideoCapture vid_cam;
		char classification; //classification as defined by the macros
		char command;	
		int x, y; //pixel location
		float theta; //angle relative to the camera frame
		Mat frame;
		float depth;

	public:
		//member accessor functions
		int getX();
		int getY();
		float getTheta();
		float getDepth();

		void setClass(char classification);
		void setX(int X);
		void setY(int Y);
		void setTheta(float theta);
		void setDepth(float depth);	
		void setCommand(char command);	

		//////////////////////
		vision();
		vision(VideoCapture cap);

		void viewVideo(); //plays whatever video stream that is associated with vid_cam
		//void saveVideo(); //saves whatever video stream that is associated with vid_cam
		//void grabandsaveFrame(); //grabs a frame from the video stream and saves it	

		void detect(char classification);
		void transmit(cArduino* port);
		float getCurrentDepth();
		float getCurrentDepth(cArduino* port);
};
