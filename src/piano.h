#ifndef PIANO_H
#define PIANO_H

#include <QWidget>
#include "camera.h"
#include <opencv2/opencv.hpp>
#include <QVector>
#include "key.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Piano; }
QT_END_NAMESPACE

class Piano : public QWidget
{
    Q_OBJECT

public:
    Piano(QWidget *parent = nullptr);
    ~Piano();

    struct MyCameraCallback : Camera::SceneCallback {
            Piano* piano = nullptr;
            virtual void nextScene(const cv::Mat &mat) {
                if (nullptr != piano) {
                    piano->runDetection(mat);
                }
            }
        };

        void runDetection(const cv::Mat &mat);

private:
    void pressDetect(const cv::Mat &mat);
    void keyInit(const cv::Mat &mat);

private:
    Ui::Piano *ui;
    MyCameraCallback myCallback;
    Camera camera;
    bool ready = false;
    QVector<Key*> keys;
};
#endif // PIANO_H
