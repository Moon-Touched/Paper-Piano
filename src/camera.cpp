#include "camera.h"

/*!
 * The function operates in a loop as long as the camera is running to add frames to the pipeline.
 */
void Camera::runLoop(){
    while(cameraActive){
        deliverFrame();
    }
}

/*!
 * Retrieves the next available frame and forwards it to the assigned callback. This function depends on the OpenCV method videoCapture.read(), which is assumed to delay for an intra-frame period.
 */
void Camera::deliverFrame(){
    if(nullptr == frameCallback) return;
    cv::Mat capturedFrame;
    videoStream.read(capturedFrame);
    // Verify if the operation is successful
    if (capturedFrame.empty()) {
        std::cerr << "ERROR! Captured frame is blank\n";
        return;
    }
    frameCallback->nextScene(capturedFrame);
}

/*!
 * Initializes the recording on a separate thread.
 */
void Camera::startCapture(int deviceIdentifier, int apiIdentifier){
	cameraActive=true;
	videoStream.open(deviceIdentifier,apiIdentifier);
	cameraThread = std::thread(&Camera::runLoop, this);
}

/*!
 * Halts recording, releases thread resources, and must be invoked prior to program termination.
 */
void Camera::endCapture(){
    cameraActive=false;
    cameraThread.join();
}
