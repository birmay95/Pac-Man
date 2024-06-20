#ifndef SEM_3_MENU_H
#define SEM_3_MENU_H
#include "Exception.h"
#include "OptionsMenu.h"
#include "Tree.h"
#include "Tree.cpp"
#include "PacMan.h"
#include "Map.h"
#include "Ghost.h"
// Класс для реализации игрового процесса
class Menu : public Item
{
private:
    OptionsMenu optionsMenu; // Меню настроек
    Item lidersMenu;
    Item enterNickname;
    Item newGame;
    Item resume;
    Item liders;
    Item options;
    Item exit;
    static int conditionStartMenu; // состояние текущей кнопки
    bool conditionNewGame;
    bool conditionResume;
    bool conditionLiders;
    static bool conditionOptions;
    bool conditionExit;
    bool activeGame;
    static bool gameover; // состояние конца игры
    bool allTimeMusicPlaying;
    static Map map;
    static PacMan pacman;
    static Ghost Red;
    static Ghost Pink;
    static Ghost Cyan;
    static Ghost Orange;
    sf::Clock pauseTime;
    static float allPauseTime;
    std::string nickname;
    sf::Font fontNickname;
    sf::Text textNickname;
    std::vector<std::pair<std::string, int> > recordsMens;
// Метод для обновления положений объектов в окне
    void processGame(sf::RenderWindow& window);
// Метод для продолжения последней запущенной игры
    void resumeGame(sf::RenderWindow& window);
// Метод для вывода лидеров на окно
    void lidersGame(sf::RenderWindow& window);
// Метод для выхода из игры
    void exitGame(sf::RenderWindow& window);
// Метод для обработки конца игры и нажатия кнопок стартового меню
    bool menuEngine(sf::RenderWindow& window);
// Метод для проверки и сохранения рекордов
    void checkAndSaveRecords(sf::RenderWindow& window);
// Метод для загрузки рекордов
    void loadRecords();
// Метод для ввода имени игрока
    void enterNickName(sf::RenderWindow& window);
// Метод для загрузки последней игры
    void loadGame();
// Метод для проверки строки на отличный от enter символ
    bool checkEnter();
public:
// Конструктор с параметрами
    Menu(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H);
// Метод для реализации стартового меню
    void gameMenu(sf::RenderWindow& window);
// Метод для сохранения игры
    void saveGame();
// Метод для получения времени паузы
    static float getAllPauseTime();
// Метод для установки конца игры
    static void setGameOver(sf::RenderWindow& window);
// Метод для получения состояния стартового меню
    int getConditionStartMenu();
// Метод для управления музыкой и звуками
    static void setAudio(int Sound, int Music);
// Метод для обработки нажатия клавиши 'Escape'
    static void processEscapeFromOptions();
// Метод для получения времени паузы
    float getPauseTime();
// Метод для инициализации состояний звуков и музыки
    void menuInit();
// Деструктор по умолчанию
    ~Menu() override;
};

#endif //SEM_3_MENU_H
