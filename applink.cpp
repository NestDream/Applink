#include "applink.h"

#include<QBitmap>
#include<QPixmap>
#include<QTimer>
#include<QPalette>
#include<algorithm>
#include<iostream>
#include<stdio.h>
#include<time.h>

applink::applink()
{
    StartStatus=2;
    window=0;
    MainWindowInitialize();
}

applink::~applink()
{
    if(StartStatus==1){
        cancelgame();
        delete window;
    }
    else if(StartStatus==0){
        cancelstart();
        delete window;
    }
}

void applink::createmap()
{
    int b[WIDTH*HEIGHT];
    int i,j,k;

    for(i=0;i<WIDTH*HEIGHT;i+=4){
        b[i]=b[i+1]=b[i+2]=b[i+3]=i/4+1;
    }
    srand((unsigned)time(NULL));
    std::random_shuffle(b,b+WIDTH*HEIGHT);
    k=0;
    memset(map,0,sizeof(map));
    for(i=1;i<=WIDTH;i++){
        for(j=1;j<=HEIGHT;j++){
            map[i][j]=b[k];
            k++;
        }
    }
}
void applink::recreate()
{
    int b[WIDTH*HEIGHT];
    int i,j;
    int k=0;
    int temp;

    for(i=1;i<=WIDTH;i++){
        for(j=1;j<=HEIGHT;j++){
            b[k]=map[i][j];
            k++;
        }
    }
    srand((unsigned)time(NULL));
    for(i=1;i<WIDTH*HEIGHT;i++){
        if(b[i]==0)
            continue;
        j=rand()%(i+1);
        k=2;
        while(b[j]==0){
            j=rand()%(i+k);
            k++;
        }
        temp=b[i];
        b[i]=b[j];
        b[j]=temp;
    }
    k=0;
    for(i=1;i<=WIDTH;i++){
        for(j=1;j<=HEIGHT;j++){
            map[i][j]=b[k];
            k++;
        }
    }
    for(i=0;i<WIDTH;i++){
        for(j=0;j<HEIGHT;j++){
            if(map[i+1][j+1]!=0){
                delete image[i][j];
                delete signalMapper[i][j];
            }
        }
    }
    setimage();
    binitial();
    if(!notdeadgame())recreate();
}

void applink::cancelgame()
{
    int i,j;
    for(i=0;i<WIDTH;i++){
        for(j=0;j<HEIGHT;j++){
            if(map[i+1][j+1]!=0){
                delete image[i][j];
                delete signalMapper[i][j];
            }
        }
    }
    for(i=0;i<2*WIDTH+2*HEIGHT+4;i++){
        delete block[i];
    }
    delete mapchangingbutton;
    delete tipbutton;
    if(isEasy)delete easymodebutton;
    delete timer;

    delete gridlayout;
    delete vlayout;
    delete hlayout1;
}

void applink::cancelstart()
{
    delete hardmode;
    delete ranks;
    delete hlayout1;
    delete hlayout2;
    delete hlayout3;
    delete vlayout;
}

void applink::change(int num)
{

    int x=num/100+1;
    int y=num%100+1;
    double ftime;
    enum{first,second};
    static int vis=first;
    if(vis==first){
        x1=x;
        y1=y;
        vis=second;
        sound->play1();
        sound->stop1();
    }
    else if(vis==second){
        x2=x;
        y2=y;
        if(x1==x2&&y1==y2){
            sound->play1();
            sound->stop1();
        }
        else if(canbeeliminate()){
            del(map[x1][y1],x1,y1);
            del(map[x1][y1],x2,y2);
            delete image[x1-1][y1-1];
            delete image[x2-1][y2-1];
            delete signalMapper[x1-1][y1-1];
            delete signalMapper[x2-1][y2-1];
            map[x1][y1]=0;
            map[x2][y2]=0;
            imageNum-=2;

            if(imageNum==0){
                QMessageBox msg;
                timer->end();
                sound->stop();
                ftime=timer->count;
                eUser::user.Game_End(eUser::user.qname,ftime);
                msg.setText(tr("恭喜！游戏胜利！"));
                msg.exec();
                cancelgame();
                delete window;
                MainWindowInitialize();
                return;
            }
            if(!notdeadgame()){
                 QMessageBox msg;
                 msg.setText(tr("地图上的图标均不可连接，\n系统自动生成新地图"));
                 msg.exec();
                 recreate();
            }
        }
        else{
            sound->play1();
            sound->stop1();
        }
        vis=first;
    }
}

