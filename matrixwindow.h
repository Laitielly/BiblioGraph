#ifndef MATRIXWINDOW_H
#define MATRIXWINDOW_H

#include <QWidget>
//#include <vector>
#include <string>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include "dataclass.h"

#include "propertieswindow.h"

namespace Ui {class MatrixWindow; }


class MatrixWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MatrixWindow(QWidget *parent = 0);
    ~MatrixWindow();

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

    void send_data_names();

private slots:
    // Слот-обработчик нажатия кнопки

    void on_matrix_step_botom_clicked();


    void on_enter_clicked();

    void on_check_table_clicked();

    void on_pushButton_clicked();

private:
    Ui::MatrixWindow *ui;
    Propertieswindow *pr_win;
    int value_table;
    int **data_matrix;
    std::string  *data_names;

};
#endif // MATRIXWINDOW_H
