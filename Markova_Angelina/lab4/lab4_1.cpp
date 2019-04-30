#include <iostream>
#include <string>
#include <vector>

std:: vector <int> prefix;

void Prefix_function(std:: string &pattern) {      //префикс-функция
    prefix.assign(pattern.size(), 0);              //обнуляем вектор
    prefix[0] = 0;                                 //всегда равно 0
    int index = 1, current = 0;
    while (index < pattern.size()) {               //пока не дошли до конца шаблона
        if(pattern[index] == pattern[current]) {
            prefix[index] = current + 1;           //записываем указатель на символ, идущий после последнего совпавшего
            index++;                               //двигаемся вперёд по шаблону
            current++;
        }
        if(pattern[index] != pattern[current])     //если символы не совпали
            if(current == 0) {                     //если текущий на начале, т.е двигаться больше некуда
                prefix[index] = 0;                 //совпадений нет
                index++;                           //сравниваем следующий элемент с первым
            }
            else current = prefix[current - 1];    //переход на символ, предшествующий несовпавшему
    }
}

void Algorithm_KMP(std:: string &pattern) {        //алгоритм Кнута-Морриса-Пратта
    char symbol;                                   //считываемый символ строки
    bool check = false;                            //показывает встретили ли хоть один раз совпадение
    std:: cin >> symbol;
    int text = 0, image = 0;                       //начинаем сравнивать с первого символа строки и образа (шаблона)
    Prefix_function(pattern);
    while(true) {
        if(symbol == pattern[image]) {
            text++;
            image++;
            if(image == pattern.size()) {          //если дошли до конца шаблона
                if(check)                          //когда check = true
                    std:: cout << "," << text - pattern.size();
                else {
                    check = true;
                    std:: cout << text - pattern.size();
                }
                image = prefix[image - 1];         //переход на символ, предшествующий несовпавшему
            }
            if(!(std:: cin >> symbol)) break;      //если поток ввода пуст, то заканчиваем поиск подстроки
        }
        else {
            if(image == 0) {
                text++;
                if(!(std:: cin >> symbol)) break;
            }
            else image = prefix[image - 1];
        }
    }
    if(!check) std:: cout << -1;                   //нет ни одного совпадения в строке
}

int main() {
    std:: string pattern;
    std:: cin >> pattern;
    Algorithm_KMP(pattern);
    std:: cout << std:: endl;
    return 0;
}
