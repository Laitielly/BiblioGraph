#include "matrixwindow.h"
#include "ui_matrixwindow.h"
#include "datafile.h"
//#include "GraphLibrary/graph.h"

MatrixWindow::MatrixWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatrixWindow)
{
    ui->setupUi(this);
    value_table=0;
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(30);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(30);

    ui->Table_names->setRowCount(1);
    ui->Table_names->setColumnCount(1);
    ui->Table_names->setColumnWidth(1,250);
    ui->Table_names->horizontalHeader()->setDefaultSectionSize(142);
    ui->Table_names->verticalHeader()->setDefaultSectionSize(30);

    //ui->pushButton->setStyleSheet("QPushButton{border: 5px solid black;}");
    ui->pushButton->setStyleSheet("QPushButton{background: transparent;}");

    pr_win = new Propertieswindow;
    connect(pr_win,&Propertieswindow::inputwindow,this,&Propertieswindow::show);

    connect(this,&MatrixWindow::send_data_names,pr_win,&Propertieswindow::on_get_data_names);
}

MatrixWindow::~MatrixWindow()
{
    delete ui;
}

void MatrixWindow::on_matrix_step_botom_clicked()
{
    ui->Table_names->clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(1);
    ui->Table_names->setRowCount(1);
    ui->Table_names->setColumnCount(1);
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}



void MatrixWindow::on_enter_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->insertColumn(ui->tableWidget->columnCount());

    ui->Table_names->insertRow(ui->Table_names->columnCount());
}

void MatrixWindow::on_check_table_clicked()
{
    ROW_matrix=ui->tableWidget->rowCount();
    count_names=ROW_matrix;
    COL_matrix=ui->tableWidget->columnCount();
    Data_matrix.clear();
    Data_matrix.resize(ROW_matrix);
    //data_matrix= new int*[ROW];
    for(int i=0;i<ROW_matrix;i++)
    {
        Data_matrix[i].resize(COL_matrix);
    }
    QTableWidgetItem *item;
    for(int i=0;i<ROW_matrix;i++)
    {
        for(int j=0;j<COL_matrix;j++)
        {
            item = ui->tableWidget->item(i,j);

            if(item==NULL)
            {
                 Data_matrix[i][j]=0;
            }
            else
            {
                Data_matrix[i][j]= (item->text().toInt());

            }
        }
    }
    Data_names.clear();
    Data_names.resize(count_names);
    for(int i=0;i<count_names;i++)
    {
        item = ui->Table_names->item(i,0);
        if(item==NULL)
        {
            Data_names[i]="";
        }
        else
        {
            Data_names[i]=item->text().toStdString();
            qDebug()<< item->text();
        }
    }

    //Вызов функции передачи данных для преобразования их в вектор и вызыва конструктора Graph:

    //clear
    Where=WhereAreFrom::ADJANCENCY_MATRIX;
    matrix.clear();
    vertices.clear();
    edges.clear();
    adjacencyList.clear();
    //download from matrix to vector (for adjacency matrix)
    matrix.resize(count_names);
    for(int i=0; i<count_names; ++i){
        matrix[i].resize(count_names);
        for(int j=0; j<count_names; ++j){
            matrix[i][j]=Data_matrix[i][j];
        }
    }

    //download from matrix to vector (for names of verticies)
    vertices.resize(count_names);
    for(int i=0; i<count_names; ++i){
        vertices[i]=Data_names[i];
    }

    //Парсер проверки ввода
    //Проверка названий вершин
    int verticesCounter = matrix.size();
    if(vertices.size()==0){
        QMessageBox::warning(this, "Внимание","Не возможно создать граф без вершин.\n");
        return;
    }
        if (verticesCounter!=vertices.size()){
            QMessageBox::warning(this, "Внимание","Недостаточное количество вершин передано в функцию.\n");
            return;
        }
        for(int i=0; i<verticesCounter; ++i){
            if(vertices[i]==""){
                QMessageBox::warning(this, "Внимание","Вы не ввели названия вершинам.\n");
                return;
            }
            for(int j=0; j<verticesCounter; ++j){
                if (i!=j and vertices[i]==vertices[j]){
                    QMessageBox::warning(this, "Внимание","Названия некоторых вершин дублируются.\n");
                    return;
                }
            }
        }
        for (int i=0; i < verticesCounter; ++i){
                    for(int j=0; j < verticesCounter; ++j){
                        if (!(matrix[i][j] == 0 or matrix[i][j] == 1)){
                            QMessageBox::warning(this, "Внимание","Матрица смежности может содержать только числа 0 и 1.\n");
                            return;
                        }
                    }
                }

    pr_win->show();
    this->close();
    emit send_data_names();
}

void MatrixWindow::on_pushButton_clicked()
{
    //в matrixwindow.cpp:
    QMessageBox::warning(this,"Справка", "Для того, чтобы задать граф:\n-укажите названия всем вершинам\n-в матрице смежности поставьте в i строке j столбце:\n    -1, если из i-й вершины в j-ю вершину есть ребро\n    -0, иначе");
}
