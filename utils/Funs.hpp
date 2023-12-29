#include "../includes/Node.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Funs {

    using Point3D = vector<double>;

    public:
        void printVector(const vector<Point3D> &vec) {
            for (const auto &element : vec)
                cout << element << "\n";
            cout << "\n";
        }

};

