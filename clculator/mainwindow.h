#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void onPushButton();
    int percent (int val,  double p);
    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *event);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString op;
    QStack<double> id;



    static double percent (double val,  double p){
         return (p * val )/100;
    }


    static double sum(double a, double b) {
        return a + b;
    }

    static double sub(double a, double b) {
        return a - b;
    }

    static double mull(double a, double b) {
        return a * b;
    }

    static double division(double a, double b) {
        if(b == 0) {
            return -1;
        }
        return a / b;
    }

    QMap<QString, double(*)(double, double)> oper = {
        {"+", &sum},
        {"-", &sub},
        {"*", &mull},
        {"/", &division},
        {"%", &percent}

    };

private:
    QLabel *lbl = new QLabel();
    QPushButton **btns;
    QLineEdit *le;
};
#endif // MAINWINDOW_H
