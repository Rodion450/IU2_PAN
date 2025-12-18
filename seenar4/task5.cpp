#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;

// Структура для хранения правила валидации
struct ValidationRule {
    double minValue;
    double maxValue;
    string fieldName;
    
    ValidationRule() : minValue(0), maxValue(0) {}
    ValidationRule(double min, double max, const string& name) 
        : minValue(min), maxValue(max), fieldName(name) {}
    
    bool isValid(double value) const {
        return value >= minValue && value <= maxValue;
    }
};

// Класс для валидации данных
class DataValidator {
private:
    map<string, ValidationRule> rules;
    vector<string> validationResults;
    int totalChecks;
    int passedChecks;
    
public:
    DataValidator() : totalChecks(0), passedChecks(0) {
        // Инициализация базовых правил
        rules["x"] = ValidationRule(-10000, 10000, "координата X");
        rules["y"] = ValidationRule(-10000, 10000, "координата Y");
        rules["z"] = ValidationRule(0, 5000, "высота Z");
        rules["speed"] = ValidationRule(0, 300, "скорость");
        rules["acceleration"] = ValidationRule(0, 20, "ускорение");
    }
    
    // Добавление правила валидации
    void addValidationRule(const string& field, double min, double max) {
        rules[field] = ValidationRule(min, max, field);
    }
    
    // Валидация координат
    bool validateCoordinates(double x, double y, double z) {
        bool isValid = true;
        string result;
        
        if (!rules["x"].isValid(x)) {
            result = "Координата X: ОШИБКА - значение " + toString(x) + 
                     " выходит за допустимый диапазон [" + 
                     toString(rules["x"].minValue) + ", " + 
                     toString(rules["x"].maxValue) + "]";
            validationResults.push_back(result);
            isValid = false;
            totalChecks++;
        } else {
            totalChecks++;
            passedChecks++;
        }
        
        if (!rules["y"].isValid(y)) {
            result = "Координата Y: ОШИБКА - значение " + toString(y) + 
                     " выходит за допустимый диапазон [" + 
                     toString(rules["y"].minValue) + ", " + 
                     toString(rules["y"].maxValue) + "]";
            validationResults.push_back(result);
            isValid = false;
            totalChecks++;
        } else {
            totalChecks++;
            passedChecks++;
        }
        
        if (!rules["z"].isValid(z)) {
            result = "Координаты: ОШИБКА - высота " + toString(z) + 
                     " превышает максимум " + toString(rules["z"].maxValue);
            validationResults.push_back(result);
            isValid = false;
            totalChecks++;
        } else {
            totalChecks++;
            passedChecks++;
        }
        
        return isValid;
    }
    
    // Валидация скорости
    bool validateSpeed(double speed) {
        totalChecks++;
        
        if (rules["speed"].isValid(speed)) {
            passedChecks++;
            return true;
        } else {
            string result = "Скорость: ОШИБКА - скорость " + toString(speed) + 
                           " превышает максимум " + toString(rules["speed"].maxValue);
            validationResults.push_back(result);
            return false;
        }
    }
    
    // Валидация ускорения
    bool validateAcceleration(double acceleration) {
        totalChecks++;
        
        if (rules["acceleration"].isValid(acceleration)) {
            passedChecks++;
            return true;
        } else {
            string result = "Ускорение: ОШИБКА - ускорение " + toString(acceleration) + 
                           " превышает максимум " + toString(rules["acceleration"].maxValue);
            validationResults.push_back(result);
            return false;
        }
    }
    
    // Генерация отчета валидации
    void generateValidationReport() {
        ofstream reportFile("validation_report.txt");
        
        if (!reportFile.is_open()) {
            cerr << "Ошибка создания файла отчета!" << endl;
            return;
        }
        
        reportFile << "=== ОТЧЕТ ВАЛИДАЦИИ ДАННЫХ ===" << endl;
        reportFile << "Дата: " << getCurrentDateTime() << endl;
        reportFile << "=================================" << endl;
        
        if (validationResults.empty()) {
            reportFile << "Все данные прошли валидацию успешно." << endl;
        } else {
            reportFile << "Обнаружены следующие ошибки:" << endl;
            reportFile << "---------------------------------" << endl;
            
            for (size_t i = 0; i < validationResults.size(); i++) {
                reportFile << validationResults[i] << endl;
            }
        }
        
        reportFile << "=================================" << endl;
        reportFile << "СТАТИСТИКА:" << endl;
        
        double score = getValidationScore();
        reportFile << "Всего проверок: " << totalChecks << endl;
        reportFile << "Успешных проверок: " << passedChecks << endl;
        reportFile << "Неуспешных проверок: " << (totalChecks - passedChecks) << endl;
        reportFile << fixed << setprecision(1);
        reportFile << "Процент валидных данных: " << score << "%" << endl;
        
        if (score == 100.0) {
            reportFile << "СТАТУС: ВСЕ ДАННЫЕ ВАЛИДНЫ" << endl;
        } else if (score >= 80.0) {
            reportFile << "СТАТУС: УДОВЛЕТВОРИТЕЛЬНО" << endl;
        } else if (score >= 50.0) {
            reportFile << "СТАТУС: ТРЕБУЕТ ВНИМАНИЯ" << endl;
        } else {
            reportFile << "СТАТУС: КРИТИЧЕСКИЕ ОШИБКИ" << endl;
        }
        
        reportFile.close();
        cout << "Отчет сохранен в файл: validation_report.txt" << endl;
    }
    
    // Получение процента валидных данных
    double getValidationScore() {
        if (totalChecks == 0) return 0.0;
        return (passedChecks * 100.0) / totalChecks;
    }
    
