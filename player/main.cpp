#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  QIcon icon(":/home/astghik/Desktop/Task for Cloud/Task_for_cloud/task2/player/icon.webp"); // Путь к иконке приложения
   // a.setWindowIcon(icon);
    MainWindow w;
    w.show();
    return a.exec();
}
