#ifndef MULTREPRESWINDOW_H
#define MULTREPRESWINDOW_H

#include <QWidget>
#include <string>
#include <QDebug>
#include <QMessageBox>

#include "propertieswindow.h"

namespace Ui {
class MultRepresWindow;
}

class MultRepresWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MultRepresWindow(QWidget *parent = nullptr);
    ~MultRepresWindow();

signals:
    void firstWindow();  // Сигнал для первого окна на открытие
    void send_data_names();

private slots:
    void on_btn_back_clicked();

    void on_vertex_spin_valueChanged(int arg1);

    void on_edges_spin_valueChanged(int arg1);

    void on_btn_cont_clicked();

    void on_pushButton_clicked();

private:
    Ui::MultRepresWindow *ui;

    int ROW_NAMES;
    int ROW_EDGES;
    std::string **data_matrix;
    std::string  *data_names;

    Propertieswindow *pr_win;
};

#endif // MULTREPRESWINDOW_H
