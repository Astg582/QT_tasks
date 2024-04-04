#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>


class Playlist : public QLabel
{
    Q_OBJECT

private:
    QVBoxLayout *lay;

public:
    explicit Playlist(QWidget *parent = nullptr);
    void append_songs(QStringList& songs);


signals:
};

#endif // PLAYLIST_H
