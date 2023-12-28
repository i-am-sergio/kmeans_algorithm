#pragma once
#include <iostream>
#include <vector>
using namespace std;

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

ostream& operator<<(ostream& os, const vector<double>& point) {
    os << "(";
    for (int i=0; i<point.size(); i++)
        os << point[i] << ( i!=point.size()-1 ? "," : "");
    os << ")";
    return os;
}
