#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> parseInput();

int main() {
    vector<int> data = parseInput();

    // oh my
    for (int i = 0; i < data.size(); i++) {
        for (int j = i + 1; j < data.size(); j++) {
            for (int h = j + 1; h < data.size(); h++) {
                if (data[i] + data[j] + data[h] == 2020) {
                    cout << data[i] * data[j] * data[h] << "\n";
                    return 0;
                }
            }  
        }
    }

    
}

vector<int> parseInput() {
    ifstream infile;
    infile.open("./day1.in");
    
    vector<int> result;
    int data;

    while (infile >> data) {
        result.push_back((int) data);
    }
    infile.close();

    return result;
};