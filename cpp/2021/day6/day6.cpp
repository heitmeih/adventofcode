#include <iostream>
#include <vector>
#include <fstream>

#define LOG(x) cout << x << endl;

using namespace std;

unsigned long count_fish(long fish[9]) {
    unsigned long count = 0;
    for (int age = 0; age < 9; age++) {
        count += fish[age];
    }
    return count;
}

int main() {
    ifstream infile;
    infile.open("day6.in");
    vector<int> stuff;

    // idk how sets work (and i don't have internet so i can't look it up)
    // also, i think i figured out a way to do it without it (i.e., arrays are basically the same as set<int, int>)
    // set<int, int> data;

    long fish[9];

    for (long& f : fish) f = 0;

    string num;

    while (getline(infile, num, ',')) {
        fish[stoi(num)]++;
    }

    infile.close();

    for (int day = 0; day < 256; day++) {
        long age_zero = fish[0];
        for (int age = 0; age < 8; age++) {
            fish[age] = fish[age+1];
        }
        fish[8] = age_zero;
        fish[6] += age_zero;
        // for (int& f : fish) cout << f << ' ';
        // cout << endl;
        if (day == 79) LOG(count_fish(fish)) // print part 1
    }

    LOG(count_fish(fish))

}