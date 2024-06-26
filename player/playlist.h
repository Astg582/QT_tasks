#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QMap>
#include <QSet>

class Playlist : public QLabel
{
    Q_OBJECT

signals:
    void songIsReady();

private:
    QSet <QString> set;
    QStringList plist;
    QString cursong;
    qint64 ind;
    qint64 curindex{0};
    QVBoxLayout *lay;

public:
    explicit Playlist(QWidget *parent = nullptr);
    void append_songs(QStringList& songs);
    void click(qint64 i);
    void set_next();
    void set_prev();
    QString get_carsong();



signals:
};

#endif // PLAYLIST_H
