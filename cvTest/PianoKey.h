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

/**
 * @brief Piano key class
 *
 */
class PianoKey
{
public:
    string note = ""; /**< Corresponding note of this key(do, re, mi etc.) */
    void set(char name[]);
    virtual void isPressed() = 0;
};

/**
 * @brief Set the name of the note.
 * @param name: do re mi etc
 */
void PianoKey::set(char name[])
{
    note = name;
}