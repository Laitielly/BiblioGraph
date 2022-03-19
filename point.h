#ifndef GRAPH_POINT_H
#define GRAPH_POINT_H

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
    friend bool operator!= (const Point &p1, const Point &p2);
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
    return ((p1.a == p2.a) && (p1.b == p2.b));
}
bool operator!= (const Point &p1, const Point &p2)
{
    return (!(p1.a == p2.a) or !(p1.b == p2.b));
}

#endif //GRAPH_POINT_H