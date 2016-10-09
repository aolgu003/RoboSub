#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

//returns true if black
bool blackWhite(Mat chans[3],int y, int x)
{


    chans[0];
    chans[1];
    chans[2];

    if(chans[0].at<unsigned char>(y,x) < 20 || chans[0].at<unsigned char>(y,x) > 150)
    {
      if(chans[1].at<unsigned char>(y,x)<40)
        {
          return true;
        }
      else
        {
          if(chans[2].at<unsigned char>(y,x) < 30 || chans[2].at<unsigned char>(y,x) > 230 )
            {
              return true;
            }
          else
            {
              return false;
            }
        }
    }
    else
    {
      return true;
    }

}

// Point[] findSeed(Mat J)
// {
//   /*
//   w = size(J,1);
//   h = size(J,2);
//
//   num_w = floor(w/16);
//   num_h = floor(h/16);
//   x = [];
//   y = [];
//
//   for i=1:num_w
//       for j=1:num_h
//           if i == 1 && j == 1
//               small_J = J(1:16, 1:16);
//
//               num_pixels = sum(sum(small_J));
//               if num_pixels >= 60
//                   x = 8;
//                   y = 8;
//               end
//           elseif j == 1
//               small_J = J(((i-1)*16):(i*16) , 1:16);
//
//               num_pixels = sum(sum(small_J));
//               if num_pixels >= 60
//                   index_x = size(x)+1;
//                   index_y = size(y)+1;
//
//                   y(index_x) = (i-i)*16+8;
//                   x(index_y) = 8;
//               end
//           elseif i == 1
//               small_J = J(1:16,((j-1)*16):(j*16));
//
//               num_pixels = sum(sum(small_J));
//               if num_pixels >= 60
//                   index_x = size(x)+1;
//                   index_y = size(y)+1;
//
//                   y(index_x) = 8;
//                   x(index_y) = 8+16*(j-1);
//
//               end
//           else
//               small_J = J(((i-1)*16):(i*16),((j-1)*16):(j*16));
//
//               num_pixels = sum(sum(small_J));
//               if num_pixels >= 60
//                   index_x = size(x)+1;
//                   index_y = size(y)+1;
//
//                   y(index_x) = 8+16*(i-1);
//                   x(index_y) = 8+16*(j-1);
//               end
//           end
//       end
//   end*/
// }

unsigned char/***/ shapeSegmentation(Mat& I)
{
  Mat hsvI;
  cvtColor(I,hsvI,CV_RGB2HSV,0);
  Mat chans[3];

  // may not actually be seperated as hsv order
  split(hsvI,chans);
  // imshow("hue",chans[0]);
  Mat filtered;

  medianBlur(chans[0],filtered,7);//filters a single channel
  filtered.copyTo(chans[0]);
  merge(chans,3,hsvI);//mnerges back into hsvI


  Mat  norm_hsv;
  hsvI.convertTo(norm_hsv,CV_8UC3);//should probably check if this actually normalized the mat
  // double min, max;
  // cv::minMaxLoc(norm_hsv, &min, &max);
  // cout << min << " " << max<<endl;
  //to deterimine if normalized. nothing should be above 255



  split(norm_hsv,chans);
  //check each value of the split array than edit accordingly
  //turn norm_hsv to black or white

//converts image to black and white based on criteria in blackWhite(Mat,int i,int j)
  for (int i = 0; i < chans[0].size().height; ++i)
  {
    for(int j = 0; j < chans[0].size().width; ++j)
    {
      // cout<<"i:"<<i <<",j:"<<j<<":";
      if(blackWhite(chans,i,j))
      // if(true)
      {
        chans[0].at<unsigned char>(i,j)  = 0;
        // cout<<(int)chans[0].at<unsigned char>(i,j)<<endl;
      }
      else
      {
        chans[0].at<unsigned char>(i,j) = 255;
        // cout<<(int)chans[0].at<unsigned char>(i,j)<<endl;
      }
    }
  }

  //find contours
  vector< vector<cv::Point> > contours;
  findContours(chans[0],contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
  //find contour area
  vector<double> conAreas(contours.size());

  for(int i = 0; i < contours.size(); ++i)
  {
    conAreas.at(i) = contourArea(contours.at(i));
  }

  //PLEASE REWRITE THIS LATER
  //REMOVING CONTOURS WITH SIZE LESS THAN 60
  vector< vector<cv::Point> > seeds;
  for(int i =0; i < conAreas.size(); ++i)
  {
    if(conAreas.at(i) >=16.0)
    {
      seeds.push_back(contours.at(i));
      cout << contours.at(i) << endl;

    }
  }

  Mat cons = Mat::zeros(chans[0].rows, chans[0].cols, CV_8UC3);
  Scalar white(255,255,255);

  drawContours(cons,seeds,-1,white,CV_FILLED,LINE_8,noArray());
  imwrite("segmented.jpg",cons);
  imshow("Contours",cons);
  //using split and merge you can filter a single channel and merge them
  waitKey(0);
  return 0;//J;
}

int main() {
  cout << "Please Enter FileName"<<endl;
  string f;
  cin >> f;
  Mat I;

  I = imread(f,1);
  if(!I.data)
  {
    cout <<"Could not load image"<<endl;
    return -1;
  }
  imshow("Origianl",I);
  shapeSegmentation(I);
  waitKey(0);
  return 0;
}
