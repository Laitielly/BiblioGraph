#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <string>

//#include "datafile.h"

namespace Ui {
class Propertieswindow;
}

class Propertieswindow : public QWidget
{
    Q_OBJECT

public:

    explicit Propertieswindow(QWidget *parent = nullptr);
    ~Propertieswindow();

signals:
    void firstwindow();
    void inputwindow();

public slots:
    void on_get_data_names();
private slots:
    void on_btn_Rename_clicked();

    void on_btn_Distance_clicked();

    void on_btn_PrintVertexDegree_clicked();

    void on_btn_PrintAdjacencyMatrix_clicked();

    void on_btn_PrintIncidenceMatrix_clicked();

    void on_btn_PrintSets_clicked();

    void on_btn_PrintAdjacencyList_clicked();

    void on_btn_IsUndirected_clicked();

    void on_btn_CheckLoops_clicked();

    void on_btn_VerticesNumber_clicked();

    void on_btn_EdgesNumber_clicked();

    void on_btn_WeakConnectivityComponents_clicked();

    void on_btn_StrongConnectivityComponents_clicked();

    void on_btn_back_clicked();

private:
    Ui::Propertieswindow *ui;
};

#endif // PROPERTIESWINDOW_H
