#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    vector<String> fileName;
    Mat img(800, 800, CV_8UC1);
    /*give input image name from commandline or default image is set to jellyfish.jpg*/
    cv::CommandLineParser parser(argc, argv, "{@input |../data/jellyfish.jpg| }");
    fileName.push_back(parser.get<string>("@input"));
    img = imread(fileName[0], IMREAD_COLOR); /*reading image file*/
    if (img.rows*img.cols <= 0)
    {
        cout << "Image " << fileName[0] << " is empty or cannot be found\n";
        return(0);
    }

    /*using bolb detecter to detect jellyfish*/
    SimpleBlobDetector::Params pDefaultBLOB;
    /*parameters for SimpleBlobDetector*/   
    pDefaultBLOB.thresholdStep = 10;
    pDefaultBLOB.minThreshold = 10;
    pDefaultBLOB.maxThreshold = 220;
    pDefaultBLOB.minRepeatability = 2;
    pDefaultBLOB.minDistBetweenBlobs = 10;
    pDefaultBLOB.filterByColor = false;
    pDefaultBLOB.blobColor = 0;
    pDefaultBLOB.filterByArea = false;
    pDefaultBLOB.minArea = 25;
    pDefaultBLOB.maxArea = 5000;
    pDefaultBLOB.filterByCircularity = false;
    pDefaultBLOB.minCircularity = 0.9f;
    pDefaultBLOB.maxCircularity = (float)1e37;
    pDefaultBLOB.filterByInertia = false;
    pDefaultBLOB.minInertiaRatio = 0.1f;
    pDefaultBLOB.maxInertiaRatio = (float)1e37;
    pDefaultBLOB.filterByConvexity = false;
    pDefaultBLOB.minConvexity = 0.95f;
    pDefaultBLOB.maxConvexity = (float)1e37;
    
    vector<String> typeDesc;      /*Descriptor array for BLOB*/
    vector<SimpleBlobDetector::Params> pBLOB;       /*Param array for BLOB*/
    vector<SimpleBlobDetector::Params>::iterator itBLOB;  /*iterator for  blob*/

    /*parameter for blob detection using min and max area concept*/
    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByArea = true;
    pBLOB.back().minArea = 160;   /*setting minimum area for homagenity detection*/
    pBLOB.back().maxArea = 800;     /*setting maximum area for homagenity detection*/
    

    itBLOB = pBLOB.begin();
    vector<double> desMethCmp;
    Ptr<Feature2D> b;
    int count=0;
    // Descriptor loop
    vector<String>::iterator itDesc;
    for (itDesc = typeDesc.begin(); itDesc != typeDesc.end(); ++itDesc)
    {
        vector<KeyPoint> keyImg1;
        if (*itDesc == "BLOB")
        {
            b = SimpleBlobDetector::create(*itBLOB);
            ++itBLOB;
        }
        /*try catch block is used to catch unhandled exceptions in Descriptor*/
        try     
        {
            vector<KeyPoint>  keyImg;  /*vector to store keypoints here center of jellyfish in image*/
            /*convert keypoints vector to Point2f conversion to store x,y coordinates of KeyPoint for plotting purpose*/
            vector<Point2f> points;    

            if (b.dynamicCast<SimpleBlobDetector>() != NULL)
            {
                Ptr<SimpleBlobDetector> sbd = b.dynamicCast<SimpleBlobDetector>();
                sbd->detect(img, keyImg, Mat()); /*detection of keypoints and storing it in keyImg*/
                for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); k++)
                    {   
                        points.push_back(k->pt);  /*conversion of keypoints vector to Point2f*/
                    }
                Mat pointmatrix(points);;

                for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); ++k, ++i)
                {
                    /*draw circle around detected jellyfish*/
                    circle(img, k->pt, (int)k->size, Scalar( 255, 255, 0 ));
                    /*printing "x" at the centroid of jellyfish*/
                    putText(img, "x", points[i], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 2);
                }
            }
            namedWindow("Detected jellyfish", WINDOW_AUTOSIZE); /*creating new window*/
            imshow("Detected jellyfish", img);  /*display the resultant image*/
            waitKey();
        }
        catch (Exception& e)
        {
            cout << "Feature : " << *itDesc << "\n";
            cout << e.msg << endl;
        }
    }

    return 0;
}