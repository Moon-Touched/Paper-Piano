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
	struct SceneCallback {
		virtual void nextScene(const cv::Mat &mat) = 0;
	};

	/**
	 * Basic constructor.
	 **/
	Camera() = default;

	/**
	 * Initiates the data capture from the camera.
	 * The callback function is invoked at the frame rate.
	 **/
	void start(int deviceID = 0, int apiID = 0);

	/**
	 * Ceases the data acquisition from the camera.
	 **/
	void stop();

	/**
	 * Assigns the callback that will be receiving
	 * the frames.
	 **/
	void registerSceneCallback(SceneCallback* sc) {
		sceneCallback = sc;
	}
    
private:
	void postFrame();
	void threadLoop();
	cv::VideoCapture videoCapture;
	std::thread cameraThread;
	bool isOn = false;
	SceneCallback* sceneCallback = nullptr;
};
