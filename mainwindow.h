#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "matrixwindow.h"
#include "incidmatrix.h"
#include "adj_listwindow.h"
#include "multrepreswindow.h"
#include "propertieswindow.h"

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void send_data_names();

private slots:
    void on_mainExit_clicked();

    void on_btn_matrix_adjacency_clicked();

    void on_btn_matrix_incid_clicked();

    void on_btn_list_adjacency_clicked();

    void on_btn_multrepres_clicked();

    void on_btn_properties_clicked();

private:
    Ui::MainWindow *ui;

    MatrixWindow *matrixwindow;
    IncidMatrix *incidmatrix;
    Adj_listWindow *adj_lstwindow;
    MultRepresWindow *multwindow;
    Propertieswindow *prwindow;
};
#endif // MAINWINDOW_H
