#include "includes/KDTree.hpp"
#include "includes/Kmeans.hpp"
#include "utils/Reader.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace rdr;
using namespace kdt;



int main(){
    using Point2D = vector<double>;
    CSVReader rdr("data2k.csv"); // file , numPoints
    vector<Point2D> points = rdr.readCSV(true, 2400);
    // for(int i=0; i<points.size(); i++){
    //     cout<<points[i]<<endl;
    // }
    cout << "Points readed: " << points.size() << endl;
    
    KDTree<2> kdtree;
    for (auto &row : points){
        kdtree.insert(row);
    }

    vector<Point2D> knns = kdtree.searchKNN2({0,0}, 1);
    for(int i=0; i<knns.size(); i++){
        cout<<knns[i]<<endl;
    }

    return 0;
}