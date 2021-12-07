#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    
    // initialize variables
    ifstream infile;
    vector<int> data;
    string line;

    // get data from the input file
    infile.open("./day1.in");

    while (getline(infile, line)) {
        data.push_back(stoi(line));
    }

    infile.close();

    
    // solve
    int p1_increases = 0, p2_increases = 0;

    for (int i = 0; i < data.size() - 1; i++) {
        p1_increases += data[i] < data[i+1];
    }

    for (int i = 0; i < data.size() - 3; i++) {
        p2_increases += data[i] + data[i+1] + data[i+2] < data[i+1] + data[i+2] + data[i+3];
    }

    printf("Part 1: %d\nPart 2: %d\n", p1_increases, p2_increases);

    return 0;
}