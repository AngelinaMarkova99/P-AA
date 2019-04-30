#include <iostream>
#include <string>
#include <vector>

#define N 5000000

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

int Algorithm_KMP(std:: string &pattern, std:: string &text) {  //алгоритм Кнута-Морриса-Пратта
    Prefix_function(pattern);                                   //заполяем вектор
    int first = 0, second = 0, check = 0;
    for (int i = 0; i < pattern.size(); i++) {                  //пока не дошли до конца шаблона
        while (pattern[first] == text[second]) {
            check++;                                            //считаем длину пройденного "пути"
            first = (first + 1) % pattern.size();               //берём остаток, т.е учитываем циклический сдвиг
            second = (second + 1) % pattern.size();
            if (check == pattern.size()) return (second % pattern.size());
            i++;
        }
        check=0;                                                //при первом несовпадении счетчик обнуляем
        if (pattern[first] != text[second])
            if (first != 0) {
                first =  prefix[first - 1];
                i--;
            }
            else second++;
    }
    return -1;
}

int main() {
    std::string text_A,text_B;
    text_A.reserve(N);
    text_B.reserve(N);
    std::cin >> text_B >> text_A;
    if (text_A.size() - text_B.size()) {
        std::cout << -1;
        return 0;
    }
    std::cout << Algorithm_KMP(text_A,text_B) << std:: endl;
    return 0;
}
