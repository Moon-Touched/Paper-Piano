# README

# Paper Piano

![https://user-images.githubusercontent.com/103563340/232306862-8a78c59b-50db-45c7-840b-f6bb2d6f425b.jpg](https://user-images.githubusercontent.com/103563340/232306862-8a78c59b-50db-45c7-840b-f6bb2d6f425b.jpg)

## Social Media

https://twitter.com/PaperPiano

## Project Overview

This project aims to develop a real-time piano key recognition and audio output system based on Raspberry Pi. The camera captures and recognizes the keys printed on the paper, and when a key action is detected, the corresponding audio will be played in real time. This system uses computer vision and image processing technology to realize piano key recognition and key detection in various scenarios.

More specific doxgen documents can be found in rasPi forder or show folder. Those 2 version of codes have same function but differenr step to use it on RaspberryPi.

## Social media

[https://twitter.com/PaperPiano](https://twitter.com/PaperPiano)

## Members

FangZhou Liu(2751741L)

Dong Zhao(2818441Z)

Zheng Chen(2706870C)

Han Zhang(2755881Z)

## Features

1. Real-time recognition and storage of initial piano key coordinates.
2. Provide pattern for recognition, or designed by users. Any clear rectangle shape can be recognized.
3. Play corresponding audio when a key press is detected.

## Hardware Requirements

1. Raspberry Pi
2. Camera (Raspberry Pi Camera Module)
3. Speaker or headphones (connected to Raspberry Pi’s 3.5mm) or HDMI output

## Software Requirements

1. Raspberry Pi OS. Also can build in other Linux environments or windows visual studio
2. OpenCV library
3. mplayer(Raspberry Pi OS).

## Installation Guide

1. Update your Pi first.
    
    ```bash
    sudo apt update
    sudo apt upgrade
    ```
    
2. Install opencv and mplayer. The Pi OS should has include C++ environments don’t need installation.
    
    ```bash
    sudo apt install libopencv-dev
    sudo apt install mplayer
    ```
    
3. Download rasPi or show folder to your raspberryPi, navigate to the folder and run the codes below. A executable file named ‘cvKey’ will be generated in the build folder.
    
    ```bash
    mkdir build
    cd build
    cmake ..make
    ```
    

## User Instructions

- rasPi
1. Generate a FIFO file in the folder.
    
    ```bash
    cd rasPi
    mkfifo /tmp/ff
    ```
    
2. Run the codes below in command line. The mplayer will play a note to indicate it is running and been set to slave mode. The mplayer will monitor named pipe(FIFO file). So that the program can operate the player.
    
    ```bash
    mplayer -slave -idle -input file=../tmp/ff do1.mp3
    ```
    
3. In another command line window, run the project
    
    ```bash
    cd rasPi/build
    ./cvKey
    ```
    
4. The system will capture graph and recognize the piano keys. It will assign note to keys from left to right.
5. Adjust camera or your paper until obtain a satisfied view then press q.
6. The program will start detect weather a key is pressed and play the audio of the key’s note.

- show
1. Compare with previous version. This version has faster response to pressed key. But need more preparation.
2. Generate a FIFO file in the folder. Each will be assigned to a mplayer.
    
    ```bash
    cd show
    mkfifo /tmp/do1
    mkfifo /tmp/re1
    mkfifo /tmp/mi1
    mkfifo /tmp/fa1
    mkfifo /tmp/so1
    mkfifo /tmp/la1
    mkfifo /tmp/xi1
    ```
    
3. Navigate to show/sound forder. Run each line in 7 different command line tabs or windows. So that each key can be monitored separately.
    
    ```bash
    mplayer -slave -idle -input file=../tmp/do1 do1.mp3
    mplayer -slave -idle -input file=../tmp/re1 re1.mp3
    mplayer -slave -idle -input file=../tmp/mi1 mi1.mp3
    mplayer -slave -idle -input file=../tmp/fa1 fa1.mp3
    mplayer -slave -idle -input file=../tmp/so1 so1.mp3
    mplayer -slave -idle -input file=../tmp/la1 la1.mp3
    mplayer -slave -idle -input file=../tmp/xi1 xi1.mp3
    ```
    
4. Other step are the same.

## Future Improvements

1. Improve the accuracy and speed of piano key recognition.
2. Support for real structure of piano(2 rows of keys) and more types of keyboard instruments.
3. Add recognition and audio output for multiple keys pressed simultaneously.

## An example of hand detection is as follows ：

- developing demo example： https://user-images.githubusercontent.com/103563340/232533313-ad513ca6-4c4b-4f53-844a-a986e2bf0c66.mp4
