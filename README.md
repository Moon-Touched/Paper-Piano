# README

# Paper Piano

![https://user-images.githubusercontent.com/103563340/232306862-8a78c59b-50db-45c7-840b-f6bb2d6f425b.jpg](https://user-images.githubusercontent.com/103563340/232306862-8a78c59b-50db-45c7-840b-f6bb2d6f425b.jpg)

## Project Overview

This project aims to develop a real-time piano key recognition and audio output system based on Raspberry Pi. The camera captures and recognizes the keys printed on the paper, and when a key action is detected, the corresponding audio will be played in real time. This system uses computer vision and image processing technology to realize piano key recognition and key detection in various scenarios.

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
    
2. Install opencv and mplayer. The Pi OS should has include C++ 
    
    ```bash
    sudo apt install libopencv-dev
    sudo apt install mplayer
    ```
    
3. Download rasPi folder to your raspberryPi, navigate to the folder and run the codes below. A executable file named ‘main’ will be generated in the build folder.
    
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
    

## User Instructions

1. Run the project
2. The system will capture graph and recognize the piano keys. It will assign note to keys from left to right.
3. Adjust camera or your paper until obtain a satisfied view then press q.
4. The program will start detect weather a key is pressed and play the audio of the key’s note.

## Future Improvements

1. Improve the accuracy and speed of piano key recognition.
2. Support for real structure of piano(2 rows of keys) and more types of keyboard instruments.
3. Add recognition and audio output for multiple keys pressed simultaneously.

## An example of hand detection is as follows ：

- developing demo example：
    
    
    [372ce5e7a3087d05368b9e8819bc000f.mp4](README%20449fc8455e314eb0a8f3f84dd914dc94/372ce5e7a3087d05368b9e8819bc000f.mp4)