#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    vector<double> positions;
    
    positions.push_back(0.0);
    positions.push_back(50.0);
    positions.push_back(120.0);
    positions.push_back(180.0);
    positions.push_back(210.0);
    positions.push_back(200.0);
    positions.push_back(150.0);
    positions.push_back(80.0);
    positions.push_back(10.0);
    positions.push_back(0.0);
    
    cout << fixed << setprecision(1);
    cout << "Координаты ракеты по оси Y:" << endl;
    cout << "==========================" << endl;
    
    for (size_t i = 0; i < positions.size(); i++) {
        cout << "[" << i << "] " << positions[i] << " м" << endl;
    }
    
    cout << "==========================" << endl;
    
    if (positions.size() < 2) {
        cout << "Недостаточно данных для вычисления пути" << endl;
        return 0;
    }
    
    vector<double> displacements(positions.size());
    
    for (size_t i = 1; i < positions.size(); i++) {
        displacements[i] = positions[i] - positions[i-1];
    }
    
    double total_distance = 0.0;
    for (size_t i = 1; i < positions.size(); i++) {
        total_distance += fabs(displacements[i]);
    }
    
    cout << "\nРазности координат (смещения):" << endl;
    cout << "=============================" << endl;
    
    for (size_t i = 1; i < displacements.size(); i++) {
        cout << "От [" << i-1 << "] к [" << i << "]: " 
             << setw(6) << displacements[i] << " м" << endl;
    }
    
    cout << "=============================" << endl;
    cout << "Суммарный пройденный путь: " << total_distance << " м" << endl;
    
    double net_displacement = positions.back() - positions.front();
    cout << "Чистое перемещение: " << net_displacement << " м" << endl;
    
    return 0;
}