#include "Entity.h"
//Конструктор с параметрами
Entity::Entity(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H) :
Item(F, X, Y, X_image, Y_image, W, H), speed(0), dx(0), dy(0), dir(Direction::Neutral), health(1) {}
//Метод для обновления положения существа на карте
void Entity::update()
{
    switch(dir)
    {
        case Direction::Right: dx = speed; dy = 0; break;
        case Direction::Left: dx = -speed; dy = 0; break;
        case Direction::Up: dx = 0; dy = -speed; break;
        case Direction::Down: dx = 0; dy = speed; break;
    }
    coord.x += dx;
    coord.y += dy;
    speed = 0;
    sprite.setPosition(coord.x, coord.y);
}
//Деструктор по умолчанию
Entity::~Entity() = default;
