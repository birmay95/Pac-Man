#ifndef SEM_3_PACMAN_H
#define SEM_3_PACMAN_H
#include "Entity.h"
#include "Ghost.h"
class Map;
class Menu;
// Класс для реализации персонажа Pac-Man
class PacMan : public Entity
{
private:
    bool energizer; // состояние силы
    int score; // очки
    sf::Clock energizerTime;
    sf::Clock aliveTime;
    float loadAliveTime; // загруженное время
    sf::Music energizerMusic;
    sf::Sound pointSound;
    sf::SoundBuffer pointSoundBuffer;
    sf::Sound fruitSound;
    sf::SoundBuffer fruitSoundBuffer;
    sf::Sound failSound;
    sf::SoundBuffer failSoundBuffer;
    sf::Sound killingGhostSound;
    sf::SoundBuffer killingGhostSoundBuffer;
    int countKillingGhosts; // количество съеденных привидений
public:
// Конструктор с параметрами
    PacMan(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H);
// Метод для обновления положения на карте
    void update() override;
// Метод для взаимодействия с картой
    void interactionWithMap(Map& map);
// Метод для взаимодействия с привидениями
    void interactionWithGhost(Ghost& ghost);
// Метод для установки финального количества очков
    void setFinalScore();
// Метод для получения количества очков
    int getScore();
// Метод для получения количества жизней
    int getHealth();
// Метод для получения состояния силы
    bool getEnergizer();
// Метод для получения количества времени силы
    float getEnergizerTime();
// Метод для получения времени существования
    float getAliveTime();
// Метод для получения загруженного времени
    float getLoadAliveTime();
// Метод для перезапуска времени силы
    void restartEnergizer();
// Метод для сброса объекта на начальное состояние
    void resetPacman();
// Метод для сохранения объекта в бинарный файл
    void savePacman(std::ofstream& file);
// Метод для загрузки объекта в бинарный файл
    void loadPacman(std::ifstream& file);
// Метод для остановки музыки во время силы
    void stopMusic();
// Метод для получения музыки во время силы
    bool getEnergizerMusicStatusPlaying();
// Метод для управления громкостью музыки и звуков
    void setAudio(int Sound, int Music);
// Деструктор по умолчанию
    ~PacMan() override;
};
#endif //SEM_3_PACMAN_H