# Библиотека для работы с графами
## Подключение библиотеки
- Подключите библиотеку к файлу **CMakeList.txt**. Ниже пример подключения библиотеки к проекту с названием **ProjectName**.
```CMake
add_subdirectory(GraphLibrary)
target_link_libraries(ProjectName GraphLibrary)
```
- Подключите файл **graph.h** к тому файлу, в котором вы собираетесь использовать библиотеку. Пример:
```C++
#include "graph.h"
```
## Формат входных данных
Для того, чтобы создать граф с вершинами объектов определенного типа, явно укажите его.

Вершинами графа могут быть объекты любого класса с перегруженными операторами **<<, <, ==, !=**.

В примере ниже будет создан граф объектов типа **std::string**.
```C++
Graph<std::string>a(...);
```

В дальнейшем под вершинами будем понимать объекты типа, граф которого мы создали. Под ребрами будем понимать пары вершин.
### Матрица смежности
Для того, чтобы задать граф матрицей смежности - передайте в конструктор класса Graph:
- первым параметром идентификатор `MatrixType::ADJACENCY`
- вторым параметром матрицу смежности, определяемую следующими правилами: 
    - если ребро **(i, j)** содержится в графе, то в **i** строке **j** столбца ставится **1**
    - в противном случае ставится **0**
- третьим параметром вектор всех вершин

Пример входных данных:
```C++
Graph<std::string>a(MatrixType::ADJACENCY, {
            {0,1,1},
            {1,0,1},
            {0,1,0}
                                           },
{"a","b","c"});
```

### Матрица инцидентности:
Для того, чтобы задать граф матрицей инцидентности - передайте в конструктор класса Graph:
- первым параметром идентификатор `MatrixType::INCIDENCE`
- матрицу инцидентности, определяемую следующими правилами: 
    - каждый столбец определяет ребро
    - в случае ребра петли поставьте **2** вершине, его образующей
    - в случае неориентированого ребра поставьте **1** вершинам, её образующим
    - в случае ориентированного ребра поставьте **1** вершине из которой исходит ребро, **-1** вершине, в которую приходит ребро
- третьим параметром вектор всех вершин

Пример входных данных:
```C++
Graph<std::string>a(MatrixType::INCIDENCE, {
            { 1, 1, 0, 0},
            {-1, 0, 2, 1},
            { 0,-1, 0, 1}
                                           },
{"a","b","c"});
```
### Задание графа множествами вершин и ребер:
Для того, чтобы задать граф множествами вершин и ребер - передайте в конструктор класса Graph:
- первым параметром вектор вершин
- вторым параметром вектор ребер(вектор пар вершин)

Пример входных данных:
```C++
Graph<std::string>a({"a", "b", "c"},
                        {{"a", "b"}, {"a", "c"}, {"b", "b"}, {"b", "c"}, {"c", "b"}});
```
### Задание графа списком смежности
Для того, чтобы задать граф списком смежности - передайте в конструктор класса Graph:
- первым параметром идентификатор `AdjacencyList::LIST`
- вторым параметром вектор, состоящий из векторов, в которых первый параметр это вершина, а второй параметр это вектор, содержащий смежные вершины

Пример входных данных:
```C++
Graph<std::string>a(AdjacencyList::LIST,
                    {
                            {"a", {"b","c"}},
                            {"b", {"b","c"}},
                            {"c", {"b"}}
                    });
```
## Список функций библиотеки
- `PrintAdjacencyMatrix` - выводит матрицу смежности графа
- `PrintIncidenceMatrix` - выводит матрицу инцидентности графа
- `PrintSets` - выводит множество вершин и ребер графа
- `PrintAdjacencyList` - выводит список смежности
- `Rename` - заменяет имя вершины передаваемой первым параметром, на имя передаваемое вторым параметром. Не работает с константными экземплярами класса Graph.
- `IsUndirected` - проверка графа на неориентированность
- `CheckLoops` - проверка графа на наличие петель
- `VerticesNumber` - выводит информацию о количестве вершин
- `EdgesNumber` - выводит информацию о количество ребер
- `PrintVertexDegree` - выводит степень передаваемой вершины
- `Distance` - находит минимальное реберное расстояние от вершины, передаваемой первым параметром, до вершины, передаваемой вторым параметром
- `WeakConnectivityComponents` - выводит компоненты слабой связности графа
- `StrongConnectivityComponents` - выводит компоненты сильной связности графа
- `MaxClique` - находит в графе максимальную клику
- `SizeClique` - находит в графе все клики размера, переданного параметром
- `FindCycles` - проверяет граф на наличие циклов
- `FindCyclesSize` - находит в графе все циклы размера, переданного параметром
- `Eccentricity` - находит эксцентриситет вершины, переданной параметром
- `FindDiameter` - находит диаметр графа
- `FindRadius` - находит радиус графа
- `FindCentralVertices` - находит центральные вершины графа
- `IsTree` - проверяет является ли граф деревом
- `MaxIndependentSet` - находит максимальное независимое множество в графе
- `IndependentSetSize` - находит все независимые множества размера, переданного параметром
- `IsBipartite` - проверяет граф на двудольность
- `OptimalColoring` - находит оптимальную раскраску графа
- `IsEulerGraph` - проверяет граф на эйлеровость
- `IsHamiltonGraph` - проверяет граф на гамильтоновость