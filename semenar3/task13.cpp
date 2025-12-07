#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

bool isErrorValue(double temp) {
    return temp < -100.0 || temp > 200.0;
}

int main() {
    vector<double> temperatures;
    
    temperatures.push_back(50.5);
    temperatures.push_back(150.0);
    temperatures.push_back(-150.0);
    temperatures.push_back(180.5);
    temperatures.push_back(250.0);
    temperatures.push_back(80.2);
    temperatures.push_back(-120.0);
    temperatures.push_back(120.8);
    temperatures.push_back(300.0);
    temperatures.push_back(90.1);
    temperatures.push_back(-50.0);
    temperatures.push_back(210.0);
    
    cout << fixed << setprecision(1);
    cout << "Исходные данные температуры двигателя:" << endl;
    cout << "======================================" << endl;
    
    for (size_t i = 0; i < temperatures.size(); i++) {
        cout << "[" << i << "] " << temperatures[i] << "°C";
        if (isErrorValue(temperatures[i])) {
            cout << " (ОШИБКА)";
        }
        cout << endl;
    }
    
    cout << "======================================" << endl;
    cout << "Общее количество измерений: " << temperatures.size() << endl;
    
    vector<double>::iterator new_end = remove_if(temperatures.begin(), temperatures.end(), isErrorValue);
    temperatures.erase(new_end, temperatures.end());
    
    cout << "\nОчищенные данные температуры двигателя:" << endl;
    cout << "======================================" << endl;
    
    if (temperatures.empty()) {
        cout << "Все данные были удалены как ошибочные" << endl;
    } else {
        for (size_t i = 0; i < temperatures.size(); i++) {
            cout << "[" << i << "] " << temperatures[i] << "°C" << endl;
        }
    }
    
    cout << "======================================" << endl;
    cout << "Количество корректных измерений: " << temperatures.size() << endl;
    
    return 0;
}