#include "multrepreswindow.h"
#include "ui_multrepreswindow.h"
//#include "GraphLibrary/graph.h"
#include "datafile.h"

MultRepresWindow::MultRepresWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultRepresWindow)
{
    ui->setupUi(this);

    ROW_NAMES=0;
    ROW_EDGES=0;

    ROW_matrix=0;
    COL_matrix=0;
    count_names=0;

    ui->table_Widget->horizontalHeader()->setDefaultSectionSize(80);
    ui->table_Widget->verticalHeader()->setDefaultSectionSize(30);
    ui->table_Widget->setColumnCount(2);

    ui->table_names->setColumnCount(1);
    ui->table_names->setHorizontalHeaderLabels(QStringList("Названия вершин: "));
    ui->table_names->horizontalHeader()->setDefaultSectionSize(115);

    pr_win = new Propertieswindow;
    connect(pr_win,&Propertieswindow::inputwindow,this,&Propertieswindow::show);
    connect(this,&MultRepresWindow::send_data_names,pr_win,&Propertieswindow::on_get_data_names);
}

MultRepresWindow::~MultRepresWindow()
{
    delete ui;
}

void MultRepresWindow::on_btn_back_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}

void MultRepresWindow::on_vertex_spin_valueChanged(int arg1)
{
    //ROW_NAMES=arg1;
    count_names=arg1;
    ui->table_names->setRowCount(count_names);
}

void MultRepresWindow::on_edges_spin_valueChanged(int arg1)
{
    //ROW_EDGES=arg1;
    ROW_matrix=arg1;
     ui->table_Widget->setRowCount(ROW_matrix);
}

void MultRepresWindow::on_btn_cont_clicked()
{
    Data_matrix_str= new std::string*[ROW_matrix];
    for(int i=0;i<ROW_matrix;i++)
    {
        Data_matrix_str[i]=new std::string[2];
    }

    QTableWidgetItem *item;
    //заполнение массива тута
    for(int i=0;i<ROW_matrix;i++)
    {
        for(int j=0;j<2;j++)
        {
            item = ui->table_Widget->item(i,j);
           if(item==NULL)
           {
//               qDebug() << "ERROR_1";
//               QMessageBox::warning(this, "Внимание","Неверный ввод!\nПустых полей не должно быть");
//               return;
               Data_matrix_str[i][j]="";
           }
           //тут неоходима полноценная проверка пар
           else
           {
               Data_matrix_str[i][j]= (item->text().toStdString());//и вот тута
               qDebug() <<QString::fromStdString(Data_matrix_str[i][j]);
           }

        }
    }

    Data_names = new std::string[count_names];
    for(int i=0;i<count_names;i++)
    {
        item = ui->table_names->item(i,0);
        if(item==NULL)
        {
//            qDebug() << "ERROR_1";
//            QMessageBox::warning(this, "Внимание","Неверный ввод!\nПустых полей не должно быть");
//            return;
            Data_names[i]="";
        }
        else
        {
            Data_names[i]=(item->text().toStdString());
            qDebug()<< item->text();
        }
    }

    //Вызов функции передачи данных для преобразования их в вектор и вызыва конструктора Graph:
    Where=WhereAreFrom::SETS;
    matrix.clear();
    vertices.clear();
    edges.clear();
    adjacencyList.clear();
    //download from matrix to vector (for adjacency matrix)
    vertices.resize(count_names);
    for(int i=0; i<count_names; ++i){
        vertices[i]=Data_names[i];
    }
    edges.resize(ROW_matrix);
    for(int i=0; i<ROW_matrix; ++i){
        edges[i].first=Data_matrix_str[i][0];
        edges[i].second=Data_matrix_str[i][1];
    }
//            Graph<std::string> a(vertices, edges);
//            qDebug()<<QString::fromStdString(a.PrintSets());
    //Проверка корректности ввода
    int edgesCounter = edges.size(), verticesCounter=vertices.size();
    if(vertices.size()==0){
        QMessageBox::warning(this, "Внимание","Не возможно создать граф без вершин.\n");
        return;
    }
    for(int i=0; i<verticesCounter; ++i){
       if(vertices[i]==""){
           QMessageBox::warning(this, "Внимание","Не всем вершинам присвоены названия.\n");
           return;
       }
    }
    for(int i=0; i<edgesCounter; ++i){
        if(edges[i].first=="" or edges[i].second==""){
            QMessageBox::warning(this, "Внимание","Не у всех ребер определены вершины их образующие.\n");
            return;
        }
    }
        for(int i=0; i<verticesCounter; ++i){
            for(int j=0; j<verticesCounter; ++j){
                if (i!=j and vertices[i]==vertices[j]){
//                    throw std::runtime_error("Some vertex is duplicated!");
                    QMessageBox::warning(this, "Внимание","Некоторые вершины дублируются.\n");
                    return;
                }
            }
        }

        for(int i=0; i<edgesCounter; ++i){
            std::pair<bool,bool> check;
            for(int j=0; j<verticesCounter; ++j){
                if (vertices[j]==edges[i].first){
                    check.first=true;
                }
                if (vertices[j]==edges[i].second){
                    check.second=true;
                }
            }
            if(!check.first or !check.second){
//                throw std::runtime_error("Some edge contains a non-existent vertex!");
                QMessageBox::warning(this, "Внимание","Некоторые ребра содержат несуществующие вершины.\n");
                return;
            }
            for(int j=0; j<edgesCounter; ++j){
                if (i!=j and edges[i]==edges[j]){
//                    throw std::runtime_error("Some edge is duplicated!");
                    QMessageBox::warning(this, "Внимание","Некоторые ребра дублируются.\n");
                    return;
                }
            }
        }

    pr_win->show();
    this->close();
    emit send_data_names();
}
