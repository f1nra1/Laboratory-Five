#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

void print_help() {
    cout << "Доступные команды:\n"
         << "NEW_STUDENTS number    - Добавить (если number > 0) или удалить (если number < 0) студентов\n"
         << "SUSPICIOUS number      - Отметить студента с номером number как подозрительного (в топ-лист на отчисление)\n"
         << "IMMORTAL number        - Сделать студента с номером number неприкасаемым (удалить из топ-листа)\n"
         << "TOP-LIST               - Показать отсортированный список студентов для отчисления\n"
         << "SCOUNT                 - Показать количество студентов в топ-листе\n\n"
         << "Введите количество студентов: \n"
         << endl;
}

int main() {
    print_help();  // выводим подсказку
    int initial_count;
    cin >> initial_count; // исходное число студентов

    if (initial_count < 0) {
        cout << "Incorrect" << endl;
        return 1;
    }

    vector<int> students;
    set<int> top_list;
    set<int> immortal;

    for (int i = 1; i <= initial_count; ++i) {
        students.push_back(i);
    }

    string command;
    while (cin >> command) {
        if (command == "NEW_STUDENTS") {
            int number;
            cin >> number;
            if (number == 0) {
                cout << "Добро пожаловать 0 студентов!" << endl;
                continue;
            }
            if (number > 0) {
                int start = (int)students.size() + 1;
                for (int i = 0; i < number; ++i) {
                    students.push_back(start + i);
                }
                cout << "Добро пожаловать " << number << " студентов!" << endl;
            } else {
                int remove_count = -number;
                if (remove_count > (int)students.size()) {
                    cout << "Incorrect" << endl;
                    continue;
                }
                for (int i = 0; i < remove_count; ++i) {
                    int removed_student = students.back();
                    students.pop_back();
                    top_list.erase(removed_student);
                    immortal.erase(removed_student);
                }
                cout << "Прощайте " << remove_count << " студентов!" << endl;
            }
        } else if (command == "SUSPICIOUS") {
            int num;
            cin >> num;
            if (num < 1 || num > (int)students.size()) {
                cout << "Incorrect" << endl;
                continue;
            }
            if (immortal.count(num) == 0) {
                top_list.insert(num);
            }
            cout << "Подозрительный студент: " << num << endl;
        } else if (command == "IMMORTAL") {
            int num;
            cin >> num;
            if (num < 1 || num > (int)students.size()) {
                cout << "Incorrect" << endl;
                continue;
            }
            immortal.insert(num);
            top_list.erase(num);
            cout << "Студент " << num << " помилован!" << endl;
        } else if (command == "TOP-LIST") {
            cout << "Список студентов на отчисление:";
            if (top_list.empty()) {
                cout << " пуст" << endl;
            } else {
                vector<int> sorted_list(top_list.begin(), top_list.end());
                sort(sorted_list.begin(), sorted_list.end());
                for (size_t i = 0; i < sorted_list.size(); ++i) {
                    if (i > 0) cout << ",";
                    cout << " Студент " << sorted_list[i];
                }
                cout << endl;
            }
        } else if (command == "SCOUNT") {
            cout << "В списке на отчисление " << top_list.size() << " студентов" << endl;
        } else {
            cout << "Incorrect" << endl;
        }
    }

    return 0;
}
