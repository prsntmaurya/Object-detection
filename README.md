# This project deals with two separate problems of object detection
- ##### Problem 1: Face detection and eye detection.
- ##### Problem 2: Jelly fish detection and its centroid.

#### Dependencies and system requirements to run and test this project on a system are as follows:
- C++ compiler 
- OpenCV 3.0 and above

## Problem 1: face detection and eye detection

Command to compile code face_detection.cpp:
```sh
$ g++ -ggdb `pkg-config --cflags opencv` -o `basename face_detection.cpp .cpp` face_detection.cpp `pkg-config --libs opencv`
```


Command to run code face_detection.cpp:
```sh
./face_detection oscarSelfie.jpg
```

This problem code uses Haar features based cascade classifier, which has pre trained xml file which is used in this code to detect human face and eyes. Training a classifier needs a lot of positive and negative images. The steps in which code works is given below:
 
- loading pretrained xml file containing features of face and eyes
- creating cascade classifier for face and eyes
- detect face using classifier
- for each detected face detect eyes in it
- display the result

Input Image

![alt text](https://raw.githubusercontent.com/prsntmaurya/Object-detection/master/Section1/oscarSelfie.jpg "Logo Title Text 1")

Output Image

![alt text](https://raw.githubusercontent.com/prsntmaurya/Object-detection/master/results/detectedFaces.png "Logo Title Text 2")

## Problem 2: Jelly fish detection and its centroid.
Command to compile code face_detection.cpp:
```sh
$ g++ -ggdb `pkg-config --cflags opencv` -o `basename jellyfish_detection.cpp .cpp` jellyfish_detection.cpp `pkg-config --libs opencv``
```

Command to run code face_detection.cpp:
```sh
$ ./jellyfish_detection jellyfish.jpg
```

This code deals with detection of jelly fish there are two ways I can think of either to train a classifier to detect jellyfish or to search for correlated homogeneous region in neighbourhood. This code uses the second option to detect jellyfish, it uses blob detection algorithm to calculate similar or homogeneous regions in the given area bound.
Certain parameters needs to be tuned to increase the accuracy of the detection like setting threshold for minimum and maximum area. Steps in which code executes are:

- setting default parameters for blob detection
- setting minimum and maximum area threshold
- defining descriptor for blob
- detecting key points as centroid of jellyfish
- detecting jellyfish
- displaying the resultant image

Input Image

![alt text](https://raw.githubusercontent.com/prsntmaurya/Object-detection/master/Section1/jellyfish.jpg "Logo Title Text 1")

Output Image

![alt text](https://raw.githubusercontent.com/prsntmaurya/Object-detection/master/results/jellydetection.png "Logo Title Text 2")
