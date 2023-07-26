#include "piano.h"
#include "./ui_piano.h"
#include <iostream>

Piano::Piano(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Piano)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::pressed,this,[=](){ready = true;});
    keys.push_back(new Key("C", "sound/do1.mp3"));
    keys.push_back(new Key("D", "sound/re1.mp3"));
    keys.push_back(new Key("E", "sound/mi1.mp3"));
    keys.push_back(new Key("F", "sound/fa1.mp3"));
    keys.push_back(new Key("G", "sound/so1.mp3"));
    keys.push_back(new Key("A", "sound/la1.mp3"));
    keys.push_back(new Key("B", "sound/xi1.mp3"));

    myCallback.piano = this;
    camera.registerSceneCallback(&myCallback);
    camera.start();
}

Piano::~Piano()
{
    camera.stop();
    delete ui;
}

void Piano::runDetection(const cv::Mat &mat)
{
    if (!ready)
        keyInit(mat);
    else
        pressDetect(mat);
    cv::Mat outMat;
    mat.copyTo(outMat);
    for (int i = 0; i < keys.size(); i++)
    {
        cv::rectangle(outMat, keys[i]->pos, cv::Scalar(0,0,255));
    }
    cv::cvtColor(outMat, outMat, cv::COLOR_BGR2RGB);
    QImage img = QImage((uchar*) outMat.data, outMat.cols, outMat.rows, outMat.step, QImage::Format_RGB888);
    ui->realImg->setPixmap(QPixmap::fromImage(img));
}

/**
 * @brief transform a frame of graph to a binary one. Specificly designed for detecting finger
 *
 * @param frame: original frame
 * @return a openCV binary frame
 */
cv::Mat convertToBinary(cv::Mat frame)
{
    cv::Mat grayFrame, binaryFrame, blurFrame, edgeFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::threshold(grayFrame, binaryFrame, 50, 255, cv::THRESH_BINARY);
    cv::GaussianBlur(binaryFrame, blurFrame, cv::Size(7, 7), 1);
    return binaryFrame;
}

void Piano::pressDetect(const cv::Mat &mat)
{
    bool anyPressed;
    std::cout << "press detect" << std::endl;
    cv::Mat binaryFrame = convertToBinary(mat);
    for (int i = 0; i < keys.size(); i++)
    {
        anyPressed = false;
        int row = keys[i]->pos.y + keys[i]->pos.height * 0.5;
        int col = keys[i]->pos.x + keys[i]->pos.width * 0.5;
        //std::cout << "row:" << row << " col:" << col << std::endl;
        //std::cout << "mat rows:" << mat.rows << " mat cols:" << mat.cols << std::endl;
        if (binaryFrame.at<uchar>(row, col) == 255)
        {
            keys[i]->press();
            anyPressed = true;
        }

    }
}

/**
 * @brief extract edge from a frame of graph
 *
 * @param frame: original frame
 * @return a openCV mat with extracted edges
 */
cv::Mat convertToEdge(cv::Mat frame)
{
    cv::Mat grayFrame, binaryFrame, blurFrame, edgeFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::threshold(grayFrame, binaryFrame, 50, 255, cv::THRESH_BINARY);
    cv::GaussianBlur(binaryFrame, blurFrame, cv::Size(7, 7), 1);
    cv::Canny(blurFrame, edgeFrame, 0, 50);
    return edgeFrame;
}

void Piano::keyInit(const cv::Mat &mat)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Point> approx;

    cv::findContours(convertToEdge(mat), contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::cout << contours.size() << std::endl;

    int j = 0;

    for (int i = 0; i < contours.size(); i++)
    {
        cv::approxPolyDP(contours[i], approx, cv::arcLength(contours[i], true) * 0.02, true);
        if (approx.size() == 4 && sqrtf(powf((approx[0].x - approx[2].x), 2) + powf((approx[0].y - approx[2].y), 2)) > 50 &&
            sqrtf(powf((approx[0].x - approx[2].x), 2) + powf((approx[0].y - approx[2].y), 2)) < 200)
        {
            keys[j]->pos.x = approx[0].x;
            keys[j]->pos.y = approx[0].y;
            keys[j]->pos.width = approx[2].x - approx[0].x;
            keys[j]->pos.height = approx[2].y - approx[0].y;
            j++;
            if (j >= 7)
                return;
        }
    }
}


