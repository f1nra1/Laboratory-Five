#include "func.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

void create_trl(const string& name, const vector<string>& stops,
                map<string, vector<string>>& trls,
                map<string, set<string>>& stop_to_trls) {
    trls[name] = stops;
    for (const string& stop : stops) {
        stop_to_trls[stop].insert(name);
    }
}

void trl_in_stop(const string& stop,
                 const map<string, set<string>>& stop_to_trls) {
    if (stop_to_trls.count(stop) == 0) {
        cout << "Stops is absent\n";
    } else {
        for (const string& trl : stop_to_trls.at(stop)) {
            cout << trl << " ";
        }
        cout << endl;
    }
}

void stops_in_trl(const string& trl,
                  const map<string, vector<string>>& trls,
                  const map<string, set<string>>& stop_to_trls) {
    if (trls.count(trl) == 0) {
        cout << "Trls is absent\n";
    } else {
        for (const string& stop : trls.at(trl)) {
            cout << "Stop " << stop << ": ";
            if (stop_to_trls.count(stop)) {
                for (const string& other : stop_to_trls.at(stop)) {
                    if (other != trl) cout << other << " ";
                }
            }
            cout << endl;
        }
    }
}

void print_trls(const map<string, vector<string>>& trls) {
    if (trls.empty()) {
        cout << "Trls is absent\n";
    } else {
        for (const auto& [trl, stops] : trls) {
            cout << "TRL " << trl << ": ";
            for (const string& stop : stops) {
                cout << stop << " ";
            }
            cout << endl;
        }
    }
}

optional<Type> parse_command(const string& command) {
    if (command == "CREATE_TRL") return Type::CREATE_TRL;
    if (command == "TRL_IN_STOP") return Type::TRL_IN_STOP;
    if (command == "STOPS_IN_TRL") return Type::STOPS_IN_TRL;
    if (command == "TRLS") return Type::TRLS;
    return nullopt; // неизвестная команда
}
