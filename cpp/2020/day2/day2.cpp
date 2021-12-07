#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class password_checker {
    private:
        char letter;
        int start, stop;
        string password;
    public:
        password_checker(string input) {
            //parse input string
            int hyphen = input.find("-"), space = input.find(" "), colon = input.find(": ");

            start = stoi(input.substr(0, hyphen));
            stop = stoi(input.substr(hyphen+1, space - hyphen));
            letter = input.at(colon-1);
            password = input.substr(colon + 2, input.length() - colon + 1);

        }
        bool is_valid_p1() {
            int letter_count = 0;

            for (const char c : password) {
                if (c == letter) {
                    letter_count++;
                }
            }

            return (letter_count >= start && letter_count <= stop);
        }
        bool is_valid_p2() {
            char a = (start - 1 < password.length()) ? password.at(start-1) : '_';
            char b = (stop - 1 < password.length()) ? password.at(stop-1) : '_';

            return ((a == letter && b != letter) || (b == letter && a != letter));
        }
};

int main() {
    
    int p1_valid = 0, p2_valid = 0;
    

    ifstream infile;
    infile.open("./day2.in");

    string line;
    while (getline(infile, line)) {
        password_checker pc(line);
        if (pc.is_valid_p1()) p1_valid++;
        if (pc.is_valid_p2()) p2_valid++;
    }

    cout << p1_valid << "\n";
    cout << p2_valid << "\n";
    
}