#include "includes/Kmeans.hpp"
#include "utils/Reader.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>

using namespace std;
using namespace kdt;
using namespace rdr;

int main(){
    using Point2D = vector<double>;
    CSVReader rdr("data2k.csv");
        auto start = chrono::high_resolution_clock::now();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tiempo;

    vector<int> k = {5, 15, 25, 50, 75};
    vector<int> n = {1000, 1150, 1300, 1450, 1600, 1750, 1900, 2050, 2200, 2400};
    ofstream myfile; 
    myfile.open ("ejerC.csv");
    for(int i = 0; i < k.size(); i++){
        vector<double> tiempoKd;
        vector<double> tiempoFb;
        for(int j = 0; j < n.size(); j++){
            vector<Point2D> points = rdr.readCSV(true,n[j]);
            cout << "Points readed: " << points.size() << endl;
            Kmeans kmeans(points, k[i]);
            //kmeans.printCentroides();
            kmeans.exportKmeansCSVkd("cluster1.csv", points, tiempoKd); 
            kmeans.exportKmeansCSVfb("cluster2.csv", points, tiempoFb); 
        }
        for(int j = 0; j < tiempoKd.size(); j++){
            myfile << tiempoKd[j] << (j == tiempoKd.size()-1 ? "\n" : ",");
        }
        for(int j = 0; j < tiempoFb.size(); j++){
            myfile << tiempoFb[j] << (j == tiempoFb.size()-1 ? "\n" : ",");
        }
    }
    myfile.close();








    //vector<Point2D> points = rdr.readCSV(true,2000);
    //cout << "Points readed: " << points.size() << endl;
    //Kmeans kmeans(points,5);
    ////kmeans.printCentroides();
    //kmeans.exportKmeansCSVkd("cluster1.csv", points);


    //kmeans.exportKmeansCSVfb("cluster2.csv", points);
    //cout << "Finished!\n";

    return 0;
}
