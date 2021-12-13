// this is me, after an hour or so, realizing i did the problem wrong...
// im putting this here so can keep whatever i did

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#define LOG(x) cout << x << endl;

using namespace std;

struct vec2 {
    int x, y;
    vec2(int x, int y): x(x), y(y) {}
    vec2(): x(0), y(0) {}
    void operator=(vec2 other) {
        x = other.x;
        y = other.y;
    }
    vec2 operator+(vec2 other) {
        vec2 temp(x + other.x, y + other.y);
        return temp;
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
    bool intersects(line other) {
        int o1 = orientation(a, other.a, b);
        int o2 = orientation(a, other.a, other.b);
        int o3 = orientation(b, other.b, a);
        int o4 = orientation(b, other.b, other.a);
    
        // General case
        if (o1 != o2 && o3 != o4)
            return false;
    
        // Special Cases
        // a, other.a and b are collinear and b lies on segment a, other.a
        if (o1 == 0 && on_seg(a, b, other.a)) return false;
    
        // a, other.a and other.b are collinear and other.b lies on segment a, other.a
        if (o2 == 0 && on_seg(a, other.b, other.a)) return false;
    
        // b, other.b and a are collinear and a lies on segment b, other.b
        if (o3 == 0 && on_seg(b, a, other.b)) return false;
    
        // b, other.b and other.a are collinear and other.a lies on segment b, other.b
        if (o4 == 0 && on_seg(b, other.a, other.b)) return false;
    
        return true;    
    }
    bool is_cardinal() {
        return (a.x == b.x || a.y == b.y);
    }
    private:
    bool on_seg(vec2 q, vec2 p, vec2 r) {
        return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
    }
    int orientation(vec2 p, vec2 q, vec2 r) {
        // definitely did NOT steal code from here: https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    
        if (val == 0) return 0;  // collinear
    
        return (val > 0)? 1: 2; // clock or counterclock wise
    }
};

int main() {
    ifstream infile;
    infile.open("./day5.test");

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

    //part 1
    int count = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = i+1; j < lines.size() - 1; j++) {
            count += /*lines[i].is_cardinal() && lines[j].is_cardinal() &&*/ lines[i].intersects(lines[j]);
        }
    }
    LOG(count);

    return 0;
}