void applink::setimage()
{
    QString str1[]={"/image/1.jpg",
                   "/image/2.jpg",
                   "/image/3.jpg",
                   "/image/4.jpg",
                   "/image/5.jpg",
                   "/image/6.jpg",
                   "/image/7.jpg",
                   "/image/8.jpg",
                   "/image/9.jpg",
                   "/image/10.jpg",
                   "/image/11.jpg",
                   "/image/12.jpg",
                   "/image/13.jpg",
                   "/image/14.jpg",
                   "/image/15.jpg",
                   "/image/16.jpg",
                   "/image/17.jpg",
                   "/image/18.jpg",
                   "/image/19.jpg",
                   "/image/20.jpg",
                   "/image/21.jpg",
                   "/image/22.jpg",
                   "/image/23.jpg",
                   "/image/24.jpg",
                   "/image/25.jpg",
                   "/image/26.jpg",
                   "/image/27.jpg",
                   "/image/28.jpg",
                   "/image/29.jpg",
                   "/image/30.jpg",
                   "/image/31.jpg",
                   "/image/32.jpg",
                   "/image/33.jpg",
                   "/image/34.jpg",
                   "/image/35.jpg",
                   "/image/36.jpg"};
    QString str2[]={"/image/1s.jpg",
                   "/image/2s.jpg",
                   "/image/3s.jpg",
                   "/image/4s.jpg",
                   "/image/5s.jpg",
                   "/image/6s.jpg",
                   "/image/7s.jpg",
                   "/image/8s.jpg",
                   "/image/9s.jpg",
                   "/image/10s.jpg",
                   "/image/11s.jpg",
                   "/image/12s.jpg",
                   "/image/13s.jpg",
                   "/image/14s.jpg",
                   "/image/15s.jpg",
                   "/image/16s.jpg",
                   "/image/17s.jpg",
                   "/image/18s.jpg",
                   "/image/19s.jpg",
                   "/image/20s.jpg",
                   "/image/21s.jpg",
                   "/image/22s.jpg",
                   "/image/23s.jpg",
                   "/image/24s.jpg",
                   "/image/25s.jpg",
                   "/image/26s.jpg",
                   "/image/27s.jpg",
                   "/image/28s.jpg",
                   "/image/29s.jpg",
                   "/image/30s.jpg",
                   "/image/31s.jpg",
                   "/image/32s.jpg",
                   "/image/33s.jpg",
                   "/image/34s.jpg",
                   "/image/35s.jpg",
                   "/image/36s.jpg"};
    QString str3[]={"/image/1p.jpg",
                   "/image/2p.jpg",
                   "/image/3p.jpg",
                   "/image/4p.jpg",
                   "/image/5p.jpg",
                   "/image/6p.jpg",
                   "/image/7p.jpg",
                   "/image/8p.jpg",
                   "/image/9p.jpg",
                   "/image/10p.jpg",
                   "/image/11p.jpg",
                   "/image/12p.jpg",
                   "/image/13p.jpg",
                   "/image/14p.jpg",
                   "/image/15p.jpg",
                   "/image/16p.jpg",
                   "/image/17p.jpg",
                   "/image/18p.jpg",
                   "/image/19p.jpg",
                   "/image/20p.jpg",
                   "/image/21p.jpg",
                   "/image/22p.jpg",
                   "/image/23p.jpg",
                   "/image/24p.jpg",
                   "/image/25p.jpg",
                   "/image/26p.jpg",
                   "/image/27p.jpg",
                   "/image/28p.jpg",
                   "/image/29p.jpg",
                   "/image/30p.jpg",
                   "/image/31p.jpg",
                   "/image/32p.jpg",
                   "/image/33p.jpg",
                   "/image/34p.jpg",
                   "/image/35p.jpg",
                   "/image/36p.jpg"};

    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT;j++){
            int tmp=map[i+1][j+1];
            if(tmp!=0){
                signalMapper[i][j]= new QSignalMapper;
                image[i][j]=createButton(str1[tmp-1],str2[tmp-1],str3[tmp-1]);
                gridlayout->addWidget(image[i][j],i+1,j+1);
                connect(image[i][j],SIGNAL(clicked()),signalMapper[i][j],SLOT(map()));
                signalMapper[i][j]->setMapping(image[i][j],100*i+j);
                connect(signalMapper[i][j],SIGNAL(mapped(int)),this, SLOT(change(int)));
            }
        }
    }
}

