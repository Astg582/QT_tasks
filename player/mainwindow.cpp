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
    this->resize(900, 600);
    play = new QPushButton("Play", this);
    stop = new QPushButton("Stop", this);
    open = new QPushButton("Open", this);
    name = new QLabel("Song name", this);
    time = new QLabel("00:00", this);
    volume = new QSlider(Qt::Horizontal, this);
    dur = new QSlider(Qt::Horizontal, this);
    player = new QMediaPlayer(this);
    out = new QAudioOutput();
    playlist = new Playlist(this);
    out->setParent(this);
    player->setMedia(QUrl("file:////home/astghik/Music/01.RedCity.mp3"));
    player->play();
    QString path = "file:///home/astghik/Music/01.RedCity.mp3";
    QStringList l = path.split("/");
    name->setText(l[l.length()-1]);

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
    QStringList songs=QFileDialog::getOpenFileNames(this, tr("Open Audio File"), QDir::homePath(), tr("Audio Files (*.mp3 *.wav *.ogg)"));

    playlist->append_songs(songs);

  //    QString songs = QFileDialog::getOpenFileName(this, tr("Open Audio File"), QDir::homePath(), tr("Audio Files (*.mp3 *.wav *.ogg)"));

  //  if (songs == "") {
     //   return;
   // }
    //player->setMedia(QUrl::fromLocalFile(songs));
    //QStringList l = songs.split("/");
    //name->setText(l[l.length()-1]);
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

    int start_h = percent(h, 5);
    play->setGeometry(percent(w, 5), percent(h, 15), percent(w, 10), start_h);
    play->setStyleSheet("background: magenta");

    int pause_h = percent(h, 5);
    stop->setGeometry(percent(w, 20), percent(h, 15), percent(w, 10), pause_h);
    stop->setStyleSheet("color: white; background-color: black; font: bold;");

    int name_h = percent(h, 5);
    name->setGeometry(percent(w, 35), percent(h, 15), percent(w, 35), name_h);
    name->setStyleSheet("background: magenta");

    int open_h = percent(h, 5);
    open->setGeometry(percent(w, 75), percent(h, 15), percent(w, 20), open_h);
    open->setStyleSheet("background: magenta");

    int volume_h = percent(h, 5);
    volume->setGeometry(percent(w, 80), percent(h, 20), percent(w, 10), volume_h);
    volume->setStyleSheet("color: darkCyan");

    int duration_h = percent(h, 5);
    dur->setGeometry(percent(w, 5), percent(h, 25), percent(w, 80), duration_h);
    dur->setStyleSheet("color: darkCyan");

    int sliderDur_h = percent(h, 5);
    time->setGeometry(percent(w, 90), percent(h, 25), percent(w, 8), sliderDur_h);
    time->setStyleSheet("background: pink");

    int list_h = percent(h, 25);
    playlist->setGeometry(percent(w, 5), percent(h, 65), percent(w, 90), list_h);
    playlist->setStyleSheet("background: purple");
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
