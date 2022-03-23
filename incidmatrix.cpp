#include "incidmatrix.h"
#include "ui_incidmatrix.h"
//#include "GraphLibrary/graph.h"
#include "datafile.h"


IncidMatrix::IncidMatrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncidMatrix)
{
    ui->setupUi(this);

    ROW=0;
    COLUMN=0;

    ROW_matrix=0;
    COL_matrix=0;
    count_names=0;

    ui->table_incid->horizontalHeader()->setDefaultSectionSize(30);
    ui->table_incid->verticalHeader()->setDefaultSectionSize(30);

      ui->table_names->setColumnCount(1);
    ui->table_names->setHorizontalHeaderLabels(QStringList("Названия вершин: "));
      ui->table_names->horizontalHeader()->setDefaultSectionSize(115);
    pr_win=new Propertieswindow;
    connect(pr_win,&Propertieswindow::inputwindow,this,&Propertieswindow::show);
    connect(this,&IncidMatrix::send_data_names,pr_win,&Propertieswindow::on_get_data_names);

     ui->pushButton->setStyleSheet("QPushButton{background: transparent;}");
}

IncidMatrix::~IncidMatrix()
{
    delete ui;
}

void IncidMatrix::on_incid_val_points_valueChanged(int arg1)
{
    //ROW=arg1;
    ROW_matrix=arg1;
    ui->table_incid->setRowCount(ROW_matrix);

    ui->table_names->setRowCount(ROW_matrix);
}

void IncidMatrix::on_incid_back_clicked()
{
    ui->incid_val_points->clear();
    ui->incid_val_edges->clear();
    ui->table_names->clear();
    ui->table_incid->clear();
    ui->table_incid->setRowCount(1);
    ui->table_incid->setColumnCount(1);
    ui->table_names->setRowCount(1);
    ui->table_names->setColumnCount(1);
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}

void IncidMatrix::on_incid_val_edges_valueChanged(int arg2)
{
    //COLUMN=arg2;
    COL_matrix=arg2;
    ui->table_incid->setColumnCount(COL_matrix);
}

void IncidMatrix::on_incid_cont_clicked()
{

    Data_matrix.clear();
    Data_matrix.resize(ROW_matrix);
    for(int i=0;i<ROW_matrix;i++)
    {
        Data_matrix[i].resize(COL_matrix);
    }

    QTableWidgetItem *item;
    for(int i=0;i<ROW_matrix;i++)
    {
        for(int j=0;j<COL_matrix;j++)
        {
            item = ui->table_incid->item(i,j);
           if(item==NULL)
           {
               Data_matrix[i][j]=0;
               qDebug() << Data_matrix[i][j];
           }
           else
           {
               Data_matrix[i][j]= (item->text().toInt());
               qDebug() <<Data_matrix[i][j];
           }
        }
    }

    count_names=ROW_matrix;
    Data_names.resize(count_names);
    for(int i=0;i<count_names;i++)
    {
        item = ui->table_names->item(i,0);
        if(item==NULL) {
            Data_names[i]="";
        }
        else
        {
            Data_names[i]=(item->text().toStdString());
            qDebug()<< item->text();
        }
    }
    //Вызов функции передачи данных для преобразования их в вектор и вызыва конструктора Graph:
    Where=WhereAreFrom::INCIDENCE_MATRIX;
    matrix.clear();
    vertices.clear();
    edges.clear();
    adjacencyList.clear();
    //download from matrix to vector (for adjacency matrix)
    matrix.resize(count_names);
    for(int i=0; i<count_names; ++i){
        matrix[i].resize(COL_matrix);
        for(int j=0; j<COL_matrix; ++j){
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

        //то что ведет к исключениям
        int edgesCounter = matrix[0].size();
        std::vector<std::vector<int>> m_adjacency_matrix;
                for(int i=0; i < verticesCounter; ++i){
                    for(int j=0; j < edgesCounter; ++j){
                        if (!(matrix[i][j] == 0 or matrix[i][j] == 1 or matrix[i][j] == -1 or matrix[i][j]==2)){
                            QMessageBox::warning(this, "Внимание","Матрица инцидентности может содержать только числа -1, 0, 1, 2.\n");
                            return;
                        }
                    }
                }
                m_adjacency_matrix.resize(verticesCounter);
                for(int i=0; i < verticesCounter; ++i){
                    m_adjacency_matrix[i].resize(verticesCounter);
                }
                for(int j=0; j < edgesCounter; ++j){
                    int counterMinus1=0,counter1=0, counter2=0;
                    std::pair<int,int> index;
                    bool find=false;
                    for (int i=0; i < verticesCounter; ++i){
                        if (matrix[i][j]==1){
                            ++counter1;
                            if (!find){
                                index.first=i;
                                find = true;
                            }else {
                                index.second=i;
                            }
                        }
                        if (matrix[i][j]==-1){
                            ++counterMinus1;
                            index.second=i;
                        }
                        if (matrix[i][j]==2){
                            ++counter2;
                            index.first=i;
                            index.second=i;
                        }
                    }
                    bool loop = (counter2==1) and (!counterMinus1) and (!counter1);
                    bool oriented = (!counter2) and (counter1==1) and (counterMinus1==1);
                    bool undirected = (!counter2) and (!counterMinus1) and (counter1==2);
                    if (loop and !oriented and !undirected){
                        m_adjacency_matrix[index.first][index.first]=1;
                    }else if(!loop and oriented and !undirected){
                        if (m_adjacency_matrix[index.first][index.second] or m_adjacency_matrix[index.second][index.first]){
//                            throw std::runtime_error("A double edge assignment in the incidence matrix is found.");
                            QMessageBox::warning(this, "Внимание","Дублируется объявление ребра.\n");
                            return;
                        }
                        m_adjacency_matrix[index.first][index.second]=1;
                    }else if(!loop and !oriented and undirected){
                        if (m_adjacency_matrix[index.first][index.second] or m_adjacency_matrix[index.second][index.first]){
//                            throw std::runtime_error("A double edge assignment in the incidence matrix is found.");
                            QMessageBox::warning(this, "Внимание","Дублируется объявление ребра.\n");
                            return;
                        }
                        m_adjacency_matrix[index.first][index.second]=1;
                        m_adjacency_matrix[index.second][index.first]=1;
                    }else{
//                        throw std::runtime_error("The incidence matrix is incorrectly set.");
                        QMessageBox::warning(this, "Внимание","Матрица инцидентности задана некорректно.\n");
                        return;
                    }
                }


    //добавление имен в combobox(всплывающий список в свойствах)
    this->close();
    pr_win->show();
    emit send_data_names();

}

void IncidMatrix::on_pushButton_clicked()
{
    //в incidmatrix.cpp:
    QMessageBox::warning(this, "Справка","Для того, чтобы задать граф:\n-укажите названия всем вершинам\n-каждый столбец матрицы инцидентности определяет ребро по правилам:\n    -если между i-ой и j-ой вершинами есть неориентированное ребро,\n         поставьте в i-й и j-й строке 1\n    -если из i-ой вершины в  j-ю вершинами есть ориентированное ребро,\n         поставьте в i-й строке 1, в j-й строке -1\n    -если у i-й вершины есть петля, поставьте в i-й строке 2\n    -остальные строки в столбце заполните 0\n-дублирование ребер запрещается");
}
