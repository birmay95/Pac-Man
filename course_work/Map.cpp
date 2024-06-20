#include "Map.h"
#include "Menu.h"
// Метод для обновления карты
void Map::init(sf::RenderWindow& window, PacMan& pacman, Ghost& ghost)
{
    currentFrame += 0.005;
    if(currentFrame > 2)
        currentFrame -= 2;
    for(int i = 0; i < HEIGHT_MAP; i++)
    {
        for(int j = 1; j < WIDTH_MAP - 1; j++)
        {
            if(convertedMap[i][j].first == 1)
            {
                if (convertedMap[i][j - 1].first == 1)
                    convertedMap[i][j].second |= 8;
                if (convertedMap[i + 1][j].first == 1)
                    convertedMap[i][j].second |= 4;
                if (convertedMap[i][j + 1].first == 1  && j != 19)
                    convertedMap[i][j].second |= 2;
                if (convertedMap[i - 1][j].first == 1)
                    convertedMap[i][j].second |= 1;
                sprite.setTextureRect(sf::IntRect(42 * convertedMap[i][j].second, 0, 42, 42));
            }
            else if(basicMap[i][j] == 2)
                sprite.setTextureRect(sf::IntRect(0, 42, 42, 42));
            else if(basicMap[i][j] == 3)
                sprite.setTextureRect(sf::IntRect (42, 42 * int(currentFrame) + 42, 42, 42));
            else if(basicMap[i][j] == 4)
                sprite.setTextureRect(sf::IntRect (42 * 2 -1, 42, 42, 42));
            else if(basicMap[i][j] == 5)
                sprite.setTextureRect(sf::IntRect (42 * 3, 42, 42, 42));
            else if(basicMap[i][j] == 6)
                sprite.setTextureRect(sf::IntRect (42 * 4, 42, 42, 42));
            else if(basicMap[i][j] == 7)
                sprite.setTextureRect(sf::IntRect (42 * 5, 42, 42, 42));
            else if(basicMap[i][j] == 8)
                sprite.setTextureRect(sf::IntRect (42 * 6, 42, 42, 42));
            else
                sprite.setTextureRect((sf::IntRect(42 * 10, 42, 42, 42)));
            sprite.setPosition(static_cast<float>(j) * 42 - 42, static_cast<float>(i) * 42);
            window.draw(sprite);
        }
    }
    window.draw(textScore);
    std::ostringstream scoreChar;
    scoreChar << pacman.getScore();
    const sf::String scoreString(scoreChar.str());
    Score.setString(scoreString);
    Score.setPosition(168, 0);
    window.draw(Score);

    window.draw(textPoints);
    std::ostringstream pointsChar;
    pointsChar << points;
    const sf::String pointsString(pointsChar.str());
    Points.setString(pointsString);
    window.draw(Points);

    window.draw(textAliveTime);
    std::ostringstream aliveTime;
        float currentTime(pacman.getLoadAliveTime() + pacman.getAliveTime() - Menu::getAllPauseTime());
        int minutes(currentTime / 60);
        if(currentTime - minutes * 60 > 59.5 && currentTime - minutes * 60 < 61)
            aliveTime << "01:00";
        else
            aliveTime << std::setfill('0') << std::setw(2) << minutes << ":";
        if(currentTime - minutes * 60 < 1)
            aliveTime << "00";
        else if(currentTime - minutes * 60 > 9.5 && currentTime - minutes * 60 < 11)
            aliveTime << "10";
        else if(currentTime - minutes * 60 < 10)
            aliveTime << std::setfill('0') << std::setprecision(0) << std::setw(2) << currentTime - minutes * 60;
        else if(currentTime - minutes * 60 < 59.5 || currentTime - minutes * 60 > 61)
            aliveTime << std::setprecision(2) << std::setw(2) << currentTime - minutes * 60;
    const sf::String aliveTimeString(aliveTime.str());
    AliveTime.setString(aliveTimeString);
    window.draw(AliveTime);
    if(pacman.getEnergizer())
    {
        window.draw(textEnergizerTime);
        std::ostringstream energizerTime;
        if(pacman.getEnergizerTime() < 1)
            energizerTime << std::setprecision(1) << pacman.getEnergizerTime();
        else
            energizerTime << std::setprecision(2) << pacman.getEnergizerTime();
        const sf::String energizerTimeString(energizerTime.str());
        EnergizerTime.setString(energizerTimeString);
        window.draw(EnergizerTime);
    }
    if(ghost.getPursuit())
    {
        window.draw(textPursuitTime);
        std::ostringstream pursuitTime;
        if(ghost.getPursuitTime() - 10 < 1)
            pursuitTime << std::setprecision(1) << ghost.getPursuitTime() - 10;
        else
            pursuitTime << std::setprecision(2) << ghost.getPursuitTime() - 10;
        const sf::String pursuitTimeString(pursuitTime.str());
        PursuitTime.setString(pursuitTimeString);
        window.draw(PursuitTime);
    }
    for(int i = pacman.getHealth(), j = 756; i > 0; i--, j -= 42)
    {
        Item life("heart.png", j, 0, 0, 0, 42, 42);
        life.draw(window);
    }
    if(ghost.getPursuit() && ((ghost.getPursuitTime() - 10 > 0 && ghost.getPursuitTime() - 10 < 0.5) || (ghost.getPursuitTime() - 10 > 1.0 && ghost.getPursuitTime() - 10 < 1.5) || (ghost.getPursuitTime() - 10 > 2.0 && ghost.getPursuitTime() - 10 < 2.5)))
    {
        window.draw(Pursuit);
    }
    std::vector<int>::iterator iter;
    int i(756);
    for(iter = fruits.begin(), i; iter != fruits.end(); iter++, i -= 42)
    {
        if(*iter == 5)
            sprite.setTextureRect(sf::IntRect(42 * 3, 42, 42, 42));
        else if(*iter == 6)
            sprite.setTextureRect(sf::IntRect (42 * 4, 42, 42, 42));
        else if(*iter == 7)
            sprite.setTextureRect(sf::IntRect (42 * 5, 42, 42, 42));
        else if(*iter == 8)
            sprite.setTextureRect(sf::IntRect (42 * 6, 42, 42, 42));
        sprite.setPosition(i, 42);
        window.draw(sprite);
    }
    if(points == 0 || (!pacman.getHealth() && (pacman.getEnergizerTime() > 4.5)))
    {
        pacman.stopMusic();
        if(points == 0)
            victoryMusic.openFromFile("audioCourseWork/victoryMusic.wav");
        else
            victoryMusic.openFromFile("audioCourseWork/defeatMusic.wav");
        victoryMusic.play();
        pacman.setFinalScore();
        Menu::setGameOver(window);
    }
}
// Конструктор с параметрами
Map::Map(sf::String f, float x_image, float y_image, float x, float y, float w, float h) : Item(f, x_image, y_image, x, y, w, h), fruits(4), points(0) {
    fontPacman.loadFromFile("fontsCourseWork/Pac-Man.ttf");
    textPoints.setFont(fontPacman);
    textPoints.setFillColor(sf::Color::Yellow);
    textPoints.setStyle(sf::Text::Bold);
    textPoints.setString("Points: ");
    textPoints.setPosition(0, 42);
    textScore.setFont(fontPacman);
    textScore.setFillColor(sf::Color::Green);
    textScore.setStyle(sf::Text::Bold);
    textScore.setString("Score: ");
    textScore.setPosition(0, 0);
    textAliveTime.setFont(fontPacman);
    textAliveTime.setFillColor(sf::Color::Magenta);
    textAliveTime.setStyle(sf::Text::Bold);
    textAliveTime.setString("All time: ");
    textAliveTime.setPosition(7 * 42, 0);
    textEnergizerTime.setFont(fontPacman);
    textEnergizerTime.setFillColor(sf::Color::Cyan);
    textEnergizerTime.setStyle(sf::Text::Bold);
    textEnergizerTime.setString("Energizer: ");
    textEnergizerTime.setPosition(7 * 42, 42);
    textPursuitTime.setFont(fontPacman);
    textPursuitTime.setFillColor(sf::Color::Red);
    textPursuitTime.setStyle(sf::Text::Bold);
    textPursuitTime.setString("Pursuit: ");
    textPursuitTime.setPosition(7 * 42, 42);
    fontText.loadFromFile("fontsCourseWork/info.ttf");
    Points.setFont(fontText);
    Points.setPosition(42 * 4, 42);
    Score.setFont(fontText);
    AliveTime.setFont(fontText);
    AliveTime.setPosition(13 * 42 - 21, 0);
    EnergizerTime.setFont(fontText);
    EnergizerTime.setPosition(14 * 42 - 21, 42);
    PursuitTime.setFont(fontText);
    PursuitTime.setPosition(12 * 42 - 21, 42);
    fontPursuit.loadFromFile("fontsCourseWork/pursuit.ttf");
    Pursuit.setFont(fontPursuit);
    Pursuit.setFillColor(sf::Color::Red);
    Pursuit.setString("Pursuit");
    Pursuit.setPosition(3 * 42, 8 * 42);
    Pursuit.setCharacterSize(225);
    for(int i = 0; i < HEIGHT_MAP; i++)
    {
        for(int j = 1; j < WIDTH_MAP; j++)
        {
            convertedMap[i][j].first = basicMap[i][j];
            convertedMap[i][j].second = 0;
        }
    }
    Coordinates<int> cherry = randomCoordinates();
    Coordinates<int> strawberry = randomCoordinates();
    Coordinates<int> orange = randomCoordinates();
    Coordinates<int> apple = randomCoordinates();
    basicMap[cherry.y][cherry.x] = 5;
    basicMap[strawberry.y][strawberry.x] = 6;
    basicMap[orange.y][orange.x] = 7;
    basicMap[apple.y][apple.x] = 8;
    for(int i = 0; i < HEIGHT_MAP; i++)
    {
        for(int j = 1; j < WIDTH_MAP; j++)
        {
            if(basicMap[i][j] == 2)
                points++;
        }
    }
    fruits = {5, 6, 7, 8};
    victoryMusic.openFromFile("audioCourseWork/victoryMusic.wav");
    victoryMusic.setLoop(true);
    victoryMusic.setVolume(35);
}
// Метод для удаления фрукта
void Map::setMinusFruit(int temp)
{
    auto ptr = find(fruits.begin(), fruits.begin() + fruits.size(), temp);
    fruits.erase(fruits.begin() + (ptr - fruits.begin()));
}
// Метод для генерации случайных координат
Coordinates<int> Map::randomCoordinates()
{
    Coordinates<int> temp;
    do
    {
        temp = {(rand() % 19 + 1), (rand() % 18 + 3)};
    }while(basicMap[temp.y][temp.x] == 1 || basicMap[temp.y][temp.x] == 3 || ((temp.y == 9 || temp.y == 13) && (temp.x == 1 || temp.x == 2 || temp.x == 3 || temp.x == 17 || temp.x == 18 || temp.x == 19)) || (temp.y == 11 && (temp.x == 9 || temp.x == 10 || temp.x == 11)) || (temp.y == 10 && temp.x == 10));
    return temp;
}
// Метод для уменьшения оставшихся точек
void Map::setPointsMinusOne()
{
    points--;
}
//Метод для сброса до начала игры
void Map::resetMap()
{
    points = 0;
    for(int i = 0; i < HEIGHT_MAP; i++)
    {
        for(int j = 0; j < WIDTH_MAP; j++)
        {
            basicMap[i][j] = convertedMap[i][j].first;
            if(basicMap[i][j] == 2)
                points++;
        }
    }
    Coordinates<int> cherry = randomCoordinates();
    Coordinates<int> strawberry = randomCoordinates();
    Coordinates<int> orange = randomCoordinates();
    Coordinates<int> apple = randomCoordinates();
    if(basicMap[cherry.y][cherry.x] == 2)
        points--;
    basicMap[cherry.y][cherry.x] = 5;
    if(basicMap[strawberry.y][strawberry.x] == 2)
        points--;
    basicMap[strawberry.y][strawberry.x] = 6;
    if(basicMap[orange.y][orange.x] == 2)
        points--;
    basicMap[orange.y][orange.x] = 7;
    if(basicMap[apple.y][apple.x] == 2)
        points--;
    basicMap[apple.y][apple.x] = 8;
    fruits.clear();
    fruits = {5, 6, 7, 8};
}
// Метод для сохранения в бинарный файл
void Map::saveMap(std::ofstream &file)
{
    for(int i = 0; i < HEIGHT_MAP; i++)
    {
        for(int j = 0; j < WIDTH_MAP; j++)
        {
            file.write(reinterpret_cast<char*>(&basicMap[i][j]), sizeof(basicMap[i][j]));
        }
    }
    file.write(reinterpret_cast<char*>(&points), sizeof(points));
    std::vector<int>::iterator iter;
    for(iter = fruits.begin(); iter != fruits.end(); iter++)
        file.write(reinterpret_cast<char*>(&(*iter)), sizeof(*iter));
}
// Метод для считывания с бинарного файла
void Map::loadMap(std::ifstream &file)
{
    for(int i = 0; i < HEIGHT_MAP; i++)
    {
        for(int j = 0; j < WIDTH_MAP; j++)
        {
            file.read(reinterpret_cast<char*>(&basicMap[i][j]), sizeof(basicMap[i][j]));
        }
    }
    file.read(reinterpret_cast<char*>(&points), sizeof(points));
    int temp;
    fruits.clear();
    while(file.read(reinterpret_cast<char*>(&temp), sizeof(temp)))
    {
        fruits.push_back(temp);
    }
}
// Метод для получения количества точек
int Map::getPoints() {
    return points;
}
// Метод для получения состояния музыки
bool Map::getVictoryMusicStatusPlaying()
{
    return victoryMusic.getStatus() == sf::Music::Playing;
}
// Метод для остановки музыки
void Map::stopVictoryMusic()
{
    victoryMusic.stop();
}
// Метод для управления музыкой
void Map::setMusic(bool Music)
{
    if(Music)
        victoryMusic.setVolume(35);
    else
        victoryMusic.setVolume(0);
}
// Деструктор по умолчанию
Map::~Map() = default;
