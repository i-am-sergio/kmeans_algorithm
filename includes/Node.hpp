#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using Point2D = vector<double>;


class Node {
    public:
        vector<double> point;
        Node * left;
        Node * right;

        Node(){}
        Node(const vector<double>& point){
            left = nullptr;
            right = nullptr;
            this->point = point;
        }
        ~Node(){}
};

double EuclideanDistance(const Point2D &p1, const Point2D &p2)
{
    if (p1.size() != p2.size())
        throw invalid_argument("Los puntos tienen dimensiones diferentes");
    double sum = 0;
    for (size_t i = 0; i < p1.size(); ++i)
        sum += pow(p1[i] - p2[i], 2);
    return sqrt(sum);
}
ostream& operator<<(ostream& os, const vector<double>& point) {
    os << "(";
    for (int i=0; i<point.size(); i++)
        os << point[i] << ( i!=point.size()-1 ? "," : "");
    os << ")";
    return os;
}

Point2D operator+(const Point2D &p1, const Point2D &p2)
{
    if (p1.size() != p2.size())
        throw invalid_argument("Los puntos tienen dimensiones diferentes");
    Point2D suma;
    for (size_t i = 0; i < p1.size(); ++i)
        suma.push_back(p1[i] + p2[i]);
    return suma;
}
Point2D operator/(const Point2D &point, int divisor)
{
    Point2D result;
    if (divisor != 0)
    {
        result.reserve(point.size());
        for (const auto &element : point)
            result.push_back(element / static_cast<double>(divisor));
    }
    else
        std::cerr << "Error: Division by zero" << std::endl;
    return result;
}
