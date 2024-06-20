#ifndef SEM_3_GHOST_H
#define SEM_3_GHOST_H
const int INF = 1e9;
#include "Entity.h"
#include <vector>
#include <queue>
#include <windows.h>
class Map;
class Menu;
// Класс для реализации привидений
class Ghost : public Entity{
private:
    std::string name; // Имя
    static bool unPower; // Состояние силы Pac-Man'a
    static bool pursuit; // Состояние преследования
    Coordinates<float> target; // Цель на карте
    static sf::Clock pursuitTime; // Время преследования
    sf::Music pursuitMusic; // Музыка преследования
    // Поиск в ширину
     std::vector<Coordinates<float> > bfs(Map& map, Coordinates<float> pacman);
    //Метод для генерации случайных координат на карте
    Coordinates<float> randomCoordinates(Map& map);
public:
//Конструктор с параметрами
    Ghost(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H, std::string Name);
//Метод для обновления положения привидения на карте
    void update(float aliveTime, float spawn, Map &map, Coordinates<float> pacman, int healthPacman);
//Метод для столкновения привидения с картой
    void interactionWithMap(Map& map);
//Метод для получения состояния преследования
    bool getPursuit();
//Метод для обнуления количества жизней
    void setHealth();
//Метод для перезапуска время преследования
    static void restartPursuitTime();
//Метод для установки состояния преследования
    static void setUnPower(bool temp);
//Метод для получения времени преследования
    float getPursuitTime();
//Метод для получения количества жизней
    int getHealth();
//Метод для сброса до начала игры
    void resetGhost();
//Метод для сохранения в бинарный файл
    void saveGhost(std::ofstream& file);
//Метод для считывания с бинарного файла
    void loadGhost(std::ifstream& file);
//Метод для получения статуса музыки
    bool getPursuitMusicStatusPlaying();
//Метод для управления музыкой
    void setMusic(bool Music);
//Деструктор по умолчанию
    ~Ghost() override;
};


#endif //SEM_3_GHOST_H
