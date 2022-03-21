#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "datafile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //auto& datas=DataClass::instance();


    matrixwindow = new MatrixWindow();
    connect(matrixwindow, &MatrixWindow::firstWindow, this, &MainWindow::show);

    incidmatrix = new IncidMatrix();
    connect(incidmatrix,&IncidMatrix::firstWindow,this,&IncidMatrix::show);

    adj_lstwindow = new Adj_listWindow();
    connect(adj_lstwindow,&Adj_listWindow::firstWindow,this,&Adj_listWindow::show);

    multwindow = new MultRepresWindow();
    connect(multwindow,&MultRepresWindow::firstWindow,this,&MultRepresWindow::show);

    prwindow= new Propertieswindow();
    connect(prwindow,&Propertieswindow::firstwindow,this,&Propertieswindow::show);

    connect(this,&MainWindow::send_data_names,prwindow,&Propertieswindow::on_get_data_names);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_mainExit_clicked()
{
    this->close();
}


void MainWindow::on_btn_matrix_adjacency_clicked()
{
    matrixwindow->show();
    this->close();
}

void MainWindow::on_btn_matrix_incid_clicked()
{
    incidmatrix->show();
    this->close();
}

void MainWindow::on_btn_list_adjacency_clicked()
{
    adj_lstwindow->show();
    this->close();
}

void MainWindow::on_btn_multrepres_clicked()
{
    multwindow->show();
    this->close();
}

void MainWindow::on_btn_properties_clicked()
{
    prwindow->show();
    this->close();
    emit send_data_names();
}
