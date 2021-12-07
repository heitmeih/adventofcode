#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

template <class T>
class undefinable {
    private:
        T val;
        bool defined;

    public:
        undefinable() {
            defined = false;
        }
        T operator= (T value) {
            val = value;
            defined = true;
            return value;
        }
        bool is_defined() {
            return defined;
        }
        T value() {
            return val;
        }
};

struct passport {
    undefinable<unsigned int> birth_yr, issue_yr, expire_yr; 
    undefinable<string> height, hair_clr, eye_clr, pid;

    string in;

    passport(const string &input) {
        string field, key, value;
        stringstream stream;
        stream << input;

        in = input;

        while (stream >> field) {
            key = field.substr(0, 3);
            value = field.substr(4);

            if (key == "byr") {
                birth_yr = stoi(value);
            } else if (key == "iyr") {
                issue_yr = stoi(value);
            } else if (key == "eyr") {
                expire_yr = stoi(value);
            } else if (key == "hgt") {
                height = value;
            } else if (key == "hcl") {
                hair_clr = value;
            } else if (key == "ecl") {
                eye_clr = value;
            } else if (key == "pid") {
                pid = value;
            }
        }
    } 

    bool all_assigned() {
        return (birth_yr.is_defined() && issue_yr.is_defined() && expire_yr.is_defined() && height.is_defined() && 
            hair_clr.is_defined() && eye_clr.is_defined() && pid.is_defined());
    }

    bool byr_valid() {
        return (birth_yr.value() >= 1920 && birth_yr.value() <= 2002);
    }

    bool iyr_valid() {
        return (issue_yr.value() >= 2010 && issue_yr.value() <= 2020);
    }

    bool eyr_valid() {
        return (expire_yr.value() >= 2020 && expire_yr.value() <= 2030);
    }

    bool hgt_valid() {
        const string &h = height.value();
        if (h.length() < 2) return false;

        string end = h.substr(h.length() - 2);  
        unsigned int val;
        try {
            val = stoi(h.substr(0, h.length() - 2));
        } catch (const std::exception &e) {
            return false;
        }


        return ((end == "cm" && val >= 150 && val <= 193) || (end == "in" && val >= 59 && val <= 76));
    }

    bool hcl_valid() {
        if (hair_clr.value()[0] == '#' && hair_clr.value().length() == 7) {
            for (char c : hair_clr.value().substr(1)) {
                if ((c < '0' || c > '9') && (c < 'a' || c > 'f')) {
                    cout << "char:" << c << endl;
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool ecl_valid() {
        string colors[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

        for (string c : colors) if (eye_clr.value() == c) return true;
        return false;
    }

    bool pid_valid() {
        if (pid.value().length() == 9) {
            for (char digit : pid.value()) {
                if (digit < '0' || digit > '9') {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool all_valid() {
        return (all_assigned() && byr_valid() && eyr_valid() && iyr_valid() && hcl_valid() && ecl_valid() && pid_valid() && hgt_valid());
    }
};

void insert_data(vector<passport> &data) {
    ifstream infile;
    infile.open("./day4.in");

    string line, pp_string = "";

    while (getline(infile, line)) {
        if (line != "") {
            pp_string += " " + line;
        } else {
            passport pp(pp_string);
            data.push_back(pp);
            pp_string = "";
        }
    }
    passport pp(pp_string);
    data.push_back(pp);

    infile.close();
}

int main() {

    vector<passport> data;
    insert_data(data);

    int p1_count = 0, p2_count = 0;

    for (passport p : data) {
        if (p.all_assigned()) {
            p1_count++;
        }
        if (p.all_valid()) {
            p2_count++;
        }
    }

    cout << p1_count << "\n" << p2_count << "\n";

    return 0;
}

