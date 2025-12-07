#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    vector<double> x_coordinates;
    
    x_coordinates.push_back(50.0);
    x_coordinates.push_back(30.0);
    x_coordinates.push_back(50.0);
    x_coordinates.push_back(80.0);
    x_coordinates.push_back(30.0);
    x_coordinates.push_back(60.0);
    x_coordinates.push_back(80.0);
    x_coordinates.push_back(90.0);
    x_coordinates.push_back(60.0);
    x_coordinates.push_back(50.0);
    x_coordinates.push_back(70.0);
    x_coordinates.push_back(30.0);
    
    cout << fixed << setprecision(1);
    cout << "Исходные координаты X:" << endl;
    cout << "======================" << endl;
    
    for (size_t i = 0; i < x_coordinates.size(); i++) {
        cout << "[" << i << "] " << x_coordinates[i] << " м" << endl;
    }
    
    cout << "======================" << endl;
    cout << "Количество координат: " << x_coordinates.size() << endl;
    
    sort(x_coordinates.begin(), x_coordinates.end());
    
    cout << "\nОтсортированные координаты X:" << endl;
    cout << "============================" << endl;
    
    for (size_t i = 0; i < x_coordinates.size(); i++) {
        cout << "[" << i << "] " << x_coordinates[i] << " м" << endl;
    }
    
    vector<double>::iterator unique_end = unique(x_coordinates.begin(), x_coordinates.end());
    x_coordinates.erase(unique_end, x_coordinates.end());
    
    cout << "\nУникальные координаты X (без дубликатов):" << endl;
    cout << "========================================" << endl;
    
    if (x_coordinates.empty()) {
        cout << "Нет уникальных координат" << endl;
    } else {
        for (size_t i = 0; i < x_coordinates.size(); i++) {
            cout << "[" << i << "] " << x_coordinates[i] << " м" << endl;
        }
    }
    
    cout << "========================================" << endl;
    cout << "Количество уникальных координат: " << x_coordinates.size() << endl;
    
    return 0;
}