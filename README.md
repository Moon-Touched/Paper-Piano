# Paper Piano
![1a850e7f0fbf527ce8a594be7264bfd](https://user-images.githubusercontent.com/103563340/232306862-8a78c59b-50db-45c7-840b-f6bb2d6f425b.jpg)

## Project Overview
This project aims to develop a real-time piano key recognition and audio output system based on Raspberry Pi. 
The camera captures and recognizes the keys printed on the paper, and when a key action is detected,
the corresponding audio will be played in real time. This system uses computer vision and 
image processing technology to realize piano key recognition and key detection in various scenarios.

## Features

1. Real-time recognition and storage of initial piano key coordinates.
2. Option to re-recognize or continue.
3. Real-time comparison of the current frame with the initial frame to detect key presses.
4. Play corresponding audio when a key press is detected.

## Hardware Requirements

1. Raspberry Pi
2. Camera (Raspberry Pi Camera Module)
3. Speaker or headphones (connected to Raspberry Pi's 3.5mm audio jack or using a Bluetooth speaker)

## Software Requirements

1. Raspbian or other compatible operating systems
2. Python 3.7 or higher
3. OpenCV library
4. Other relevant Python libraries

## Installation Guide

1. Clone the project files to your Raspberry Pi:
git clone https://github.com/Moon-Touched/Paper-Piano
2. In the project root directory, run the following command to install the required dependencies:
pip3 install -r requirements.txt
3. Connect the camera and speaker (or headphones).

## Usage Instructions

1. Run the project's main program
2. The system will capture and recognize a frame with the piano keys, storing the detected key coordinates.
3. Wait for the user to decide whether to re-recognize or continue.
4. If continuing, the system will recognize each frame and compare the initially stored key coordinates with the real-time detected key coordinates. When a key press is detected, the corresponding audio will be played.

## Future Improvements

1. Improve the accuracy and speed of piano key recognition.
2. Support for more types of keyboard instruments.
3. Add recognition and audio output for multiple keys pressed simultaneously.

## An example of hand detection is as follows ：    
* Picture example：  
![03b34b1f93796640a73494721e365ba](https://user-images.githubusercontent.com/127966120/231911747-6bfe8fa8-30c9-4e38-a783-6c5129b49988.png)
![90daad36309c5c7abe70a7562500943](https://user-images.githubusercontent.com/127966120/231911750-303a0ac8-6f86-40e7-993b-fd845ac443a7.png)
