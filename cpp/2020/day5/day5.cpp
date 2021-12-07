#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

// made better version with parse_bin
int partition(string::iterator iter, unsigned int bottom = 0, unsigned int top = 127) {
    if (*iter == '\0') {
        return top;
    }
    if (*iter == 'B' || *iter == 'R') {
        return partition(++iter, bottom + ((top-bottom)/2) + 1, top);
    } else if (*iter == 'F' || *iter == 'L') {
        return partition(++iter, bottom, top - ((top-bottom)/2) - 1);
    } else {
        return -1; // this means there was an issue with formatting
    }
}

int parse_bin(string s) {
    int val = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == 'B' || s[i] == 'R') {
            val += pow(2, s.length() - i - 1);
        }
    }
    return val;

}

// not necessary for this
int get_max(vector<int> vec) {
    int current_max = numeric_limits<int>::min();
    for (int i = 0; i < vec.size(); i++) {
        current_max = max(current_max, vec[i]);
    }
    return current_max;
}

int main() {
    ifstream infile;
    infile.open("./day5.in");

    string line;
    vector<int> ids;

    while(getline(infile, line)) {
        ids.push_back(parse_bin(line.substr(0, 7)) * 8 + parse_bin(line.substr(7, 3)));
    }
    
    sort(ids.begin(), ids.end());

    infile.close();

    //could do ids[ids.size() - 1] instead (probably)
    cout << "Part 1: " << get_max(ids) << "\n";

    vector<int>::iterator it = ids.begin();
    while (it < ids.end()) {
        if (*it + 2 == *(++it)) {
            cout << "Part 2: " << *it - 1 << endl;
        }
    }
}