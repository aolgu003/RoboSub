#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

//There are the algorithms
#define HIGHLIGHT_INVARIENT 0

class segmentation {	
	public:
		cv::Mat result;

	private:
		int hue_upper;
 		int hue_lower;
		int sat_upper;
		int sat_lower;
		int var_upper;
		int var_lower;

	public:
		segmentation(char classification);

	private:
		void thresh();
		void watershed();
		void set_thresholds(char classification);
		bool blackWhite(unsigned char h,unsigned char s,unsigned char v );
};
