#ifndef APPENDICES_H
#define APPENDICES_H
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QString>
#include <QPushButton>
#include <QSound>
#include <user.h>

class Time : public QWidget
{
    Q_OBJECT
public:
    QString time;
    long count;
    Time(QWidget *parent = 0);
    virtual ~Time();
    void end();
private:
    QPushButton *timeLabel;
    QTimer* timer;
public slots:
    void timerEvent(QTimerEvent * event);
};

class MusicPLayer : public QSound
{
    Q_OBJECT
private:
    QSound* backsound;
    QSound* sound1;
    QSound* sound2;

public:
    void play();
    void stop();
    ~MusicPLayer();
    void setLoops (int l);
    void play1 ();
    void stop1 ();
    void play2 ();
    void stop2 ();
};



class QLabel;
class QPushButton;

class Rank : public QDialog
{
    Q_OBJECT

public:
    Rank(QWidget *parent = 0);

signals:
    void Close(const QString &str,Qt::CaseSensitivity cs);

private:
    QLabel *label;
    QPushButton *closeButton;
};
#endif // APPENDICES_H
