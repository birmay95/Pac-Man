#ifndef SEM_3_MAP_H
#define SEM_3_MAP_H
#include "Item.h"
#include "PacMan.h"
#include "Ghost.h"
#include <iomanip>
#include <algorithm>
const int HEIGHT_MAP = 23; // Высота карты
const int WIDTH_MAP = 21; // Ширина карты
class Menu;
//Класс для реализации игровой карты
class Map : public Item
{
private:
    // Карта, представленная массивом
    int basicMap[HEIGHT_MAP][WIDTH_MAP] = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
            { 1, 1, 3, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 3, 1 },
            { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
            { 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1 },
            { 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1 },
            { 1, 1, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1 },
            { 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 4, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1 },
            { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
            { 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1 },
            { 1, 1, 3, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 3, 1 },
            { 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1 },
            { 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1 },
            { 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
            { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
    sf::Font fontPacman;
    sf::Font fontText;
    sf::Font fontPursuit;
    sf::Text textPoints;
    sf::Text Points;
    sf::Text textScore;
    sf::Text Score;
    sf::Text textAliveTime;
    sf::Text AliveTime;
    sf::Text textPursuitTime;
    sf::Text PursuitTime;
    sf::Text textEnergizerTime;
    sf::Text EnergizerTime;
    sf::Text Pursuit;
    // Обновленная карта со значениями соседей
    std::pair<int, int> convertedMap[HEIGHT_MAP][WIDTH_MAP];
    std::vector<int> fruits; // Фрукты
    int points; // Количество точек
// Метод для генерации случайных координат
    Coordinates<int> randomCoordinates();
    sf::Music victoryMusic; // Победная музыка
public:
// Конструктор с параметрами
    Map(sf::String f, float x_image, float y_image, float x, float y, float w, float h);
// Метод для обновления карты
    void init(sf::RenderWindow& window, PacMan& pacman, Ghost& ghost);
    // Шаблонная перегрузка скобок
    template<typename T>
    int& operator()(T y, T x)
    {
        int i(y), j(x);
        return basicMap[i][j];
    }
    // Шаблонная перегрузка скобок
    template<typename T>
    int& operator()(Coordinates<T> coordinates)
    {
        int i(coordinates.y), j(coordinates.x);
        return basicMap[i][j];
    }
// Метод для удаления фрукта
    void setMinusFruit(int temp);
// Метод для уменьшения оставшихся точек
    void setPointsMinusOne();
//Метод для сброса до начала игры
    void resetMap();
// Метод для сохранения в бинарный файл
    void saveMap(std::ofstream& file);
// Метод для считывания с бинарного файла
    void loadMap(std::ifstream& file);
// Метод для получения количества точек
    int getPoints();
// Метод для получения состояния музыки
    bool getVictoryMusicStatusPlaying();
// Метод для управления музыкой
    void setMusic(bool Music);
// Метод для остановки музыки
    void stopVictoryMusic();
// Деструктор по умолчанию
    ~Map() override;
};
#endif //SEM_3_MAP_H