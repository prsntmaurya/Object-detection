/*This code deals with the problem of face detection and eye detection.
Written by Prashant Maurya.
The code uses opencv and Haar features based cascade classifier to detect both eyes and face.*/

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void detect_faces( Mat img );
/*loading pretrained Haar CascadeClassifiers*/
String face_cascade1_name = "haarcascade_frontalface_default.xml";
String face_cascade2_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade1;
CascadeClassifier face_cascade2;
CascadeClassifier eyes_cascade;

int main( int argc, const char** argv )
{
	Mat img;	
	img=imread(argv[1],CV_LOAD_IMAGE_COLOR);  /*reading input image*/
	if(! img.data ) 
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    /*throwing error when any cascade file is unable to load*/
    if( !face_cascade1.load( face_cascade1_name ) )
    { 
        printf("--(!)Error loading face cascade1\n"); return -1; 
    }

    if( !face_cascade2.load( face_cascade2_name ) )
    { 
        printf("--(!)Error loading face cascade2\n"); return -1; 
    }

    if( !eyes_cascade.load( eyes_cascade_name ) )
    { 
        printf("--(!)Error loading face cascade\n"); return -1; 
    }

    detect_faces( img );
    return 0;
}

void detect_faces( Mat img )
{
    std::vector<Rect> faces;
    Mat img_gray;
    cvtColor( img, img_gray, COLOR_BGR2GRAY ); /*converting input image in grayscale form*/
    equalizeHist( img_gray, img_gray ); 
    
    /*Detecting faces*/
    face_cascade1.detectMultiScale( img_gray, faces, 1.2, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {   
        /*Drawing circle around faces*/ 
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( img, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 0, 0, 255 ), 4, 8, 0 );
        Mat faceROI = img_gray( faces[i] );
        std::vector<Rect> eyes;

        /*Detect eyes in detected faces*/
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        /*for each detected eyes draw a circle around it*/
        for ( size_t j = 0; j < eyes.size(); j++ )
        {   
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)/4 );
            circle( img, eye_center, radius, Scalar( 255, 255, 0 ), 4, 8, 0 );
        }
    }

    /*Detecting faces*/
    face_cascade2.detectMultiScale( img_gray, faces, 1.2, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {   
        /*Drawing circle around faces*/ 
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( img, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 0, 0, 255 ), 4, 8, 0 );
        Mat faceROI = img_gray( faces[i] );
        std::vector<Rect> eyes;

        /*Detect eyes in detected faces*/
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        /*for each detected eyes draw a circle around it*/
        for ( size_t j = 0; j < eyes.size(); j++ )
        {   
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)/4 );
            circle( img, eye_center, radius, Scalar( 255, 255, 0 ), 4, 8, 0 );
        }
    }    
    /*showing output image*/
    namedWindow( "Detected faces and eyes", WINDOW_AUTOSIZE );
    imshow( "Detected faces and eyes", img );
    waitKey(0);
}    