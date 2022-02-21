#include "graph.h"
#include <iostream>

class Point{
private:
    int a,b;
public:
    Point(){
        a=0;
        b=0;
    }
    Point(int a, int b){
        this->a = a;
        this->b = b;
    }
    friend std::ostream& operator<< (std::ostream &out, const Point &point);
    friend bool operator== (const Point &p1, const Point &p2);
    bool operator<(const Point& p) const
    {
        return this->a<p.a and this->b<p.b;
    }
};

std::ostream& operator<< (std::ostream &out, const Point &point)
{
    out << "(" << point.a <<", " << point.b <<")";
    return out;
}
bool operator== (const Point &p1, const Point &p2)
{
    return p1.a == p2.a && p1.b == p2.b;
}

int main() {
    Graph<Point>a(MatrixType::ADJACENCY, {
                  {1,0,1},
                  {0,0,0},
                  {1,1,1}
    }, {Point(1,2),Point(3,4),Point(5,6)});
    a.Complement();
    std::cout << a.PrintSets() << a.PrintAdjacencyList() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
    return 0;
}
