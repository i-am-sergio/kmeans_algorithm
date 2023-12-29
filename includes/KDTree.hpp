#pragma once
#include "Node.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
using namespace std;

namespace kdt {
    
    template <int dimension> // dimension
    class KDTree {
        private:
            Node * root;

        public:
            KDTree(){
                root = nullptr;
            }
            ~KDTree(){
                delete root; 
                root = nullptr;
            }
            void insert(vector<double> point){
                root = insertRecursivo(root, point);
            }
            bool search(vector<double> point){
                return searchRecursive(root, point);
            }
            void print(){
                printRecursive(root);
            }

            vector<vector<double>> searchKNN(vector<double> point, int k) {
                k = k+1;
                priority_queue<pair<double, Node*>> nearestNeighbors;
                KNNRecursive(root,point,k,nearestNeighbors,0);
                vector<vector<double>> kNeighbors;
                while(!nearestNeighbors.empty()){
                    kNeighbors.push_back(nearestNeighbors.top().second->point);
                    nearestNeighbors.pop();
                }
                if(!kNeighbors.empty()) kNeighbors.pop_back();
                return kNeighbors;
            }

            vector<vector<double>> searchKNN2(vector<double> point, int k) {
                // k = k+1;
                priority_queue<pair<double, Node*>> nearestNeighbors;
                KNNRecursive(root,point,k,nearestNeighbors,0);
                vector<vector<double>> result;
                result.push_back(nearestNeighbors.top().second->point);
                return result;
            }

        protected:
        
            Node * insertRecursivo(Node * current, vector<double> point, int depth = 0){
                if(current == nullptr){
                    return new Node(point);
                }
                
                int axis = depth % dimension;

                if (point[axis] < current->point[axis]) {
                    current->left = insertRecursivo(current->left, point, depth+1);
                } else {
                    current->right = insertRecursivo(current->right, point, depth+1);
                }
                return current;
            }

            bool searchRecursive(Node * node, vector<double> point, int depth = 0){
                if(node == nullptr){
                    return false;
                }
                if(node->point == point){
                    return true;
                }

                int axis = depth % dimension;

                if(point[axis] < node->point[axis]){
                    return searchRecursive(node->left, point, depth+1);
                } else {
                    return searchRecursive(node->right, point, depth+1);
                }
            }

            void printRecursive(Node *node, int depth = 0){
                if(node == nullptr){
                    return;
                }
                printRecursive(node->right, depth+1);
                for(int i = 0; i < depth; i++){
                    cout<<setw(6*depth);
                }
                cout<<node->point;
                cout<<"["<<depth<<"]"<<endl;// depth
                printRecursive(node->left, depth+1);
            }

            double distanceL2(const vector<double>& p1, const vector<double>& p2) {
                double distancia = 0.0;
                for (int i = 0; i < p1.size(); i++) {
                    distancia += pow(p1[i] - p2[i], 2);
                }
                return sqrt(distancia);
            }
            
            /*
            *`KNNRecursive` es una función recursiva que realiza una búsqueda de k vecinos más cercanos en un KDTree.
            * @param node: el nodo actual en el que se encuentra la recursión.
            * @param point: el punto de consulta.
            * @param k: el número de vecinos más cercanos a encontrar.
            * @param nearestNeighbors: una cola de prioridad que contiene los k vecinos más cercanos.
            * @param depth: la profundidad actual en la que se encuentra la recursión.
            * @return: void.
            */
            void KNNRecursive(Node* node, const vector<double>& point, int k, priority_queue<pair<double, Node*>>& nearestNeighbors, int depth = 0) {
                if (node == nullptr) {
                    return;
                }

                int axis = depth % point.size();
                double distance = distanceL2(point, node->point);

                if (nearestNeighbors.size() < k || distance < nearestNeighbors.top().first) {
                    if (nearestNeighbors.size() == k) {
                        nearestNeighbors.pop();
                    }
                    nearestNeighbors.push({distance, node});
                }

                if (point[axis] < node->point[axis]) {
                    KNNRecursive(node->left, point, k , nearestNeighbors, depth + 1);
                    if (nearestNeighbors.size() < k || abs(node->point[axis] - point[axis]) < nearestNeighbors.top().first) {
                        KNNRecursive(node->right, point, k, nearestNeighbors, depth + 1);
                    }
                } else {
                    KNNRecursive(node->right, point, k, nearestNeighbors, depth + 1);
                    if (nearestNeighbors.size() < k || abs(node->point[axis] - point[axis]) < nearestNeighbors.top().first) {
                        KNNRecursive(node->left, point, k, nearestNeighbors, depth + 1);
                    }
                }
            }

            /*
            * `KNNRecursive2` es una función recursiva que realiza una búsqueda de k vecinos más cercanos en un KDTree.
            * @param current: el nodo actual en el que se encuentra la recursión.
            * @param point: el punto de consulta.
            * @param k: el número de vecinos más cercanos a encontrar.
            * @param nearestNeighbors: una cola de prioridad que contiene los k vecinos más cercanos.
            * @param depth: la profundidad actual en la que se encuentra la recursión.
            * @return: void.
            */

            void KNNRecursive2(Node *current, const vector<double>& point, int k,
                        priority_queue<pair<double, Node*>>& nearestNeighbors, int depth = 0) {
                if (current == nullptr) {
                    return;
                }

                int axis = depth % dimension;
                double distance = distanceL2(current->point, point);

                nearestNeighbors.push({distance, current});

                if (nearestNeighbors.size() > k) {
                    nearestNeighbors.pop();
                }

                Node *first, *second;
                if (point[axis] < current->point[axis]) {
                    first = current->left;
                    second = current->right;
                } else {
                    first = current->right;
                    second = current->left;
                }

                KNNRecursive2(first, point, k, nearestNeighbors, depth + 1);

                if (fabs(point[axis] - current->point[axis]) <= nearestNeighbors.top().first) {
                    KNNRecursive2(second, point, k, nearestNeighbors, depth + 1);
                }
            }
    
    };

}
