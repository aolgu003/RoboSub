#include "segmentation.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

using namespace std;
using namespace cv;

int numPixels(Mat& I);

//////////////////////////////////////////////

segmentation::segmentation(char classification) {
	/* what if we were to read from text file so that we can modify easily using JK's slider code that he has */ 
	//this->set_thresholds(classification);

} 	

void segmentation::set_thresholds(char classification) {
	ifstream thresholds;
	string line;
	cout << "Setting thresholds for: " << endl;
	if (classification == 0) {

	} else if(classification == 1) {
		cout << "thresholds/MARKER.txt" << endl;
		thresholds.open("thresholds/MARKER.txt");
		int i = 0;
		int thresh_val;
		while (getline( thresholds, line )) {
			cout << "Getting lines" << endl;
			thresh_val = atoi(line.c_str());
			cout << thresh_val << endl;
			if (i == 0) {
				hue_lower = thresh_val;
			} else if (i == 1) {
				hue_upper = thresh_val;
			} else if (i == 2) {
				sat_lower = thresh_val;
			} else if (i == 3) {
				sat_upper = thresh_val;
			} else if (i == 4) {
				var_lower = thresh_val;
			} else if (i == 5) {
				sat_upper = thresh_val;
			}
		}
		thresholds.close();
		
	} else if(classification == 2) {
		cout << "Searching for red buoy" << endl;
	} else if(classification == 3) {
		cout << "Searching for yellow buoy" << endl;
	} else if(classification == 4) {
		cout << "Searching for green buoy" << endl;
	} else if(classification == 5) {
		cout << "Searching for manuvering gate" << endl;
	} else if(classification == 6) {
		cout << "Searching for bins" << endl;
	} else if(classification == 7) {
		cout << "Searching for torpedo target" << endl;
	} else if(classification == 8) {
		cout << "Searching for end gate" << endl;
	} else {
		cout << "Error: No such target classification" << endl;
	}
}

void segmentation::thresh() {
	/*Mat src, dst_img;
	pyrDown(this->result, src);
	double t;
  Mat dst(src.size(), CV_8UC1, Scalar(0));
 // Mat dist(src.size(), CV_8UC1, Scalar(0));
  t = (double) getTickCount();

  Mat rgb[3];
  split(src, rgb);
  //merge(rgb, 3, src);

  vector<vector<Point> > contours;
  Mat hsvI, gradh, grads;
  cvtColor(src,hsvI,CV_RGB2HSV,0);
  medianBlur(hsvI, hsvI, 7);

  //cvtColor(out,hsvI,CV_RGB2HSV,0);
  Mat chans[3];
  
  // may not actually be seperated as hsv order
  split(hsvI,chans);
  Mat filtered;
	unsigned char h,s,v;
	imshow("Sat",chans[1]);
	imshow("Hue",chans[0]);
	imshow("Var",chans[2]);
//converts image to black and white based on criteria in blackWhite(Mat,int i,int j)
  for (int i = 0; i < chans[0].size().height; ++i)
  {
    for(int j = 0; j < chans[0].size().width; ++j)
    {
	  h = chans[0].at<unsigned char>(i,j);
	  s = chans[1].at<unsigned char>(i,j);
	  v = chans[2].at<unsigned char>(i,j);

      if(this->blackWhite(h,s,v))
      {
        chans[0].at<unsigned char>(i,j)  = 255;
      }
      else
      {
        chans[0].at<unsigned char>(i,j) = 0;
      }
    }
  }

	dst = chans[0].clone();
	Mat element = getStructuringElement( MORPH_RECT, Size( 2*2 + 1, 2*2+1 ), Point( 2, 2 ) );
	morphologyEx(chans[0],chans[0],MORPH_OPEN,element,Point(-1,-1),2,BORDER_CONSTANT);
    findContours(chans[0], contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	vector<vector<Point> >hull( contours.size() );	

    for( size_t i = 0; i < contours.size(); i++ ) {
        // approximate contour with accuracy proportional
    	// to the contour perimeter
		convexHull( Mat(contours[i]	), hull[i], false );
	}

	drawContours( dst, hull, -1, Scalar(255), CV_FILLED, LINE_8,noArray());
 
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    cout << "Time of segmenting image " << t << " milliseconds."<< endl;

	imshow("Orignal image",src);
	imshow("Orignal image",dst);*/
}

