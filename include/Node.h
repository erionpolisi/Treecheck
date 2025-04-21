#ifndef NODE_H
#define NODE_H


//one Leaf of the tree
struct Node{
    double currentNode;
    Node* leftNode;
    Node* rightNode;

    Node(double value);
};

#endif // NODE_H
