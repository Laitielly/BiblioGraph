#include "propertieswindow.h"
#include "ui_propertieswindow.h"

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


     qDebug()<<  count_names;
    for(int i=0;i<count_names;i++)
    {
            qDebug()<< "////";
            //заполнение spinbox-ов данными
            ui->comboBox_rename->addItem( QString::fromStdString(Data_names[i]));
            ui->comboBox_distance_1->addItem( QString::fromStdString(Data_names[i]));
            ui->comboBox_distance_2->addItem( QString::fromStdString(Data_names[i]));
            ui->comboBox_vertexdegree->addItem( QString::fromStdString(Data_names[i]));

    }
}

//нажатия кнопок проверки свойств

//ДАННЫЕ (ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ) КОТОРЫЕ НУЖНЫ ДЛЯ ФУНКЦИЙ СМ В DATAFILE.H

//заменяет имя вершины передаваемой первым параметром, на имя передаваемое вторым параметром
void Propertieswindow::on_btn_Rename_clicked()
{
    //проверка поля нового имени
    if(ui->lineEdit_rename->text()==NULL)
    {
        QMessageBox::warning(this,"Внимание", "Поле имени пустое!");
        return;
    }


    //параметры для функции RENAME
    std::string first_parametr, second_parametr;

    first_parametr= ui->comboBox_rename->currentText().toStdString();
    second_parametr= ui->lineEdit_rename->text().toStdString();

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
            ui->lineEdit_rename->clear();
            for(int i=0;i<count_names;i++)
            {
                ui->comboBox_rename->addItem( QString::fromStdString(Data_names[i]));
                ui->comboBox_distance_1->addItem( QString::fromStdString(Data_names[i]));
                ui->comboBox_distance_2->addItem( QString::fromStdString(Data_names[i]));
                ui->comboBox_vertexdegree->addItem( QString::fromStdString(Data_names[i]));
            }
        }
    }


    qDebug()<< "Вывод первого параметра: ";
    qDebug()<<  QString::fromStdString(first_parametr);
    qDebug()<< "Вывод второго параметра: ";
    qDebug()<<  QString::fromStdString(second_parametr);

    //тут вызов функции Rename:
    //Rename(first_parametr, second_parametr);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText("Вершина успешно переименована!");

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
    //ui->plainTextEdit->insertPlainText(Distance());
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
     //ui->plainTextEdit->insertPlainText(PrintVertexDegree());
}

//выводит матрицу смежности графа
void Propertieswindow::on_btn_PrintAdjacencyMatrix_clicked()
{
    //тут вызов функции PrintAdjacencyMatrix
    ui->plainTextEdit->clear();
    //ui->plainTextEdit->insertPlainText(PrintAdjacencyMatrix());
}

//выводит матрицу инцидентности графа
void Propertieswindow::on_btn_PrintIncidenceMatrix_clicked()
{
    //тут вызов функции PrintIncidenceMatrix
     ui->plainTextEdit->clear();
    //ui->plainTextEdit->insertPlainText(PrintIncidenceMatrix());
}

//выводит множество вершин и ребер графа
void Propertieswindow::on_btn_PrintSets_clicked()
{
     //тут вызов функции PrintSets
      ui->plainTextEdit->clear();
     //ui->plainTextEdit->insertPlainText(PrintSets());
}

//выводит список смежности
void Propertieswindow::on_btn_PrintAdjacencyList_clicked()
{
    //тут вызов функции PrintAdjacencyList
    ui->plainTextEdit->clear();
    //ui->plainTextEdit->insertPlainText(PrintAdjacencyList());
}

//проверка графа на неориентированность
void Propertieswindow::on_btn_IsUndirected_clicked()
{
     //тут вызов функции IsUndirected
     ui->plainTextEdit->clear();
     //ui->plainTextEdit->insertPlainText(IsUndirected());
}

// проверка графа на наличие петель
void Propertieswindow::on_btn_CheckLoops_clicked()
{
    //тут вызов функции CheckLoops
    ui->plainTextEdit->clear();
    //ui->plainTextEdit->insertPlainText(CheckLoops());
}

//выводит информацию о количестве вершин
void Propertieswindow::on_btn_VerticesNumber_clicked()
{
    //тут вызов функции VerticesNumber
    ui->plainTextEdit->clear();
    //ui->plainTextEdit->insertPlainText(VerticesNumber());
}

//выводит информацию о количество ребер
void Propertieswindow::on_btn_EdgesNumber_clicked()
{
    //тут вызов функции EdgesNumber
    ui->plainTextEdit->clear();
    //ui->plainTextEdit->insertPlainText(EdgesNumber());
}

//выводит компоненты слабой связности графа
void Propertieswindow::on_btn_WeakConnectivityComponents_clicked()
{
    //тут вызов функции WeakConnectivityComponents
    ui->plainTextEdit->clear();
    //ui->plainTextEdit->insertPlainText(WeakConnectivityComponents());
}

//выводит компоненты сильной связности графа
void Propertieswindow::on_btn_StrongConnectivityComponents_clicked()
{
    //тут вызов функции trongConnectivityComponents
    ui->plainTextEdit->clear();
    //ui->plainTextEdit->insertPlainText(trongConnectivityComponents());
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
