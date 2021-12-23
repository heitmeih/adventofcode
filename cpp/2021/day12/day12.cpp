#include "../../common.h"
#include <map>
#include <string>
#include <queue>
#include <algorithm>

bool is_small(const string &node);

struct path { 
    // idk what I did, but this method apparently requires over 35 gigs of ram to run...
    vector<string> nodes;
    string duped;
    bool has_dupe;

    path() {
        has_dupe = false;
        duped = "";
        cerr << "PATH()" << endl;
    }
    path(vector<string> &n) {
        nodes = n;
        has_dupe = false;
        cerr << "PATH(vector)" << endl;
    }
    path(const path* p) {
        nodes = p->nodes;
        has_dupe = p->has_dupe;
        duped = p->duped;
        cerr << "PATH(path)" << p << endl;
    }
    void push_back(string node) {
        nodes.push_back(node);
        if (!has_dupe && is_small(node) && count(nodes.begin(), nodes.end(), node) == 2) {
            has_dupe = true;
            duped = node;
        }
    }
    bool node_is_allowed(string node) {
        if (!is_small(node)) return true;
        return (!has_dupe || (has_dupe && node != duped && count(nodes.begin(), nodes.end(), node) != 1));
    }
};

struct pathfinder {
    map<string, vector<string>>* caves;
    queue<path*> q;
    int num_paths;

    pathfinder(map<string, vector<string>>* caves) {
        this->caves = caves;
        path* p = new path();
        p->push_back("start");
        queue<path*> q;
        q.push(p);
        this->q = q;
        num_paths = 0;
    }

    void find_paths() {
        //cerr << q.size() << endl;
        while (q.size() != 0 && *(q.front()->nodes.end()-1) == "end") {
            num_paths++;
            delete q.front();
            q.pop();
        }
        //cerr << "fat?" << q.front() << endl;
        if (q.empty()) return;
        for (const auto &node : (*caves)[*(q.front()->nodes.end()-1)]) {
            if (node == "start" || !q.front()->node_is_allowed(node)) continue; 
            path* temp = new path(q.front());
            temp->push_back(node);
            cerr << temp << endl;
            q.push(temp);
        }
        delete q.front();
        q.pop();
        cerr << "hello?" << endl;
        for (string n : q.front()->nodes) {
            cerr << n << ' ';
        }
        cerr << endl;
        find_paths();
    }
};

void get_paths(map<string, vector<string>> &caves, int &num_paths);

int main() {
    map<string, vector<string>> caves;
    
    ifstream infile;
    infile.open("day12.in");

    string line;

    while (getline(infile, line)) {
        int dash_pos = line.find('-');
        string first = line.substr(0, dash_pos);
        string second = line.substr(dash_pos+1);

        if (caves.find(first) == caves.end()) {
            vector<string> temp;
            caves[first] = temp;
        }
        if (caves.find(second) == caves.end()) {
            vector<string> temp;
            caves[second] = temp;
        }

        if (second != "start") caves[first].push_back(second);
        if (first != "start") caves[second].push_back(first);
    }

    caves.erase("end");

    infile.close();

    // for (const auto &[key, value] : caves) {
    //     cout << key << " = { ";
    //     for (auto v : value) {
    //         cout << v << " ";
    //     }
    //     cout << "}" << endl;
    // }

    pathfinder pathf(&caves);

    pathf.find_paths();

    LOG(pathf.num_paths);
}

bool is_small(const string &node) {
    return (node[0] >= 'a' && node[0] <= 'z');
}

bool node_is_allowed(vector<string> &path, const string &node) {
    if (!is_small(node)) return true;
    string duped;
    bool has_dupe = false;

    for (string n : path) {
        if (count(path.begin(), path.end(), n) >= 2) {
            duped = n;
            has_dupe = true;
            break;
        }
    }

    return (!has_dupe || (has_dupe && node != duped && count(path.begin(), path.end(), node) != 1));
}

void get_paths(map<string, vector<string>> &caves, int &num_paths, queue<path*> &q) {
    cerr << q.size() << endl;
    while (q.size() != 0 && *(q.front()->nodes.end()-1) == "end") {
        num_paths++;
        delete q.front();
        q.pop();
    }
    cerr << "fat?" << &caves[*(q.front()->nodes.end()-1)] << endl;
    if (q.empty()) return;
    for (const auto &node : caves[*(q.front()->nodes.end()-1)]) {
        if (node == "start" || !q.front()->node_is_allowed(node)) continue; 
        path* temp = new path(q.front());
        cerr << "unga" << q.front() << endl;
        temp->push_back(node);
        cerr << temp << endl;
        q.push(temp);
    }
    delete q.front();
    q.pop();
    cerr << "hello?" << endl;
    // for (string n : *q.front()->nodes) {
    //     cout << n << ' ';
    // }
    // cerr << '"' << *(q.front()->nodes->end()-1) << '"' << endl;
    return get_paths(caves, num_paths, q);

    // while (q.size() != 0 && *(q.front().end()-1) == "end") {
    //     paths.push_back(q.front());
    //     q.pop();
    // }
    // if (q.empty()) return;
    // for (const auto &node : caves[*(q.front().end()-1)]) {
    //     if (node == "start" || !node_is_allowed(q.front(), node)) continue; 
    //     vector<string> temp { node };
    //     q.push(temp);
    // }
    // q.pop();
    // return get_paths(caves, paths, q);
}

void get_paths(map<string, vector<string>> &caves, int &num_paths) {
    queue<path*> q;
    path* p = new path();
    p->push_back("start");
    q.push(p);

    return get_paths(caves, num_paths, q);
}