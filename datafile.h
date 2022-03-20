#ifndef DATAFILE_H
#define DATAFILE_H

#include <string>
#include <vector>

extern std::string *Data_names;//массив имен вершин
extern int count_names;//количество  вершин

extern int **Data_matrix;//матрица ребер
extern std::string **Data_matrix_str;
extern int ROW_matrix;//кол-во строк
extern int COL_matrix;//кол-во столбцов

#endif // DATAFILE_H
