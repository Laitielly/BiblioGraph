#include "datafile.h"

std::string *Data_names;
int count_names;

int **Data_matrix;
std::string **Data_matrix_str;
int ROW_matrix;
int COL_matrix;

std::vector<std::vector<int>> matrix; //матрицы числовые
std::vector<std::string> vertices; //названия вершин
std::vector<std::pair<std::string,std::string>> edges; //названия ребер
std::vector<std::pair<std::string,std::vector<std::string>>> adjacencyList; //список смежности
WhereAreFrom Where = WhereAreFrom::EMPTY;
//Graph<std::string> a;
