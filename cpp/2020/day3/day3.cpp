#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void insert_data(vector<string> &data) {
    ifstream infile;
    infile.open("./day3.in");

    string line;
    while (getline(infile, line)) {
        data.push_back(line);
    }

    infile.close();
}

int get_trees_hit(vector<string> input, int right, int down) {
    int trees = 0;

    for (int h_pos = 0, v_pos = 0; v_pos < input.size(); h_pos += right, v_pos += down) {
        if (input[v_pos][h_pos % input[v_pos].length()] == '#') {
            trees++;
        }    
    }
    return trees;
}

int main() {

    vector<string> data;

    insert_data(data);

    int t1, t2, t3, t4, t5;

    t1 = get_trees_hit(data, 1, 1);
    t2 = get_trees_hit(data, 3, 1);
    t3 = get_trees_hit(data, 5, 1);
    t4 = get_trees_hit(data, 7, 1);
    t5 = get_trees_hit(data, 1, 2);

    cout << "Part 1: " << t2 << endl;

    cout << "Part 2: " << long (t1)*t2*t3*t4*t5 << endl;

}