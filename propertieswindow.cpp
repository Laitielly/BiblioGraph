#include "propertieswindow.h"
#include "ui_propertieswindow.h"
#include "GraphLibrary/graph.h"
#include "datafile.h"


Graph<std::string> a;

Propertieswindow::Propertieswindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Propertieswindow)
{
    ui->setupUi(this);




}

Propertieswindow::~Propertieswindow()
{
    delete ui;
}

//заполнение spinbox-ов данными
void Propertieswindow::on_get_data_names()
{
    if(Where==WhereAreFrom::ADJANCENCY_MATRIX){
        Graph<std::string> b(MatrixType::ADJACENCY, matrix, vertices);
        a=b;
    }else if(Where==WhereAreFrom::INCIDENCE_MATRIX){
        Graph<std::string> b(MatrixType::INCIDENCE, matrix, vertices);
        a=b;
    }else if(Where==WhereAreFrom::ADJACENCY_LIST){
        Graph<std::string> b(AdjacencyList::LIST, adjacencyList);
        a=b;
    }else if(Where==WhereAreFrom::SETS){
        Graph<std::string> b(vertices, edges);
        a=b;
    }


     qDebug()<<  count_names;
    for(int i=0;i<count_names;i++)
    {
            qDebug()<< "////";
            //заполнение spinbox-ов данными
            ui->comboBox_rename->addItem( QString::fromStdString(Data_names[i]));
            ui->comboBox_distance_1->addItem( QString::fromStdString(Data_names[i]));
            ui->comboBox_distance_2->addItem( QString::fromStdString(Data_names[i]));
            ui->comboBox_vertexdegree->addItem( QString::fromStdString(Data_names[i]));
            ui->comboBox_Eccentricity->addItem( QString::fromStdString(Data_names[i]));

    }

    ui->spinBox_SizeClique->setMinimum(1);
    ui->spinBox_SizeClique->setMaximum(count_names);

    ui->spinBox_FindCyclesSize->setMinimum(1);
    ui->spinBox_FindCyclesSize->setMaximum(count_names);

    ui->spinBox_IndependentSetSize->setMinimum(1);
    ui->spinBox_IndependentSetSize->setMaximum(count_names);
}

//нажатия кнопок проверки свойств

//ДАННЫЕ (ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ) КОТОРЫЕ НУЖНЫ ДЛЯ ФУНКЦИЙ СМ В DATAFILE.H

//заменяет имя вершины передаваемой первым параметром, на имя передаваемое вторым параметром
void Propertieswindow::on_btn_Rename_clicked()
{
    //проверка поля нового имени
    if(ui->lineEdit_rename->text()=="")
    {
        QMessageBox::warning(this,"Внимание", "Поле имени пустое!");
        return;
    }


    //параметры для функции RENAME
    std::string first_parametr, second_parametr;

    first_parametr= ui->comboBox_rename->currentText().toStdString();
    second_parametr= ui->lineEdit_rename->text().toStdString();

    bool allowRename = true;

    for(int i=0; i<count_names; ++i){
        if(Data_names[i]==second_parametr){
            allowRename = false;
        }
    }

    if(allowRename){
    for(int i=0;i<count_names;i++)
    {
        if(Data_names[i]==first_parametr)
        {
             qDebug()<< "Замена имени";
            Data_names[i]=second_parametr;
            ui->comboBox_rename->clear();
            ui->comboBox_distance_1->clear();
            ui->comboBox_distance_2->clear();
            ui->comboBox_vertexdegree->clear();
            ui->comboBox_Eccentricity->clear();
            ui->lineEdit_rename->clear();
            for(int i=0;i<count_names;i++)
            {
                ui->comboBox_rename->addItem( QString::fromStdString(Data_names[i]));
                ui->comboBox_distance_1->addItem( QString::fromStdString(Data_names[i]));
                ui->comboBox_distance_2->addItem( QString::fromStdString(Data_names[i]));
                ui->comboBox_vertexdegree->addItem( QString::fromStdString(Data_names[i]));
                ui->comboBox_Eccentricity->addItem( QString::fromStdString(Data_names[i]));
            }
        }
    }


    qDebug()<< "Вывод первого параметра: ";
    qDebug()<<  QString::fromStdString(first_parametr);
    qDebug()<< "Вывод второго параметра: ";
    qDebug()<<  QString::fromStdString(second_parametr);


        //тут вызов функции Rename:
        a.Rename(first_parametr, second_parametr);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText("Вершина успешно переименована.");
    }else{
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText("Вершина с таким названием уже существует!");
    }

}

//находит минимальное реберное расстояние от вершины,
//передаваемой первым параметром, до вершины, передаваемой вторым параметром
void Propertieswindow::on_btn_Distance_clicked()
{
    //параметры для функции DISTANCE
    std::string first_parametr, second_parametr;

    first_parametr=ui->comboBox_distance_1->currentText().toStdString();
    second_parametr=ui->comboBox_distance_2->currentText().toStdString();

    qDebug()<< "Вывод первого параметра: ";
    qDebug()<<  QString::fromStdString(first_parametr);
    qDebug()<< "Вывод второго параметра: ";
    qDebug()<<  QString::fromStdString(second_parametr);

    //тут вызов функции Distance:
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.Distance(first_parametr, second_parametr)));
}

