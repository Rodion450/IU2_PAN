#include <iostream>

using namespace std;

int main() {
    int N;
    cout << "Введите количество самолетов: ";
    cin >> N;
    
    double maxAcceleration = -1e9;
    int leaderIndex = -1;
    
    cout << "\n";
    
    for (int i = 0; i < N; i++) {
        double mass, area, thrust, CL, CD;
        
        cout << "=== Самолет " << i+1 << " ===" << endl;
        cout << "Масса (кг): ";
        cin >> mass;
        cout << "Площадь крыла (м²): ";
        cin >> area;
        cout << "Тяга (Н): ";
        cin >> thrust;
        cout << "CL: ";
        cin >> CL;
        cout << "CD: ";
        cin >> CD;
        
        const double rho = 1.225;
        const double g = 9.81;
        
        double V = sqrt((2 * mass * g) / (rho * area * CL));
        double lift = 0.5 * rho * V * V * area * CL;
        double drag = 0.5 * rho * V * V * area * CD;
        double acceleration = (thrust - drag) / mass;
        
        cout << "\nРезультаты:" << endl;
        cout << "Скорость: " << V << " м/с" << endl;
        cout << "Подъемная сила: " << lift << " Н" << endl;
        cout << "Сопротивление: " << drag << " Н" << endl;
        cout << "Ускорение: " << acceleration << " м/с²" << endl;
        cout << "-------------------------\n" << endl;
        
        if (acceleration > maxAcceleration) {
            maxAcceleration = acceleration;
            leaderIndex = i;
        }
    }
    
    if (leaderIndex != -1) {
        cout << "Самолет с наибольшим ускорением: Самолет " << leaderIndex + 1 << endl;
        cout << "Максимальное ускорение: " << maxAcceleration << " м/с²" << endl;
    }
    
    return 0;
}