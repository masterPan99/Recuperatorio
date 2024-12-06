#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "muParser.h"
#include <stdlib.h>
//using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Plotter,SIGNAL(clicked(bool)),this,SLOT(Graphic()));
    connect(ui->rootbtm_B,SIGNAL(clicked(bool)),this,SLOT(bisection()));
    connect(ui->AreaBtm,SIGNAL(clicked(bool)),this,SLOT(Plot_Integral()));
    connect(ui->rootbtm_NRM,SIGNAL(clicked(bool)),this,SLOT(Newton_Rapson()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Graphic()
{

    mu::Parser parser;
    ui->Graphic->addGraph();//Creo Grafica
    double xmin = ui->Xmin->text().toDouble();//TOMO VALORES DE QLINE Y LOS CONVIERTO A ENTEROS
    double xmax = ui->Xmax->text().toDouble();
    double dx   = ui->dx->text().toDouble();
    double N = (xmax - xmin)/ dx;//determino el Numero de puntos a usar
    x.resize(N);
    y.resize(N);
    qDebug()<<"N PPAL"<<N;
    for(int i=0;i<N;i++)// inicia en cero porque no tiene  nada que ver con los valores del eje x, es un vector adimencional
    {
        x[i] = xmin + double(i)*dx; //x[i] = x[i-1] + dx el anterior + dx (otra forma)
        y[i]=f(x[i],parser);
    }

    ui->Graphic->graph(0)->setData(x,y);
    ui->Graphic->xAxis->setRange(xmin,xmax);//seteo limites de graficacion
    ui->Graphic->rescaleAxes();
    ui->Graphic->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);//Hace zoom y permite desplazarte ene el grafico
    ui->Graphic->replot();//carga los datos
    qDebug()<<"Valor de x1"<<x[1];

}
/*
void MainWindow::Escritura()
{
    FILE *fichero = fopen("C:\\Users\\Ing. Gadiel Pardo\\Desktop\\Recuperatorio Info 2 2024\\RecuParcial2\\Data.txt","wb+");

    for(int i=0;i<N;i++)// inicia en cero porque no tiene  nada que ver con los valores del eje x, es un vector adimencional
    {
        x[i] = xmin + double(i)*dx; //x[i] = x[i-1] + dx el anterior + dx (otra forma)
        y[i]=f(x[i],parser);
        fprintf(fichero, "%f %f\n",x[i],y[i]);
    }

    fclose(fichero);
}*/



//FUNCION f(x)
double MainWindow::f(double x,mu::Parser &parser) //(double x, mu::Parser &parser) es referencia &
{
    parser.DefineVar(L"x",&x);
    parser.SetExpr(ui->Equation->text().toStdWString());
    double y = parser.Eval();
    return y;
}

void MainWindow::bisection()//decalrar ROOT como estructura
{
    mu::Parser parser;
    double x_left = ui->X1Root->text().toDouble();
    double x_right = ui->X2Root->text().toDouble();
    double umbral = 1e-6;//defino hasta donde busco la raiz
    //qDebug()<<x_left;
    //qDebug()<<x_right;
    Root root;
    double y_left = f(x_left,parser);
    double y_right = f(x_right,parser);

    if(y_left * y_right < 0)
    {
        //qDebug()<< "there is a root";
        while((x_right - x_left) > umbral) //mientras el intervalo sea grande, lo sigo achicando
        {
            //qDebug()<<"Im In";
           double x_middle = (x_left + x_right)/2.0;//si pusiera solo 2, donde es un entero, para poder hacer la operacion el programa me convierte los double a int y estaría mal, por eso uso 2.0
           double y_middle =f(x_middle,parser);
           if((y_left * y_middle) <0 )
              x_right = x_middle;
           else
              x_left = x_middle;
        }
        root.valid=true;
        root.value=(x_left + x_right)/2.0;
        //qDebug()<<"Root here"<<root.value;
    }
    else
    {
        qDebug()<< "there are no roots";
        root.valid=false;
    }
    ui->ShowRoot->setText(QString::number(root.value));
}

void MainWindow::Newton_Rapson()
{
    mu::Parser parser;
    double X1= ui->X1_NRM->text().toDouble();
    double umbral = 1e-6;
    double Xprox = X1;


    do
    {
        X1 = Xprox;
        double fx = f(X1,parser);
        double fdx = df(X1);

        if (fdx < 1e-6 && fdx > -1e-6)
        {
            qDebug() << "intervalo muy chico =" << X1;

        }

        Xprox = X1 - fx / fdx;


    } while (qAbs(Xprox - X1) > umbral); //verifico umbral

    qDebug() << "Raíz  en x =" << Xprox;
    ui->ShowRoot_NRM->setText(QString::number(Xprox));
}


double MainWindow::df(double x)
{
    mu::Parser parser;
    double dx = 1e-6;
    double dy = f(x+dx,parser) - f(x,parser);
    return dy/dx;
}


void MainWindow::Plot_Integral()
{
    mu::Parser parser;
    //----------------Prearea-----------------//
    double xmin = ui->X1Area->text().toDouble();//TOMO VALORES DE QLINE Y LOS CONVIERTO A DOBLES.
    double xmax = ui->X2Area->text().toDouble();
    double dx   = ui->dx_Area->text().toDouble();
    double N = (xmax - xmin)/ dx;//determino el Numero de puntos a usar
    //compute area
    double delta_x;
    double area_total = 0;
    X2.resize(N);
    Y2.resize(N);
    qDebug()<<N;
    double P_A;//base por altura por iteracion.
    for(int i=0; i<(N-1.0); i++)
    {
        delta_x= x[i+1]-x[i];// Base
        X2[i]=x[i];
        P_A=(delta_x * f(x[i],parser));//Base por altura
        Y2[i]=P_A;
        area_total = area_total + P_A;//tengo el error el modo de guardar la Integral.
    }
        Integral();
        //qDebug()<< "area total = "<< area_total;
        ui->ValueArea->setText(QString::number(area_total));
}

void MainWindow::Integral()
{
    ui->Graphic->addGraph();
    ui->Graphic->graph(1)->setData(X2,Y2);
    QPen pen;
    pen.setColor(Qt::red);
    ui->Graphic->graph(1)->setPen(pen);//cambio color
    ui->Graphic->replot();
}