    // Вывод текущего состояния валидации
    void printValidationState() {
        cout << "\n=== ТЕКУЩЕЕ СОСТОЯНИЕ ВАЛИДАЦИИ ===" << endl;
        cout << "Всего проверок: " << totalChecks << endl;
        cout << "Успешных: " << passedChecks << endl;
        cout << "Ошибок: " << validationResults.size() << endl;
        cout << fixed << setprecision(1);
        cout << "Процент валидных данных: " << getValidationScore() << "%" << endl;
        
        if (!validationResults.empty()) {
            cout << "\nОшибки валидации:" << endl;
            for (size_t i = 0; i < validationResults.size(); i++) {
                cout << "  " << (i+1) << ". " << validationResults[i] << endl;
            }
        }
    }
    
    // Очистка результатов валидации
    void clearValidationResults() {
        validationResults.clear();
        totalChecks = 0;
        passedChecks = 0;
    }
    
    // Проверка всех типов данных
    void validateAll(double x, double y, double z, double speed, double acceleration) {
        clearValidationResults();
        
        cout << "=== ПОЛНАЯ ВАЛИДАЦИЯ ДАННЫХ ===" << endl;
        cout << "Проверяемые значения:" << endl;
        cout << "  X: " << x << endl;
        cout << "  Y: " << y << endl;
        cout << "  Z: " << z << endl;
        cout << "  Скорость: " << speed << endl;
        cout << "  Ускорение: " << acceleration << endl;
        
        validateCoordinates(x, y, z);
        validateSpeed(speed);
        validateAcceleration(acceleration);
    }
    
private:
    // Вспомогательная функция для преобразования числа в строку
    string toString(double value) {
        stringstream ss;
        ss << fixed << setprecision(1) << value;
        return ss.str();
    }
    
    // Получение текущей даты и времени
    string getCurrentDateTime() {
        // Упрощенная версия (можно использовать <ctime> для реальной даты)
        return "2024-12-15 10:30:00";
    }
};

// Главная функция
int main() {
    cout << "=== СИСТЕМА ВАЛИДАЦИИ ДАННЫХ ===" << endl;
    
    // Создаем валидатор
    DataValidator validator;
    
    // Пример 1: Данные из условия задачи
    cout << "\n=== ПРИМЕР 1: ДАННЫЕ ИЗ УСЛОВИЯ ЗАДАЧИ ===" << endl;
    
    double x1 = 5000.5;
    double y1 = 3000.2;
    double z1 = 10000.0;
    double speed1 = 350.0;
    double acceleration1 = 25.0;
    
    validator.validateAll(x1, y1, z1, speed1, acceleration1);
    validator.printValidationState();
    validator.generateValidationReport();
    
    // Пример 2: Корректные данные
    cout << "\n=== ПРИМЕР 2: КОРРЕКТНЫЕ ДАННЫЕ ===" << endl;
    
    DataValidator validator2;
    
    double x2 = 1000.0;
    double y2 = 2000.0;
    double z2 = 3000.0;
    double speed2 = 250.0;
    double acceleration2 = 15.0;
    
    validator2.validateAll(x2, y2, z2, speed2, acceleration2);
    validator2.printValidationState();
    validator2.generateValidationReport();
    
    // Пример 3: Смешанные данные
    cout << "\n=== ПРИМЕР 3: СМЕШАННЫЕ ДАННЫЕ ===" << endl;
    
    DataValidator validator3;
    
    // Добавляем пользовательские правила
    validator3.addValidationRule("temperature", -50, 50);
    validator3.addValidationRule("pressure", 900, 1100);
    
    // Проверяем различные данные
    cout << "\nВалидация координат:" << endl;
    if (validator3.validateCoordinates(500.0, 600.0, 4500.0)) {
        cout << "  Координаты: OK" << endl;
    }
    
    cout << "\nВалидация скорости:" << endl;
    if (validator3.validateSpeed(280.0)) {
        cout << "  Скорость: OK" << endl;
    }
    
    cout << "\nВалидация ускорения:" << endl;
    if (validator3.validateAcceleration(25.0)) {
        cout << "  Ускорение: OK" << endl;
    } else {
        cout << "  Ускорение: ОШИБКА" << endl;
    }
    
    validator3.printValidationState();
    
    // Демонстрация работы с пользовательским вводом
    cout << "\n=== ИНТЕРАКТИВНАЯ ВАЛИДАЦИЯ ===" << endl;
    
    DataValidator interactiveValidator;
    char choice;
    
    do {
        double x, y, z, speed, accel;
        
        cout << "\nВведите координаты (x y z): ";
        cin >> x >> y >> z;
        
        cout << "Введите скорость: ";
        cin >> speed;
        
        cout << "Введите ускорение: ";
        cin >> accel;
        
        interactiveValidator.clearValidationResults();
        interactiveValidator.validateCoordinates(x, y, z);
        interactiveValidator.validateSpeed(speed);
        interactiveValidator.validateAcceleration(accel);
        
        interactiveValidator.printValidationState();
        
        cout << "\nСгенерировать отчет? (y/n): ";
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            interactiveValidator.generateValidationReport();
        }
        
        cout << "\nПродолжить? (y/n): ";
        cin >> choice;
        
    } while (choice == 'y' || choice == 'Y');
    
    // Вывод всех правил валидации
    cout << "\n=== ТЕКУЩИЕ ПРАВИЛА ВАЛИДАЦИИ ===" << endl;
    cout << "1. Координата X: [-10000.0, 10000.0]" << endl;
    cout << "2. Координата Y: [-10000.0, 10000.0]" << endl;
    cout << "3. Высота Z: [0.0, 5000.0]" << endl;
    cout << "4. Скорость: [0.0, 300.0]" << endl;
    cout << "5. Ускорение: [0.0, 20.0]" << endl;
    
    cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===" << endl;
    
    return 0;
}