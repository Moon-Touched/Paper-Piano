#include "camera.h"

/*!
 * Loops while camera is on to add frames to the pipeline
 */

void Camera::threadLoop(){
    while(isOn){
        postFrame();
    }
}

/*!
 * Gets the next available frame and passes it on to the registered callback. Relies on the videoCapture.read() OpenCV method which is understood to wait for an intra-frame delay.
 */
void Camera::postFrame(){
    cv::Mat cap;
    videoCapture.read(cap);
    // check if we succeeded
    if (cap.empty()) {
        std::cerr << "ERROR! blank frame grabbed\n";
        return;
    }
    if(step==0)
    {
        if(callback->nextScene(allKeys,cap)==-1)
            step=1;
    }
    if(step==1)
    {
        if(pressCallback->nextScene(allKeys,cap)==-1)
            this->stop();
    }
}

/*!
 * Starts the worker thread recording
 */
void Camera::start(int deviceID, int apiID){
    isOn=true;
    videoCapture.open(deviceID,apiID);
    cameraThread = std::thread(&Camera::threadLoop, this);
}

/*!
 * Frees thread resources and stops recording, must be called prior to program exit.
 */
void Camera::stop(){
    isOn=false;
    cameraThread.join();
}
