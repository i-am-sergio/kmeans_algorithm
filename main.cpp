#include "includes/KDTree.hpp"
#include "includes/Kmeans.hpp"
#include "utils/Reader.hpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace kdt;
using namespace rdr;

int main(){
    using Point2D = vector<double>;

    CSVReader rdr("data2k.csv");
    vector<Point2D> points = rdr.readCSV(true);
    cout << "Points readed: " << points.size() << endl;

    KDTree<2> tree;
    
    Kmeans<6> kmeans(points);
    kmeans.printCentroides();

    // cout<< boolalpha << tree.search({1,2}) << endl;
    cout << "Finished!\n";

    return 0;
}