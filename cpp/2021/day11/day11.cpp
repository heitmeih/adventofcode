#include <iostream>
#include <fstream>

#define LOG(x) cout << x << endl;

using namespace std;

int main() {
    ifstream infile;
    infile.open("./day11.in");

    char octopuses[10][10];
    string line;

    for (int r = 0; getline(infile, line); r++)
        for (int c = 0; c < 10; c++)
            octopuses[r][c] = (char) (line[c] - '0');
        
    infile.close();

    int total_flash_count = 0;
    for (int step = 0; step > -1; step++) {
        // for (int r = 0; r < 10; r++) {
        //     for (int c = 0; c < 10; c++) {
        //         cout << ((int) octopuses[r][c]);
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        for (int r = 0; r < 10; r++) 
            for (int c = 0; c < 10; c++)
                octopuses[r][c]++;

        short flash_count;
        int temp_total = total_flash_count;
        do {
            flash_count = 0;
            for (int r = 0; r < 10; r++) 
                for (int c = 0; c < 10; c++) {
                    if (octopuses[r][c] > 9 && octopuses[r][c] != 0) {
                        octopuses[r][c] = 0;

                        flash_count++;
                        total_flash_count++;
                        
                        octopuses[r-1][c] += (r-1 >= 0 && octopuses[r-1][c] != 0);
                        octopuses[r-1][c+1] += (r-1 >= 0 && c+1 < 10 && octopuses[r-1][c+1] != 0);
                        octopuses[r][c+1] += (c+1 < 10 && octopuses[r][c+1] != 0);
                        octopuses[r+1][c+1] += (c+1 < 10 && r+1 < 10 && octopuses[r+1][c+1] != 0);
                        octopuses[r+1][c] += (r+1 < 10 && octopuses[r+1][c] != 0);
                        octopuses[r+1][c-1] += (r+1 < 10 && c-1 >= 0 && octopuses[r+1][c-1] != 0);
                        octopuses[r][c-1] += (c-1 >= 0 && octopuses[r][c-1] != 0);
                        octopuses[r-1][c-1] += (r-1 >= 0 && c-1 >= 0 && octopuses[r-1][c-1] != 0);            
                    }
                }
        } while (flash_count != 0);

        if (step == 99) {
            LOG("Part 1: " << total_flash_count);
        }
        if (total_flash_count - temp_total == 100) {
            LOG("Part 2: " << step + 1);
            break;
        } 
    }
}