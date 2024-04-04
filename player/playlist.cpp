#include "playlist.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStringList>

Playlist::Playlist(QWidget *parent)
    :QLabel(parent){
    lay = new QVBoxLayout(this);

}


void Playlist::append_songs(QStringList& songs){
    for(auto& song : songs){
        QLabel *l = new QLabel(song);
        lay->addWidget(l);
    }
}
