#include "Item.h"
//Конструктор с параметрами
Item::Item(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H):
file(F), coord(X, Y), picture(X_image, Y_image), width(W), height(H), currentFrame(0)
{
    image.loadFromFile("imagesCourseWork/" + file);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect (picture.x, picture.y, width, height));
    sprite.setPosition(coord.x, coord.y);
}
//Метод для отображения на окне объекта
void Item::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}
//Метод для получения координат
Coordinates<float> Item::getCoord()
{
    return coord;
}
//Конструктор без параметров
Item::Item() : width(0), height(0), currentFrame(0), picture(), coord() {}
//Перегрузка оператора присваивания
Item &Item::operator=(std::string fileName)
{
    file = fileName;
    image.loadFromFile("imagesCourseWork/" + file);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    return *this;
}
//Деструктор по умолчанию
Item::~Item() = default;
