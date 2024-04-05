#include "playlist.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStringList>
#include <QPushButton>


Playlist::Playlist(QWidget *parent)
    :QLabel(parent){
    lay = new QVBoxLayout(this);
    ind = 0;
}


void Playlist::click(qint64 i){
  /*  if(i < 0 ){
        return;
    }
    if(i >= ind){
        i = 0;
    }*/
    if (plist.isEmpty()) { // Проверяем, не пуст ли список
        return;
    }

    if (i < 0) {
        i = plist.size() - 1; // Если индекс отрицательный, переходим к последнему элементу
    } else if (i >= plist.size()) {
        i = 0; // Если индекс больше или равен размеру списка, переходим к первому элементу
    }


    cursong = plist[i];
    curindex = i;

     emit songIsReady();
}

void Playlist::set_next(){
    click(curindex + 1);
}

void Playlist::set_prev(){
    click(curindex - 1);
}

QString Playlist::get_carsong(){
    return cursong;
}

void Playlist::append_songs(QStringList& songs){
    for(auto& song : songs){
        if(set.contains(song)){
            continue;
        }
        set.insert(song);
        QStringList num = song.split("/");
        QPushButton *btn = new QPushButton(num[num.length() -1]);
        lay->addWidget(btn);
        plist << song;
        qint64 i = this->ind;
        connect(btn, &QPushButton::clicked, [=](){ click(i); });
        ++ind;
    }
}
