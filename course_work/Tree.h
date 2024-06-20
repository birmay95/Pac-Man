#ifndef SEM_3_TREE_H
#define SEM_3_TREE_H
#include <iostream>
#include <fstream>
#include <vector>
// Шаблонная структура узла дерева
template<typename T1 = std::string, typename T2 = int>
struct Elem
{
    std::pair<T1, T2> data;
    int height;
    struct Elem* right;
    struct Elem* left;
    struct Elem* prev;
};
// Шаблонный класс для реализации самобалансирующегося бинарного дерева
template <typename T1 = std::string, typename T2 = int>
class Tree
{
private:
    Elem<T1, T2>* first; // Указатель на корень
// Метод для получения высоты узла
    int height(Elem<T1, T2>* node);
// Метод для получения разности высот поддеревьев
    int balanceFactor(Elem<T1, T2>* node);
// Метод для обновления высоты узла
    void fixHeight(Elem<T1, T2>* node);
// Метод для реализации правого поворота дерева
    Elem<T1, T2>* rotateRight(Elem<T1, T2>* node);
// Метод для реализации левого поворота дерева
    Elem<T1, T2>* rotateLeft(Elem<T1, T2>* node);
// Метод для балансировки дерева
    Elem<T1, T2>* balance(Elem<T1, T2>* node);
// Метод для балансировки дерева после удаления
    Elem<T1, T2>* balanceAfterPop(Elem<T1, T2>* node);
public:
// Конструктор без параметров
    Tree();
// Метод для добавления элемента в дерево
    Elem<T1, T2>* push(Elem<T1, T2>* node, std::pair<T1, T2> x, Elem<T1, T2>* prev);
// Метод для удаления элемента из дерева
    Elem<T1, T2>* pop(Elem<T1, T2>* node, std::pair<T1, T2> x, bool& fl);
// Метод для удаления дерева
    void del_tree(Elem<T1, T2>* node);
// Метод для получения корня
    Elem<T1, T2>* get_first();
// Метод для обновления дерева после добавления
    void add(std::pair<T1, T2> temp);
// Метод для проверки имен на совпадение
    void pre_order(Elem<T1, T2>* node, std::string& nickname, bool &fl, int value);
// Метод для обновления лидеров с дерева
    void getLidersTree(Elem<T1, T2>* node, std::vector<std::pair<std::string, int> >& recordsMens);
// Метод для сохранения элементов дерева
    void saveLiders(Elem<T1, T2>* node, std::ofstream& file);
// Деструктор
    ~Tree();
};

#endif //SEM_3_TREE_H
