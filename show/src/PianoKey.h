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
 * @brief PianoKey calss
 */
class PianoKey
{
public:
    string note = "";   ///< THe note that this key represent to
    Point position;     ///< The center coordinate of this key
    int left;           ///< The left boundary of this key
    int right;          ///< The right boundary of this key
    int top;            ///< The top boundary of this key
    int bottom;         ///< The bottom boundary of this key
    int play_count = 0; ///< record howmany frames the key is pressed.
    bool isPressed = false;
    bool isPlaying = false;
    /**
     * @brief Will be called when play_count exceed a threshold.
     * Will output corresponding audio
     *
     * @param isPressed whether the key is pressed
     * @return void
     */
    void Pressed(bool isPressed)
    {
        if (isPressed && !isPlaying)
        {
            // system(string("loadfile ../sound/" + note + ".mp3 &").c_str());
            play_count++;
            //            std::cout<<play_count<<std::endl;
        }

        if (play_count == 1 && play_count > 0)
        {
            system(string("nohup echo \"loadfile " + note + ".mp3\" > ../tmp/" + note).c_str());
            isPlaying = true;
            // system(string("nohup mplayer -idle ../sound/" + note + ".mp3  &").c_str());
            play_count = 0;
            std::cout << note << std::endl;
        }

    }
};