//выводит степень передаваемой вершины
void Propertieswindow::on_btn_PrintVertexDegree_clicked()
{
     //параметры для функции PRINTVERTEXDEGREE
     std::string first_parametr;

     first_parametr=ui->comboBox_vertexdegree->currentText().toStdString();

     qDebug()<< "Вывод первого параметра: ";
     qDebug()<<  QString::fromStdString(first_parametr);

      //тут вызов функции PrintVertexDegree:
     ui->plainTextEdit->clear();
     ui->plainTextEdit->insertPlainText(QString::fromStdString(a.PrintVertexDegree(first_parametr)));
}

//выводит матрицу смежности графа
void Propertieswindow::on_btn_PrintAdjacencyMatrix_clicked()
{
    //тут вызов функции PrintAdjacencyMatrix
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.PrintAdjacencyMatrix()));
}

//выводит матрицу инцидентности графа
void Propertieswindow::on_btn_PrintIncidenceMatrix_clicked()
{
    //тут вызов функции PrintIncidenceMatrix
     ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.PrintIncidenceMatrix()));
}

//выводит множество вершин и ребер графа
void Propertieswindow::on_btn_PrintSets_clicked()
{
     //тут вызов функции PrintSets
      ui->plainTextEdit->clear();
     ui->plainTextEdit->insertPlainText(QString::fromStdString(a.PrintSets()));
}

//выводит список смежности
void Propertieswindow::on_btn_PrintAdjacencyList_clicked()
{
    //тут вызов функции PrintAdjacencyList
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.PrintAdjacencyList()));
}

//проверка графа на неориентированность
void Propertieswindow::on_btn_IsUndirected_clicked()
{
     //тут вызов функции IsUndirected
     ui->plainTextEdit->clear();
     ui->plainTextEdit->insertPlainText(QString::fromStdString(a.IsUndirected()));
}

// проверка графа на наличие петель
void Propertieswindow::on_btn_CheckLoops_clicked()
{
    //тут вызов функции CheckLoops
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.CheckLoops()));
}

//выводит информацию о количестве вершин
void Propertieswindow::on_btn_VerticesNumber_clicked()
{
    //тут вызов функции VerticesNumber
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.VerticesNumber()));
}

//выводит информацию о количество ребер
void Propertieswindow::on_btn_EdgesNumber_clicked()
{
    //тут вызов функции EdgesNumber
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.EdgesNumber()));
}

//выводит компоненты слабой связности графа
void Propertieswindow::on_btn_WeakConnectivityComponents_clicked()
{
    //тут вызов функции WeakConnectivityComponents
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.WeakConnectivityComponents()));
}

//выводит компоненты сильной связности графа
void Propertieswindow::on_btn_StrongConnectivityComponents_clicked()
{
    //тут вызов функции trongConnectivityComponents
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.StrongConnectivityComponents()));
}


void Propertieswindow::on_btn_MaxClique_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.MaxClique()));
}


void Propertieswindow::on_btn_SizeClique_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.SizeClique(ui->spinBox_SizeClique->value())));
}


void Propertieswindow::on_btn_FindCycles_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.FindCycles()));
}


void Propertieswindow::on_btn_FindCyclesSize_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.FindCyclesSize(ui->spinBox_FindCyclesSize->value())));
}


void Propertieswindow::on_btn_Eccentricity_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.Eccentricity(ui->comboBox_Eccentricity->currentText().toStdString())));
}


void Propertieswindow::on_btn_FindDiameter_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.FindDiameter()));
}


void Propertieswindow::on_btn_FindRadius_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.FindRadius()));
}


void Propertieswindow::on_btn_FindCentralVertices_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.FindCentralVertices()));
}


void Propertieswindow::on_btn_IsTree_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.IsTree()));
}


void Propertieswindow::on_btn_MaxIndependentSet_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.MaxIndependentSet()));
}


void Propertieswindow::on_btn_IndependentSetSize_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.IndependentSetSize(ui->spinBox_IndependentSetSize->value())));
}


void Propertieswindow::on_btn_IsBipartite_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.IsBipartite()));
}


void Propertieswindow::on_btn_OptimalColoring_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.OptimalColoring()));
}


void Propertieswindow::on_btn_IsEulerGraph_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.IsEulerGraph()));
}


void Propertieswindow::on_pushButton_20_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(QString::fromStdString(a.IsHamiltonGraph()));
}

void Propertieswindow::on_btn_back_clicked()
{

    ui->comboBox_rename->clear();
    ui->comboBox_distance_1->clear();
    ui->comboBox_distance_2->clear();
    ui->comboBox_vertexdegree->clear();
    ui->lineEdit_rename->clear();
    ui->plainTextEdit->clear();
    this->close();
    emit firstwindow();
    emit inputwindow();
}

void Propertieswindow::on_pushButton_2_clicked()
{
    this->close();
}
