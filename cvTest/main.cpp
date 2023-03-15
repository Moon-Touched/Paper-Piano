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
#include <PianoKey.h>

using namespace std;
using namespace cv;

/**
 * @brief Detect rectangles in the frame and draw the contours on the same frame
 * @param capFrame: the frame captured by camera
 * @return capFrame with detected contours drawn on it
 */
Mat rectDetect(Mat capFrame, Mat edgeFrame)
{
    vector<PianoKey> keys;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;

    cv::findContours(edgeFrame, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);
        if (approx.size() == 4 && contourArea(contours[i]) > 50)
        {
            // drawContours(capFrame, contours, i, Scalar(255), 1, 8, hierarchy);
            rectangle(capFrame, approx[0], approx[2], Scalar(255), 3);
        }
    }

    return capFrame;
}

int main()
{
    Mat capFrame, grayFrame,binaryFrame, blurFrame, edgeFrame;
    VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    while (true)
    {
        cap.read(capFrame);
        cvtColor(capFrame, grayFrame, COLOR_BGR2GRAY);
        threshold(grayFrame, binaryFrame, 50, 255, THRESH_BINARY);
        GaussianBlur(binaryFrame, blurFrame, Size(7, 7), 1);
        Canny(blurFrame, edgeFrame, 0, 50);

        imshow("qqq", rectDetect(capFrame, edgeFrame));
        imshow("sharp", binaryFrame);
        imshow("canny", edgeFrame);
        // esc quit
        if (waitKey(30) == 27)
        {
            break;
        }
    }

    /*
        capFrame = imread("qqq.jpg");
        cvtColor(capFrame, grayFrame, COLOR_BGR2GRAY);
        GaussianBlur(grayFrame, blurFrame, Size(7, 7), 1);
        Canny(blurFrame, edgeFrame, 0, 50);

        imshow("qqq", rectDetect(capFrame, edgeFrame));
        imshow("canny", edgeFrame);
        waitKey(0);
    */
}