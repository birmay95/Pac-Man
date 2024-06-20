#include "Tree.h"
// Конструктор без параметров
template <typename T1, typename T2>
Tree<T1, T2>::Tree(): first(nullptr) {};
// Метод для получения корня
template <typename T1, typename T2>
Elem<T1, T2>* Tree<T1, T2>::get_first()
{
    return first;
}
// Метод для обновления дерева после добавления
template <typename T1, typename T2>
void Tree<T1, T2>::add(std::pair<T1, T2> temp)
{
    first = push(first, temp, first);
}
// Метод для добавления элемента в дерево
template <typename T1, typename T2>
Elem<T1, T2>* Tree<T1, T2>::push(Elem<T1, T2>* node, std::pair<T1, T2> x, Elem<T1, T2>* prev)
{
    if (node == nullptr)
    {
        node = new Elem<T1, T2>;
        node->data = x;
        node->height = 1;
        node->right = nullptr;
        node->left = nullptr;
        node->prev = prev;
        return node;
    }
    if (x.second < node->data.second)
        node->left = push(node->left, x, node);
    else
        node->right = push(node->right, x, node);
    return balance(node);
}
// Метод для удаления элемента из дерева
template <typename T1, typename T2>
Elem<T1, T2>* Tree<T1, T2>::pop(Elem<T1, T2>* node, std::pair<T1, T2> x, bool& fl)
{
    if (node == nullptr)
        return node;
    else if (x.second < node->data.second && x.first != node->data.first)
        node->left = pop(node->left, x, fl);
    else if (x.second > node->data.second && x.first != node->data.first)
        node->right = pop(node->right, x, fl);
    else if (node->right != nullptr && node->left != nullptr)
    {
        Elem<T1, T2>* n = node;
        n = n->right;
        while (n->left != nullptr)
            n = n->left;
        node->data = n->data;
        if (n->prev != node)
        {
            n->prev->left = n->right;
            if(n->right != nullptr)
                n->right->prev = n->prev;
        }
        else
        {
            n->prev->right = n->right;
            if(n->right != nullptr)
                n->right->prev = n->prev;
        }
        fl = true;
        delete n;
    }
    else
    {
        Elem<T1, T2>* temp = node;
        if (node->right == nullptr && node->left == nullptr)
            node = nullptr;
        else if (node->right != nullptr)
        {
            node = node->right;
            node->prev = temp->prev;
        }
        else if (node->left != nullptr)
        {
            node = node->left;
            node->prev = temp->prev;
        }
        fl = true;
        if(temp == first)
            first = node;
        delete temp;
    }
    return node;
}
// Метод для удаления дерева
template <typename T1, typename T2>
void Tree<T1, T2>::del_tree(Elem<T1, T2>* node)
{
    if (node != nullptr)
    {
        del_tree(node->left);
        del_tree(node->right);
        delete node;
    }
    first = nullptr;
}
// Метод для проверки имен на совпадение
template <typename T1, typename T2>
void Tree<T1, T2>::pre_order(Elem<T1, T2>* node, std::string& nickname, bool& fl, int value)
{
    if(node != nullptr)
    {
        if(node->data.first == nickname && value <= node->data.second)
            fl = false;
        if(node->data.first == nickname && value > node->data.second)
        {
            bool flag(false);
            pop(first, node->data,flag);
            if(flag)
                first = balanceAfterPop(first);
        }
        pre_order(node->left, nickname, fl, value);
        pre_order(node->right, nickname, fl, value);
    }
    else
        return;
}
// Метод для обновления лидеров с дерева
template<typename T1, typename T2>
void Tree<T1, T2>::getLidersTree(Elem<T1, T2>* node, std::vector<std::pair<std::string, int>> &recordsMens)
{
    if(node != nullptr)
    {
        getLidersTree(node->right, recordsMens);
        if(recordsMens.size() < 3)
            recordsMens.push_back(node->data);
        getLidersTree(node->left, recordsMens);
    }
    else
        return;
}
// Метод для балансировки дерева после удаления
template<typename T1, typename T2>
Elem<T1, T2> *Tree<T1, T2>::balanceAfterPop(Elem<T1, T2>* node)
{
    if(node != nullptr)
    {
        node->left = balanceAfterPop(node->left);
        node->right = balanceAfterPop(node->right);
        return balance(node);
    }
    else
        return node;
}
// Метод для получения высоты узла
template<typename T1, typename T2>
int Tree<T1, T2>::height(Elem<T1, T2> *node)
{
    return (node? node->height: 0);
}
// Метод для получения разности высот поддеревьев
template<typename T1, typename T2>
int Tree<T1, T2>::balanceFactor(Elem<T1, T2>* node)
{
    return height(node->right) - height(node->left);
}
// Метод для обновления высоты узла
template<typename T1, typename T2>
void Tree<T1, T2>::fixHeight(Elem<T1, T2>* node)
{
    int heightLeft = height(node->left);
    int heightRight = height(node->right);
    node->height = (heightLeft > heightRight?heightLeft:heightRight) + 1;
}
// Метод для балансировки дерева
template<typename T1, typename T2>
Elem<T1, T2> *Tree<T1, T2>::balance(Elem<T1, T2> *node)
{
    fixHeight(node);
    if(balanceFactor(node) == -2)
    {
        if(balanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if(balanceFactor(node) == 2)
    {
        if(balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}
// Метод для реализации левого поворота дерева
template<typename T1, typename T2>
Elem<T1, T2> *Tree<T1, T2>::rotateLeft(Elem<T1, T2> *node)
{
    Elem<T1, T2>* temp = node->right;
    temp->prev = node->prev;
    node->prev = temp;
    node->right = temp->left;
    temp->left = node;
    fixHeight(node);
    fixHeight(temp);
    return temp;
}
// Метод для реализации правого поворота дерева
template<typename T1, typename T2>
Elem<T1, T2> *Tree<T1, T2>::rotateRight(Elem<T1, T2> *node)
{
    Elem<T1, T2>* temp = node->left;
    temp->prev = node->prev;
    node->prev = temp;
    node->left = temp->right;
    temp->right = node;
    fixHeight(node);
    fixHeight(temp);
    return temp;
}
// Деструктор
template<typename T1, typename T2>
Tree<T1, T2>::~Tree()
{
    del_tree(first);
}
// Метод для сохранения элементов дерева
template<typename T1, typename T2>
void Tree<T1, T2>::saveLiders(Elem<T1, T2> *node, std::ofstream& file)
{
    if(node != nullptr)
    {
        saveLiders(node->right, file);
        file << node->data.first << " " << node->data.second << "\n";
        saveLiders(node->left, file);
    }
    else
        return;
}