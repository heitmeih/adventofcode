#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// I've never made a macro before, so why not try it now?
#define LOG(x) cout << x << endl;

vector<int> split_int(const string &str) {
    vector<int> result;
    stringstream stream(str);

    string next;
    while (getline(stream, next, ',')) {
        result.push_back(stoi(next));
    }

    return result;
}

void split_int(const string &str, int (&arr)[5]) {
    stringstream stream(str);

    int next;
    for (int i = 0; stream >> next; i++) {
        arr[i] = next;
    }
}

typedef struct board {
    int vals[5][5];
    bool chosen[5][5];
    board(int v[5][5]) {
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                vals[r][c] = v[r][c];
                chosen[r][c] = false;
            }
        }
    }
    string str() {
        string result = "";
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                result += to_string(vals[r][c]) + ' ';
            }
            result += '\n';
        }
        return result;
    }
    string str_chosen() {
        string result = "";
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                result += to_string(chosen[r][c]) + ' ';
            }
            result += '\n';
        }
        return result;
    }
    bool is_winner() {
        for (int i = 0; i < 5; i++) {
            if ((chosen[i][0] && chosen[i][1] && chosen[i][2] && chosen[i][3] && chosen[i][4]) || 
                (chosen[0][i] && chosen[1][i] && chosen[2][i] && chosen[3][i] && chosen[4][i])) return true;
        }
        return false;
    }
    void draw_number(int num) {
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (vals[r][c] == num) {
                    chosen[r][c] = true;
                    return;
                }
            }
        }
    }
    int sum_unchosen() {
        int sum = 0;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (!chosen[r][c]) {
                    sum += vals[r][c];
                }
            }
        }
        return sum;
    }
} board;

int main() {

    ifstream infile;
    infile.open("./day4.in");

    string line;
    getline(infile, line);

    vector<int> nums = split_int(line);
    vector<board> boards;

    getline(infile, line); //move to next line

    int raw_board[5][5];
    int col = 0;
    while(getline(infile, line)) {
        if (line.length() == 0) {
            board b(raw_board);
            boards.push_back(b);
            col = 0;
            continue;
        }
        split_int(line, raw_board[col++]);
    }
    board b(raw_board);
    boards.push_back(b);

    infile.close();

    int p1_score, p2_score;
    const int num_boards = boards.size();
    

    for (int num : nums) {
        for (int i = boards.size() - 1; i >= 0; i--)/*(board &bo : boards)*/ {
            board &bo = boards[i];
            bo.draw_number(num);
            if (bo.is_winner()) {
                if (boards.size() == num_boards) {
                    LOG("Part 1: " << bo.sum_unchosen() * num);
                } else if (boards.size() == 1) {
                    LOG("Part 2: " << bo.sum_unchosen() * num)
                    return 0;
                }
                boards.erase(boards.begin() + i);
            }
        }
    }

    return 0;
}

/*
// I have a feeling that this is very unsafe, so I won't use it
int * split_int(const string &str, const char delim = ',') {
    int delim_count = 0;
    for (const char c : str) {
        delim_count += (c == ',');
    } 

    int result[delim_count+1];
    //int i = 0, find_pos = 0;

    stringstream stream(str);

    int next;
    for (int i = 0; stream >> next; i++) {
        result[i] = next;
    }

    return result;
}
*/