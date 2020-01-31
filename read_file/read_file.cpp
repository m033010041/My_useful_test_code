#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

#define EETI_CTP_VERION_FILE "EETI_version"

using namespace std;
int main(int argc, char **argv)
{

    ifstream ifile;
    ofstream ofile;
    string line, token, fw;
    string search("FW Version:");
    size_t found;
    int count = 0;

    ifile.open(EETI_CTP_VERION_FILE, ifstream::in);
    if (ifile.is_open()) {
        ifile >> token;
        cout << "has file and get token: " << token << endl;
        ifile.close();
        return 0;
    }

    ifile.open("test");

    if (ifile.is_open()) {
        while (getline(ifile, line)) {
            if (line.find(search, 0) != string::npos) {
                found = line.find(':');
                fw = line.substr(++found);
                cout << fw << endl;
                stringstream ss(fw);
                while (ss >> token) {
                    count++;
                    cout << "get token: " << count << " is " << token << endl;
                    ofile.open("EETI_version");
                    ofile << token;
                    ofile.close();
                }
            }
        }
        ifile.close();
    }

    return 0;
}
