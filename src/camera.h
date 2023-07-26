#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <stdlib.h>
#include <thread>

class Camera {
public:
	/**
	 * This callback must be implemented by the client.
	 **/
	struct FrameCallback {
		virtual void onNewFrame(const cv::Mat &frame) = 0;
	};

	/**
	 * Basic constructor.
	 **/
	Camera() = default;

	/**
	 * Initiates the data capture from the camera.
	 * The callback function is invoked at the frame rate.
	 **/
	void startCapture(int deviceIndex = 0, int apiIndex = 0);

	/**
	 * Ceases the data acquisition from the camera.
	 **/
	void endCapture();

	/**
	 * Assigns the callback that will be receiving
	 * the frames.
	 **/
	void registerFrameCallback(FrameCallback* callback) {
		frameCallback = callback;
	}
    
private:
	void deliverFrame();
	void runLoop();
	cv::VideoCapture videoStream;
	std::thread cameraThread;
	bool cameraActive = false;
	FrameCallback* frameCallback = nullptr;
};
