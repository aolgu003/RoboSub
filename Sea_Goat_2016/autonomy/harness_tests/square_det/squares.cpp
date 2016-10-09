// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <string.h>
#include <numeric>

using namespace cv;
using namespace std;

#define PI 3.1416

static void help()
{
    cout <<
    "\nA program using pyramid scaling, Canny, contours, contour simpification and\n"
    "memory storage (it's got it all folks) to find\n"
    "squares in a list of images pic1-6.png\n"
    "Returns sequence of squares detected on the image.\n"
    "the sequence is stored in the specified memory storage\n"
    "Call:\n"
    "./squares\n"
    "Using OpenCV version %s\n" << CV_VERSION << "\n" << endl;
}


int thresh = 50, N = 11;
const char* wndname = "Square Detection Demo";

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares( const Mat& image, vector<vector<Point> >& squares)
{
    squares.clear();

    Mat pyr, timg;

    // down-scale and upscale the image to filter out the noise
    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;

	// find contours and store them all as a list
            findContours(timg, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	    vector<vector<Point> >hull( contours.size() );
            vector<Point> approx;
            // test each contour

            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
		convexHull( Mat(contours[i]	), approx, false );
 
                //approxPolyDP(Mat(hull[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
		
                if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)) )
                {

                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 )
                        squares.push_back(approx);
                }
            }
		squares.push_back(approx);
/*
    // find squares in every color plane of the image
    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);
        // try several threshold levels
        for( int l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
            }
            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
            vector<Point> approx;
            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;
                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }
                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 )
                        squares.push_back(approx);
                }
            }
        }
    }
*/
}


// the function draws all the squaraes in the image
static void drawSquares( Mat& src, Mat& dst, const vector<vector<Point> >& squares )
{
	Mat temp = Mat(src.size(), CV_8U, Scalar(0));

	drawContours(temp, squares, -1, Scalar(255,0,0), 1);
	imshow("Edges", temp);
	dst = temp;
}

static void detectTarget(const Mat& src, Mat& dst) {
	Mat h_max, h_min, s_min, v_min, v_max;
	
	Mat hsvI, eq_img;
	vector<Mat> rgb(3);
	eq_img = src;
	split(eq_img, rgb);
	//equalizeHist(rgb[0], rgb[0]);
	//equalizeHist(rgb[1], rgb[1]);	
	//equalizeHist(rgb[2], rgb[2]);
	
	merge(rgb, eq_img);

	cvtColor(eq_img,hsvI,CV_RGB2HSV,0);
	Mat chans[3];

	  // may not actually be seperated as hsv order
	split(hsvI,chans);
	equalizeHist(chans[0], chans[0]);
	equalizeHist(chans[2], chans[2]);
	threshold(chans[0], h_min, 240, 255, CV_THRESH_BINARY_INV); //hue max thresh
	threshold(chans[0], h_max, 235, 255, CV_THRESH_BINARY); //hue min thresh
	threshold(chans[1], s_min, 200, 255, CV_THRESH_BINARY); //saturation min
	threshold(chans[2], v_min, 0, 20, CV_THRESH_BINARY_INV); //varience min 
	threshold(chans[2], v_max, 220, 255, CV_THRESH_BINARY); //varience max

	//imshow("Hue", h_min);
	//imshow("Sat", h_max);	
	//imshow("Var", chans[2]);

	dst = s_min;

	Mat element = getStructuringElement( MORPH_RECT, Size( 2*2 + 1, 2*2+1 ), Point( 2, 2 ) );

	morphologyEx(dst,dst,MORPH_OPEN,element,Point(-1,-1),2,BORDER_CONSTANT);
	imshow("detected target", dst);	
}

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

// Finds the intersection of two lines, or returns false.
// The lines are defined by (o1, p1) and (o2, p2).
bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2,
                      Point2f &r)
{
    Point2f x = o2 - o1;
    Point2f d1 = p1 - o1;
    Point2f d2 = p2 - o2;

    float cross = d1.x*d2.y - d1.y*d2.x;
    if (abs(cross) < /*EPS*/1e-8)
        return false;

    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
    r = o1 + d1 * t1;
    return true;
}

