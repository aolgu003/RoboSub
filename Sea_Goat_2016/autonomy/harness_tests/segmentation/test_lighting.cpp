#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include "segmentation.h"

using namespace std;
using namespace cv;

int main(int /*argc*/, char** /*argv*/)
{
    static const char* names[] = { "../../image_data_set/lighting_data_set/1.jpg","../../image_data_set/lighting_data_set/2.jpg", "../../image_data_set/lighting_data_set/3.jpg","../../image_data_set/lighting_data_set/4.jpg","../../image_data_set/lighting_data_set/5.jpg","../../image_data_set/lighting_data_set/6.jpg","../../image_data_set/lighting_data_set/7.jpg","../../image_data_set/lighting_data_set/8.jpg","../../image_data_set/lighting_data_set/10.jpg",0 };

    vector<vector<Point> > squares;
	segmentation segMarker(1);
	Mat result_image;
    for( int i = 0; names[i] != 0; i++ )
    {
        segMarker.result = imread(names[i], 1);
		if( segMarker.result.empty() )
        {
            cout << "Couldn't load " << names[i] << endl;
            continue;
        }
		//segMarker.highlight_invarient();
		waitKey(0);
	}
}
