#include "mainwindow.h"
#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <QLabel>
#include <QSlider>
#include <QFileDialog>
#include <QAudioOutput>


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->resize(900, 300);
    play = new QPushButton("Play", this);
    stop = new QPushButton("Stop", this);
    open = new QPushButton("Open", this);
    name = new QLabel("Song name", this);
    time = new QLabel("00:00", this);
    volume = new QSlider(Qt::Horizontal, this);
    dur = new QSlider(Qt::Horizontal, this);
    player = new QMediaPlayer(this);
    out = new QAudioOutput();
    out->setParent(this);
    player->setMedia(QUrl("file:///home/astghik/Music/10sec.mp3"));
    player->play();

    connect(play, &QPushButton::clicked, this, &MainWindow::play_pause);
    connect(stop, &QPushButton::clicked, this, &MainWindow::play_pause);
    connect(player, &QMediaPlayer::stateChanged, this, &MainWindow::dataChanged);

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::handlePosition);
    connect (dur, &QSlider::valueChanged, this, &MainWindow::handleDuration);
    connect(volume, &QSlider::valueChanged, this,  &MainWindow::handleVolume);
    connect(open, &QPushButton::clicked, this, &MainWindow::openFile);
}


void MainWindow::handleVolume() {
    out->setVolume(volume->value()/100.0);
    volume->setMinimum(0);
    volume->setMaximum(100);
}

void MainWindow::openFile() {
    QString path = QFileDialog::getOpenFileName();
    if (path == "") {
        return;
    }
    player->setMedia(QUrl(path));
    QStringList l = path.split("/");
    name->setText(l[l.length()-1]);
}


void MainWindow::dataChanged () {
    milis = player->duration();
    dur->setMinimum(0);
    dur->setMaximum(milis);
    setTime(0);
}

void MainWindow::setTime (qint64 m){
    qint64 t = milis-m;
    time->setText(QString::number(t/60000)+":"+QString::number((t % 60000)/1000));
}

void MainWindow::handlePosition(qint64 m){
    if (!lock){
        lock = true;
        dur -> setValue(m);
        setTime(m);
        lock = false;
    }

}

void MainWindow::handleDuration(){
    if(!lock){
        lock = true;
        qint64 t = dur->value();
        setTime(t);
        player->setPosition(t);
        lock = false;
    }

}

int MainWindow::percent(int val, double p) {
    return (p * val) / 100;
}


void MainWindow::resizeEvent(QResizeEvent* e) {
    QMainWindow::resizeEvent(e);

    int h = this->height();
    int w = this->width();

    int start_h = percent(h, 10);
    play->setGeometry(percent(w, 5), percent(h, 45), percent(w, 10), start_h);
    play->setStyleSheet("background: magenta");

    int pause_h = percent(h, 10);
    stop->setGeometry(percent(w, 20), percent(h, 45), percent(w, 10), pause_h);
    stop->setStyleSheet("background: moss");

    int name_h = percent(h, 10);
    name->setGeometry(percent(w, 35), percent(h, 45), percent(w, 35), name_h);
    name->setStyleSheet("background: magenta");

    int open_h = percent(h, 10);
    open->setGeometry(percent(w, 75), percent(h, 45), percent(w, 20), open_h);
    open->setStyleSheet("background: magenta");

    int volume_h = percent(h, 10);
    volume->setGeometry(percent(w, 80), percent(h, 60), percent(w, 10), volume_h);
    volume->setStyleSheet("color: darkCyan");

    int duration_h = percent(h, 10);
    dur->setGeometry(percent(w, 5), percent(h, 75), percent(w, 80), duration_h);
    dur->setStyleSheet("color: darkCyan");

    int sliderDur_h = percent(h, 10);
    time->setGeometry(percent(w, 90), percent(h, 75), percent(w, 8), sliderDur_h);
    time->setStyleSheet("background: pink");
}

void MainWindow::play_pause() {
    if (!play_flag) {
        player->play();
        play->setText("⏸️");
    } else {
        player->pause();
        play->setText("▶️");
    }
    play_flag = !play_flag;
}
void MainWindow::pauseSong() {
    player->stop();
    play_flag = false;
}


MainWindow::~MainWindow()
{
   // delete ui;
}
