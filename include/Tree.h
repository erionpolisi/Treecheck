#ifndef TREE_H
#define TREE_H

#include <vector>
#include "Node.h"

class Tree {
    private:
        Node* root;
        std::vector<double> path;
    public:
        Tree();
        Node* getRoot();
        void insert(double value);
        void insert(double value, Node* leaf);
        Node* simpleSearch(double value, Node* leaf);
        bool subTreeSearch(Node* subtree, Node* leaf);

        void checkAVL(Node* node, bool& isAVL);
        int height(Node* node);
        void getStats(Node* node, double& minVal, double& maxVal, double& sum, int& count);


};

#endif // TREE_H
