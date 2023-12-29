#include "Node.hpp"
#include "KDTree.hpp"
#include "GreedyVector.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace kdt;
using Point2D = vector<double>;

class Kmeans {

    private:
        int numClusters;
        vector<Point2D> centroides;
        const int maxIterations = 10;

    protected:

        Point2D getPointWithMinX(const vector<Point2D> & points) {
            Point2D minPoint = points[0];
            for (int i=1; i<points.size(); i++) {
                if (points[i][0] < minPoint[0])
                    minPoint = points[i];
            }
            return minPoint;
        }

        Point2D getPointWithMaxX(const vector<Point2D> & points) {
            Point2D maxPoint = points[0];
            for (int i=1; i<points.size(); i++) {
                if (points[i][0] > maxPoint[0])
                    maxPoint = points[i];
            }
            return maxPoint;
        }

        Point2D getPointWithMinY(const vector<Point2D> & points) {
            Point2D minPoint = points[0];
            for (int i=1; i<points.size(); i++) {
                if (points[i][1] < minPoint[1])
                    minPoint = points[i];
            }
            return minPoint;
        }

        Point2D getPointWithMaxY(const vector<Point2D> & points) {
            Point2D maxPoint = points[0];
            for (int i=1; i<points.size(); i++) {
                if (points[i][1] > maxPoint[1])
                    maxPoint = points[i];
            }
            return maxPoint;
        }

        // Funcion para generar un número aleatorio dentro de un rango [min, max]
        double generarNumeroAleatorio(double min, double max) {
            random_device rd;  // Dispositivo de generación de números aleatorios
            std::mt19937 gen(rd()); // Generador
            // Distribución uniforme dentro del rango [min, max]
            std::uniform_real_distribution<double> distribution(min, max);
            // Generar y devolver el número aleatorio
            return distribution(gen);
        }

        void obtenerCentroides(const vector<Point2D> & puntos) {
            vector<Point2D> _centroides;
            Point2D minPointX = getPointWithMinX(puntos);
            Point2D maxPointX = getPointWithMaxX(puntos);
            Point2D minPointY = getPointWithMinY(puntos);
            Point2D maxPointY = getPointWithMaxY(puntos); 
            
            for (int i=0; i<numClusters; i++) {
                double x = generarNumeroAleatorio(minPointX[0], maxPointX[0]);
                double y = generarNumeroAleatorio(minPointY[1], maxPointY[1]);
                _centroides.push_back({x, y});
            }
            this->centroides = _centroides;
        }

        double distanceL2(const vector<double>& p1, const vector<double>& p2) {
            double distancia = 0.0;
            for (int i = 0; i < p1.size(); i++) {
                distancia += pow(p1[i] - p2[i], 2);
            }
            return sqrt(distancia);
        }

    public:
    
        Kmeans(const vector<Point2D> & puntos, int numClusters) {
            this->numClusters = numClusters;
            obtenerCentroides(puntos);
        }

        void printCentroides() {
            for (int i=0; i<(int)centroides.size(); i++) {
                cout << centroides[i] << endl;
            }
        }

    void printVector(const vector<Point2D> &vec)
    {
        std::cout << "Vector Elements: ";
        for (const auto &element : vec)
            std::cout << element << "\n";
        std::cout << "\n";
    }

    //vector<Point2D>
    void newCenters(vector<vector<Point2D>> &clusteres)
    {
        vector<Point2D> newCentroides;
        for (int i = 0; i < (int)clusteres.size(); i++)
        {
            Point2D newCentroide = {0, 0};
            for (const auto &point : clusteres[i])
                newCentroide = newCentroide + point;
            int size = clusteres[i].size();
            if (size != 0)
                newCentroide = newCentroide / size;
            newCentroides.push_back(newCentroide);
        }
        this->centroides = newCentroides;
        //printCentroides();
        //cout<<"1 vez"<<endl;
    }

