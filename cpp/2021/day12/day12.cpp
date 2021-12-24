#include "../../common.h"
#include <map>
#include <string>
#include <deque>
#include <algorithm>

bool is_small(const string &node);

struct path { 
    vector<const string*> nodes;
    const string* duped;
    bool has_dupe;

    path() {
        has_dupe = false;
    }
    path(vector<const string*> &n) {
        nodes = n;
        has_dupe = false;
    }
    path(const path* p) {
        nodes = p->nodes;
        has_dupe = p->has_dupe;
        duped = p->duped;
    }
    void push_back(const string* node) {
        nodes.push_back(node);
        if (!has_dupe && is_small(*node) && count(nodes.begin(), nodes.end(), node) == 2) {
            has_dupe = true;
            duped = node;
        }
    }
    bool node_is_allowed(const string* node) {
        if (!is_small(*node)) return true;
        return (!has_dupe || (has_dupe && node != duped && count(nodes.begin(), nodes.end(), node) != 1));
    }
};

struct pathfinder {
    map<string, vector<const string*>>* caves;
    deque<path*> q;
    unsigned int num_paths;

    pathfinder(map<string, vector<const string*>>* caves, const string* start_ptr) {
        this->caves = caves;
        path* p = new path();
        p->push_back(start_ptr);
        deque<path*> q;
        q.push_back(p);
        this->q = q;
        num_paths = 0;
    }

    void find_paths() {
        while (!q.empty()) {
            if (q.size() != 0 && **(q.front()->nodes.end()-1) == "end") {
                num_paths++;
                //delete q.front();
                q.pop_front();
                continue;
            }
            if (q.empty()) return;
            for (const string* node : (*caves)[**(q.front()->nodes.end()-1)]) {
                if (!q.front()->node_is_allowed(node)) continue; 
                path* temp = new path(q.front());
                temp->push_back(node);
                q.emplace_back(temp);
            }
            q.pop_front();
        }
    }
};

int main() {
    map<string, vector<const string*>> caves;
    map<string, const string*> pointers;
    
    ifstream infile;
    infile.open("day12.in");

    string line;

    while (getline(infile, line)) {
        int dash_pos = line.find('-');
        const string* first = new string(line.substr(0, dash_pos));
        const string* second = new string(line.substr(dash_pos+1));

        if (pointers.find(*first) == pointers.end()) {
            pointers[*first] = first;
        }
        if (pointers.find(*second) == pointers.end()) {
            pointers[*second] = second;
        }
        if (caves.find(*first) == caves.end()) {
            vector<const string*> temp;
            caves[*first] = temp;
        }
        if (caves.find(*second) == caves.end()) {
            vector<const string*> temp;
            caves[*second] = temp;
        }

        if (*second != "start") caves[*first].push_back(pointers[*second]);
        if (*first != "start") caves[*second].push_back(pointers[*first]);
    }

    caves.erase("end");

    infile.close();

    // for (const auto &[key, value] : pointers) {
    //     cout << key << '=' << *value << endl;
    // }

    // for (const auto &[key, value] : caves) {
    //     cout << key << " = { ";
    //     for (auto v : value) {
    //         cout << *v << " ";
    //     }
    //     cout << "}" << endl;
    // }

    pathfinder pathf(&caves, pointers["start"]);

    pathf.find_paths();

    LOG(pathf.num_paths);
}

bool is_small(const string &node) {
    return (node[0] >= 'a' && node[0] <= 'z');
}