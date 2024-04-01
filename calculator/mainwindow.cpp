#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QResizeEvent>
#include <QStringList>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    QStringList but = {
        "(",  ")", "%", "AC",
        "7", "8",  "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };


    QStringList butL = {
        "RED", "Deg", "x!", "(",  ")", "%", "AC",
        "Inv","sin", "In", "7", "8",  "9", "/",
        "π", "cos", "log", "4", "5", "6", "*",
        "e", "tan", "√", "1", "2", "3", "-",
        "Ans", "EXP", "x^y", "0", ".", "=", "+"
    };

    btns = new QPushButton*[5];


    int position = 0;

    for(int i = 0; i < 5; ++i){
           btns[i] = new QPushButton[4];
           for(int j = 0; j < 4; ++j){
               btns[i][j].setParent(this);
               btns[i][j].setText(but[position]);
               ++position;
                connect(&btns[i][j], &QPushButton::clicked, this, &MainWindow::onPushButton);
           }
       }

       le = new QLineEdit("", this);
       le->setAlignment(Qt::AlignRight);

}

void MainWindow::keyPressEvent(QKeyEvent *event) {

     Qt::Key key = static_cast<Qt::Key>(event->key());
     if (key == Qt::Key_Delete) {
         le->clear();
         return;
     }


     QString keyString = QKeySequence(key).toString();
     for (int i = 0; i < 5; ++i) {
         for (int j = 0; j < 4; ++j) {
             if (btns[i][j].text() == keyString) {
                 btns[i][j].click();
                 return;
             }
         }
     }

    QMainWindow::keyPressEvent(event);
}



int MainWindow::percent (int val,  double p){
    return (p * val )/100;
}

void MainWindow::resizeEvent(QResizeEvent *e){
    int w = e->size().width();
    int h = e->size().height();
    int le_h = percent(h,20);
       le->setGeometry(percent(w, 5), percent(le_h, 5), percent(w, 90), percent(le_h, 90));

       int x = 0;
       int y = le_h;
       int iw = percent(w, 25);
       int ih = percent(h, 14);
       int bx = percent(iw, 5);
       int by = percent(ih, 5);
       int bw = percent(iw, 90);
       int bh = percent(ih, 90);
       for(int i = 0; i < 5; ++i){
           for (int j = 0; j < 4; ++j){
               int cx = x + j * iw;
               int cy = y + i * ih;
               int cbx = cx + bx;
               int cby = cy + by;
               btns[i][j].setGeometry(cbx, cby, bw, bh);
           }
       }

}
void MainWindow::onPushButton() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    qDebug() << "Button clicked:" << button->text();

    if(button->text() == "AC"){
        qDebug() << "Clear button clicked";
        le->clear();
        num.clear();
        id.clear();
    }
    else if (button->text() == "="){
        qDebug() << "Equals button clicked";
        id.push(num.toDouble());
        num.clear();
        if (oper.contains(op)) {
            double result = oper[op](id.pop(), id.pop());
            qDebug() << "Performing calculation with operator" << op;
            le->setText(QString::number(result));
            num += (QString::number(result));
        } else {
            qDebug() << "Operator" << op << "not found in QMap";
        }
    }
    else if(oper.keys().contains(button->text())) {
        id.push(num.toDouble());
        num.clear();
        qDebug() << "Operator button clicked:" << button->text();
        op = button->text();
        le->setText(le->text() + button->text());
    } else {
        qDebug() << "Number or decimal point button clicked:" << button->text();
        num += button->text();
        le->setText(le->text() + button->text());
    }
}

MainWindow::~MainWindow()
{

}

