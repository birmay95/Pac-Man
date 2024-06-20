#ifndef SEM_3_ITEM_H
#define SEM_3_ITEM_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
//Шаблонный класс координат
template <typename T>
class Coordinates
{
public:
    T x; //Координата по оси х
    T y; //Координата по оси у
    // Конструктор без параметров
    Coordinates(): x(0), y(0) {}
    //Конструктор без параметров
    Coordinates(T X, T Y): x(X), y(Y) {};
    //Перегрузка оператора сравнивания
    bool operator==(Coordinates<T> temp)
    {
        return (x == temp.x && y == temp.y);
    }
    //Перегрузка оператора сравнивания
    Coordinates& operator=(Coordinates temp)
    {
        x = temp.x;
        y = temp.y;
        return *this;
    }
    //Деструктор по умолчанию
    ~Coordinates() = default;
};
//Класс для изображения
class Item {
protected:
    Coordinates<float> picture; //Координаты изображения
    Coordinates<float> coord; //Координаты на карте
    float width; //Ширина изображения
    float height; //Высота изображения
    float currentFrame; // Текущее изображение
    sf::String file; // Имя файла изображения
    sf::Image image; // Изображение
    sf::Texture texture; //Текстура
    sf::Sprite sprite; // Спрайт изображения
public:
//Конструктор без параметров
    Item();
//Конструктор с параметрами
    Item(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H);
//Метод для отображения на окне объекта
    void draw(sf::RenderWindow& window);
//Метод для получения координат
    Coordinates<float> getCoord();
//Перегрузка оператора присваивания
    Item& operator=(std::string fileName);
//Деструктор по умолчанию
    virtual ~Item();
};
#endif //SEM_3_ITEM_H
