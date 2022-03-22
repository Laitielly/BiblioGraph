#ifndef INCIDMATRIX_H
#define INCIDMATRIX_H
#include <QWidget>
#include <QDebug>
#include <string>
#include <QMessageBox>
#include "propertieswindow.h"


namespace Ui {class IncidMatrix; }

class IncidMatrix : public QWidget
{
       Q_OBJECT
public:
    explicit IncidMatrix(QWidget *parent = 0);
    ~IncidMatrix();




private slots:
   void on_incid_val_points_valueChanged(int arg1);

   void on_incid_back_clicked();

   void on_incid_val_edges_valueChanged(int arg2);

   void on_incid_cont_clicked();

   void on_pushButton_clicked();

signals:
    void firstWindow();
    //void secondWindow();
    void send_data_names();
private:
    Ui::IncidMatrix *ui;
    Propertieswindow *pr_win;
    int ROW, COLUMN;
protected:
    int **data_matrix;
    std::string  *data_names;


};

#endif // INCIDMATRIX_H
