#include "datafile.h"

std::vector<std::string> Data_names;
int count_names;

std::vector<std::vector<int>> Data_matrix;
std::vector<std::vector<std::string>> Data_matrix_str;
int ROW_matrix;
int COL_matrix;

std::vector<std::vector<int>> matrix; //матрицы числовые
std::vector<std::string> vertices; //названия вершин
std::vector<std::pair<std::string,std::string>> edges; //названия ребер
std::vector<std::pair<std::string,std::vector<std::string>>> adjacencyList; //список смежности
WhereAreFrom Where = WhereAreFrom::EMPTY;
//Graph<std::string> a;
