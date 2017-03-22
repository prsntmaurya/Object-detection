# This project deals with problem of object detection.
Dependencies and system requirements to run and test this project on a system are as follows:
1. C++ compiler 
2. Opencv 3.0 and above

Command to compile code face_detection.cpp:
g++ -ggdb `pkg-config --cflags opencv` -o `basename face_detection.cpp .cpp` face_detection.cpp `pkg-config --libs opencv`

Command to run code face_detection.cpp:
./face_detection