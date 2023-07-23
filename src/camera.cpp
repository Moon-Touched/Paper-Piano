#include "camera.h"

/*!
 * The function operates in a loop as long as the camera is active to add frames to the pipeline.
 */
void Camera::threadLoop(){
    while(isOn){
        postFrame();
    }
}

/*!
 * Retrieves the next accessible frame and forwards it to the assigned callback. This function depends on the OpenCV method videoCapture.read(), which is assumed to delay for an intra-frame period.
 */
void Camera::postFrame(){
    if(nullptr == sceneCallback) return;
    cv::Mat cap;
    videoCapture.read(cap);
    // Verify if the operation is successful
    if (cap.empty()) {
        std::cerr << "ERROR! Grabbed frame is blank\n";
        return;
    }
    sceneCallback->nextScene(cap);
}

/*!
 * Initializes the recording on a separate thread.
 */
void Camera::start(int deviceID, int apiID){
	isOn=true;
	videoCapture.open(deviceID,apiID);
	cameraThread = std::thread(&Camera::threadLoop, this);
}

/*!
 * Halts recording, releases thread resources, and must be invoked prior to program termination.
 */
void Camera::stop(){
    isOn=false;
    cameraThread.join();
}
