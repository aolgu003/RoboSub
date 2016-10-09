/*
* File:   main.cpp
* Author: sagar
*
* Created on 10 September, 2012, 7:48 PM
*/
 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
 
int main() {
VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.
 
if (!stream1.isOpened()) { //check if video device has been initialised
cout << "cannot open camera";
}
 
//unconditional loop
while (true) {
Mat cameraFrame;
stream1.read(cameraFrame);
imshow("cam", cameraFrame);
if (waitKey(30) >= 0)
break;
}
return 0;
}
