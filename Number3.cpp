#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include "func.h"

using namespace std;

int main() {
    map<string, vector<string>> trls;
    map<string, set<string>> stop_to_trls;

    cout << "Добро пожаловать в систему управления движением троллейбусов!\n";
    cout << "Доступные команды:\n";
    cout << "  CREATE_TRL <имя> <остановка1> <остановка2> ... <остановкаN>\n";
    cout << "  TRL_IN_STOP <остановка>\n";
    cout << "  STOPS_IN_TRL <имя троллейбуса>\n";
    cout << "  TRLS\n";
    cout << "Введите команды:\n";

    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "CREATE_TRL") {
            string name;
            iss >> name;
            vector<string> stops;
            string stop;
            while (iss >> stop) {
                stops.push_back(stop);
            }
            create_trl(name, stops, trls, stop_to_trls);
        } else if (command == "TRL_IN_STOP") {
            string stop;
            iss >> stop;
            trl_in_stop(stop, stop_to_trls);
        } else if (command == "STOPS_IN_TRL") {
            string name;
            iss >> name;
            stops_in_trl(name, trls, stop_to_trls);
        } else if (command == "TRLS") {
            print_trls(trls);
        } else {
            cout << "Неизвестная команда. Повторите ввод.\n";
        }
    }

    return 0;
}
