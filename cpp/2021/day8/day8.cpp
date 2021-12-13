// just looking at the input, i can tell this one will be a doozy
/*
      0:      1:      2:      3:      4:
     aaaa    ....    aaaa    aaaa    ....
    b    c  .    c  .    c  .    c  b    c
    b    c  .    c  .    c  .    c  b    c
     ....    ....    dddd    dddd    dddd
    e    f  .    f  e    .  .    f  .    f
    e    f  .    f  e    .  .    f  .    f
     gggg    ....    gggg    gggg    ....

    5:      6:      7:      8:      9:
     aaaa    aaaa    aaaa    aaaa    aaaa
    b    .  b    .  .    c  b    c  b    c
    b    .  b    .  .    c  b    c  b    c
     dddd    dddd    ....    dddd    dddd
    .    f  e    f  .    f  e    f  .    f
    .    f  e    f  .    f  e    f  .    f
     gggg    gggg    ....    gggg    gggg
    
     aaaa    
    b    c 
    b    c  
     dddd   
    e    f  
    e    f  
     gggg 


2 signals -> 1
    c, f
3 signals -> 7
    a, c, f
4 signals -> 4
    b, c, d, f
5 signals -> 2, 3, 5
    2 - a, c, d, e, g
    3 - a, c, d, f, g
    5 - a, b, d, f, g
    could be a, b, c, d, e, f, or g
6 signals -> 0, 6, 9
    0 - a, b, c, e, f, g
    6 - a, b, d, e, f, g
    9 - a, b, c, d, f, g
    could be a, b, c, d, e, f, or g
7 signals -> 8 (useless for decoding)
    a, b, c, d, e, f, g

to decode any of the 5 or six digit ones, it's easier to find which in output it cannot be
thus, shorter signal combinations should be focuses first

as problem states, the unique length ones can be figured out without decoding what each signal means

"Each entry consists of ten unique signal patterns" means that every digit is represented once in the inputs

solving the example by hand

    rules i've found:
        - the two letters that make up a two-signal must be either c or f (groupA)
        - of the three letters in the three-signal, the one not present in the two-signal will be a
        - of the four letters in the four-signal, the two not present in the two-signal will be b or d (groupB)
        - the remaining two letters will be either e or g (groupC)
    
    char a;
    char groupA[2];
    char groupB[2];
    char groupC[2];


    Following these rules, you will always get this setup:

    a is always present (except for when there are only 2 signals, but that equals one no matter what so it can be ignored)
    groupA = c, f
          |
          |
    groupB = b, d
        |_

    groupC = e, g

        |_


     ....    
    B    A 
    B    A  
     BBBB   
    C    A  
    C    A  
     CCCC 
    
    This is enough info to find each number:
        - a is present for every number except 1
        - 3 must have both the possible aliases of c and f and be a five-signal (other groups have 1 each)
            consider:
            2 from groupA
            1 groupB
            1 groupC

            can be:
             _      _      _      _
             _|    | |    | |     _|
             _| or  _| or | | or | | 
             so it's 3, bc that's the only valid combination
        - 2 must have both the possible aliases of e and g and be a five-signal
            1 groupA
            1 groupB
            2 groupC

            can be:
             _      _      _      _
            | |    |       _|     _
            |_  or |_| or |_  or |_| 
            so 2
        - 5 must have both the possible aliases of b and d and be a five-signal
            1 groupA
            2 groupB
            1 groupC

            can be:
             _      _      _      _
            |_|    |_     |_     |_|
            |   or | | or  _| or  _  
            so 5
        - 0 must have one of the aliases of b, d; both aliases for c, f; both aliases of e, g; and be a six-signal
            2 groupA
            1 groupB
            2 groupC

            can be:
             _      _
            | |     _|
            |_| or |_| 
            so 0 (or a)
        - 6 must have one of the aliases of c, f; both aliases for b, d; both aliases of e, g; and be a six-signal
            1 groupA
            2 groupB
            2 groupC

            can be:
             _      _
            |_     |_|
            |_| or |_ 
            so 6 (or e)
        - 9 must have one of the aliases of e, g; both aliases for c, f; both aliases of b, d; and be a six-signal
            2 groupA
            2 groupB
            1 groupC

            can be:
             _      _
            |_|    |_|
            | | or  _| 
            so 9 (or A)
        - 1, 4, 7, 8 can be idenfied by the length of their signal combinations
            1 - 2 sig
            7 - 3 sig
            4 - 4 sig
            8 - 7 sig 
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>

#define LOG(x) cout << x << endl;

using namespace std;

short count_chars(const char (&chars)[2], const string& sig);

int decode_entry(vector<string> inputs, vector<string> outputs);

int main() {

    //parse input
    // i love parsing input in c++ :)
    ifstream infile;
    infile.open("day8.in");
    vector<vector<string>> inputs;
    vector<vector<string>> outputs;

    string line, io, signal;
    bool is_inputs = true;

    while (getline(infile, line)) {
        stringstream line_stream(line);
        while(getline(line_stream, io, '|')) {
            stringstream io_stream(io);
            vector<string> temp;
            while(getline(io_stream, signal, ' ')) {
                temp.push_back(signal);
            }
            if (is_inputs) {
                sort(temp.begin(), temp.end(), []
                    (const string &first, const string& second) {
                        return first.size() < second.size();
                    });
                inputs.push_back(temp);
            } else {
                temp.erase(temp.begin());
                outputs.push_back(temp);
            }
            is_inputs = !is_inputs;
        }
    }

    infile.close();

    //solve

    //part1
    int p1_count = 0;
    for (vector<string> output : outputs) {
        for (string sig : output) {
            p1_count += (sig.length() == 7 || sig.length() <= 4);
            //cout << '"' << sig << "\" ";
        }
        //cout << endl;
    }

    int p2_count = 0;
    for (int i = 0; i < inputs.size(); i++) {
        p2_count += decode_entry(inputs[i], outputs[i]);
        //LOG(decode_entry(inputs[i], outputs[i]));
    }

    LOG(p1_count);
    LOG(p2_count);

}

short count_chars(const char (&chars)[2], const string &sig) {
    short count = 0;
    for (char c : chars) for (char s : sig) count += (s == c);
    return count;
}

inline bool check_groups(const string& sig, const char (&ga)[2], int a_count, const char (&gb)[2], int b_count, const char (&gc)[2], int c_count) {
    return ((count_chars(ga, sig) == a_count) && (count_chars(gb, sig) == b_count) && (count_chars(gc, sig) == c_count));
}

bool is_char_included(const char (&array)[2], const char c) {
    for (const char character : array) if (character == c) return true;
    return false;
}

int decode_entry(vector<string> inputs, vector<string> outputs) {
    
    // find groups

    int index = 0;
    char groupA[] = {inputs[0][0], inputs[0][1]};
    char a;
    for (char c : inputs[1]) if (!is_char_included(groupA, c)) a = c;
    char groupB[2];
    for (char c : inputs[2]) if (!is_char_included(groupA, c)) {groupB[index] = c; index++;}
    index = 0;
    char groupC[2];
    for (char c : "abcdefg") if (!is_char_included(groupA, c) && !is_char_included(groupB, c) && c != a) {groupC[index] = c; index++;}
    
    //LOG(groupA[0] << ' ' << groupA[1] << ' ' << a << ' ' << groupB[0] << ' ' << groupB[1] << ' ' << groupC[0] << ' ' << groupC[1]);
    
    int result = 0, digit;
    for (int i = 0; i < outputs.size(); i++) {
        if (outputs[i].size() == 2) {
            digit = 1;
        } else if (outputs[i].size() == 3) {
            digit = 7;
        } else if (outputs[i].size() == 4) {
            digit = 4;
        } else if (outputs[i].size() == 7) {
            digit = 8;
        } else if (check_groups(outputs[i], groupA, 2, groupB, 1, groupC, 1)) {
            digit = 3;
        } else if (check_groups(outputs[i], groupA, 1, groupB, 1, groupC, 2)) {
            digit = 2;
        } else if (check_groups(outputs[i], groupA, 1, groupB, 2, groupC, 1)) {
            digit = 5;
        } else if (check_groups(outputs[i], groupA, 2, groupB, 1, groupC, 2)) {
            digit = 0;
        } else if (check_groups(outputs[i], groupA, 1, groupB, 2, groupC, 2)) {
            digit = 6;
        } else {
            digit = 9;
        }
        //LOG( endl << digit << endl);

        result += digit * int(pow(10, 3-i));
    }
    return result;
}