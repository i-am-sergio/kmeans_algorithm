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
        /*
         * La función "KNNBruteForce" implementa el enfoque de fuerza bruta para encontrar los k 
         * vecinos más cercanos (KNN) de un punto determinado en un espacio vectorial.
         * Params: el punto de consulta y el número de vecinos más cercanos a encontrar.
         * Return: un vector de vectores que contiene los k vecinos más cercanos.
        */
        vector<vector<double>> KNNBruteForce(vector<double> point, int k){
            multimap<double, vector<double>> distances; // distance , punto x y z
            for(int i=0; i < nodes.size(); i++){
                distances.emplace(distanceL2(point,nodes[i].point),nodes[i].point);
            }
            if (!distances.empty()) {
                auto firstElement = distances.begin();
                distances.erase(firstElement);
            }
            vector<vector<double>> knns;
            for(auto& d : distances){
                // cout<<d.first<<" "<<d.second<<endl;
                knns.push_back(d.second);
                if(knns.size() >= k)
                    break;
            }
            return knns;
        }

        /*
        * La función `KNNBruteForce2` es una implementación del enfoque de fuerza bruta para 
        * encontrar los k vecinos más cercanos (KNN) de un punto dado en un espacio vectorial.
        * Params: el punto de consulta y el número de vecinos más cercanos 
        * a encontrar.
        * Return: un vector de vectores que contiene los k vecinos más cercanos.
        */
        vector<vector<double>> KNNBruteForce2(const vector<double>& point, int k) {
            vector<pair<double, vector<double>>> distances;

            // Calcular distancias y almacenar en el vector de pares
            for (int i = 0; i < nodes.size(); i++) {
                distances.emplace_back(distanceL2(point, nodes[i].point), nodes[i].point);
            }

            // Ordenar el vector de pares por distancia
            sort(distances.begin(), distances.end());

            // Eliminar el primer elemento si es necesario
            if (!distances.empty()) {
                distances.erase(distances.begin());
            }

            // Extraer los k vecinos más cercanos
            vector<vector<double>> knns;
            for (int i = 0; i < min(k, static_cast<int>(distances.size())); i++) {
                knns.push_back(distances[i].second);
            }

            return knns;
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