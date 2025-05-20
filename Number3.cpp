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
    cout << "  CREATE_TRL <имя> <остановка1> <остановка2> ...\n";
    cout << "  TRL_IN_STOP <остановка>\n";
    cout << "  STOPS_IN_TRL <имя троллейбуса>\n";
    cout << "  TRLS\n";
    cout << "Введите команды:\n";

    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string command_str;
        iss >> command_str;

        auto cmd = parse_command(command_str);
        if (!cmd) {
            cout << "Неизвестная команда. Повторите ввод.\n";
            continue;
        }

        switch (*cmd) {
            case Type::CREATE_TRL: {
                string name;
                iss >> name;
                vector<string> stops;
                string stop;
                while (iss >> stop) {
                    stops.push_back(stop);
                }
                if (stops.size() < 2) {
                    cout << "Ошибка: необходимо указать хотя бы две остановки для маршрута " << name << ".\n";
                } else {
                    create_trl(name, stops, trls, stop_to_trls);
                }
                break;
            }
            case Type::TRL_IN_STOP: {
                string stop;
                iss >> stop;
                trl_in_stop(stop, stop_to_trls);
                break;
            }
            case Type::STOPS_IN_TRL: {
                string name;
                iss >> name;
                stops_in_trl(name, trls, stop_to_trls);
                break;
            }
            case Type::TRLS: {
                print_trls(trls);
                break;
            }
        }
    }

    return 0;
}
