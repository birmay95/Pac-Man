#include "OptionsMenu.h"
#include "Menu.h"
// Конструктор с параметрами
OptionsMenu::OptionsMenu(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H) :
Item("optionsMenu.png", 0, 0, 0, 0, 798, 966),
conditionOptionsMenu(0),
conditionHelp(false),
conditionMusicTap(true),
conditionSoundTap(true),
conditionMusic(false),
conditionSound(false),
sound("sound.png", 222, 292, 0, 0, 351, 131),
music("music.png", 222, 292 + 165, 0, 0, 351, 131),
help("help.png", 222, 292 + 330, 0, 0, 351, 131),
helpMenu("helpMenu.png", 0, 0, 0, 0, 798, 966)
{
    enterBuffer.loadFromFile("audioCourseWork/enter.wav");
    enter.setBuffer(enterBuffer);
    enter.setVolume(40);
    arrowBuffer.loadFromFile("audioCourseWork/duck.wav");
    arrow.setBuffer(arrowBuffer);
    arrow.setVolume(40);
    allTimeMusic.openFromFile("audioCourseWork/allTimeMusic.wav");
    allTimeMusic.setLoop(true);
    allTimeMusic.setVolume(0);
    allTimeMusic.play();
}
// Метод для реализации меню настроек
void OptionsMenu::optionsGame(sf::RenderWindow &window)
{
    optionsEngine(window);
    if(conditionOptionsMenu == 0)
        return;
    this->draw(window);
    if(conditionOptionsMenu == 1 && conditionSound)
        sound = "soundPressed.png";
    else if(conditionOptionsMenu == 1 && !conditionSound)
        sound = "unSoundPressed.png";
    else if(conditionSound)
        sound = "sound.png";
    else if(!conditionSound)
        sound = "unSound.png";
    sound.draw(window);
    if(conditionOptionsMenu == 2 && conditionMusic)
        music = "musicPressed.png";
    else if (conditionOptionsMenu == 2 && !conditionMusic)
        music = "unMusicPressed.png";
    else if(conditionMusic)
        music = "music.png";
    else if(!conditionMusic)
        music = "unMusic.png";
    music.draw(window);
    if(conditionOptionsMenu == 3)
        help = "helpPressed.png";
    else
        help = "help.png";
    help.draw(window);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        arrow.play();
        conditionOptionsMenu++;
        if(conditionOptionsMenu == 4)
            conditionOptionsMenu = 1;
        Sleep(150);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        arrow.play();
        conditionOptionsMenu--;
        if(conditionOptionsMenu == 0)
            conditionOptionsMenu = 3;
        Sleep(150);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        conditionOptionsMenu = 0;
        Menu::processEscapeFromOptions();
        Sleep(150);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        enter.play();
        if (conditionOptionsMenu == 1)
            conditionSoundTap = true;
        else if (conditionOptionsMenu == 2)
            conditionMusicTap = true;
        else if (conditionOptionsMenu == 3)
        {
            conditionHelp = true;
            conditionOptionsMenu = 0;
        }
        Sleep(150);
    }
}
// Метод для обработки нажатия кнопок меню
void OptionsMenu::optionsEngine(sf::RenderWindow &window)
{
    optionsEngine();
    if(conditionHelp)
        helpGame(window);
}
// Метод для вывода окна 'HELP'
void OptionsMenu::helpGame(sf::RenderWindow &window)
{
    helpMenu.draw(window);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        conditionHelp = false;
        conditionOptionsMenu = 1;
        Sleep(150);
    }
}
// Метод для управления звуками
void OptionsMenu::soundPlay(bool key)
{
    if(key)
        arrow.play();
    else
        enter.play();
}
// Метод для сохранения состояний звуков и музыки
void OptionsMenu::saveSoundAndMusic(std::ofstream& file)
{
    file.write(reinterpret_cast<char*>(&conditionMusic), sizeof(conditionMusic));
    file.write(reinterpret_cast<char*>(&conditionSound), sizeof(conditionSound));
}
// Метод для загрузки состояний звуков и музыки
void OptionsMenu::loadSoundAndMusic()
{
    std::ifstream file("filesCourseWork/Game.bin", std::ios::binary);
    try
    {
        if(!file)
            throw ExceptionFileOpening(3, "The file 'Game.bin' can not be opened, that's why it has been created\n");
    }
    catch(ExceptionFileOpening& ex)
    {
        ex.processEvent(false);
        std::fstream File("filesCourseWork/Game.bin", std::ios::out | std::ios::binary);
        File.put(false);
        File.put(false);
        File.close();
        file.open("filesCourseWork/Game.bin");
        if(!file)
            throw ExceptionFileOpening(4, "The file 'Game.bin' can not be opened\n");
    }
    file.read(reinterpret_cast<char*>(&conditionMusic), sizeof(conditionMusic));
    file.read(reinterpret_cast<char*>(&conditionSound), sizeof(conditionSound));
    if(conditionMusic)
        conditionMusic = false;
    else conditionMusic = true;
    if(conditionSound)
        conditionSound = false;
    else conditionSound = true;
    file.close();
}
// Метод для инициализации меню настроек
void OptionsMenu::setConditionOptionsMenuOne()
{
    conditionOptionsMenu = 1;
}
// Метод для управления громкостью музыки и звуков
void OptionsMenu::setAudio(int Sound, int Music)
{
    Menu::setAudio(Sound, Music);
    if(Sound == 0)
    {
        enter.setVolume(0);
        arrow.setVolume(0);
    }
    else if(Sound == 1)
    {
        enter.setVolume(40);
        arrow.setVolume(40);
    }
    if(Music == 0)
        allTimeMusic.setVolume(0);
    else if(Music == 1)
        allTimeMusic.setVolume(30);
}
// Метод для управления звуками и музыкой
void OptionsMenu::musicManage(bool condition)
{
    if(condition)
        allTimeMusic.play();
    else
        allTimeMusic.pause();
}
// Метод для обработки нажатий кнопок звуков и музыки
void OptionsMenu::optionsEngine()
{
    if(conditionSoundTap)
    {
        if(conditionSound)
        {
            conditionSound = false;
            setAudio(0, 2);
        }
        else
        {
            conditionSound = true;
            setAudio(1, 2);
        }
        conditionSoundTap = false;
    }
    if(conditionMusicTap)
    {
        if(conditionMusic)
        {
            conditionMusic = false;
            setAudio(2, 0);
        }
        else
        {
            conditionMusic = true;
            setAudio(2, 1);
        }
        conditionMusicTap = false;
    }
}
// Метод для получения состояния меню настроек
int OptionsMenu::getConditionOptionsMenu() {
    return conditionOptionsMenu || conditionHelp;
}
// Деструктор по умолчанию
OptionsMenu::~OptionsMenu() = default;