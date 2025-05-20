#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <optional>

using namespace std;

enum class Type {
    CREATE_TRL,
    TRL_IN_STOP,
    STOPS_IN_TRL,
    TRLS
};

optional<Type> parse_command(const string& command);

void create_trl(const string& name, const vector<string>& stops,
                map<string, vector<string>>& trls,
                map<string, set<string>>& stop_to_trls);

void trl_in_stop(const string& stop,
                 const map<string, set<string>>& stop_to_trls);

void stops_in_trl(const string& trl,
                  const map<string, vector<string>>& trls,
                  const map<string, set<string>>& stop_to_trls);

void print_trls(const map<string, vector<string>>& trls);

#endif
