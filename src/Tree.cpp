#include "Tree.h"
#include <iostream>

Tree::Tree()
{
    root = nullptr;
}

Node* Tree::getRoot()
{
    return root;
}

// Einfügen eines Wertes in den Baum
void Tree::insert(double value)
{
    if (root == nullptr)
    {
        // Root setzen, wenn der Baum leer ist
        root = new Node(value);
    }
    else
    {
        // Rekursiver Aufruf zur Positionierung im Baum
        insert(value, root);
    }
}

void Tree::insert(double value, Node* leaf)
{
    // Einfügen nach rechts
    if (value > leaf->currentNode)
    {
        if (leaf->rightNode == nullptr)
        {
            leaf->rightNode = new Node(value);
        }
        else
        {
            // Rekursiver Aufruf wenn Knoten schon belegt ist
            insert(value, leaf->rightNode);
        }
    }
    // Einfügen nach links
    else if (value < leaf->currentNode)
    {
        if (leaf->leftNode == nullptr)
        {
            leaf->leftNode = new Node(value);
        }
        else
        {
            insert(value, leaf->leftNode);
        }
    }
    else
    {
        std::cout << "Duplicate Value, deleting it!" << std::endl;
    }
}

// Sucht einen einzelnen Wert und gibt den Pfad aus
Node* Tree::simpleSearch(double value, Node* leaf)
{
    if (leaf != nullptr)
    {
        path.push_back(leaf->currentNode);
        if (leaf->currentNode == value)
        {
            std::cout << value << " found ";
            for (int i = 0; i < path.size(); i++)
            {
                std::cout << path[i] << " ";
            }

            std::cout << std::endl;
            return leaf;
            std::cout << std::endl; // wird nie erreicht
        }
        else if (leaf->currentNode > value)
        {
            return simpleSearch(value, leaf->leftNode);
        }
        else
        {
            return simpleSearch(value, leaf->rightNode);
        }
    }
    else
    {
        std::cout << value << " not found!" << std::endl;
        return nullptr;
    }
}

// Prüft ob Teilbaum strukturell übereinstimmt
bool Tree::subTreeSearch(Node* subtree, Node* leaf)
{
    // Wenn beide leer sind → gleich
    if (subtree == nullptr)
    {
        return true;
    }
    // Einer ist leer, der andere nicht → nicht gleich
    else if (leaf == nullptr)
    {
        return false;
    }
    // Werte stimmen nicht überein → nicht gleich
    else if (subtree->currentNode != leaf->currentNode)
    {
        return false;
    }

    // Rekursiver Vergleich von linker und rechter Seite
    return subTreeSearch(subtree->leftNode, leaf->leftNode) &&
           subTreeSearch(subtree->rightNode, leaf->rightNode);
}

// Durchläuft jeden Knoten und berechnet Balance-Faktor
void Tree::checkAVL(Node* node, bool& isAVL)
{
    if (!node) return;

    checkAVL(node->leftNode, isAVL);
    checkAVL(node->rightNode, isAVL);

    int leftHeight = height(node->leftNode);
    int rightHeight = height(node->rightNode);
    int balance = rightHeight - leftHeight;

    std::cout << "bal(" << node->currentNode << ") = " << balance;
    if (abs(balance) > 1)
    {
        std::cout << " (AVL violation!)";
        isAVL = false;
    }
    std::cout << std::endl;
}

// Ermittelt min, max, sum und count für Statistik
void Tree::getStats(Node* node, double& minVal, double& maxVal, double& sum, int& count)
{
    if (!node) return;

    getStats(node->leftNode, minVal, maxVal, sum, count);
    minVal = std::min(minVal, node->currentNode);
    maxVal = std::max(maxVal, node->currentNode);
    sum += node->currentNode;
    count++;
    getStats(node->rightNode, minVal, maxVal, sum, count);
}

// Ermittelt Höhe eines Teilbaums zur Balance-Berechnung
int Tree::height(Node* node)
{
    if (!node) return 0;
    return 1 + std::max(height(node->leftNode), height(node->rightNode));
}