void segmentation::watershed() {
	/*Mat src, dst_img;
	pyrDown(this->result, src);
	double t;
  Mat dst(src.size(), CV_8UC1, Scalar(0));
 // Mat dist(src.size(), CV_8UC1, Scalar(0));
  t = (double) getTickCount();

  Mat rgb[3];
  split(src, rgb);
  //merge(rgb, 3, src);

  vector<vector<Point> > contours;
  Mat hsvI, gradh, grads;
  cvtColor(src,hsvI,CV_RGB2HSV,0);
  medianBlur(hsvI, hsvI, 7);

  //cvtColor(out,hsvI,CV_RGB2HSV,0);
  Mat chans[3];
  
  // may not actually be seperated as hsv order
  split(hsvI,chans);
  Mat filtered;
	unsigned char h,s,v;
	imshow("Sat",chans[1]);
	imshow("Hue",chans[0]);
	imshow("Var",chans[2]);
//converts image to black and white based on criteria in blackWhite(Mat,int i,int j)
  for (int i = 0; i < chans[0].size().height; ++i)
  {
    for(int j = 0; j < chans[0].size().width; ++j)
    {
	  h = chans[0].at<unsigned char>(i,j);
	  s = chans[1].at<unsigned char>(i,j);
	  v = chans[2].at<unsigned char>(i,j);

      if(this->blackWhite(h,s,v))
      {
        chans[0].at<unsigned char>(i,j)  = 255;
      }
      else
      {
        chans[0].at<unsigned char>(i,j) = 0;
      }
    }
  }

	dst = chans[0].clone();
	Mat element = getStructuringElement( MORPH_RECT, Size( 2*2 + 1, 2*2+1 ), Point( 2, 2 ) );
	morphologyEx(chans[0],chans[0],MORPH_OPEN,element,Point(-1,-1),2,BORDER_CONSTANT);
    Mat kernel1 = Mat::ones(7, 7, CV_8UC1);
    dilate(dst, dst, kernel1);

	// find contours and store them all as a list
    findContours(dst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	vector<vector<Point> >hull( contours.size() );
    vector<Point> approx;

    // test each contour
	Mat dist;
	distanceTransform(dst, dist, CV_DIST_L2, 3);
 	normalize(dist, dist, 0, 1., NORM_MINMAX);
	imshow("Distance transform", dist);
	
	threshold(dist, dist, .4, 1., CV_THRESH_BINARY);
    // Dilate a bit the dist image
    dilate(dist, dist, kernel1);
    imshow("Peaks", dist);

	 // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);
    // Find total markers
    findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32SC1);
    // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); i++)
        drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);
    // Draw the background marker
    circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);
    imshow("Markers", markers*10000);
	cout << "Input type: " << chans[1].type() << endl;
    // Perform the watershed algorithm
    //watershed(hsvI, markers);
    Mat mark = Mat::zeros(markers.size(), CV_8UC1);
    markers.convertTo(mark, CV_8UC1);
    bitwise_not(mark, mark);
    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
                                  // image looks like at that point    // Generate random colors*/
}

//bool blackWhite(Mat &chans[3],int y, int x)
bool segmentation::blackWhite(unsigned char h,unsigned char s,unsigned char v )
{
	if(h > 80 && h < 140) {
		if(s < 50 ) {
			return false;
    	} else {
			/*if(v > 230 || v < 30 ) {
            	return false;
        	} else {*/
			  return true;
            //}
        	}
    }
    else {
      return false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//returns number of white pixels of a binary image
int numPixels(Mat& I)
{
  int num = 0;
  for (int i = 0; i < I.size().height; ++i)
  {
    for(int j = 0; j < I.size().width; ++j)
    {
      if(  I.at<unsigned char>(i,j)  == 255)
      num++;

    }
  }
  return num;
}



