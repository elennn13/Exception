#include <iostream>
#include <exception>// подкл библ хранящей в себе базовый класс, описывающий исключения
#include <string>
#include <fstream>// подкл библ для работы с файловыми потоками

double divide(double num1, double num2) { //  функция divide бросает исключение
    if (num2 == 0.)
        throw std::invalid_argument("деление на ноль");// класс exception 
    return num1 / num2;
}

int input_int() { // функция принимает число от пользователя 
    std::string tmp;
    std::getline(std::cin, tmp);
    return std::stoi(tmp); // stoi бросается исключение
}




class Person {

private:
    std::string name;
    unsigned int age;
    const unsigned int max_age = 110;

public:
    Person() : age(0){}
    Person(std::string name, unsigned int age) {
        if (age > max_age)
            throw std::invalid_argument("возраст не входит в допустимый диапазон");
        this->age  = age;
        this->name = name;
    }
    
void print() {
    std::cout << "Имя: " << name << std::endl;
    std::cout << "Возраст: " << age << std::endl;
}
};


// функция тестировки
void test_person(std::string name, int age) {
    static unsigned int test_number = 0;
    std::cout << "---Тест№" << ++test_number << "---\n";
    try {
        Person tmp(name, age);
        tmp.print();
    }
    catch (const std::invalid_argument& ex) {
        std::cout << "Обнаружена ошибка: " << ex.what() << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    int n, m;

    // Обработка исключений
    
    std::cout << "Введите первое число ->";
    std::cin >> n;
    try { // блок try пробует выполнить, если не получается то блок прерывается
        std::cout << "Введите второе число ->";
        std::cin >> m;
        if (m == 0)
            throw "деление на ноль"; // бросаем исключение
        if (m > 1'000'000)
            throw "слишком большой делитель";
        std::cout << n << " / " << m << n / m << std::endl;
}
    catch (int ex) { // если бросили throw(исключение) то catch  должен это поймать  и выполнить
        std::cout << "Ошибка! Делить на 0 нельзя!\n";
    }
    catch (const char* ex) {
        std::cout << "Обнаружена ошибка: " << ex << std::endl;
    }


// Бросок исключения из функции

std::cout << "Введите первое число ->";
std::cin >> n;
std::cout << "Введите второе число ->";
std::cin >> m;
try {
std::cout << n << " / " << m << " = " << divide(n, m) << std::endl;
}
    catch (const std::exception& ex) {
        std::cout << "Обнаружена ошибка: " << ex.what() << std::endl;
    }

// Поимка стандартных исключений 

try {
    std::cout << "Введите число -> ";
    n = input_int(); // вводится число от пользователя
    std::cout << "Вы ввели число " << n << std::endl;
}
catch (const std::exception& ex) {
    std::cout << "Возникла ошибка: " << ex.what() << std::endl;
}

// Управление исключениями в потоке ввода вывода
    
    std::ifstream in; // объект класса ifstream для чтения данных из файла
    in.exceptions(
        std::ios::badbit | 
        std::ios::failbit |
        std::ios::eofbit); // подключение исключений 
    try {
        in.open("file.txt"); // открываем файл
        std::cout << "Файл открыт.\n";
    }
    catch (const std::ifstream::failure& ex) {
        std::cout << "Ошибка открытия файла: " << ex.what() << std::endl;
        std::cout << "Код ошибки: " << ex.code() << std::endl;
    }

    // if (in.is_open()) // проверить открыли ли мы файл или нет
    // std::cout << "файл открыт.\n";
    // in.close(); // закрыть файл
    // }
    // else
    // std::cout << "Ошибка открытия файлаю\n";
    test_person("Иван", 25);
    test_person("Родион", -10);
    test_person("Светлана", 18);
    test_person("Логан", 200);





    return 0;
}