    vector<vector<Point2D>>
    KMeans_def(vector<Point2D> &all_points, int cont)
    {

        kdt::KDTree<2> kdtree_centroides;
        for (auto &row : centroides){
            kdtree_centroides.insert(row);
        }
        //kdtree_centroides.print();
        vector<vector<Point2D>> clusters(centroides.size());
        for (int i = 0; i < all_points.size(); i++){
            vector<Point2D> num = kdtree_centroides.searchKNN2(all_points[i], 1);
            for (int j = 0; j < centroides.size(); ++j) {
                if (num[0] == centroides[j])
                {
                    clusters[j].push_back(all_points[i]);
                    break;
                }
            }
        }
        // for (int i = 0; i < clusters.size(); ++i)
        //     std::cout << "cluster " << i + 1 << " => " << clusters[i].size() << std::endl;

        //vector<Point2D> auxCentroides = centroides;
        newCenters(clusters);

        //double distanceThreshold = 1;
        //double distance = 0.0;
        //for (int i = 0; i < centroides.size(); ++i){
        //    distance += EuclideanDistance(auxCentroides[i], this->centroides[i]);
        //}
        if (cont==maxIterations){
            //std::cout << "Algoritmo no convergió. Distancia: " << distance << std::endl;
            return clusters;
        }
        //if (distance < distanceThreshold)
        //{
        //    //std::cout << "Algoritmo convergió. Distancia: " << distance << std::endl;
        //    return clusters;
        //}

        //std::cout << "Algoritmo NO convergió. Distancia: " << distance << std::endl;
        //cout<<cont<<endl;
        cont++;
        return KMeans_def(all_points,cont);
    }
    vector<vector<Point2D>>
      KMeans_fb(vector<Point2D> &all_points, int cont)
      {
          grd::GreedyVector<2> fb_centroides;
          for (auto &row : centroides){
              fb_centroides.insert(row);
          }
          //kdtree_centroides.print();
          vector<vector<Point2D>> clusters(centroides.size());
          for (int i = 0; i < all_points.size(); i++){
              vector<Point2D> num = fb_centroides.KNNBruteForce3(all_points[i], 1);
              for (int j = 0; j < centroides.size(); ++j) {
                  if (num[0] == centroides[j])
                  {
                      clusters[j].push_back(all_points[i]);
                      break;
                  }
              }
          }
          //vector<Point2D> auxCentroides = centroides;
          newCenters(clusters);

          //double distanceThreshold = 1;
          //double distance = 0.0;
          //for (int i = 0; i < centroides.size(); ++i){
          //    distance += EuclideanDistance(auxCentroides[i], this->centroides[i]);
          //}
          if (cont==maxIterations){
              //std::cout << "Algoritmo no convergió. Distancia: " << distance << std::endl;
              return clusters;
          }
          //if (distance < distanceThreshold)
          //{
          //    //std::cout << "Algoritmo convergió. Distancia: " << distance << std::endl;
          //    return clusters;
          //}

          //std::cout << "Algoritmo NO convergió. Distancia: " << distance << std::endl;
          cont++;
          return KMeans_fb(all_points,cont);
      }

    void exportKmeansCSVkd(const string& filename,vector<Point2D> &all_points){
        ofstream myfile;
        vector<vector<Point2D>> puntos = KMeans_def(all_points,0);

        myfile.open (filename);
        myfile << centroides.size() << "\n";
        for(int i=0; i<puntos.size(); i++){
            myfile << puntos[i].size() << (i == puntos.size()-1 ? "\n" : ",");
        }
        for (int i = 0; i < centroides.size(); ++i)
            myfile << centroides[i][0] << "," << centroides[i][1] << "\n";
        for(vector<Point2D> p : puntos){
            for(Point2D p2 : p){
                myfile << p2[0] << "," << p2[1]<<"\n";
            }
        }
        myfile.close();
    }

    void exportKmeansCSVkd(const string& filename,vector<Point2D> &all_points, vector<double> &tiempoKd){
        ofstream myfile;
        auto start = chrono::high_resolution_clock::now();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tiempo;
        start = chrono::high_resolution_clock::now();
        vector<vector<Point2D>> puntos = KMeans_def(all_points,0);
        end = chrono::high_resolution_clock::now();
        tiempo = end - start;
        tiempoKd.push_back(tiempo.count());
        cout << "Tiempo de ejecucion kd: " << tiempo.count() << " milisegundos." << endl;

        myfile.open (filename);
        myfile << centroides.size() << "\n";
        for(int i=0; i<puntos.size(); i++){
            myfile << puntos[i].size() << (i == puntos.size()-1 ? "\n" : ",");
        }
        for (int i = 0; i < centroides.size(); ++i)
            myfile << centroides[i][0] << "," << centroides[i][1] << "\n";
        for(vector<Point2D> p : puntos){
            for(Point2D p2 : p){
                myfile << p2[0] << "," << p2[1]<<"\n";
            }
        }
        myfile.close();
    }

    void exportKmeansCSVfb(const string& filename,vector<Point2D> &all_points){
        ofstream myfile;
        vector<vector<Point2D>> puntos = KMeans_fb(all_points,0);

        myfile.open (filename);
        myfile << centroides.size() << "\n";
        for(int i=0; i<puntos.size(); i++){
            myfile << puntos[i].size() << (i == puntos.size()-1 ? "\n" : ",");
        }
        for (int i = 0; i < centroides.size(); ++i)
            myfile << centroides[i][0] << "," << centroides[i][1] << "\n";
        for(vector<Point2D> p : puntos){
            for(Point2D p2 : p){
                myfile << p2[0] << "," << p2[1]<<"\n";
            }
        }
        myfile.close();
    }
    
    void exportKmeansCSVfb(const string& filename,vector<Point2D> &all_points, vector<double> &tiempoFb){
        ofstream myfile;

        auto start = chrono::high_resolution_clock::now();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tiempo;
        start = chrono::high_resolution_clock::now();
        vector<vector<Point2D>> puntos = KMeans_fb(all_points,0);
        end = chrono::high_resolution_clock::now();
        tiempo = end - start;
        tiempoFb.push_back(tiempo.count());
        cout << "Tiempo de ejecucion fb: " << tiempo.count() << " milisegundos." << endl;

        myfile.open (filename);
        myfile << centroides.size() << "\n";
        for(int i=0; i<puntos.size(); i++){
            myfile << puntos[i].size() << (i == puntos.size()-1 ? "\n" : ",");
        }
        for (int i = 0; i < centroides.size(); ++i)
            myfile << centroides[i][0] << "," << centroides[i][1] << "\n";
        for(vector<Point2D> p : puntos){
            for(Point2D p2 : p){
                myfile << p2[0] << "," << p2[1]<<"\n";
            }
        }
        myfile.close();
    }

};
