#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#define LOG(x) cout << x << endl;

using namespace std;

inline int triangular_sum(int x) {
    return (x*x + x)/2;
}

int main() {
    ifstream infile;
    infile.open("day7.in");
    vector<int> positions;
    string pos;

    while(getline(infile, pos, ',')) {
        positions.push_back(stoi(pos));
    }

    // using the median so have to sort
    sort(positions.begin(), positions.end());

    // in my CS class, my teacher did the mathematical proof for why the correct position for p1 is the median
    int median = positions[(positions.size() + 2)/2 - 1];

    // not even joking, p2 being the average was a guess
    int sum = 0;
    for (int n : positions) {
        sum += n;
    }
    double avg = double(sum)/positions.size();

    int fuel_p1 = 0, fuel_p2_1 = 0, fuel_p2_2 = 0;
    for (int x : positions) {
        fuel_p1 += abs(x-median);

        //have to do both rounding up and rounding down because it could be either
        fuel_p2_1 += triangular_sum(abs(x-int(avg)));
        fuel_p2_2 += triangular_sum(abs(x-int(avg + 0.5)));
    }

    LOG(fuel_p1 << "\n" << ((fuel_p2_1 < fuel_p2_2) ? fuel_p2_1 : fuel_p2_2));
}