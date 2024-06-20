#ifndef SEM_3_GAME_H
#define SEM_3_GAME_H
#include "Menu.h"
//Класс для реализации игрового процесса с обработкой на исключения
class Game
{
private:
    static sf::RenderWindow window; //Окно игры
    static Menu menu; //Меню игры
public:
    //Конструктор по умолчанию
    Game();
    //Метод для инициализации состояние звуков и музыки
    static void GameInit();
    //Метод для обновления информации окна
    static void Update();
    //Метод для проверки существования окна
    static bool IsOpen();
    //Метод для закрытия окна
    static void windowClose(bool saving);
    //Деструктор по умолчанию
    ~Game();
};
#endif //SEM_3_GAME_H
