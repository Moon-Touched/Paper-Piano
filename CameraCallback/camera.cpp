#include "camera.h"

/*!
 * Loops while camera is on to add frames to the pipeline
 */
void Camera::threadLoop()
{
    while (isOn)
    {
        postFrame();
    }
}

/*!
 * Gets the next available frame and passes it on to the registered callback. Relies on the videoCapture.read() OpenCV method which is understood to wait for an intra-frame delay.
 */
void Camera::postFrame()
{
    Mat cap;
    videoCapture.read(cap);
    myCallBack(cap);
}

/*!
 * Starts the worker thread recording
 */
void Camera::start()
{
    //videoCapture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    //videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    isOn = true;
    //videoCapture.open(0);
    cameraThread = std::thread(&Camera::threadLoop, this);
}

/*!
 * Frees thread resources and stops recording, must be called prior to program exit.
 */
void Camera::stop()
{
    isOn = false;
    cameraThread.join();
}

void Camera::registerFrameCallback(CallBack fc)
{
    myCallBack = fc;
}