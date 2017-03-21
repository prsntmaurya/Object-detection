#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, const char** argv )
{
	Mat img;
		
	img=imread(argv[1],CV_LOAD_IMAGE_COLOR);


	if(! img.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
	namedWindow( "Input Image", WINDOW_AUTOSIZE );
	imshow( "Input Image", img );  
	waitKey(0); 

}