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
#include <camera.cpp>

using namespace std;
using namespace cv;

/**
 * @brief Detect rectangles in the frame and draw the contours on the same frame
 * @param capFrame: the frame captured by camera
 * @return capFrame with detected contours drawn on it
 */



Mat rectDetect(Mat capFrame)
{
    string noteName[] = {"do", "re", "mi", "fa", "so", "la", "xi"};
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;

    cv::findContours(convertToEdge(capFrame), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int j = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);
        if (approx.size() == 4 && sqrtf(powf((approx[0].x - approx[2].x), 2) + powf((approx[0].y - approx[2].y), 2)) > 50)
        {
            Point center = (approx[0] + approx[2]) / 2;
            rectangle(capFrame, approx[0], approx[2], Scalar(255), 2);
            circle(capFrame, center, 3, Scalar(0, 255, 0), -1);
        }
    }

    return capFrame;
}

Mat convertToEdge(Mat frame)
{
    Mat grayFrame, binaryFrame, blurFrame, edgeFrame;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    threshold(grayFrame, binaryFrame, 50, 255, THRESH_BINARY);
    GaussianBlur(binaryFrame, blurFrame, Size(7, 7), 1);
    Canny(blurFrame, edgeFrame, 0, 50);
    return edgeFrame;
}

int main()
{
    Camera camera;
    Mat capFrame;
    VideoCapture cap(0);
    camera.start();
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    vector<PianoKey> allKeys;

    while (true)
    {
        cap.read(capFrame);
        imshow("qqq", rectDetect(capFrame, allKeys));
        cout << "captured\n";
        if (waitKey(0) == 65) // a
        {
            continue;
        }
        else if (waitKey(0) == 13) // enter
        {

            break;
        }
    }

    while (true)
    {
        cap.read(capFrame);

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