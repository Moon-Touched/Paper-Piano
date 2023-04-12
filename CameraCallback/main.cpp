/**
 * @file main.cpp
 * @brief qqq
 * @author Moon-Touched
 */

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "camera.h"

using namespace std;
using namespace cv;

void nextFrame(Mat mat)
{
    cout << "captured" << "\n";
    imshow("qqq", mat);
}

int main()
{
    VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    Camera camera;
    camera.videoCapture = cap;
    camera.registerFrameCallback(nextFrame);
    camera.start();
}