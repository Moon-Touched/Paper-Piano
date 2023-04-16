#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "camera.h"

using namespace cv;
using namespace std;

Mat convertToEdge(Mat frame)
{
    Mat grayFrame, binaryFrame, blurFrame, edgeFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    threshold(grayFrame, binaryFrame, 50, 255, THRESH_BINARY);
    GaussianBlur(binaryFrame, blurFrame, Size(7, 7), 1);
    Canny(blurFrame, edgeFrame, 0, 50);
    return edgeFrame;
}

Mat convertToBinary(Mat frame)
{
    Mat grayFrame, binaryFrame, blurFrame, edgeFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    threshold(grayFrame, binaryFrame, 50, 255, THRESH_BINARY);
    GaussianBlur(binaryFrame, blurFrame, Size(7, 7), 1);
    return binaryFrame;
}

void pressDetect(Mat capFrame, vector<PianoKey> &allKeys)
{
    Mat binaryFrame = convertToBinary(capFrame);
    for (int i = 0; i < allKeys.size(); i++)
    {
        int row = allKeys[i].position.y;
        int col = allKeys[i].position.x;
        if (binaryFrame.at<uchar>(row,col)==255)
        {
            allKeys[i].Pressed(true);
        }
        // rectangle(capFrame, range, Scalar(255), 2);
    }
    imshow("play", capFrame);
    imshow("qqq", binaryFrame);
}

vector<PianoKey> rectDetect(Mat capFrame)
{
    //string noteName[] = {"xi", "la", "so", "fa", "mi", "re", "do"};
    string noteName[] = {"do1", "re1", "mi1", "fa1", "so1", "la1", "xi1", "do2", "re2", "mi2", "fa2", "so2", "la2", "xi2"};
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;
    vector<PianoKey> allKeys;
    cv::findContours(convertToEdge(capFrame), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    allKeys.clear();
    int j = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);
        if (approx.size() == 4 && sqrtf(powf((approx[0].x - approx[2].x), 2) + powf((approx[0].y - approx[2].y), 2)) > 50 &&
            sqrtf(powf((approx[0].x - approx[2].x), 2) + powf((approx[0].y - approx[2].y), 2)) < 200)
        {
            Point center = (approx[0] + approx[2]) / 2;
            PianoKey newKey;
            newKey.position = center;
            newKey.note = noteName[j % 14];
            newKey.left = min(approx[0].x, approx[2].x);
            newKey.top = max(approx[0].y, approx[2].y);
            newKey.right = max(approx[0].x, approx[2].x);
            newKey.bottom = min(approx[0].y, approx[2].y);
            j = j + 1;
            allKeys.push_back(newKey);
            rectangle(capFrame, approx[0], approx[2], Scalar(255), 2);
            circle(capFrame, center, 3, Scalar(0, 255, 0), -1);
            putText(capFrame, newKey.note, newKey.position - Point(20, 0), 0, 1, Scalar(255, 0, 0), 2);
        }
    }
    imshow("ini", capFrame);
    return allKeys;
}

struct MyCallback : Camera::DetectCallback
{
    virtual int nextScene(vector<PianoKey> &allKeys, const cv::Mat &mat)
    {
        allKeys = rectDetect(mat);
        char key = waitKey(30);
        if (key == 'a') // a
        {
            cout << "captured\n";
            return 0;
        }
        else if (key == 'q') // q
        {
            return -1;
        }
        return 0;
    }
};

struct MyCallback1 : Camera::PressCallback
{
    virtual int nextScene(vector<PianoKey> &allKeys, const cv::Mat &mat)
    {
        pressDetect(mat, allKeys);
        if (waitKey(30) == 27)
        {
            return -1;
        }
        return 0;
    }
};
struct MyCallback myCallback;
struct MyCallback1 myCallback1;
int main(int argc, char **argv)
{
    Camera camera;
    camera.registerCallback(&myCallback);
    camera.registeraPressCallback(&myCallback1);
    camera.start(0, 0);
    while (1)
    {
    };
}