void applink::MainWindowInitialize()
{
    StartStatus=0;
    window=new QWidget;
    window->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap("/image/window.jpg")));
    window->setPalette(palette);

    ranks=new QPushButton("查看TOP5玩家排行榜");
    hardmode=new QPushButton("开始游戏（困难）");
    easymode=new QPushButton("开始游戏（简单）");
    exitgame=new QPushButton("退出游戏");

    vlayout=new QVBoxLayout;
    hlayout1=new QHBoxLayout;
    hlayout2=new QHBoxLayout;
    hlayout3=new QHBoxLayout;
    hlayout4=new QHBoxLayout;

    hlayout1->addStretch();
    hlayout1->addWidget(hardmode);
    hlayout1->addStretch();

    hlayout3->addStretch();
    hlayout3->addWidget(easymode);
    hlayout3->addStretch();

    hlayout2->addStretch();
    hlayout2->addWidget(ranks);
    hlayout2->addStretch();

    hlayout4->addStretch();
    hlayout4->addWidget(exitgame);
    hlayout4->addStretch();

    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout4);

    window->setLayout(vlayout);
    window->setFixedSize(800,600);
    window->show();

    connect(hardmode,SIGNAL(clicked()),this,SLOT(start_normal()));
    connect(easymode,SIGNAL(clicked()),this,SLOT(start_easy()));
    connect(ranks,SIGNAL(clicked()),this,SLOT(showRanks()));
    connect(exitgame,SIGNAL(clicked()),this,SLOT(exitGame()));
}

void applink::setblock()
{

    QString str("/image/null.png");
    int cnt=0;
    for(int i=0;i<=WIDTH+1;i++){
        block[cnt]=createButton(str);
        gridlayout->addWidget(block[cnt++],i,0);
    }
    for(int j=1;j<=HEIGHT+1;j++){
        block[cnt]=createButton(str);
        gridlayout->addWidget(block[cnt++],0,j);
    }
    for(int i=1;i<=WIDTH+1;i++){
        block[cnt]=createButton(str);
        gridlayout->addWidget(block[cnt++],i,HEIGHT+1);
    }
    for(int j=1;j<=HEIGHT+1;j++){
        block[cnt]=createButton(str);
        gridlayout->addWidget(block[cnt++],WIDTH+1,j);
    }
}

