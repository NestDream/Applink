#include <QtGui>
#include "start.h"
#include "user.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QByteArray>
#include <iostream>
#include <fstream>
using namespace std;

User::User(char* name="None",double time=99999)
{
    this->name = (char*)malloc(strlen(name)+1);
    strcpy(this->name,name);
    this->time = time;
}

char* User::Get_Name() const
{
    return name;
}

double User::Get_Time() const
{
    return time;
}

void User::set_name(char* Name)
{
    this->name=Name;
}

void User::set_time(double Time)
{
    this->time=Time;
}

void User::point(char* Name,double Time)
{
    this->name=Name;
    this->time=Time;
}

void User::Game_End(QString qname,double now_time)
{
    char* ch;
    QByteArray ba = qname.toLatin1();
    ch=ba.data();
    User allname[6];
    User temp(ch,now_time);
    double Time;
    char* Name=(char*)malloc(10*sizeof(char));
    int rank=0;

    ifstream out("/rank/rank.txt",ios::in);
    while(out>>Name>>Time){
        allname[rank].point(Name,Time);
        if(rank<=5){
            rank++;
            Name=(char*)malloc(10);
        }
        else
            break;
    }
    out.close();
    allname[5]=temp;

    for(int i=0;i<5;i++){
        for(rank=0;rank<5-i;rank++){
            if(allname[rank].Get_Time()>allname[rank+1].Get_Time()){
                temp=allname[rank];
                allname[rank]=allname[rank+1];
                allname[rank+1]=temp;
            }
        }
    }

    ofstream file;
    file.open("/rank/rank.txt",ios::out);
    for(rank=0;rank<5;rank++){

        file<<allname[rank].Get_Name()<<"  "<<allname[rank].Get_Time()<<endl;
    }
    file.close();
}

User::~User()
{
    if(name!=NULL)
        free(name);
}

User eUser::user;

Enter::Enter(QWidget *parent) :
    QDialog(parent)
{
    label=new QLabel(tr("请输入你的名字:"));
    lineEdit=new QLineEdit;
    label->setBuddy(lineEdit);

    startButton=new QPushButton(tr("开始游戏"));
    startButton->setDefault(true);
    startButton->setEnabled(false);

    returnButton=new QPushButton(tr("取消"));

    connect(lineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(enableFindButton(const QString &)));
    connect(startButton,SIGNAL(clicked()),this,SLOT(startClicked()));
    connect(returnButton,SIGNAL(clicked()),this,SLOT(close()));

    QHBoxLayout *lastButton=new QHBoxLayout;
    lastButton->addWidget(returnButton);
    lastButton->addWidget(startButton);

    QVBoxLayout *mainLayout= new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(lastButton);
    setLayout(mainLayout);

    setWindowTitle(tr("输入姓名"));
    setFixedHeight(sizeHint().height());
}

void Enter::startClicked()
{
    QString text=lineEdit->text();
    char* ch;
    QByteArray ba = text.toLatin1();
    ch=ba.data();
    eUser::user.set_name(ch);
    eUser::user.qname=text;
    close();
}

void Enter::enableFindButton(const QString &text)
{
    startButton->setEnabled(!text.isEmpty());
}
