#pragma once
#include "includes/Node.hpp"
#include "includes/KDTree.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <ctime>
#include <iomanip>
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;
using Point2D = vector<double>;

class KMeans
{
public:
    void printVector(const vector<Point2D> &vec)
    {
        std::cout << "Vector Elements: ";
        for (const auto &element : vec)
            std::cout << element << "\n";
        std::cout << "\n";
    }

    void printVV(const std::vector<std::vector<Point2D>> &vectorOfVectors)
    {
        for (const auto &innerVector : vectorOfVectors)
        {
            for (const auto &element : innerVector)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }

    // obtener 3 centroides random
    std::vector<Point2D> obtenerTresPuntosAleatorios(const std::vector<Point2D> &puntos, int quantity)
    {
        std::vector<Point2D> all_centroides;
        if (puntos.size() < quantity || quantity < 1)
            return all_centroides;
        std::mt19937 gen(static_cast<long unsigned int>(12));
        std::uniform_int_distribution<int> distribution(0, puntos.size() - 1);
        for (int i = 0; i < quantity; ++i)
        {
            int indice = distribution(gen);
            while (std::find(all_centroides.begin(), all_centroides.end(), puntos[indice]) != all_centroides.end())
                indice = distribution(gen);
            all_centroides.push_back(puntos[indice]);
        }
        return all_centroides;
    }

    vector<Point2D> newCenters(vector<vector<Point2D>> clusteres)
    {
        vector<Point2D> newCentroides;
        for (int i = 0; i < clusteres.size(); i++)
        {
            Point2D newCentroide = {0, 0};
            for (const auto &point : clusteres[i])
                newCentroide = newCentroide + point;
            int size = clusteres[i].size();
            if (size != 0)
                newCentroide = newCentroide / size;
            newCentroides.push_back(newCentroide);
        }
        return newCentroides;
    }

    vector<vector<Point2D>>
    KMeans_def(const vector<Point2D> &all_centroides, vector<Point2D> &all_points)
    {
        kdt::KDTree<2> kdtree_centroides;
        for (auto &row : all_centroides)
            kdtree_centroides.insert(row);
        vector<vector<Point2D>> clusters(all_centroides.size());
        for (int i = 0; i < all_points.size(); i++)
        {
            vector<Point2D> num = kdtree_centroides.searchKNN(all_points[i], 1);
            for (int j = 0; j < all_centroides.size(); ++j)
            {
                if (num[0] == all_centroides[j])
                {
                    clusters[j].push_back(all_points[i]);
                    break;
                }
            }
        }
        // for (int i = 0; i < clusters.size(); ++i)
        //     std::cout << "cluster " << i + 1 << " => " << clusters[i].size() << std::endl;
        vector<Point2D> newCentroides = newCenters(clusters);
        // printVector(newCentroides);
        double distanceThreshold = 398.4;
        double distance = 0.0;
        for (int i = 0; i < all_centroides.size(); ++i)
            distance += EuclideanDistance(all_centroides[i], newCentroides[i]);
        if (distance < distanceThreshold)
        {
            // std::cout << "Algoritmo convergió. Distancia: " << distance << std::endl;
            return clusters;
        }
        //std::cout << "Algoritmo no convergió. Distancia: " << distance << std::endl;
        return KMeans_def(newCentroides, all_points);
    }

    void exportKmeansCSV(const string& filename,vector<Point2D> &all_points, vector<Point2D> &centroides){
        ofstream myfile;
        vector<vector<Point2D>> puntos = KMeans_def(centroides, all_points);
        myfile.open ("kmeans.csv");
        myfile << centroides.size() << "\n";
        for(vector<Point2D> p : puntos){
            myfile << p.size() << ",";
        }
        myfile<< "\n";
        for (int i = 0; i < centroides.size(); ++i)
            myfile << centroides[i][0] << "," << centroides[i][1] << "\n";
        for(vector<Point2D> p : puntos){
            for(Point2D p2 : p){
                myfile << p2[0] << "," << p2[1]<<"\n";
            }
            myfile <<"\n";
        }
        myfile.close();

    }
};