void applink::setgamingwindow()
{
    window=new QWidget;
    window->setWindowTitle(tr("App-link连连看"));
    window->resize(800,600);

    gridlayout=new QGridLayout;
    hlayout1=new QHBoxLayout;
    vlayout=new QVBoxLayout;

    mapchangingbutton=new QPushButton();
    QString mapadd("/image/map2.jpg");
    QString hintadd("/image/hint3.jpg");
    QPixmap img1(mapadd),img2(hintadd);
    mapchangingbutton->setIcon(img1);
    mapchangingbutton->setIconSize(QSize(150,100));
    mapchangingbutton->setFlat(true);

    tipbutton=new QPushButton();
    tipbutton->setIcon(img2);
    tipbutton->setFlat(true);
    tipbutton->setIconSize(QSize(150,100));
    if(isEasy)easymodebutton=new QPushButton(tr("简单模式-无限提示"));
    else{
        easymodebutton=new QPushButton;
        easymodebutton->setFlat(true);
    }
    timer=new Time;

    vlayout->addWidget(timer);
    vlayout->addWidget(mapchangingbutton);
    vlayout->addWidget(tipbutton);
    vlayout->addWidget(easymodebutton);

    connect(tipbutton,SIGNAL(clicked()),this,SLOT(show()));
    connect(tipbutton,SIGNAL(clicked()),this,SLOT(updateButtonStatus()));
    connect(mapchangingbutton,SIGNAL(clicked()),this,SLOT(recreate()));
    connect(mapchangingbutton,SIGNAL(clicked()),this,SLOT(updateButtonStatus2()));
    if(isEasy)connect(easymodebutton,SIGNAL(clicked()),this,SLOT(autofind()));
    setblock();
    setimage();

    window->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap("/image/arrow.png")));
    window->setPalette(palette);
    hlayout1->addLayout(gridlayout);
    hlayout1->addLayout(vlayout);
    window->setLayout(hlayout1);
    window->show();
    notdeadgame();

}

void applink::updateButtonStatus()
{
    QString str[]={"/image/hint0.jpg",
                   "/image/hint1.jpg",
                   "/image/hint2.jpg"};
    QPixmap img0(str[0]),img1(str[1]),img2(str[2]);
    static int cnt=1;
    if(cnt==1){
        tipbutton->setIcon(img2);
    }
    else if(cnt==2){
        tipbutton->setIcon(img1);
    }
    else if(cnt==3){
        tipbutton->setIcon(img0);
        tipbutton->setEnabled(false);
    }
    cnt++;
}

void applink::updateButtonStatus2()
{
    QString str[]={"/image/map0.jpg",
                   "/image/map1.jpg"};
    QPixmap img0(str[0]),img1(str[1]);
    static int cnt=1;
    if(cnt==1){
        mapchangingbutton->setIcon(img1);
    }
    else if(cnt==2){
        mapchangingbutton->setIcon(img0);
        mapchangingbutton->setEnabled(false);
    }
    cnt++;
}

void applink::start_normal()
{
    isEasy=false;
    Enter *start=new Enter;
    start->show();
    connect(start->startButton,SIGNAL(clicked()),this,SLOT(startGame()));
}

void applink::start_easy()
{
    isEasy=true;
    Enter *start=new Enter;
    start->show();
    connect(start->startButton,SIGNAL(clicked()),this,SLOT(startGame()));
}

void applink::startGame()
{
    StartStatus=1;
    delete hardmode;
    delete ranks;
    delete hlayout1;
    delete hlayout2;
    delete hlayout3;
    delete vlayout;
    delete window;
    StartStatus=true;
    imageNum=WIDTH*HEIGHT;
    createmap();
    binitial();
    setgamingwindow();
    sound->play();
}

void applink::showRanks()
{
    Rank *p=new Rank();
    p->show();
}

void applink::exitGame()
{
    StartStatus=3;
    cancelstart();
    delete window;
}

Button *applink::createButton(QString &str1,QString &str2,QString &str3)
{
    Button *button=new Button;
    button->setGeometry(0,0,0,0);
    QPixmap img1,img2,img3;
    img1.load(str1);
    img2.load(str2);
    img3.load(str3);
    button->setFixedSize(img1.width(),img1.height());
    button->SetButtonIcons(img1,img2,img3);
    button->setIconSize(QSize(img1.width(),img1.height()));
    return button;
}


