/**@mainpage  Paper-Piano
* This project aims to develop a real-time piano key recognition and audio output system based on Raspberry Pi.
The camera captures and recognizes the keys printed on the paper,
and when a key action is detected, the corresponding audio will be played in real time.
This system uses computer vision and image processing technology to realize piano key recognition
and key detection in various scenarios.
*/

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "camera.h"

using namespace cv;
using namespace std;

/**
 * @brief extract edge from a frame of graph
 *
 * @param frame: original frame
 * @return a openCV mat with extracted edges
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

/**
 * @brief transform a frame of graph to a binary one. Specificly designed for detecting finger
 *
 * @param frame: original frame
 * @return a openCV binary frame
 */
Mat convertToBinary(Mat frame)
{
    Mat grayFrame, binaryFrame, blurFrame, edgeFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    threshold(grayFrame, binaryFrame, 50, 255, THRESH_BINARY);
    GaussianBlur(binaryFrame, blurFrame, Size(7, 7), 1);
    return binaryFrame;
}

/**
 * @brief Based on the binary grapg, detect whether a key is pressed.
 * The keys has been stored as well as the coordinate of their center position.
 * Normally the pixel at this coordinate is black(0).
 * When there is a finger, the pixel will be white(255).
 * If a key is detected as pressed, play the audio of note.
 *
 * @param capFrame: original frame
 * @param allKeys: Pointer of the stored keys.
 * @return void
 */
void pressDetect(Mat capFrame, vector<PianoKey> &allKeys)
{
    bool anyPressed;
    Mat binaryFrame = convertToBinary(capFrame);
    for (int i = 0; i < allKeys.size(); i++)
    {
        anyPressed = false;
        int row = allKeys[i].position.y;
        int col = allKeys[i].position.x;
        if (binaryFrame.at<uchar>(row, col) == 255)
        {
            allKeys[i].Pressed(true);
            anyPressed = true;
        }
        else
        {
            allKeys[i].Pressed(false);
            allKeys[i].isPlaying = false;
        }
        // rectangle(capFrame, range, Scalar(255), 2);
    }
    // if (!anyPressed)
    //{
    //     system(string("nohup echo \"pausing_toggle pause\" > ../tmp/ff").c_str());
    // }
    imshow("play", capFrame);
    imshow("qqq", binaryFrame);
}

/**
 * @brief Detect rectangles in a frame of graph and store them in a vector.
 *
 * @param capFrame: original frame
 * @return the vector of piano key
 *
 */
vector<PianoKey> rectDetect(Mat capFrame)
{
    // string noteName[] = {"xi", "la", "so", "fa", "mi", "re", "do"};"do2", "re2", "mi2", "fa2", "so2", "la2", "xi2"
    string noteName[] = {"do1", "re1", "mi1", "fa1", "so1", "la1", "xi1"};
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
            newKey.note = noteName[j % 7];
            newKey.left = min(approx[0].x, approx[2].x);
            newKey.top = max(approx[0].y, approx[2].y);
            newKey.right = max(approx[0].x, approx[2].x);
            newKey.bottom = min(approx[0].y, approx[2].y);
            j = j + 1;
            allKeys.push_back(newKey);
            rectangle(capFrame, approx[0], approx[2], Scalar(255), 2);
            circle(capFrame, center, 3, Scalar(0, 255, 0), -1);
            putText(capFrame, newKey.note, newKey.position - Point(20, 0), 0, 1, Scalar(255, 0, 0), 2);
            putText(capFrame, "Press q to continue", Point(0, 20), 0, 1, Scalar(255, 0, 0), 2);
        }
    }
    imshow("ini", capFrame);
    return allKeys;
}

/**
 * @brief Callback for the initial detection.
 * The user can adjust the camera or paper until they are satisfied.
 * Press q, the program will move to next stage.
 * Press a, just print "captured" for testing purpose
 */
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

/**
 * @brief Callback for detecting whether a key is pressed.
 */
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

/**
 * @brief Main function. Will define a camera class and start detection.
 */
int main(int argc, char **argv)
{
    // system(string("nohup echo \"loop 0\" > ../tmp/ff").c_str());
    Camera camera;
    camera.registerCallback(&myCallback);
    camera.registeraPressCallback(&myCallback1);
    camera.start(0, 0);
    while (1)
    {
    };
}
