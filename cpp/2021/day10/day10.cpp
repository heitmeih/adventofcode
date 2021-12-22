#include "../../common.h"

int main() {
    ifstream infile;
    infile.open("day10.in");
    vector<string> lines;
    string line;

    while (getline(infile, line)) {
        // could just go line by line for part 1, but perhaps we'll need to access previous lines in part 2
        lines.push_back(line);
    }

    infile.close();

    int part_1 = 0;
    vector<char> opened;
    vector<long> scores;

    for (string l : lines) {
        bool is_corrupted = false;
        for (char c : l) {
            if (c == '[' || c == '{' || c == '<' || c == '(') {
                opened.insert(opened.begin(), c);
            } else if (c == '>' && opened[0] != '<') {
                part_1 += 25137;
                is_corrupted = true;
                break;
            } else if (c == '}' && opened[0] != '{') {
                part_1 += 1197;
                is_corrupted = true;
                break;
            } else if (c == ']' && opened[0] != '[') {
                part_1 += 57;
                is_corrupted = true;
                break;
            } else if (c == ')' && opened[0] != '(') {
                part_1 += 3;
                is_corrupted = true;
                break;
            } else {
                opened.erase(opened.begin());
            }
        }
        if (!is_corrupted) {
            long score = 0;
            for (char c : opened) {
                score *= 5;
                switch (c) {
                case '(':
                    score += 1;
                    break;
                case '[':
                    score += 2;
                    break;
                case '{':
                    score += 3;
                    break;
                case '<':
                    score += 4;
                    break;            
                }
            }
            scores.push_back(score);
        }
        opened.erase(opened.begin(), opened.end());
    }

    sort(scores.begin(), scores.end());

    LOG(part_1)
    LOG(scores[(scores.size() + 2)/2 - 1])

}