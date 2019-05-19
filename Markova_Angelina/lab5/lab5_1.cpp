#include <iostream>
#include <vector>
#include <map>

struct leaf {            //лист
    bool check;          //конечная ли вершина
    int sample;          //номер образца
    int suffix_link;     //суффиксная ссылка, int тк кол-во вершин больше, чем букв в алфавите
    int previous_vertex; //родитель текущей вершины
    char curr_vertex;    //значение ребра от родителя к текущей вершине
    std:: map <char, int> edge;      //соседи
    std:: map <char, int> auto_move; //движение автомата

    leaf(int previous, char vertex) {
        check = false;
        sample = 0;
        if(previous == 0) suffix_link = 0;
        else suffix_link = -1;
        previous_vertex = previous;
        curr_vertex = vertex;
    }
};

class Aho_Korasik {
    std:: vector <leaf> tree;   //бор - дерево, в котором каждая вершина обозначает какую-то строку
    std:: vector <std:: string> result;
    int number_of_tree_nodes;   //кол-во узлов дерева
public:
    Aho_Korasik() {
        tree.push_back(leaf(0, 0)); //создаём корень дерева
        number_of_tree_nodes = 1;
    }

    void add_pattern(std:: string &P, int count_str) {   //добавление нового шаблона
        int temp = 0;                                    //начинаем идти с корня
        result.push_back(P);
        for(int num = 0; num < P.length(); num++) {
            if(tree[temp].edge.find(P[num]) == tree[temp].edge.end()) { //если от вершины нет путей в текущую
                tree.push_back(leaf(temp, P[num]));                     //создаём новое ветвление
                tree[temp].edge[P[num]] = number_of_tree_nodes++;       //увеличиваем счётчик
            }
            temp = tree[temp].edge[P[num]];    //движение по дереву
        }
        tree[temp].check = true;               //temp - конечная вершина данного шаблона
        tree[temp].sample = count_str;         //заполнили номер образца
    }

    int get_suffix_link(int index_vertex) {         //vertex - индекс вершины в tree
        if(tree[index_vertex].suffix_link == -1) {  //если ещё не считали
            if(index_vertex == 0 || tree[index_vertex].previous_vertex == 0) //если корень или предок является корнем
                tree[index_vertex].suffix_link = 0;
            else
                tree[index_vertex].suffix_link = get_auto_move(get_suffix_link(tree[index_vertex].previous_vertex), tree[index_vertex].curr_vertex);
        }
        return tree[index_vertex].suffix_link;
    }

    int get_auto_move(int index_vertex, char symbol) {      //заполнение движения
        if(tree[index_vertex].auto_move.find(symbol) == tree[index_vertex].auto_move.end())
            if(tree[index_vertex].edge.find(symbol) != tree[index_vertex].edge.end())
                tree[index_vertex].auto_move[symbol] = tree[index_vertex].edge[symbol];
            else if(index_vertex == 0)
                tree[index_vertex].auto_move[symbol] = 0;
            else
                tree[index_vertex].auto_move[symbol] = get_auto_move(get_suffix_link(index_vertex), symbol);
        return tree[index_vertex].auto_move[symbol];
    }

    void algorithm(std:: string T) {
        int ver = 0;
        for(int i = 0; i < T.length(); i++) {
            ver = get_auto_move(ver, T[i]);
            for(int j = ver; j != 0; j = get_suffix_link(j))
                if(tree[j].check)
                    std:: cout << i - result[tree[j].sample - 1].size() + 2 << " " << tree[j].sample << std:: endl; //result[tree[j].sample - 1].size() - длина шаблона
        }
    }

    void print() {
        for(int i = 0; i < number_of_tree_nodes; i++) {
            std:: cout << "[" << (char) tree[i].curr_vertex << "]" << std:: endl;
            std:: cout << (char) tree[tree[i].previous_vertex].curr_vertex << "(" << tree[i].previous_vertex << ")" << " ---> " << (char) tree[i].curr_vertex << std:: endl;
            std:: cout << "number: " << i << std:: endl;
            std:: cout << "suffix_link: " << tree[i].suffix_link << std:: endl;
            std:: cout << "the end? ";
            if(tree[i].check) std:: cout << "yes" << std:: endl;
            else std:: cout << "no" << std:: endl;
            std:: cout << "number_of_sample: " << tree[i].sample << std:: endl;
            std:: cout << "_____________________" << std:: endl;
        }
        std:: cout << std:: endl;
        for(int i = 0; i < result.size(); i++)
            std:: cout << result[i];
        std:: cout << std:: endl;
    }
};

int main() {
    Aho_Korasik object;
    std:: string text, pattern;
    int count;
    std:: cin >> text >> count;
    for(int i = 0; i < count; i++) {
        std:: cin >> pattern;
        object.add_pattern(pattern, i + 1);    //считаем образцы с единицы
    }
    object.algorithm(text);
    //object.print();
    return 0;
}
