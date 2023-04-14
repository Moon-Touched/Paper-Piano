/**
 * @file PianoKey.h
 * @brief Class represent to a piano key
 * @author Moon-Touched
 */

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

/**
 * @brief Piano key class
 *
 */
class PianoKey
{
public:
    string note = ""; /**< Corresponding note of this key(do, re, mi etc.) */
    Point position;
    void Pressed(bool isPressed)
    {
        if (isPressed)
        {
            cout << note << "\n";
        }
    };
};
