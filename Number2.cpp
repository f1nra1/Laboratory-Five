#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>
#include <random>
#include <ctime>
#include <sstream>
using namespace std;

struct Patient {
    string ticket;
    int duration;
};

struct Window {
    int total_time = 0;
    vector<Patient> assigned;
};

string generate_ticket() {
    static mt19937 rng(time(nullptr));
    int number = rng() % 1000;
    stringstream ss;
    ss << "T" << setw(3) << setfill('0') << number;
    return ss.str();
}

int main() {
    int window_count;
    cout << ">>> Введите кол-во окон\n<<< ";
    cin >> window_count;
    cin.ignore();

    queue<Patient> queue;
    string input;

    while (true) {
        cout << "<<< ";
        getline(cin, input);

        if (input.substr(0, 7) == "ENQUEUE") {
            int duration = stoi(input.substr(8));
            string ticket = generate_ticket();
            queue.push({ticket, duration});
            cout << ">>> " << ticket << endl;
        }
        else if (input == "DISTRIBUTE") {
            // Инициализация окон
            vector<Window> windows(window_count);

            // Распределение пациентов по окнам (жадным методом)
            while (!queue.empty()) {
                Patient p = queue.front();
                queue.pop();

                // Найти окно с минимальной текущей загрузкой
                int min_idx = 0;
                for (int i = 1; i < window_count; ++i) {
                    if (windows[i].total_time < windows[min_idx].total_time)
                        min_idx = i;
                }

                windows[min_idx].assigned.push_back(p);
                windows[min_idx].total_time += p.duration;
            }

            // Вывод результата
            for (int i = 0; i < window_count; ++i) {
                cout << ">>> Окно " << (i + 1)
                     << " (" << windows[i].total_time << " минут): ";

                for (size_t j = 0; j < windows[i].assigned.size(); ++j) {
                    cout << windows[i].assigned[j].ticket;
                    if (j + 1 < windows[i].assigned.size()) cout << ", ";
                }
                cout << endl;
            }
            break; // Завершаем программу после DISTRIBUTE
        }
        else {
            cout << ">>> Неизвестная команда.\n";
        }
    }

    return 0;
}
