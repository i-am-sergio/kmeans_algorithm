#include "Node.hpp"
#include "KDTree.hpp"
#include <iostream>
#include <vector>
#include <random>

using namespace std;
using namespace kdt;
using Point2D = vector<double>;

template <int numClusters> // u clusters
class Kmeans {

    private:
        vector<Point2D> centroides;

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
    
        Kmeans(const vector<Point2D> & puntos) {
            obtenerCentroides(puntos);
        }

        void printCentroides() {
            for (int i=0; i<centroides.size(); i++) {
                cout << centroides[i] << endl;
            }
        }

        // void KMeans_BruteForce(vector<Point2D>& all_points){
        //     vector<vector<Point2D>> clusteres;
        //     for (int i=0; i<numClusters; i++) {
        //         clusteres.push_back({});
        //     }
        //     for (int i=0; i<all_points.size(); i++) {
        //         double minDistance = distanceL2(all_points[i], centroides[0]);
        //         int cluster = 0;
        //         for (int j=1; j<centroides.size(); j++) {
        //             double distance = distanceL2(all_points[i], centroides[j]);
        //             if (distance < minDistance) {
        //                 minDistance = distance;
        //                 cluster = j;
        //             }
        //         }
        //         clusteres[cluster].push_back(all_points[i]);
        //     }
        //     vector<Point2D> newCentroides = newCenters(clusteres);
        //     if (newCentroides != centroides) {
        //         centroides = newCentroides;
        //         KMeans_BruteForce();
        //     }
        // }

        // void Kmean_KDTree(vector<Point2D>& all_points) {
        //     KDTree<2> kdtree_centroides;
        //     for (auto &row : centroides)
        //         kdtree_centroides.insert(row);
        //     vector<vector<Point2D>> clusteres(numClusters);
        //     for (int i=0; i<all_points.size(); i++) {
        //         vector<Point2D> num = kdtree_centroides.searchKNN(all_points[i], 1);
        //         for (int j=0; j<centroides.size(); ++j) {
        //             if (num[0] == centroides[j]) {
        //                 clusteres[j].push_back(all_points[i]);
        //                 break;
        //             }
        //         }
        //     }
        //     vector<Point2D> newCentroides = newCenters(clusteres);
        //     if (newCentroides != centroides) {
        //         centroides = newCentroides;
        //         Kmean_KDTree();
        //     }
        // }

        // vector<Point2D> newCenters(vector<vector<Point2D>> clusteres) {
        //     vector<Point2D> newCentroides;
        //     for (int i=0; i<clusteres.size(); i++) {
        //         Point2D newCentroide = {0, 0};
        //         for (const auto &point : clusteres[i])
        //             newCentroide = newCentroide + point;
        //         int size = clusteres[i].size();
        //         if (size != 0)
        //             newCentroide = newCentroide / size;
        //         newCentroides.push_back(newCentroide);
        //     }
        //     return newCentroides;
        // }

};