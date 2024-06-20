#ifndef SEM_3_OPTIONSMENU_H
#define SEM_3_OPTIONSMENU_H
#include "Item.h"
class Menu;
// Класс для реализации меню настроек
class OptionsMenu : public Item
{
private:
    Item sound;
    Item music;
    Item help;
    Item helpMenu;
    int conditionOptionsMenu; // состояние текущих кнопок меню
    bool conditionSound;
    bool conditionMusic;
    bool conditionSoundTap;
    bool conditionMusicTap;
    bool conditionHelp;
    sf::Sound enter;
    sf::SoundBuffer enterBuffer;
    sf::Sound arrow;
    sf::SoundBuffer arrowBuffer;
    sf::Music allTimeMusic;
public:
// Конструктор с параметрами
    OptionsMenu(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H);
// Метод для обработки нажатия кнопок меню
    void optionsEngine(sf::RenderWindow& window);
// Метод для вывода окна 'HELP'
    void helpGame(sf::RenderWindow& window);
// Метод для управления громкостью музыки и звуков
    void setAudio(int Sound, int Music);
// Метод для получения состояния меню настроек
    int getConditionOptionsMenu();
// Метод для реализации меню настроек
    void optionsGame(sf::RenderWindow& window);
// Метод для управления звуками
    void soundPlay(bool key);
// Метод для управления звуками и музыкой
    void musicManage(bool condition);
// Метод для сохранения состояний звуков и музыки
    void saveSoundAndMusic(std::ofstream &file);
// Метод для загрузки состояний звуков и музыки
    void loadSoundAndMusic();
// Метод для инициализации меню настроек
    void setConditionOptionsMenuOne();
// Метод для обработки нажатий кнопок звуков и музыки
    void optionsEngine();
// Деструктор по умолчанию
    ~OptionsMenu() override;
};
#endif //SEM_3_OPTIONSMENU_H
