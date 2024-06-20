#include "Menu.h"
#include "OptionsMenu.h"
Map Menu::map("MapIcons.png", 0, 0, 0, 0, 42, 42);
PacMan Menu::pacman("pacmanIcons.png", 42 * 4, 42 * 3, 0, 0, 42, 42);
Ghost Menu::Pink("pacmanIcons.png", 42 * 9, 42 * 11, 4 * 42, 42, 42, 42, "Pink");
Ghost Menu::Red("pacmanIcons.png", 42 * 8, 42 * 11, 126, 0, 42, 42, "Red");
Ghost Menu::Cyan("pacmanIcons.png", 42 * 10, 42 * 11, 5 * 42, 2 * 42, 42, 42, "Cyan");
Ghost Menu::Orange("pacmanIcons.png", 42 * 9,  42 * 11, 6 * 42, 3 * 42, 42, 42, "Orange");
float Menu::allPauseTime(0);
bool Menu::gameover(false);
bool Menu::conditionOptions(false);
int Menu::conditionStartMenu(1);
// Конструктор с параметрами
Menu::Menu(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H)
        : Item("startMenu.png", 0, 0, 0, 0, 798, 966),
          conditionNewGame(false),
          conditionLiders(false),
          conditionExit(false),
          conditionResume(false),
          activeGame(false),
          recordsMens(3),
          allTimeMusicPlaying(true),
          lidersMenu("lidersMenu.png", 0, 0, 0, 0, 798, 966),
          optionsMenu("optionsMenu.png", 0, 0, 0, 0, 798, 966),
          enterNickname("enterNickname.png", 0, 0, 0, 0, 798, 966),
          newGame("newGame.png", 170, 291, 0, 0, 404, 138),
          resume("resume.png", 44, 485, 0, 0, 351, 131),
          liders("liders.png", 406, 566, 0, 0, 351, 131),
          options("options.png", 43, 686, 0, 0, 351, 131),
          exit("exit.png", 407, 763, 0, 0, 351, 131)
{
    fontNickname.loadFromFile("fontsCourseWork/nickname.ttf");
    textNickname.setFont(fontNickname);
    textNickname.setCharacterSize(75);
    textNickname.setFillColor(sf::Color::White);
    textNickname.setPosition(42*7 + 21, 42*10 - 10);
    loadRecords();
    optionsMenu.loadSoundAndMusic();
}
// Метод для реализации стартового меню
void Menu::gameMenu(sf::RenderWindow& window)
{
    if(menuEngine(window) || conditionStartMenu == 0)
        return;
    this->draw(window);
    if(conditionStartMenu == 1)
        newGame = "newGamePressed.png";
    else
        newGame = "newGame.png";
    newGame.draw(window);
    if(conditionStartMenu == 2)
        resume = "resumePressed.png";
    else
        resume = "resume.png";
    resume.draw(window);
    if(conditionStartMenu == 3)
        liders = "lidersPressed.png";
    else
        liders = "liders.png";
    liders.draw(window);
    if(conditionStartMenu == 4)
        options = "optionsPressed.png";
    else
        options = "options.png";
    options.draw(window);
    if(conditionStartMenu == 5)
        exit = "exitPressed.png";
    else
        exit = "exit.png";
    exit.draw(window);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        optionsMenu.soundPlay(true);
        conditionStartMenu++;
        if (conditionStartMenu == 6)
            conditionStartMenu = 1;
        Sleep(150);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        optionsMenu.soundPlay(true);
        conditionStartMenu--;
        if(conditionStartMenu == 0)
            conditionStartMenu = 5;
        Sleep(150);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        Sleep(150);
        exitGame(window);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        optionsMenu.soundPlay(false);
        if (conditionStartMenu == 1)
        {
            map.resetMap();
            pacman.resetPacman();
            Orange.resetGhost();
            Pink.resetGhost();
            Cyan.resetGhost();
            Red.resetGhost();
            activeGame = true;
            conditionNewGame = true;
            allPauseTime = 0;
        }
        else if (conditionStartMenu == 2)
        {
            conditionResume = true;
            allPauseTime += pauseTime.getElapsedTime().asSeconds();
        }
        else if (conditionStartMenu == 3)
            conditionLiders = true;
        else if (conditionStartMenu == 4)
        {
            conditionOptions = true;
            optionsMenu.setConditionOptionsMenuOne();
        }
        else if (conditionStartMenu == 5)
            conditionExit = true;
        conditionStartMenu = 0;
        Sleep(150);
    }
}
// Метод для обработки конца игры и нажатия кнопок стартового меню
bool Menu::menuEngine(sf::RenderWindow &window)
{
    if(pacman.getEnergizerMusicStatusPlaying() || Orange.getPursuitMusicStatusPlaying() || map.getVictoryMusicStatusPlaying())
    {
        optionsMenu.musicManage(false);
        allTimeMusicPlaying = false;
    }
    else if(!allTimeMusicPlaying)
    {
        optionsMenu.musicManage(true);
        allTimeMusicPlaying = true;
    }
    if(gameover)
    {
        conditionNewGame = true;
        conditionResume = false;
        checkAndSaveRecords(window);
        gameover = false;
        map.resetMap();
        Orange.resetGhost();
        Pink.resetGhost();
        Cyan.resetGhost();
        Red.resetGhost();
        pacman.resetPacman();
        map.stopVictoryMusic();
        allPauseTime = 0;
    }
    if(conditionNewGame == 1)
        processGame(window);
    else if(conditionResume == 1)
        resumeGame(window);
    else if(conditionOptions == 1)
        optionsMenu.optionsGame(window);
    else if(conditionLiders == 1)
        lidersGame(window);
    else if(conditionExit == 1)
    {
        exitGame(window);
        return true;
    }
    return false;
}
// Метод для обновления положений объектов в окне
void Menu::processGame(sf::RenderWindow &window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        conditionNewGame = false;
        conditionResume = false;
        conditionStartMenu = 1;
        Sleep(220);
        pauseTime.restart();
        return;
    }
    pacman.update();
    pacman.interactionWithMap(map);
    pacman.interactionWithGhost(Orange);
    pacman.interactionWithGhost(Red);
    pacman.interactionWithGhost(Cyan);
    pacman.interactionWithGhost(Pink);
    float time = pacman.getLoadAliveTime() + pacman.getAliveTime() - getAllPauseTime();
    Orange.update(time, 0, map, pacman.getCoord(), pacman.getHealth());
    Orange.interactionWithMap(map);
    Red.update(time, 3, map, pacman.getCoord(), pacman.getHealth());
    Red.interactionWithMap(map);
    Pink.update(time, 6, map, pacman.getCoord(), pacman.getHealth());
    Pink.interactionWithMap(map);
    Cyan.update(time, 9, map, pacman.getCoord(), pacman.getHealth());
    Cyan.interactionWithMap(map);
    map.init(window, pacman, Orange);
    Red.draw(window);
    Pink.draw(window);
    Cyan.draw(window);
    Orange.draw(window);
    pacman.draw(window);
}
// Метод для продолжения последней запущенной игры
void Menu::resumeGame(sf::RenderWindow &window)
{
    if(activeGame == 0)
    {
        loadGame();
        if(map.getPoints() == 0 || pacman.getHealth() == 0)
        {
            map.resetMap();
            pacman.resetPacman();
            Orange.resetGhost();
            Pink.resetGhost();
            Cyan.resetGhost();
            Red.resetGhost();
            conditionNewGame = true;
            conditionResume = false;
            allPauseTime = 0;
        }
        activeGame = true;
        if(pacman.getEnergizer())
        {
            pacman.restartEnergizer();
            Ghost::setUnPower(true);
        }
    }
    processGame(window);
}
// Метод для вывода лидеров на окно
void Menu::lidersGame(sf::RenderWindow &window)
{
    textNickname.setCharacterSize(75);
    lidersMenu.draw(window);
    textNickname.setString(recordsMens[0].first);
    textNickname.setPosition(42 * 5, 42 * 2 + 21);
    textNickname.setFillColor(sf::Color(251, 252, 3));
    window.draw(textNickname);
    std::ostringstream nicknameFirstScore;
    nicknameFirstScore << recordsMens[0].second;
    const sf::String nicknameFirstScoreString(nicknameFirstScore.str());
    textNickname.setString(nicknameFirstScoreString);
    textNickname.setPosition(42 * 11, 42 * 2 + 21);
    window.draw(textNickname);

    textNickname.setCharacterSize(60);
    textNickname.setString(recordsMens[1].first);
    textNickname.setPosition(42 * 7 + 10, 42 * 11 + 15 - 10);
    textNickname.setFillColor(sf::Color(236, 6, 235));
    window.draw(textNickname);
    textNickname.setCharacterSize(50);
    std::ostringstream nicknameSecondScore;
    nicknameSecondScore << recordsMens[1].second;
    const sf::String nicknameSecondScoreString(nicknameSecondScore.str());
    textNickname.setString(nicknameSecondScoreString);
    textNickname.setPosition(42 * 12 + 5, 42 * 11 + 15 - 3);
    window.draw(textNickname);

    textNickname.setCharacterSize(60);
    textNickname.setString(recordsMens[2].first);
    textNickname.setPosition(42 * 7 + 10, 42 * 16 - 10);
    textNickname.setFillColor(sf::Color(255, 204, 0));
    window.draw(textNickname);
    textNickname.setCharacterSize(50);
    std::ostringstream nicknameThirdScore;
    nicknameThirdScore << recordsMens[2].second;
    const sf::String nicknameThirdScoreString(nicknameThirdScore.str());
    textNickname.setString(nicknameThirdScoreString);
    textNickname.setPosition(42 * 12 + 5, 42 * 16 - 3);
    window.draw(textNickname);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        conditionLiders = false;
        conditionStartMenu = 3;
        textNickname.setCharacterSize(75);
        textNickname.setFillColor(sf::Color::White);
        textNickname.setPosition(42*7 + 21, 42*10 - 10);
        Sleep(150);
    }
}
// Метод для выхода из игры
void Menu::exitGame(sf::RenderWindow &window)
{
    saveGame();
    window.close();
}
// Метод для сохранения игры
void Menu::saveGame()
{
    std::ofstream file("filesCourseWork/Game.bin", std::ios::binary);
    try
    {
        if(!file)
            throw ExceptionFileOpening(3, "The file 'Game.bin' can not be opened\n");
    }
    catch(ExceptionFileOpening& ex)
    {
        ex.processEvent(false);
    }
    optionsMenu.saveSoundAndMusic(file);
    pacman.savePacman(file);
    Orange.saveGhost(file);
    Pink.saveGhost(file);
    Red.saveGhost(file);
    Cyan.saveGhost(file);
    map.saveMap(file);
    file.close();
}
// Метод для загрузки последней игры
void Menu::loadGame()
{
    std::ifstream file("filesCourseWork/Game.bin", std::ios::binary);
    try
    {
        if(!file)
            throw ExceptionFileOpening(3, "The file 'Game.bin' can not be opened\n");
    }
    catch(ExceptionFileOpening& ex)
    {
        ex.processEvent(false);
    }
    file.seekg(2 * sizeof(bool), std::ios::beg);
    int n;
    file.read(reinterpret_cast<char*>(&n), sizeof(n));
    if(!file.eof()) {
        file.seekg(-1 * sizeof(n), std::ios::cur);
        pacman.loadPacman(file);
        Orange.loadGhost(file);
        Pink.loadGhost(file);
        Red.loadGhost(file);
        Cyan.loadGhost(file);
        map.loadMap(file);
    }
    else
    {
        conditionResume = false;
        conditionNewGame = true;
    }
    file.close();
}
// Метод для получения времени паузы
float Menu::getAllPauseTime()
{
    return allPauseTime;
}
// Метод для ввода имени игрока
void Menu::enterNickName(sf::RenderWindow& window)
{
    nickname.clear();
    sf::Event Event;
    while (window.pollEvent(Event)) {}
    sf::Text Score;
    Score.setString("Your Score:");
    Score.setFont(fontNickname);
    Score.setPosition(7*42-25, 12*42+10);
    Score.setCharacterSize(80);
    sf::Text Points;
    std::ostringstream pointsChar;
    pointsChar << pacman.getScore();
    const sf::String pointsString(pointsChar.str());
    Points.setString(pointsString);
    Points.setFont(fontNickname);
    Points.setCharacterSize(100);
    Points.setPosition(8*42, 14*42-21);
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered && nickname.size() < 10)
            {
                if ((event.text.unicode >= '0' && event.text.unicode <= '9') || (event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z'))
                    nickname += static_cast<char>(event.text.unicode);
                textNickname.setString(nickname);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !nickname.empty())
            {
                nickname.pop_back();
                textNickname.setString(nickname);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && checkEnter())
            {
                Sleep(150);
                return;
            }
        }
        window.clear();
        enterNickname.draw(window);
        window.draw(Score);
        window.draw(Points);
        window.draw(textNickname);
        window.display();
    }
}
// Метод для установки конца игры
void Menu::setGameOver(sf::RenderWindow& window)
{
    gameover = true;
}
// Метод для проверки и сохранения рекордов
void Menu::checkAndSaveRecords(sf::RenderWindow& window)
{
    std::ifstream fileIn("filesCourseWork/Records.txt");
    try
    {
        if(!fileIn)
            throw ExceptionFileOpening(3, "The file 'Records.txt' can not be opened\n");
    }
    catch(ExceptionFileOpening& ex)
    {
        ex.processEvent(false);
    }
    std::pair<std::string, int> lidersLoad;
    char* buff;
    buff = new char[15];
    int n;
    Tree lidersTree;
    while(!fileIn.eof())
    {
        lidersLoad.first.clear();
        fileIn.getline(buff, 15, ' ');
        if (n = fileIn.gcount())
        {
            buff[n - 1] = '\0';
            lidersLoad.first = buff;
        }
        fileIn.getline(buff, 15, '\n');
        if (n = fileIn.gcount())
        {
            buff[n - 1] = '\0';
            lidersLoad.second = std::atoi(buff);
        }
        if(!lidersLoad.first.empty())
        {
            lidersTree.add(lidersLoad);
        }
    }
    delete[] buff;
    enterNickName(window);
    bool fl(true);
    lidersTree.pre_order(lidersTree.get_first(), nickname, fl, pacman.getScore());
    if(fl)
        lidersTree.add(std::pair<std::string, int>(nickname, pacman.getScore()));
    recordsMens.clear();
    lidersTree.getLidersTree(lidersTree.get_first(), recordsMens);
    std::ofstream fileOut("filesCourseWork/Records.txt");
    try
    {
        if (!fileOut.is_open())
            throw ExceptionFileOpening(4, "The file 'Records.txt' can not be opened\n");
    }
    catch(ExceptionFileOpening& ex)
    {
        ex.processEvent(false);
    }
    lidersTree.saveLiders(lidersTree.get_first(), fileOut);
    fileOut.close();
}
// Метод для загрузки рекордов
void Menu::loadRecords()
{
    std::ifstream fileIn("filesCourseWork/Records.txt");
    try
    {
        if(!fileIn)
            throw ExceptionFileOpening(3, "The file 'Records.txt' can not be opened, that's why it has been created\n");
    }
    catch(ExceptionFileOpening& ex)
    {
        ex.processEvent(false);
        std::fstream File("filesCourseWork/Records.txt", std::ios::out);
        File.close();
        fileIn.open("filesCourseWork/Records.txt");
        if(!fileIn)
            throw ExceptionFileOpening(4, "The file 'Records.txt' can not be opened\n");
        return;
    }
    char* buff = new char[15];
    int n, count(0);
    while(count < 3)
    {
        recordsMens[count].first.clear();
        fileIn.getline(buff, 15, ' ');
        if (n = fileIn.gcount()) {
            buff[n - 1] = '\0';
            recordsMens[count].first = buff;
        }
        fileIn.getline(buff, 15, '\n');
        if (n = fileIn.gcount()) {
            buff[n - 1] = '\0';
            recordsMens[count].second = std::atoi(buff);
        }
        count++;
    }
    delete[] buff;
    fileIn.close();
}
// Метод для получения времени паузы
float Menu::getPauseTime()
{
    return pauseTime.getElapsedTime().asSeconds();
}
// Метод для обработки нажатия клавиши 'Escape'
void Menu::processEscapeFromOptions()
{
    conditionOptions = false;
    conditionStartMenu = 4;
}
// Метод для управления музыкой и звуками
void Menu::setAudio(int Sound, int Music)
{
    if(Music == 0)
    {
        pacman.setAudio(2, 0);
        Orange.setMusic(false);
        Pink.setMusic(false);
        Cyan.setMusic(false);
        Red.setMusic(false);
        map.setMusic(false);
    }
    else if(Music == 1)
    {
        pacman.setAudio(2, 1);
        Orange.setMusic(true);
        Pink.setMusic(true);
        Cyan.setMusic(true);
        Red.setMusic(true);
        map.setMusic(true);
    }
    if(Sound == 0)
        pacman.setAudio(0, 2);
    else if(Sound == 1)
        pacman.setAudio(1, 2);
}
// Метод для инициализации состояний звуков и музыки
void Menu::menuInit()
{
    optionsMenu.optionsEngine();
}
// Метод для проверки строки на отличный от enter символ
bool Menu::checkEnter()
{
    std::string::iterator iter;
    for(iter = nickname.begin(); iter != nickname.end(); iter++)
    {
        if(*iter != '\r')
            return true;
    }
    return false;
}
// Метод для получения состояния стартового меню
int Menu::getConditionStartMenu() {
    return conditionStartMenu || optionsMenu.getConditionOptionsMenu() || conditionLiders;
}
// Деструктор по умолчанию
Menu::~Menu() = default;