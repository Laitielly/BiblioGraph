#ifndef DATACLASS_H
#define DATACLASS_H

#include <string>
#include "adj_listwindow.h"


class DataClass
{
public:
    static DataClass & instance()
    {
        static DataClass data_graph;
        return data_graph;
    }
    int **Data_matrix;
    std::string *Data_names;


private:
   DataClass();
    DataClass(DataClass const &);
    DataClass& operator=(DataClass const &);

};

#endif // DATACLASS_H
