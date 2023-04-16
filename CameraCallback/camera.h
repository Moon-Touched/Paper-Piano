﻿#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <stdlib.h>
#include <thread>
#include "PianoKey.h"
/*!
 * Camera class with callback
 * GNU GPL v3.0
 * (C) 2022
 * [Ross Gardiner](https://github.com/rossGardiner)
 * [Adam Frew](https://github.com/Saweenbarra) 
 * [Alban Joseph](https://github.com/albanjoseph)
 * [Lewis Russell](https://github.com/charger4241)
 * Bernd Porr
 */
class Camera {
public:

    struct PressCallback {
        virtual int nextScene(vector<PianoKey> &allKeys,const cv::Mat &mat) = 0;
	};

    struct DetectCallback {
        virtual int nextScene(vector<PianoKey> &allKeys,const cv::Mat &mat) = 0;
    };

    Camera()=default;

	void start(int deviceID = 0, int apiID = 0);

	void stop();

    void registeraPressCallback(PressCallback* cb) {
        pressCallback = cb;
    }
    void registerCallback(DetectCallback* cb) {
        callback = cb;
    }
    vector<PianoKey> allKeys;
    int step=0;
private:
	void postFrame();
	void threadLoop();
	cv::VideoCapture videoCapture;
	std::thread cameraThread;
	bool isOn = false;
    PressCallback* pressCallback = nullptr;
    DetectCallback * callback= nullptr;
};
