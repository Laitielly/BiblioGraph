#ifndef ADJ_LISTWINDOW_H
#define ADJ_LISTWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include "propertieswindow.h"

namespace Ui {
class Adj_listWindow;
}

class Adj_listWindow : public QWidget
{
    Q_OBJECT

public:
    explicit Adj_listWindow(QWidget *parent = nullptr);
    ~Adj_listWindow();
signals:
    void firstWindow();  // Сигнал для первого окна на открытие
    void send_data_names();
private:
    int factorial (int n);

private slots:
    void on_adj_lst_back_clicked();

    void on_adj_lst_spin_valueChanged(int arg1);

    void on_adj_lst_cont_clicked();

    void on_pushButton_clicked();

private:
    Ui::Adj_listWindow *ui;
    Propertieswindow *pr_win;
    int ROW, COLUMN;
    int **data_matrix;
    std::string  *data_names;

};

#endif // ADJ_LISTWINDOW_H
