#ifndef APPLINK_H
#define APPLINK_H
#include<QLayout>
#include<QPushButton>
#include<QSignalMapper>
#include<QWidget>
#include<QMessageBox>
#include<iostream>
#include"button.h"
#include"start.h"
#include"user.h"
#include"appendices.h"

class applink:public QObject
{
    Q_OBJECT

private:
    enum{Null,Right,Left,Up,Down};
    static const int WIDTH=10,HEIGHT=14;
    static const int imagenum=36;
    int x1,y1,x2,y2,x3,y3,x4,y4;
    int map[WIDTH+2][HEIGHT+2];
    int bendcount;
    int totalpics[imagenum+1];
    bool eliminable;
    int StartStatus;
    bool isEasy;
    struct{
        int x;
        int y;
    }bucket[imagenum+1][5];
    QGridLayout *gridlayout;
    QHBoxLayout *hlayout1,*hlayout2,*hlayout3,*hlayout4;
    QVBoxLayout *vlayout;
    QSignalMapper *signalMapper[WIDTH][HEIGHT];
    QPushButton *block[2*WIDTH+2*HEIGHT+4];
    QPushButton *hardmode;
    QPushButton *ranks;
    QPushButton *easymode;
    QPushButton *exitgame;
    Button *image[WIDTH][HEIGHT];
    QPushButton *mapchangingbutton;
    QPushButton *tipbutton;
    QPushButton *easymodebutton;
    Time *timer;
    QWidget *window;
    MusicPLayer *sound;


    void binitial();
    void createmap();
    void setgamingwindow();
    void setimage();
    void setblock();
    bool canbeeliminate();
    bool notdeadgame();
    void dfs_judge(int x,int y,int x2,int y2,int type);
    void del(int k,int x,int y);
    Button *createButton(QString &str1,QString &str2,QString &str3);
    QPushButton *createButton(QString &str);
    void cancelstart();
    void cancelgame();

public:
    applink();
    virtual ~applink();
    int imageNum;

private slots:

    void MainWindowInitialize();
    void autofind();
    void start_normal();
    void start_easy();
    void showRanks();
    void startGame();
    void exitGame();
    void change(int num);
    void show();
    void recreate();
    void updateButtonStatus();
    void updateButtonStatus2();
};

#endif // APPLINK_H
