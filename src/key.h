#ifndef KEY_H
#define KEY_H
#include <QWidget>
#include <QMediaPlayer>
#include <QString>
#include <opencv2/opencv.hpp>

class Key : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Key
     * @param _text key label
     * @param _note sound file url
     * @param parent
     */
    Key(const QString& _text, const QString& _note, QWidget* parent = nullptr) : QWidget(parent) {
        text = _text;
        m_noteSound = new QMediaPlayer(this);
        m_noteSound->setMedia(QUrl::fromLocalFile(_note));

    }
    ~Key()
    {
        delete m_noteSound;
    }

    cv::Rect pos;

public slots:
    void press()
    {
        std::cout << text.toStdString() << std::endl;

        m_noteSound->play();
    }

private:
    QString text;
    QMediaPlayer* m_noteSound;
};


#endif
