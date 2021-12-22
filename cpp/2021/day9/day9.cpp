#include <iostream>
#include <fstream>
#include <vector>

#define LOG(x) cout << x << endl;

using namespace std;

struct Point {
    int r, c;

    Point(int r, int c) : r(r), c(c) {}

    inline bool operator==(const Point &other) {
        return (r == other.r && c == other.c);
    }
    
};

short min(short (&arr)[4]);
int get_basin_size(const vector<vector<short>> &height_map, vector<Point> &queue, vector<Point> &found);
int get_basin_size(const vector<vector<short>> &height_map, Point start);
bool has(vector<Point> points, Point p);

int main() {

    //parse input
    ifstream infile;
    infile.open("day9.in");

    vector<vector<short>> height_map;

    string line;

    while (getline(infile, line)) {
        vector<short> current_row;
        for (const char n : line) {
            current_row.push_back((short)(n - '0'));
        }
        height_map.push_back(current_row);
    }

    infile.close();

    // for (vector<short> r : height_map) {
    //     for (short s : r) {
    //         cout << s << ' ';
    //     }
    //     cout << endl;
    // }

    //solve
    int part_1 = 0, part_2 = 1;
    vector<Point> lows;
    vector<int> basin_sizes;
    short adjacent[4];

    for (int r = 0; r < height_map.size(); r++) {
        for (int c = 0; c < height_map[r].size(); c++) {
            adjacent[0] = (r - 1 >= 0) ? height_map[r-1][c] : 10;
            adjacent[1] = (r + 1 < height_map.size()) ? height_map[r+1][c] : 10;
            adjacent[2] = (c - 1 >= 0) ? height_map[r][c-1] : 10;
            adjacent[3] = (c + 1 <  height_map[r].size()) ? height_map[r][c+1] : 10;

            if (height_map[r][c] < min(adjacent)) {
                part_1 += 1 + height_map[r][c];

                Point p(r, c);
                lows.push_back(p);
            }
        }
    }

    for (Point low : lows) {
        basin_sizes.push_back(get_basin_size(height_map, low));
    }

    sort(basin_sizes.begin(), basin_sizes.end());

    for (int i = 0; i < 3; i++) {
        part_2 *= basin_sizes[basin_sizes.size()-1-i];
    }

    LOG(part_1)
    LOG(part_2)
}

short min(short (&arr)[4]) {
    short minimum = 11; //nums won't be higher than 9, so this is fine
    for (short s : arr) if (s < minimum) minimum = s;
    return minimum;
}

int get_basin_size(const vector<vector<short>> &height_map, Point start){
    vector<Point> f;
    vector<Point> q = {start};

    return get_basin_size(height_map, q, f);
}


int get_basin_size(const vector<vector<short>> &height_map, vector<Point> &queue, vector<Point> &found) {
    //im not gonna lie, i was very tired when making this, so it's amazing that it works
    if (queue.size() == 0) return found.size();
    
    if (!has(found, queue[0])) {
        if (queue[0].r-1 >= 0) if (height_map[queue[0].r-1][queue[0].c] != 9) {
            Point p(queue[0].r-1, queue[0].c);
            queue.push_back(p);
        }
        if (queue[0].r+1 < height_map.size()) if (height_map[queue[0].r+1][queue[0].c] != 9) {
            Point p(queue[0].r+1, queue[0].c);
            queue.push_back(p);
        }
        if (queue[0].c-1 >= 0) if (height_map[queue[0].r][queue[0].c-1] != 9) {
            Point p(queue[0].r, queue[0].c-1);
            queue.push_back(p);
        }
        if (queue[0].c+1 < height_map[0].size()) if (height_map[queue[0].r][queue[0].c+1] != 9) {
            Point p(queue[0].r, queue[0].c+1);
            queue.push_back(p);
        }
        
        found.push_back(queue[0]);
    }

    queue.erase(queue.begin());
    return get_basin_size(height_map, queue, found);
}

bool has(vector<Point> points, Point p) {
    for (const Point point : points) if (p == point) return true;
    return false;
}