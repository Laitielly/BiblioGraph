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
    //data_matrix= new int*[ROW];
    Data_matrix = new int*[ROW_matrix];
    for(int i=0;i<ROW_matrix;i++)
    {
        //data_matrix[i]=new int[COLUMN];
        Data_matrix[i] = new int[COL_matrix];
    }

    QTableWidgetItem *item;
    for(int i=0;i<ROW_matrix;i++)
    {
        for(int j=0;j<COL_matrix;j++)
        {
            item = ui->table_incid->item(i,j);
           //qDebug()<< item->text();
           if(item==NULL)
           {
               //data_matrix[i][j]=0;
               Data_matrix[i][j]=0;
               qDebug() << Data_matrix[i][j];
           }
           else if(item->text().toInt()==(-1) ||
                   item->text().toInt()==(1)  ||
                   item->text().toInt()==(2)  ||
                   item->text().toInt()==(0)    )
           {
               //data_matrix[i][j]= (item->text().toInt());
               Data_matrix[i][j]= (item->text().toInt());
               qDebug() <<Data_matrix[i][j];
           }
           //Тут потом bool запрет на клик "Продолжить"
           else
           {
            qDebug() << "ERROR_1";
            QMessageBox::warning(this, "Внимание","Неверный ввод!\nИспользуйте только 1 -1 0 2.");
            return;
           }

        }
    }

    std::string * Columns = new std::string[COL_matrix];


    bool cont_yes = true;
    for (int i=0;i<COL_matrix;i++ )
    {
        cont_yes = false;
        int count_0=0;
        int count_1=0;
        int count_minus_1=0;
        int count_2=0;
        for (int j=0;j<ROW_matrix;j++ )
        {
            if(Data_matrix[j][i]==0) count_0++;
            if(Data_matrix[j][i]==1) count_1++;
            if(Data_matrix[j][i]==-1) count_minus_1++;
            if(Data_matrix[j][i]==2) count_2++;
            Columns[i]+=std::to_string(Data_matrix[j][i]);

        }
        qDebug() << QString::fromStdString(Columns[i]);
        // 1 and -1
        if(count_0==ROW_matrix-2 &&
           count_1==1     &&
           count_minus_1==1)
        {
            cont_yes=true;
        }
        // 1 and 1
        else if(count_0==ROW_matrix-2 &&
           count_1==2)
        {
            cont_yes=true;
        }
        else if(count_0==ROW_matrix-1 &&
                count_2==1)
        {
             cont_yes=true;
        }

        //Тут потом bool запрет на клик "Продолжить"
        if(cont_yes==false)
        {
            qDebug() <<"ERROR_2";
            QMessageBox::warning(this, "Внимание","Неверный ввод!\nИсправьте столбцы.");
            return;
        }
    }

     cont_yes = true;
    for (int i=0;i<COL_matrix;i++ )
    {
        for (int j=0;j<COL_matrix;j++ )
        {
            if(Columns[i]==Columns[j] && i!=j) cont_yes=false;
        }
    }
    if(cont_yes==false)
    {
        qDebug() <<"ERROR_3";
        QMessageBox::warning(this, "Внимание","Неверный ввод!\nОдинаковые столбцы.");
        return;
    }
    delete [] Columns;
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
//    Graph<std::string> a(MatrixType::INCIDENCE,matrix,vertices);
//    qDebug()<<QString::fromStdString(a.PrintIncidenceMatrix());
//    qDebug()<<QString::fromStdString(a.PrintSets());



    //добавление имен в combobox(всплывающий список в свойствах)
    this->close();
    pr_win->show();
    emit send_data_names();

}
