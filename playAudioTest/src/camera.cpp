#include "camera.h"
using namespace cv;
using namespace std;
void Camera::threadLoop()
{
    while (isOn)
    {
        postFrame();
    }
}
void Camera::postFrame()
{
    cv::Mat cap;
    videoCapture.read(cap);
    
    if (step == 0)
    {
        if (callback->nextScene(allKeys, cap) == -1)
            step = 1;
    }
    if (step == 1)
    {
        if (pressCallback->nextScene(allKeys, cap) == -1)
            stop();
    }
}
void Camera::start(int deviceID, int apiID)
{
    isOn = true;
    videoCapture.open(deviceID, apiID);
    videoCapture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    cameraThread = std::thread(&Camera::threadLoop, this);
}
void Camera::stop()
{
    isOn = false;
    cameraThread.join();
}
