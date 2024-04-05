#include "mainwindow.h"
#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <QLabel>
#include <QSlider>
#include <QFileDialog>
#include <QAudioOutput>
#include <QIcon>


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->resize(900, 600);
    this->setWindowTitle("Music");
    this->setWindowIcon(QIcon("/home/astghik/Desktop/Task for Cloud/Task_for_cloud/task2/player/icon0.png"));
    play = new QPushButton("Play", this);
    open = new QPushButton("+", this);
    next = new QPushButton(">>", this);
    prev = new QPushButton("<<", this);
    name = new QLabel("Song name", this);
    time = new QLabel("00:00", this);
    volume = new QSlider(Qt::Vertical, this);
    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(50);
    dur = new QSlider(Qt::Horizontal, this);
    player = new QMediaPlayer(this);
    out = new QAudioOutput();
    playlist = new Playlist(this);
    out->setParent(this);
    player->setMedia(QUrl("file://///home/astghik/Music/FridayPilotsClub-ForTheWicked(LYRIC VIDEO).mp3"));
    player->play();

    QString path = "file://///home/astghik/Music/FridayPilotsClub-ForTheWicked(LYRIC VIDEO).mp3";
    QStringList l = path.split("/");
    name->setText(l[l.length()-1]);

    connect(play, &QPushButton::clicked, this, &MainWindow::play_pause);
    connect(player, &QMediaPlayer::stateChanged, this, &MainWindow::dataChanged);
    connect(next, &QPushButton::clicked, this, &MainWindow::hendle_next);
    connect(prev, &QPushButton::clicked, this, &MainWindow::hendle_prev);
    connect(playlist, &Playlist::songIsReady, this, &MainWindow::handSongR);

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::handlePosition);
    connect (dur, &QSlider::valueChanged, this, &MainWindow::handleDuration);
    connect(volume, &QSlider::valueChanged, this,  &MainWindow::handleVolume);
    connect(open, &QPushButton::clicked, this, &MainWindow::openFile);
}

void MainWindow::handSongR(){
    player->setMedia(QUrl("file:////" + playlist->get_carsong()));
    QStringList l = playlist->get_carsong().split("/");
    name->setText(l[l.length()-1]);
}

void MainWindow::hendle_next(){
    playlist->set_next();
}
void MainWindow::hendle_prev(){
    playlist->set_prev();

}

void MainWindow::handleVolume() {
    out->setVolume(volume->value()/100.0);
}

void MainWindow::openFile() {
    QStringList songs=QFileDialog::getOpenFileNames(this, tr("Open Audio File"), QDir::homePath(), tr("Audio Files (*.mp3 *.wav *.ogg)"));

    playlist->append_songs(songs);

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
    this->setStyleSheet("background: #292825;");
    int h = this->height();
    int w = this->width();



    int name_h = percent(h, 5);
    name->setGeometry(percent(w, 5), percent(h, 37), percent(w,80), name_h);
    name->setStyleSheet("background: transparent; color: white;");

    int open_h = percent(h, 5);
    open->setGeometry(percent(w, 85), percent(h, 50), percent(w, 10), open_h);
    open->setStyleSheet("QPushButton { background: DarkGoldenrod; } border: none; border-radius: 2px");

    int prev_h = percent(h, 5);
    prev->setGeometry(percent(w, 30), percent(h, 44), percent(w, 10), prev_h);
    prev->setStyleSheet("color: white; background-color: black; font: bold; border: none; border-radius: 2px");

    int start_h = percent(h, 5);
    play->setGeometry(percent(w, 41), percent(h, 44), percent(w, 10), start_h);
    play->setStyleSheet("background: DarkGoldenrod; text-align: center; border: none; border-radius: 2px");

    int next_h = percent(h, 5);
    next->setGeometry(percent(w, 52), percent(h, 44), percent(w, 10), next_h);
    next->setStyleSheet("color: white; background-color: black; font: bold; border: none; border-radius: 2px");

    int volume_h = percent(h, 15);
    volume->setGeometry(percent(w, 90), percent(h, 30), percent(w, 2), volume_h);
    volume->setStyleSheet("QSlider::groove:horizontal { color: #9C200D ; }"
                          "QSlider::handle:horizontal { color: #9C200D ; }");

    int duration_h = percent(h, 5);
    dur->setGeometry(percent(w, 5), percent(h, 50), percent(w, 70), duration_h);
    dur->setStyleSheet("color: #9C200D");

    int sliderDur_h = percent(h, 2);
    time->setGeometry(percent(w, 77), percent(h, 51), percent(w, 8), sliderDur_h);
    time->setStyleSheet("background: transparent; color: white; text-align: center;");

    int list_h = percent(h, 40);
    playlist->setGeometry(percent(w, 5), percent(h, 56), percent(w, 90), list_h);
    playlist->setStyleSheet("background: transparent; color: white; text-align: center;");
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
