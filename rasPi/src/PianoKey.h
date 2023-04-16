#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

class PianoKey
{
public:
    string note = "";
    Point position;
    int left;
    int right;
    int top;
    int bottom;
    int play_count = 0;
    void Pressed(bool isPressed)
    {
        if (isPressed)
        {
            play_count++;
            //            std::cout<<play_count<<std::endl;
        }
        if (play_count % 10 == 0 && play_count > 0)
        {
            system(string("mplayer /home/pp/paperpiano/sound/"+note+".mp3").c_str());
            //system(string("nohup mplayer sound/" + note + ".mp3").c_str());
            play_count = 0;
            std::cout << note << std::endl;
        }
    }
};
