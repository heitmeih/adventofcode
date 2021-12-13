#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#define LOG(x) cout << x << endl;

#define CANVAS_SIZE 1000
#define FILENAME "./day5.in"

using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int count_intersect(const unsigned int (&canvas)[CANVAS_SIZE][CANVAS_SIZE]) {
    int count = 0;
    for (int y = 0; y < CANVAS_SIZE; y++) {
        for (int x = 0; x < CANVAS_SIZE; x++) {
            //cout << " " << canvas[y][x];
            count += canvas[y][x] >= 2;
        }
        //cout << endl;
    }
    return count;
}

struct vec2 {
    int x, y;
    vec2(int x, int y): x(x), y(y) {}
    vec2(): x(0), y(0) {}
    void operator=(vec2 other) {
        x = other.x;
        y = other.y;
    }
    string str() {
        return "(" + to_string(x) + ", " + to_string(y) + ')';
    }
};

//i'm adding way too much functionality to these structs
struct line {
    vec2 a, b;
    line(vec2 a, vec2 b): a(a), b(b) {}
    line(int x1, int y1, int x2, int y2) {
        vec2 temp_a(x1, y1);
        vec2 temp_b(x2, y2);
        a = temp_a;
        b = temp_b;
    }
    string str() {
        return "(" + a.str() + ", " + b.str() + ')';
    }
    bool is_cardinal() {
        return (a.x == b.x || a.y == b.y);
    }
    void draw_on(unsigned int (&canvas)[CANVAS_SIZE][CANVAS_SIZE]) {
        if (a.x - b.x != 0) {
            double m = double(a.y - b.y)/(a.x - b.x);
            double yint = a.y - m*a.x;
            for (int x = min(a.x, b.x); x <= max(a.x, b.x); x++) {
                canvas[int(m*x+yint)][x]++;
            }
        } else {
            double m = double(a.x - b.x)/(a.y - b.y);
            double xint = a.x - m*a.y;
            for (int y = min(a.y, b.y); y <= max(a.y, b.y); y++) {
                canvas[y][int(m*y+xint)]++;
            }
        }
    }

   
};

int main() {
    ifstream infile;
    infile.open(FILENAME);

    vector<line> lines;

    string l, pair, val;
    int i;
    int vals[4];

    while (getline(infile, l)) {
        stringstream pair_stream(l);
        i = 0;
        while (pair_stream >> pair) {
            if (pair != "->") {
                int x;
                stringstream val_stream(pair);
                getline(val_stream, val, ',');
                vals[i++] = stoi(val);
                getline(val_stream, val, ',');
                vals[i++] = stoi(val);
            }
        }
        line li(vals[0], vals[1], vals[2], vals[3]);
        lines.push_back(li);
    }

    infile.close();

    unsigned int canvas[CANVAS_SIZE][CANVAS_SIZE];

    for (int y = 0; y < CANVAS_SIZE; y++) {
        for (int x = 0; x < CANVAS_SIZE; x++) {
            canvas[y][x] = 0;
        }
    }

    
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].is_cardinal()) lines[i].draw_on(canvas);
    }

    LOG(count_intersect(canvas));

    for (int i = 0; i < lines.size(); i++) {
        if (!lines[i].is_cardinal()) lines[i].draw_on(canvas);
    }

    LOG(count_intersect(canvas));


    return 0;
}