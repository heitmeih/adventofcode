#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream infile;
    infile.open("./day2.in");
    
    string line;
    char direction;
    int amount;

    int p1_x = 0, p1_depth = 0;
    int p2_x = 0, p2_depth = 0, aim = 0;

    while (getline(infile, line)) {
        direction = line[0];
        amount = stoi(line.substr(line.find(' ')));
        
        switch (direction) {
            case 'u':
                p1_depth -= amount;
                aim -= amount;
                break;
            case 'd':
                p1_depth += amount;
                aim += amount;
                break;
            case 'f':
                p1_x += amount;
                p2_x += amount;
                p2_depth += amount * aim;
                break;
        }
    }

    printf("\nPart 1: %d\nPart 2: %d\n\n", (p1_x * p1_depth), (p2_x * p2_depth));

    infile.close();

    return 0;
}