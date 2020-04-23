#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include <QDir>
#include <QUrl>
#include <QStyle>

bool w_showed = false;
bool pressed_1 = true;
bool pressed_2 = true;
QString timer;
QString alarm_t;
QTimer c_time;
QTimer m_timer;
QMediaPlayer m_player;
QTime count(0,0,0);



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->windowOnTopHint->setIcon(style()->standardIcon(QStyle::SP_TitleBarUnshadeButton));
    ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->setAlarm->setIcon(QIcon("resource/alarm.ico"));
    m_player.setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("1.mp3")));
    m_player.setVolume(70);
    connect(&c_time,SIGNAL(timeout()),this,SLOT(s_timechange()));
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(t_timerchange()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(changeStyleTimerButton()));
    connect(ui->setAlarm,SIGNAL(clicked()),this,SLOT(changeStyleAlarmButton()));
    connect(ui->resetTimer_new,SIGNAL(clicked()),this,SLOT(resetTimer()));
    c_time.start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::s_timechange()
{
    ui->cur_time->setText(QTime::currentTime().toString("hh : mm : ss"));
    if(alarm_t == ui->cur_time->text()){
        m_player.play();
    }
}

void MainWindow::t_timerchange()
{
   count = count.addSecs(1);
   ui->wtimer->setText(count.toString("hh : mm : ss"));
}

void MainWindow::changeStyleTimerButton()
{
    if(!pressed_1){
       m_timer.stop();
       ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
       pressed_1 = true;
    }else{
        m_timer.start(1000);
        ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        pressed_1 = false;
    }
}

void MainWindow::changeStyleAlarmButton()
{
    if(!pressed_2){
        alarm_t = "";
        m_player.stop();
        pressed_2 = true;
        ui->setAlarm->setIcon(QIcon("resource/alarm.ico"));
    }else{
        alarm_t = ui->t_alarm->text();
        ui->setAlarm->setIcon(QIcon("resource/alarm_ac.ico"));
        pressed_2 = false;
    }
}

void MainWindow::resetTimer()
{
    count = QTime(0,0,0);
    ui->wtimer->setText(count.toString("hh : mm : ss"));
}

void MainWindow::on_windowOnTopHint_clicked()
{
    if(!w_showed){
            this->setWindowFlags(Qt::WindowStaysOnTopHint);
            this->show();
            w_showed = true;
        }else{
            Qt::WindowFlags flags;
            flags &= (Qt::WindowStaysOnTopHint);
            this->setWindowFlags(flags);
            this->show();
            w_showed = false;
        }
}

