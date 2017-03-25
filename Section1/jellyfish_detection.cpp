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
    cv::CommandLineParser parser(argc, argv, "{@input |../data/jellyfish.jpg| }");

    fileName.push_back(parser.get<string>("@input"));
    img = imread(fileName[0], IMREAD_COLOR);
    if (img.rows*img.cols <= 0)
    {
        cout << "Image " << fileName[0] << " is empty or cannot be found\n";
        return(0);
    }

    SimpleBlobDetector::Params pDefaultBLOB;
    // This is default parameters for SimpleBlobDetector
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
    // Descriptor array for BLOB
    vector<String> typeDesc;
    // Param array for BLOB
    vector<SimpleBlobDetector::Params> pBLOB;
    vector<SimpleBlobDetector::Params>::iterator itBLOB;

    // Param for second BLOB detector we want area between 500 and 2900 pixels
    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByArea = true;
    pBLOB.back().minArea = 500;
    pBLOB.back().maxArea = 2900;
    

    itBLOB = pBLOB.begin();
    vector<double> desMethCmp;
    Ptr<Feature2D> b;
    String label;
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
        try
        {
            vector<KeyPoint>  keyImg;
            vector<Rect>  zone;
            vector<vector <Point> >  region;
            vector<Point2f> points;

            Mat     desc, result(img.rows, img.cols, CV_8UC3);
            if (b.dynamicCast<SimpleBlobDetector>() != NULL)
            {
                Ptr<SimpleBlobDetector> sbd = b.dynamicCast<SimpleBlobDetector>();
                sbd->detect(img, keyImg, Mat());
                for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); k++)
                    {   
                        points.push_back(k->pt);
                    }
                Mat pointmatrix(points);;
                int i = 0;
                for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); ++k, ++i)
                {

                    putText(img, "x", points[i], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1);
                }
                cout<< i<< endl;
            }
            namedWindow("Detected jellyfish", WINDOW_AUTOSIZE);
            imshow("Detected jellyfish", img);
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