QPushButton *applink::createButton(QString &str)
{
    QPushButton *button=new QPushButton;
    QPixmap img(str);
    button->setFixedSize(img.width(),img.height());
    button->setFlat(true);
    return button;
}

bool applink::canbeeliminate()
{
    eliminable=false;
    bendcount=0;
    if(map[x1][y1]!=map[x2][y2])return false;
    dfs_judge(x1,y1,x2,y2,Null);
    if(eliminable==true){
        sound->play2();
        sound->stop2();
        return true;
    }
    return false;
}

void applink::dfs_judge(int x,int y,int x2,int y2,int type)
{
    if(eliminable==true)return;
    if(bendcount>=3)return;
    if(x==WIDTH+2||x<0||y==HEIGHT+2||y<0)return;
    if(x==x2&&y==y2){
        eliminable=true;
        return;
    }
    if(map[x][y]!=0&&type!=Null)return;
    if(type!=Up&&type!=Null){
        bendcount++;
        dfs_judge(x-1,y,x2,y2,Up);
        bendcount--;
    }
    else{
        dfs_judge(x-1,y,x2,y2,Up);
    }
    if(eliminable==true)return;
    if(type!=Down&&type!=Null){
        bendcount++;
        dfs_judge(x+1,y,x2,y2,Down);
        bendcount--;
    }
    else{
        dfs_judge(x+1,y,x2,y2,Down);
    }
    if(eliminable==true)return;
    if(type!=Left&&type!=Null){
        bendcount++;
        dfs_judge(x,y-1,x2,y2,Left);
        bendcount--;
    }
    else{
        dfs_judge(x,y-1,x2,y2,Left);
    }
    if(eliminable==true)return;
    if(type!=Right&&type!=Null){
        bendcount++;
        dfs_judge(x,y+1,x2,y2,Right);
        bendcount--;
    }
    else{
        dfs_judge(x,y+1,x2,y2,Right);
    }

    if(eliminable==true)return;
}

void applink::binitial(){
    memset(totalpics,0,sizeof(totalpics));
    memset(bucket,0,sizeof(bucket));
    for(int i=1;i<=WIDTH;i++){
        for(int j=1;j<=HEIGHT;j++){
            if(map[i][j]!=0){
                bucket[map[i][j]][totalpics[map[i][j]]].x=i;
                bucket[map[i][j]][totalpics[map[i][j]]++].y=j;
            }
        }
    }
}
bool applink::notdeadgame()
{
    eliminable=false;
    static int cnt=1;
    for(int k=1;k<=imagenum;k++){
        for(int i=0;i<totalpics[k]-1;i++){
            for(int j=i+1;j<totalpics[k];j++){
                x3=bucket[k][i].x;
                y3=bucket[k][i].y;
                x4=bucket[k][j].x;
                y4=bucket[k][j].y;
                bendcount=0;
                dfs_judge(x3,y3,x4,y4,Null);
                if(eliminable){
                    return true;
                }
            }
        }
    }
    return false;
}

void applink::del(int k,int x,int y)
{
    int i;
    for(i=0;i<totalpics[k];i++){
        if(bucket[k][i].x==x&&bucket[k][i].y==y)break;
    }
    for(;i<totalpics[k]-1;i++){
        bucket[k][i].x=bucket[k][i+1].x;
        bucket[k][i].y=bucket[k][i+1].y;
    }
    totalpics[k]--;
}

