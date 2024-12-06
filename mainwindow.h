#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "muParser.h"
struct Root
{
    bool valid;//verifica correcto funcionamiento
    double value;
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   public slots:
    void Graphic();
    double f(double x,mu::Parser &parser);
    void bisection();
    void Newton_Rapson();
    double df(double x);
  //  void Escritura();
    void Plot_Integral();
    void Integral();

private:
    Ui::MainWindow *ui;
    QVector<double>x,y,X2,Y2;
};
#endif // MAINWINDOW_H
