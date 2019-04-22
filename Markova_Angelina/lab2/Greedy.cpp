#include <iostream>
#include <cstring>
#include <vector>
#include <climits>

#define Alphabet 26

struct Check {
    bool passed; //показывает пройдена ли вершина
    int index;   //вершина из которой пришли
    Check(): passed(false), index(0) {} //конструктор по умолчанию
    Check(bool passed_the_vertex, int index_prev): passed (passed_the_vertex), index (index_prev) {}
};

class Greedy_algorithm {
private:
    double graph[Alphabet][Alphabet]; //матрица смежности
    std:: vector <int> result;
public:
    Greedy_algorithm(int start) { //инициализация
        result.push_back(start);
        for(int i = 0; i < Alphabet; i++)
            memset(graph[i], 0.0, Alphabet * sizeof(double));
    }

    ~Greedy_algorithm() {
        result.clear();
    }

    void insert_paths(int i, int j, double path_length) { //заполнение длин путей графа
        graph[i][j] = path_length;
    }

    void print_matrix() { //вывод матрицы смежности
        for(int i = 0; i < Alphabet; i++) {
            for(int j = 0; j < Alphabet; j++)
                std:: cout << graph[i][j] << " ";
            std:: cout << std:: endl;
        }
    }

    void print(char start) { //вывод результата
        for(int i = 0; i < result.size(); i++)
            std:: cout <<(char)(result[i] + start);
        std:: cout << std:: endl;
    }

    int find_min(std:: vector <Check> &check_vertex, int i, int end) { //i - строка, в которой ищем
        double min = INT_MAX;
        int res = 0;
        for(int j = 0; j < Alphabet; j ++) {
            if(graph[i][j] != 0 && check_vertex[j].passed == false && min > graph[i][j]) {
                min = graph[i][j];
                res = j;
            }
        }
        return res;
    }

    void algorithm(std:: vector <Check> &check_vertex, int i, int end) {
        if(i == end) return;
        int min = find_min(check_vertex, i, end);
        if(min != 0) {
            result.push_back(min);
            check_vertex[min].passed = true;
            check_vertex[min].index = i;
        }
        else {
            result.pop_back();
            check_vertex[min].passed = true;
            min = check_vertex[i].index;
        }
        algorithm(check_vertex, min, end);
        return;
    }
};

int main() {
    char start, finish, from, to;
    double path_length;
    std:: cin >> start >> finish;
    std:: vector <Check> check_vertex(Alphabet, {false, 0});
    check_vertex[start - 'a'].passed = true;
    check_vertex[start - 'a'].index = start - 'a';
    Greedy_algorithm graph(start - 'a');
    while(std:: cin >> from >> to >> path_length) {
        graph.insert_paths(from - 'a', to - 'a', path_length);
    }
    graph.algorithm(check_vertex, start - 'a', finish - 'a');
    graph.print('a');
    check_vertex.clear();
    return 0;
}