static void findMarkerAttitude(const Mat& edges, Mat& color_img, vector<vector<Point> >& squares ) {
	//Mat edge_img = edges;

	vector<Vec4i> lines;
	Vec4f fitlines, fitlines_alpha_rot;
	Mat label,clustered_lines;
	int clusterCount = 4;

	vector<vector<Point> > contours;
	cout << "Number of squares: " << squares.size() << endl;

	Mat edge_img = Mat::zeros( edges.size(), CV_8UC1 );

	//for( int i = 0; i< squares.size(); i++ ) {
	//	drawContours( color_img, squares, i, 255, 1, 8, CV_FILLED );
	//}

    	fitLine(Mat(squares[0]),fitlines,2,0,0.01,0.01);
	cout << squares[0] << endl;
	fitlines_alpha_rot = fitlines;
	//int lefty = (-fitlines[2]*fitlines[1]/fitlines[0])+fitlines[3];
	//int righty = ((edges.cols-fitlines[2])*fitlines[1]/fitlines[0])+fitlines[3];
	//line(color_img,Point(edges.cols-1,righty),Point(0,lefty),Scalar(255,0,0),2);

	float alpha = abs(atan2(fitlines[1], fitlines[0]));
	float alpha_rotated = alpha + PI/2;
	fitlines_alpha_rot[0] = -1*fitlines[1];
	fitlines_alpha_rot[1] = fitlines[0];
	//lefty = (-fitlines_alpha_rot[2]*fitlines_alpha_rot[1]/fitlines_alpha_rot[0])+fitlines_alpha_rot[3];
	//righty = ((edges.cols-fitlines_alpha_rot[2])*fitlines_alpha_rot[1]/fitlines_alpha_rot[0])+fitlines_alpha_rot[3];
	//line(color_img,Point(edges.cols-1,righty),Point(0,lefty),Scalar(255,0,0),2);

	cout << "Big angle: " << alpha << endl;
	cout << "Orthogonal angle: " << alpha_rotated  << endl;

	HoughLinesP(edges, lines, 1, CV_PI/180, 10, 5, 11 );

	Mat points(lines.size(), 7, CV_32F,Scalar(0));
	Mat features(lines.size(), 1, CV_32F,Scalar(0));
	Mat centers(4, 4, points.type());
	
	Vec4i single_line;
	float x0 , y0, x1, y1, x, y, theta, r, slope, intercept;
	float dif1, dif2, mag, i, j;
	float v1[2], v2[2];
	bool position = false;
	vector<Point> side1, side2, side3, side4;
	for(int i = 0; i < lines.size(); i++) {
		x0 = (float) lines[i][0];
		y0 = (float) lines[i][1];
	
		x1 = (float) lines[i][2];
		y1 = (float) lines[i][3];

		x = x1 - x0;
		y = y1 - y0;
		mag = sqrt(pow(x,2) + pow(y,2));
		v2[0] = x/mag;
		v2[1] = y/mag;
		
		theta = atan2(y,x)+ PI;
		v1[0] = fitlines[0];
		v1[1] = fitlines[1];
				
		//cout << "dot is: " << inner_product(v1, v1+1, v2, 0) << endl;
		
		if (theta > PI) { 
			theta = theta - PI;
		}
		//compare lines to fitted lines using a least squares curve fitting method and filter lines based on the side of the line that they are one
		//http://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
		//if they are on one side then store them together
		//once sorted then go ahead perform another fit for each line
		
		//use the dot product to find them
		dif1 = abs(cos(theta - alpha));
		dif2 = abs(cos(theta - alpha_rotated));
				
		if (dif1 > dif2) { //then the line is located on short side of the rectangle
			position = signbit(fitlines[0] * (y0 - fitlines[3]) - fitlines[1] * (x0 - fitlines[2]));
			if (position) {
				side1.push_back(Point2f(x0,y0));
				side1.push_back(Point2f(x1,y1));
				
			}
			else {
				side2.push_back(Point2f(x0,y0));
				side2.push_back(Point2f(x1,y1));
			}
		} else {
			position = signbit(fitlines_alpha_rot[0] * (y0 - fitlines_alpha_rot[3]) - fitlines_alpha_rot[1] * (x0 - fitlines_alpha_rot[2]));
			if (position) {
				side3.push_back(Point2f(x0,y0));
				side3.push_back(Point2f(x1,y1));
			}
			else {
				side4.push_back(Point2f(x0,y0));
				side4.push_back(Point2f(x1,y1));
			}
		}
	}
	
	cout << endl;
	cout << "Number of lines in side1: " << side1.size() << endl;
	cout << "Number of lines in side2: " << side2.size() << endl;
	cout << "Number of lines in side3: " << side3.size() << endl;
	cout << "Number of lines in side4: " << side4.size() << endl << endl << endl;

	//fit lines
	Vec4f fitlines1, fitlines2, fitlines3, fitlines4;
	fitLine(Mat(side1),fitlines1,2,0,0.01,0.01);
	cout << "Line fit 1: " << fitlines1 << endl;
	int lefty = (-fitlines1[2]*fitlines1[1]/fitlines1[0])+fitlines1[3];
	int righty = ((edges.cols-fitlines1[2])*fitlines1[1]/fitlines1[0])+fitlines1[3];
	line(color_img,Point(edges.cols-1,righty),Point(0,lefty),Scalar(255,0,0),2);

	fitLine(Mat(side2),fitlines2,2,0,0.01,0.01);
	cout << "Line fit 2: " << fitlines2 << endl;
	lefty = (-fitlines2[2]*fitlines2[1]/fitlines2[0])+fitlines2[3];
	righty = ((edges.cols-fitlines2[2])*fitlines2[1]/fitlines2[0])+fitlines2[3];
	line(color_img,Point(edges.cols-1,righty),Point(0,lefty),Scalar(0,255,0),2);

	fitLine(Mat(side3),fitlines3,2,0,0.01,0.01);
	cout << "Line fit 3: " << fitlines3 << endl;
	lefty = (-fitlines3[2]*fitlines3[1]/fitlines3[0])+fitlines3[3];
	righty = ((edges.cols-fitlines3[2])*fitlines3[1]/fitlines3[0])+fitlines3[3];
	line(color_img,Point(edges.cols-1,righty),Point(0,lefty),Scalar(255,0,255),2);

	fitLine(Mat(side4),fitlines4,2,0,0.01,0.01);
	cout << "Line fit 4: " << fitlines4 << endl;
	lefty = (-fitlines4[2]*fitlines4[1]/fitlines4[0])+fitlines4[3];
	righty = ((edges.cols-fitlines4[2])*fitlines4[1]/fitlines4[0])+fitlines4[3];
	line(color_img,Point(edges.cols-1,righty),Point(0,lefty),Scalar(0,0,255),2);

	Point2f fit1_point = Point2f(fitlines1[0] + fitlines1[2], fitlines1[1] + fitlines1[3]);
	
	Point2f fit2_point = Point2f(fitlines2[0] + fitlines2[2],fitlines2[1] + fitlines2[3]);


	Point2f fit3_point = Point2f(fitlines3[0] + fitlines3[2], fitlines3[1] + fitlines3[3]);
	
	Point2f fit4_point = Point2f(fitlines4[0] + fitlines4[2],fitlines4[1] + fitlines4[3]);

	Point2f corner1, corner2, corner3, corner4;

	if (intersection( fit1_point, Point2f(fitlines1[2], fitlines1[3]), fit2_point, Point2f(fitlines2[2], fitlines2[3]), corner1)) {
		cout << "corner1 found " << corner1 << endl;
		circle(color_img, corner1, 4, Scalar(255, 0,0), 3, 8, 0);
	}
	if (intersection( fit1_point, Point2f(fitlines2[2], fitlines2[3]), fit3_point, Point2f(fitlines3[2], fitlines3[3]), corner2))  {
		cout << "corner2 found " << corner2 << endl;
		circle(color_img, corner2, 4, Scalar(255, 0,0), 3, 8, 0);
	}
	if (intersection( fit3_point, Point2f(fitlines3[2], fitlines3[3]), fit4_point, Point2f(fitlines4[2], fitlines4[3]), corner3))  {
		cout << "corner3 found " << corner3 << endl;
		circle(color_img, corner3, 4, Scalar(255, 0,0), 3, 8, 0);
	}
	if  (intersection( fit4_point, Point2f(fitlines4[2], fitlines4[3]), fit1_point, Point2f(fitlines1[2], fitlines1[3]), corner4))  {
		cout << "corner4 found " << corner4 << endl;
		circle(color_img, corner4, 4, Scalar(255, 0,0), 3, 8, 0);
	}


	/*for (int i = 0; i < side1.size(); i++) {
		line(color_img, side1[i][0], side1[i][1] Scalar(255,0,0), 2, 8);
	}
	
	for (int i = 0; i < side2.size(); i++) {
		line(color_img, Point(side2[i][0], side2[i][1]), Point(side2[i][2], side2[i][3]), Scalar(0,255,0), 2, 8);
	}
	for (int i = 0; i < side3.size(); i++) {
		line(color_img, Point(side3[i][0], side3[i][1]), Point(side3[i][2], side3[i][3]), Scalar(255,0,255), 2, 8);
	}
	
	for (int i = 0; i < side4.size(); i++) {
		line(color_img, Point(side4[i][0], side4[i][1]), Point(side4[i][2], side4[i][3]), Scalar(0,255,255), 2, 8);
	}*/
	//Next find the vertices of the line intersections
	//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection


 	namedWindow( "Detected Lines", 1 );
	imshow( "Detected Lines", color_img );
}

int main(int /*argc*/, char** /*argv*/)
{
    static const char* names[] = { "../../image_data_set/lighting_data_set/1.jpg","../../image_data_set/lighting_data_set/2.jpg", "../../image_data_set/lighting_data_set/3.jpg","../../image_data_set/lighting_data_set/4.jpg","../../image_data_set/lighting_data_set/5.jpg","../../image_data_set/lighting_data_set/6.jpg","../../image_data_set/lighting_data_set/7.jpg","../../image_data_set/lighting_data_set/8.jpg","../../image_data_set/lighting_data_set/10.jpg",0 };
    help();
    vector<vector<Point> > squares;

    for( int i = 0; names[i] != 0; i++ )
    {
        Mat image = imread(names[i], 1);
        if( image.empty() )
        {
            cout << "Couldn't load " << names[i] << endl;
            continue;
        }
	pyrDown(image, image);
	pyrDown(image, image);
	//pyrDown(image, image);
	Mat binary;
	detectTarget(image, binary);
    	findSquares(binary, squares);

	Mat edges;
    	drawSquares(image, edges, squares);	

	findMarkerAttitude( edges, image, squares );

        int c = waitKey();
        if( (char)c == 27 )
            break;

    }

    return 0;
}
