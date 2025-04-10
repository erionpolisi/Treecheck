#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    switch(argc) {
        case 2: {
            string filename = argv[1];
            ifstream infile(filename);

            if (!infile.is_open()) {
                cerr << "Could not open file: " << filename << endl;
                return 1;
            }

            int value;
            while (infile >> value) {
                cout << "Gelesener Wert: " << value << endl;
                // Hier später: insert(value);
            }

            infile.close();
            return 0;
            break;
        }

        case 3: {
            // Search-Funktion später hier
            break;
        }

        default:
            cerr << "Usage:\n  treecheck <baumdatei> oder\n  treecheck <baumdatei> <subtree-datei>" << endl;
            return 1;
    }
}
