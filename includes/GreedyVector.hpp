#pragma once
#include "Node.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

namespace grd {

template <int dimension>
class GreedyVector {
    private:
        vector<Node> nodes;

    public:
        GreedyVector(){}
        ~GreedyVector(){}

        void insert(const vector<double>& point){
            nodes.emplace_back(Node(point));
        }
        bool search(vector<double> point){
            for(auto& n : nodes)
                if(n.point == point)
                    return true;
            return false;
        }
        void print(){
            for(auto& node : nodes)
                cout << node.point << endl;
        }

        vector<vector<double>> KNNBruteForce3(const vector<double>& query_point, int k) const {
            // Verificar que haya nodos antes de realizar la búsqueda
            if (nodes.empty()) {
                cerr << "Error: No hay nodos para realizar la búsqueda KNN." << endl;
                return {};
            }

            // Calcular distancias y almacenarlas en un vector de pares (distancia, índice)
            vector<pair<double, double>> distances;
            for (double i = 0; i < nodes.size(); i++) {
                double distance = 0.0;
                for (int d = 0; d < dimension; d++) {
                    double diff = nodes[i].point[d] - query_point[d];
                    distance += diff * diff;
                }
                distances.emplace_back(sqrt(distance), i);
            }

            // Ordenar el vector de distancias por la distancia ascendente
            sort(distances.begin(), distances.end());

            // Recopilar los k vecinos más cercanos
            vector<vector<double>> k_nearest_neighbors;
            for (int i = 0; i < k && i < distances.size(); i++) {
                double index = distances[i].second;
                k_nearest_neighbors.push_back(nodes[index].point);
            }

            return k_nearest_neighbors;
        }

    protected:
        double distanceL2(const vector<double>& p1, const vector<double>& p2) {
            double distancia = 0.0;
            for (int i = 0; i < p1.size(); i++) {
                distancia += pow(p1[i] - p2[i], 2);
            }
            return sqrt(distancia);
        }
};

}
