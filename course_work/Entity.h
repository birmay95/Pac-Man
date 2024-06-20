#ifndef SEM_3_ENTITY_H
#define SEM_3_ENTITY_H
#include "Item.h"
// Класс существа, которое может передвигаться по карте
class Entity : public Item
{
protected:
    float dx; // Перемещение по оси х
    float dy; // Перемещение по оси у
    int health; // Количество жизней
    float speed; // Скорость
    enum class Direction { Neutral = 0, Up, Down, Left, Right}dir; // Направление существа
public:
    //Конструктор с параметрами
    Entity(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H);
    //Метод для обновления положения существа на карте
    virtual void update();
    //Деструктор по умолчанию
    ~Entity() override;
};
#endif //SEM_3_ENTITY_H
