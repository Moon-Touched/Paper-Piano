#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace cv;
using namespace std;
/**
 * @brief camera class with callback
 *
 */
class Camera
{
public:
    
    /**
     * Default constructor
     **/
    Camera() = default;

    /**
     * Starts the acquisition from the camera
     * and then the callback is called at the framerate.
     **/
    void start();
    /**
     * Stops the data aqusisition
     **/
    void stop();

    void threadLoop();

    VideoCapture videoCapture;
    thread cameraThread;
    bool isOn = false;
    typedef void (*CallBack)(Mat mat);
    CallBack myCallBack = nullptr;

    /**
     * Registers the callback which receives the
     * frames.
     **/
    void registerFrameCallback(CallBack fc);

    void postFrame();
};