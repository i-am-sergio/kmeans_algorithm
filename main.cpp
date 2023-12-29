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

    
    Kmeans<75> kmeans(points);
    kmeans.printCentroides();

    //vector<vector<Point2D>> clusters = kmeans.KMeans_def(points);
    kmeans.exportKmeansCSVkd("cluster1.csv", points);
    kmeans.exportKmeansCSVfb("cluster2.csv", points);

    // KMeans kmeans;
    // vector<Point2D> centroides = kmeans.obtenerTresPuntosAleatorios(points, 3);
    //vector<vector<Point2D>> clusters = kmeans.KMeans_def(centroides, points);
    // kmeans.exportKmeansCSV("data.csv", points, centroides);


    cout << "Finished!\n";

    return 0;
}
