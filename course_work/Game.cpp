#include "Game.h"
//Окно вывода
sf::RenderWindow Game::window(sf::VideoMode(798, 966), "Pac-Man", sf::Style::Close);
//Меню игры
Menu Game::menu("startMenu.png", 0, 0, 0, 0, 798, 966);
//Метод для обновления информации окна
void Game::Update()
{
    if(window.isOpen())
    {
        window.clear();
        menu.gameMenu(window);
        window.display();
    }
}
//Метод для проверки существования окна
bool Game::IsOpen()
{
    if(!window.isOpen())
        return false;
    sf::Event event;
    if (menu.getPauseTime() > 300 && menu.getConditionStartMenu())
        throw ExceptionLongTimeNoActive(2,"The window is closed, because there is more than 5 minutes in no active");
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            throw ExceptionWindowClose(1, "The window is closed by user");
    }
    return true;
}
//Метод для закрытия окна
void Game::windowClose(bool saving)
{
    window.close();
    if(saving)
        menu.saveGame();
    else
        exit(-1);
}
//Конструктор по умолчанию
Game::~Game() = default;
//Деструктор по умолчанию
Game::Game()
{
}
//Метод для инициализации состояния звуков и музыки
void Game::GameInit()
{
    sf::Image icon;
    icon.loadFromFile("imagesCourseWork/icon.png");
    window.setIcon(48, 48, icon.getPixelsPtr());
    menu.menuInit();
}

