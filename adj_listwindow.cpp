#include "adj_listwindow.h"
#include "ui_adj_listwindow.h"
//#include "GraphLibrary/graph.h"
#include "datafile.h"

Adj_listWindow::Adj_listWindow( QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Adj_listWindow)
{
    ui->setupUi(this);

    ROW=0;
    COLUMN=0;

    ROW_matrix=0;
    COL_matrix=0;
    count_names=0;

    ui->table_Widget->horizontalHeader()->setDefaultSectionSize(30);
    ui->table_Widget->verticalHeader()->setDefaultSectionSize(30);

    ui->table_names->setColumnCount(1);
    ui->table_names->setHorizontalHeaderLabels(QStringList("Названия вершин: "));
    ui->table_names->horizontalHeader()->setDefaultSectionSize(115);

    pr_win= new Propertieswindow;
    connect(pr_win,&Propertieswindow::inputwindow,this,&Propertieswindow::show);
    connect(this,&Adj_listWindow::send_data_names,pr_win,&Propertieswindow::on_get_data_names);
}

Adj_listWindow::~Adj_listWindow()
{
    delete ui;
}

void Adj_listWindow::on_adj_lst_back_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}

int Adj_listWindow::factorial (int n)
{
int f=1,i;
for(i=2;i<=n;++i)
{
    f=f*i;
}
return f;
}

void Adj_listWindow::on_adj_lst_spin_valueChanged(int arg1)
{
    //ROW=arg1;
    ROW_matrix=arg1;
    ui->table_Widget->setRowCount(ROW_matrix);
    ui->table_names->setRowCount(ROW_matrix);

    COL_matrix=(factorial(ROW_matrix))/(2*factorial(ROW_matrix-2));
    ui->table_Widget->setColumnCount(COL_matrix);
}

void Adj_listWindow::on_adj_lst_cont_clicked()
{
    //массив тута
    Data_matrix_str= new std::string*[ROW_matrix];
    for(int i=0;i<ROW_matrix;i++)
    {
        Data_matrix_str[i]=new std::string[COL_matrix];
    }


    QTableWidgetItem *item;
    //заполнение массива тута
    for(int i=0;i<ROW_matrix;i++)
    {
        for(int j=0;j<COL_matrix;j++)
        {

            item = ui->table_Widget->item(i,j);
           //qDebug()<< item->text();

           if(item==NULL)
           {
               Data_matrix_str[i][j]="";//вот тута
               //qDebug() <<Data_matrix[i][j];
           }
           else
           {
                Data_matrix_str[i][j]= (item->text().toStdString());
                //qDebug() <<Data_matrix[i][j];
           }
           /*
           //проверка с прошлого файла(страницы)
           else if(item->text().toInt()==(-1) ||
                   item->text().toInt()==(1)  ||
                   item->text().toInt()==(2)  ||
                   item->text().toInt()==(0)    )
           {

               Data_matrix[i][j]= (item->text().toInt());//и вот тута
               qDebug() <<Data_matrix[i][j];
           }
           //Тут потом bool запрет на клик "Продолжить"
           else
           {
            qDebug() << "ERROR_1";
            QMessageBox::warning(this, "Внимание","Неверный ввод!\nИспользуйте только 1 -1 0 2.");
            return;
           }
            */

        }
    }
    //вот тута запись названий поинтов
    count_names=ROW_matrix;
    Data_names = new std::string[count_names];
    for(int i=0;i<count_names;i++)
    {
        item = ui->table_names->item(i,0);
        if(item==NULL) Data_names[i]=" ";
        else
        {
            Data_names[i]=(item->text().toStdString());
            qDebug()<< item->text();
        }
    }


    //Вызов функции передачи данных для преобразования их в вектор и вызыва конструктора Graph:
    Where=WhereAreFrom::ADJACENCY_LIST;
    matrix.clear();
    vertices.clear();
    edges.clear();
    adjacencyList.clear();
    //download from matrix to vector (for adjacency matrix)
    adjacencyList.resize(count_names);
    for(int i=0; i<count_names; ++i){
        adjacencyList[i].first = Data_names[i];
        for(int j=0; j<COL_matrix; ++j){
            if(Data_matrix_str[i][j]!=""){
                adjacencyList[i].second.push_back(Data_matrix_str[i][j]);
            }
        }
    }

//        Graph<std::string> a(AdjacencyList::LIST,adjacencyList);
//        qDebug()<<QString::fromStdString(a.PrintAdjacencyList());

    //открытие окна свойств
    this->close();
    pr_win->show();
    emit send_data_names();
}
