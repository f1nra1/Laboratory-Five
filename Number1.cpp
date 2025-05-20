#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <set>

using namespace std;

const int MAX_PER_CELL = 10;
const int NUM_ZONES = 3;
const int NUM_SHELVES = 14;
const int NUM_SECTIONS = 6;
const int NUM_LEVELS = 20;
const int TOTAL_CELLS = NUM_ZONES * NUM_SHELVES * NUM_SECTIONS * NUM_LEVELS;
const int TOTAL_CAPACITY = TOTAL_CELLS * MAX_PER_CELL;

map<string, map<string, int>> warehouse; // адрес -> (товар -> количество)
set<string> all_addresses;

char zones[] = {'A', 'B', 'V'};

void help() {
    cout << "\nДоступные команды:\n"
         << "  ADD <товар> <кол-во> <адрес>     - добавить товар\n"
         << "  REMOVE <товар> <кол-во> <адрес>  - удалить товар\n"
         << "  INFO                             - информация о складе\n"
         << "  EXIT                             - выход из программы\n";
}

// Функция генерации всех ячеек
void init_addresses() {
    for (char zone : zones) {
        for (int shelf = 1; shelf <= NUM_SHELVES; ++shelf) {
            for (int section = 1; section <= NUM_SECTIONS; ++section) {
                for (int level = 1; level <= NUM_LEVELS; ++level) {
                    ostringstream addr;
                    addr << zone
                         << setw(2) << setfill('0') << shelf
                         << section
                         << level;
                    all_addresses.insert(addr.str());
                }
            }
        }
    }
}

bool is_valid_address(const string& addr) {
    return all_addresses.count(addr);
}

void add_item(const string& name, int count, const string& address) {
    if (count <= 0) {
        cout << "Ошибка: количество должно быть положительным.\n";
        return;
    }

    if (!is_valid_address(address)) {
        cout << "Ошибка: неверный адрес " << address << endl;
        return;
    }

    int total = 0;
    for (auto& item : warehouse[address]) {
        total += item.second;
    }

    if (total + count > MAX_PER_CELL) {
        cout << "Ошибка: ячейка " << address << " переполнена." << endl;
        return;
    }

    warehouse[address][name] += count;
    cout << "Добавлено: " << name << " x" << count << " в " << address << endl;
}

void remove_item(const string& name, int count, const string& address) {
    if (count <= 0) {
        cout << "Ошибка: количество должно быть положительным.\n";
        return;
    }

    if (!is_valid_address(address)) {
        cout << "Ошибка: неверный адрес " << address << endl;
        return;
    }

    if (warehouse[address][name] < count) {
        cout << "Ошибка: недостаточно товара в " << address << endl;
        return;
    }

    warehouse[address][name] -= count;
    if (warehouse[address][name] == 0) {
        warehouse[address].erase(name);
    }
    if (warehouse[address].empty()) {
        warehouse.erase(address);
    }

    cout << "Удалено: " << name << " x" << count << " из " << address << endl;
}

void info() {
    int used = 0;
    map<char, int> zone_used;

    for (const auto& [addr, items] : warehouse) {
        int cell_total = 0;
        for (const auto& [name, count] : items)
            cell_total += count;

        used += cell_total;
        char zone = addr[0];
        zone_used[zone] += cell_total;
    }

    cout << "\n--- Состояние склада ---\n";
    double total_percent = 100.0 * used / TOTAL_CAPACITY;
    cout << "Общая загруженность склада: " << fixed << setprecision(2) << total_percent << "%\n";

    for (char zone : zones) {
        double zone_capacity = NUM_SHELVES * NUM_SECTIONS * NUM_LEVELS * MAX_PER_CELL;
        double zone_percent = 100.0 * zone_used[zone] / zone_capacity;
        cout << "Зона " << zone << ": " << fixed << setprecision(2) << zone_percent << "%\n";
    }

    cout << "\nЗанятые ячейки:\n";
    for (const auto& [addr, items] : warehouse) {
        cout << addr << ": ";
        for (const auto& [name, count] : items) {
            cout << name << " " << count << "; ";
        }
        cout << endl;
    }

    cout << "\nПустые ячейки:\n";
    for (const string& addr : all_addresses) {
        if (!warehouse.count(addr)) {
            cout << addr << " ";
        }
    }
    cout << "\n";
}

int main() {
    init_addresses();
    help(); // Подсказка при запуске

    string line;
    while (true) {
        cout << "\n> ";
        getline(cin, line);
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "ADD") {
            string name, address;
            int count;
            iss >> name >> count >> address;
            add_item(name, count, address);
        } else if (command == "REMOVE") {
            string name, address;
            int count;
            iss >> name >> count >> address;
            remove_item(name, count, address);
        } else if (command == "INFO") {
            info();
        } else if (command == "EXIT") {
            cout << "Завершение работы программы.\n";
            break;
        } else {
            cout << "Неизвестная команда.\n";
            help(); // Подсказка при ошибке
        }
    }
    return 0;
}