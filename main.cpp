#include <iostream>
#include <fstream>
#include <string>
#include "Tree.h"

using namespace std;

int flag = 0;

int main(int argc, char* argv[])
{
    switch (argc)
    {
        case 2:
        {
            cout << "Starte Treecheck..." << endl;
            string filename = argv[1];
            ifstream file(filename);

            // Fehlerbehandlung beim Öffnen der Datei
            if (!file.is_open())
            {
                cerr << "Konnte Datei nicht öffnen: " << filename << endl;
                return 1;
            }

            Tree T;
            int value;
            while (file >> value)
            {
                T.insert(value);
            }

            // AVL-Bedingung überprüfen
            bool isAVL = true;
            T.checkAVL(T.getRoot(), isAVL);
            cout << "AVL: " << (isAVL ? "yes" : "no") << endl;

            // Statistiken berechnen
            double minVal = T.getRoot()->currentNode;
            double maxVal = T.getRoot()->currentNode;
            double sum = 0;
            int count = 0;
            T.getStats(T.getRoot(), minVal, maxVal, sum, count);
            double avg = count > 0 ? sum / count : 0;
            cout << "min: " << minVal << ", max: " << maxVal << ", avg: " << avg << endl;

            // Datei schließen und Programm beenden
            file.close();
            return 0;
            break;
        }

        case 3:
        {
            // Start des Suchmodus
            cout << "Starte Suche..." << endl;

            // Dateipfade aus Argumenten holen
            string treefile = argv[1];
            string subtreefile = argv[2];
            ifstream tree(treefile);
            ifstream subtree(subtreefile);

            // Bäume erstellen
            Tree T = Tree();
            vector<double> sub;
            Tree sT = Tree();
            int value;
            while (tree >> value)
            {
                T.insert(value);
            }

            while (subtree >> value)
            {
                sub.push_back(value);
            }

            Node* temp = NULL;

            // Bestimmen ob einfache Suche oder Subtree-Suche
            if (sub.size() == 1)
            {
                temp = T.simpleSearch(sub[0], T.getRoot());
            }
            else if (sub.size() > 1)
            {
                for (int i = 0; i < sub.size(); i++)
                {
                    sT.insert(sub[i]);
                }

                temp = T.simpleSearch(sT.getRoot()->currentNode, T.getRoot());
                if (temp == NULL)
                {
                    cout << "Subtree nicht gefunden!" << endl;
                }
                else
                {
                    bool found;
                    found = T.subTreeSearch(sT.getRoot(), temp);
                    if (!found)
                    {
                        cout << "Subtree nicht gefunden!" << endl;
                    }
                    else
                    {
                        cout << "Subtree gefunden!" << endl;
                    }
                }
            }

            // Dateien schließen
            tree.close();
            subtree.close();
            return 0;
            break;
        }

        default:
        {
            // Hinweis zur korrekten Verwendung des Programms
            cerr << "Verwendung:\n  treecheck <baumdatei> oder\n  treecheck <baumdatei> <subtree-datei>" << endl;
            return 1;
        }
    }
}
