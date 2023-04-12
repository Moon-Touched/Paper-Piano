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

Mat convertToEdge(Mat frame)
{
    Mat grayFrame, binaryFrame, blurFrame, edgeFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    threshold(grayFrame, binaryFrame, 50, 255, THRESH_BINARY);
    GaussianBlur(binaryFrame, blurFrame, Size(7, 7), 1);
    Canny(blurFrame, edgeFrame, 0, 50);
    return edgeFrame;
}

vector<PianoKey> pressDetect(Mat capFrame, vector<PianoKey> allKeys)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;
    vector<PianoKey> capturedKeys;

    findContours(convertToEdge(capFrame), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    capturedKeys.clear();
    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);
        if (approx.size() == 4 && sqrtf(powf((approx[0].x - approx[2].x), 2) + powf((approx[0].y - approx[2].y), 2)) > 50)
        {
            Point center = (approx[0] + approx[2]) / 2;
            PianoKey newKey;
            newKey.position = center;
            capturedKeys.push_back(newKey);
            rectangle(capFrame, approx[0], approx[2], Scalar(255), 2);
            circle(capFrame, center, 3, Scalar(0, 255, 0), -1);
        }
    }

    for (int i = 0; i < allKeys.size(); i++)
    {
        bool isPressed = true;
        for (int j = 0; j < capturedKeys.size(); j++)
        {
            if (abs((allKeys[i].position.x - capturedKeys[j].position.x) < 5) && (abs((allKeys[i].position.y - capturedKeys[j].position.y) < 5)))
            {
                isPressed = false;
            }
        }
        allKeys[i].isPressed = isPressed;
    }
    imshow("play", capFrame);
    return allKeys;
}

vector<PianoKey> rectDetect(Mat capFrame)
{
    string noteName[] = {"do", "re", "mi", "fa", "so", "la", "xi"};
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;
    vector<Point> centers;
    vector<PianoKey> allKeys;

    findContours(convertToEdge(capFrame), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    allKeys.clear();
    // find rectangles and record center point
    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);
        if (approx.size() == 4 && sqrtf(powf((approx[0].x - approx[2].x), 2) + powf((approx[0].y - approx[2].y), 2)) > 50)
        {
            Point center = (approx[0] + approx[2]) / 2;
            centers.push_back(center);
            rectangle(capFrame, approx[0], approx[2], Scalar(255), 2);
            circle(capFrame, center, 3, Scalar(0, 255, 0), -1);
        }
    }
    // bubble sort center point
    Point temp;
    for (int i = 0; i < centers.size(); i++)
    {
        for (int j = 0; j < centers.size() - i - 1; j++)
        {
            if (centers[j].x > centers[j + 1].x)
            {
                temp = centers[j];
                centers[j] = centers[j + 1];
                centers[j + 1] = temp;
            }
        }
    }
    // assign center and note name to keys, and push to vector
    for (int i = 0; i < centers.size(); i++)
    {
        PianoKey newKey;
        newKey.position = centers[i];
        newKey.note = noteName[i % 7];
        allKeys.push_back(newKey);
    }
    imshow("ini", capFrame);
    return allKeys;
}

int main()
{
    Mat capFrame;
    VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    vector<PianoKey> allKeys;

    while (true)
    {
        cap.read(capFrame);
        allKeys = rectDetect(capFrame);
        for (int i = 0; i < allKeys.size(); i++)
        {
            cout << allKeys[i].position << '\n';
            cout << allKeys[i].note << '\n';
        }
        char key = waitKey(0);
        if (key == 'a') // a
        {
            cout << "captured\n";
            continue;
        }
        else if (key == 'q') // q
        {
            break;
        }
    }

    while (true)
    {
        cap.read(capFrame);
        allKeys = pressDetect(capFrame, allKeys);
        for (int i = 0; i < allKeys.size(); i++)
        {
            if (allKeys[i].isPressed)
            {
                cout << allKeys[i].note << "\n";
            }
        }
        // esc quit
        if (waitKey(100) == 27)
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