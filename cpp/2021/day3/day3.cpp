#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

inline int bin(string& str) {
    return stoi(str, 0, 2);
}

template<typename Lambda>
int get_rating(vector<string> data, Lambda compare, int bit_pos = 0) {
    if (data.size() == 1) return bin(data[0]);

    vector<string> valid;
    //find which bit is most common
    int counter = 0; // == 0 means same, < 0 means more '0', > 0 means more '1'
    for (int row = 0; row < data.size(); row++) {
        counter += (data[row][bit_pos] == '1') ? 1 : -1;
    }

    for (string &s : data) {
        if ('0' + compare(counter) == s[bit_pos]) 
            valid.push_back(s);
    }

    return get_rating(valid, compare, bit_pos+1);
}

int main() {

    ifstream infile;
    infile.open("./day3.in");
    vector<string> data;
    string line;

    while (getline(infile, line)) {
        data.push_back(line);
    }

    infile.close();

    string gamma = "", epsilon = "";

    for (int col = 0; col < line.length(); col++) {
       int counter = 0; // == 0 means same, < 0 means more '0', > 0 means more '1'
        for (int row = 0; row < data.size(); row++) {
            counter += (data[row][col] == '1') ? 1 : -1;
        }
        gamma += '0' + (counter >= 0);
        epsilon += '0' + (counter < 0);
    }

    cout << (bin(gamma) * bin(epsilon)) << endl;
    cout << get_rating(data, [](int x){ return (x >= 0); }) * get_rating(data, [](int x){ return (x < 0); }) << endl;

    return 0;
}