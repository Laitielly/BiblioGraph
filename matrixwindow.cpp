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
    //int ROW = ui->tableWidget->rowCount();
    ROW_matrix=ui->tableWidget->rowCount();
    count_names=ROW_matrix;
    //int COLUMN = ui->tableWidget->columnCount();
    COL_matrix=ui->tableWidget->columnCount();
    Data_matrix= new int*[ROW_matrix];
    //data_matrix= new int*[ROW];
    for(int i=0;i<ROW_matrix;i++)
    {
        //data_matrix[i]=new int[ROW];
        Data_matrix[i]=new int[COL_matrix];
    }

    //qDebug() << ROW_matrix<< '\n';
    QTableWidgetItem *item;
    for(int i=0;i<ROW_matrix;i++)
    {
        for(int j=0;j<COL_matrix;j++)
        {
            item = ui->tableWidget->item(i,j);
           //qDebug()<< item->text();
            if(item->text().toInt()!=0 && item->text().toInt()!=1 && item!=NULL)
            {
                qDebug() << "ERROR_INPUT_DATA";
                QMessageBox::warning(this, "Внимание","Неверный ввод!\n Используйте только 0 и 1");
                return;
            }
           if(item==NULL)
           {

               //data_matrix[i][j]=0;
               Data_matrix[i][j]=0;
           }
           else
           {

               //data_matrix[i][j]= (item->text().toInt());
               Data_matrix[i][j]= (item->text().toInt());
           }
           //qDebug() <<data_matrix[i][j];
        }
    }

    //data_names = new std::string[COLUMN];
    Data_names = new std::string[count_names];
    for(int i=0;i<count_names;i++)
    {
        item = ui->Table_names->item(i,0);
        if(item==NULL)
        {
            qDebug() << "ERROR_INPUT_NAMES";
            QMessageBox::warning(this, "Внимание","Неверный ввод!\n Пустая строка вершины");
            return;
        }
        else
        {
            //data_names[i]=(item->text().toStdString());
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

//    Graph<std::string> a(MatrixType::ADJACENCY,matrix,vertices);
//    qDebug()<<QString::fromStdString(a.PrintAdjacencyMatrix());


    pr_win->show();
    this->close();
    emit send_data_names();
}
