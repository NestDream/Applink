#include "appendices.h"
#include<iostream>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <fstream>
using namespace std;
static int flag = 0;
Time::Time(QWidget *parent)
	: QWidget(parent)
{
	timeLabel = new QPushButton(this);
	timer = new QTimer(this);
	count = -1;
	timeLabel->setText("时间： ");
	timerEvent(0);
	timer->setInterval(1000);
	startTimer(1000);
	timeLabel->show();
}

Time::~Time()
{
	flag = 0;
	delete timer;
	delete timeLabel;
}

void Time::timerEvent(QTimerEvent *event)
{
	Q_UNUSED(event);
	if (flag == 0) {
		count++;
	}
	QString time = QString::number(count, 10);
	timeLabel->setText("时间： " + time);
	timeLabel->adjustSize();
}

void Time::end()
{
	flag = 1;
}

void MusicPLayer::play()
{
	backsound = new QSound("./music/Foxtail.wav");
	backsound->setLoops(-1);
	backsound->play();
}

void MusicPLayer::stop()
{
	delete backsound;
}

MusicPLayer::~MusicPLayer()
{
	backsound->stop();
	delete backsound;
	delete sound1;
	delete sound2;
}

void MusicPLayer::play1()
{
	sound1 = new QSound("./music/select.wav");
	sound1->play();
}

void MusicPLayer::play2()
{
	sound2 = new QSound("./music/pair.wav");
	sound2->play();
}

void MusicPLayer::stop1()
{
	sound1 = new QSound("./music/select.wav");
	sound1->stop();
}

void MusicPLayer::stop2()
{
	sound2 = new QSound("./music/pair.wav");
	sound2->stop();
}



Rank::Rank(QWidget *parent) : QDialog(parent)
{
	label = new QLabel;

	char* name[5];
	int time[5];
	char *Name = (char*)malloc(10 * sizeof(char));
	int Time;
	int rank = 0;
	ifstream fout("./rank/rank.txt", ios::in);
	while (fout >> Name >> Time) {
		name[rank] = Name;
		time[rank] = Time;
		if (rank>5) {
			break;
		}
		else {
			rank++;
			Name = (char*)malloc(10 * sizeof(char));
		}

	}
	fout.close();
	label->setText("Top5玩家排行榜\n\n1." +
		QString(name[0]) + " " + QString::number(time[0]) + "\n2." +
		QString(name[1]) + " " + QString::number(time[1]) + "\n3." +
		QString(name[2]) + " " + QString::number(time[2]) + "\n4." +
		QString(name[3]) + " " + QString::number(time[3]) + "\n5." +
		QString(name[4]) + " " + QString::number(time[4]) + "\n");

	closeButton = new QPushButton(tr("关闭"));
	closeButton->setDefault(true);
	closeButton->setEnabled(true);

	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(label);
	mainLayout->addWidget(closeButton);

	QHBoxLayout *window = new QHBoxLayout;
	window->addStretch();
	window->addLayout(mainLayout);
	window->addStretch();
	setLayout(window);
	setWindowTitle(tr("排行榜"));
	setFixedSize(200, 350);
}