void applink::show()
{
    QString str3[]={"/image/1s.jpg",
                   "/image/2s.jpg",
                   "/image/3s.jpg",
                   "/image/4s.jpg",
                   "/image/5s.jpg",
                   "/image/6s.jpg",
                   "/image/7s.jpg",
                   "/image/8s.jpg",
                   "/image/9s.jpg",
                   "/image/10s.jpg",
                   "/image/11s.jpg",
                   "/image/12s.jpg",
                   "/image/13s.jpg",
                   "/image/14s.jpg",
                   "/image/15s.jpg",
                   "/image/16s.jpg",
                   "/image/17s.jpg",
                   "/image/18s.jpg",
                   "/image/19s.jpg",
                   "/image/20s.jpg",
                   "/image/21s.jpg",
                   "/image/22s.jpg",
                   "/image/23s.jpg",
                   "/image/24s.jpg",
                   "/image/25s.jpg",
                   "/image/26s.jpg",
                   "/image/27s.jpg",
                   "/image/28s.jpg",
                   "/image/29s.jpg",
                   "/image/30s.jpg",
                   "/image/31s.jpg",
                   "/image/32s.jpg",
                   "/image/33s.jpg",
                   "/image/34s.jpg",
                   "/image/35s.jpg",
                   "/image/36s.jpg"};
    QString str1[]={"/image/1p.jpg",
                   "/image/2p.jpg",
                   "/image/3p.jpg",
                   "/image/4p.jpg",
                   "/image/5p.jpg",
                   "/image/6p.jpg",
                   "/image/7p.jpg",
                   "/image/8p.jpg",
                   "/image/9p.jpg",
                   "/image/10p.jpg",
                   "/image/11p.jpg",
                   "/image/12p.jpg",
                   "/image/13p.jpg",
                   "/image/14p.jpg",
                   "/image/15p.jpg",
                   "/image/16p.jpg",
                   "/image/17p.jpg",
                   "/image/18p.jpg",
                   "/image/19p.jpg",
                   "/image/20p.jpg",
                   "/image/21p.jpg",
                   "/image/22p.jpg",
                   "/image/23p.jpg",
                   "/image/24p.jpg",
                   "/image/25p.jpg",
                   "/image/26p.jpg",
                   "/image/27p.jpg",
                   "/image/28p.jpg",
                   "/image/29p.jpg",
                   "/image/30p.jpg",
                   "/image/31p.jpg",
                   "/image/32p.jpg",
                   "/image/33p.jpg",
                   "/image/34p.jpg",
                   "/image/35p.jpg",
                   "/image/36p.jpg"};
    delete image[x3-1][y3-1];
    delete image[x4-1][y4-1];
    delete signalMapper[x3-1][y3-1];
    delete signalMapper[x4-1][y4-1];
    signalMapper[x3-1][y3-1]=new QSignalMapper;
    signalMapper[x4-1][y4-1]=new QSignalMapper;
    image[x3-1][y3-1]=createButton(str1[map[x3][y3]-1],str1[map[x3][y3]-1],str3[map[x3][y3]-1]);
    image[x4-1][y4-1]=createButton(str1[map[x4][y4]-1],str1[map[x4][y4]-1],str3[map[x4][y4]-1]);
    gridlayout->addWidget(image[x3-1][y3-1],x3,y3);
    gridlayout->addWidget(image[x4-1][y4-1],x4,y4);
    connect(image[x3-1][y3-1],SIGNAL(clicked()),signalMapper[x3-1][y3-1],SLOT(map()));
    connect(image[x4-1][y4-1],SIGNAL(clicked()),signalMapper[x4-1][y4-1],SLOT(map()));
    signalMapper[x3-1][y3-1]->setMapping(image[x3-1][y3-1],100*(x3-1)+y3-1);
    signalMapper[x4-1][y4-1]->setMapping(image[x4-1][y4-1],100*(x4-1)+y4-1);
    connect(signalMapper[x3-1][y3-1],SIGNAL(mapped(int)),this, SLOT(change(int)));
    connect(signalMapper[x4-1][y4-1],SIGNAL(mapped(int)),this, SLOT(change(int)));
}

void applink::autofind()
{
    change(100*(x3-1)+y3-1);
    change(100*(x4-1)+y4-1);
}
