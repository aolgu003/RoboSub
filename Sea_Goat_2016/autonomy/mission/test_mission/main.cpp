#include <iostream>
#include "seagoat_vision.h"
#include "segmentation.h"
#include "comms.h"

using namespace std;
using namespace cv;

int main( int argc, char* argv[] ) {
	ostringstream InputImage;
	
	if (argc < 1) { 
		cout << "Usage: ./test_mission <path_to_competition_images>" 
			<< " <num of images to read through>" << endl;
	}
	cout << "Test out put" << endl;
    vector<vector<Point> > squares;
	segmentation segMarker(1);
	Mat result_image;
	int nj;

    for( int i = 0; i < atoi(argv[1]); i++ ) {
		InputImage << argv[0];
		InputImage << "Image" << i << ".png";
        segMarker.result = imread(InputImage.str());
		if( segMarker.result.empty() )
        {
            cout << "Couldn't load " << InputImage.str() << endl;
            continue;
			InputImage.str("");
			InputImage.clear();
			waitKey(0);
        }
		//segMarker.highlight_invarient();
		imshow("Input image", segMarker.result);
		waitKey(0);
		
		InputImage.str("");
		InputImage.clear();
	}

	return 0;
}
