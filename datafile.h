#ifndef DATAFILE_H
#define DATAFILE_H

#include <string>
#include <vector>
//#include "GraphLibrary/graph.h"

extern std::string *Data_names;//массив имен вершин
extern int count_names;//количество  вершин

extern int **Data_matrix;//матрица ребер
extern std::string **Data_matrix_str;
extern int ROW_matrix;//кол-во строк
extern int COL_matrix;//кол-во столбцов

extern std::vector<std::vector<int>> matrix; //матрицы числовые
extern std::vector<std::string> vertices; //названия вершин
extern std::vector<std::pair<std::string,std::string>> edges; //названия ребер
extern std::vector<std::pair<std::string,std::vector<std::string>>> adjacencyList; //список смежности

enum class WhereAreFrom{
  EMPTY,
  ADJANCENCY_MATRIX,
  INCIDENCE_MATRIX,
  ADJACENCY_LIST,
  SETS,
};

extern WhereAreFrom Where;
//extern Graph<std::string> a;

#endif // DATAFILE_H
