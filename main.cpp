#include "includes/KDTree.hpp"
#include <iostream>
#include <vector>
#include <cmath>

int main(){

    kdt::KDTree<3> tree;

    tree.insert({1,2,3});

    cout<< boolalpha << tree.search({1,2,3}) << endl;

    cout << "Finished!\n";

    return 0;
}