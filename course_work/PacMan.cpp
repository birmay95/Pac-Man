#include "PacMan.h"
#include "Map.h"
#include "Menu.h"
// Конструктор с параметрами
PacMan::PacMan(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H)
: Entity(F, X, Y, X_image, Y_image, W, H), energizer(false), score(0), loadAliveTime(0), countKillingGhosts(0)
{
    health = 3;
    energizerMusic.openFromFile("audioCourseWork/energizerMusic.wav");
    energizerMusic.setLoop(true);
    energizerMusic.setVolume(20);
    pointSoundBuffer.loadFromFile("audioCourseWork/point.wav");
    pointSound.setBuffer(pointSoundBuffer);
    pointSound.setVolume(30);
    fruitSoundBuffer.loadFromFile("audioCourseWork/fruit.wav");
    fruitSound.setBuffer(fruitSoundBuffer);
    fruitSound.setVolume(100);
    failSoundBuffer.loadFromFile("audioCourseWork/fail.wav");
    failSound.setBuffer(failSoundBuffer);
    failSound.setVolume(60);
    killingGhostSoundBuffer.loadFromFile("audioCourseWork/killingGhost.wav");
    killingGhostSound.setBuffer(killingGhostSoundBuffer);
    killingGhostSound.setVolume(60);
}
// Метод для обновления положения на карте
void PacMan::update()
{
    if(!health)
        return;
    currentFrame += 0.005;
    if(currentFrame > 2)
        currentFrame -= 2;
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
    {
        if(energizer)
            speed = 0.32;
        else
            speed = 0.3;
        dir = Entity::Direction::Left;
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + 82,0, -42, 42));
    }
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
        if(energizer)
            speed = 0.32;
        else
            speed = 0.3;
        dir = Entity::Direction::Right;
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + 42,0, 40, 42));
    }
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
    {
        if(energizer)
            speed = 0.32;
        else
            speed = 0.3;
        dir = Entity::Direction::Up;
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + 210,210, 42, 42));
    }
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
    {
        if(energizer)
            speed = 0.32;
        else
            speed = 0.3;
        dir = Entity::Direction::Down;
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + 252,252, -42, -42));
    }
    else
    {
        if(dir == Entity::Direction::Left)
        {
            sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + 82, 0, -42, 40));
            float tempX = coord.x;
            while(tempX > 0)
                tempX -= 42;
            tempX += 42;
            float temp = coord.x;
            while(temp > 0)
                temp -= 42;
            if(temp != 0)
                coord.x -= tempX;
        }
        if(dir == Entity::Direction::Right)
        {
            sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + 42, 0, 40, 40));
            float tempX = coord.x;
            while(tempX > 0)
                tempX -= 42;
            tempX += 42;
            float addX = (42 - tempX);
            coord.x += addX;
        }
        if(dir == Entity::Direction::Up)
        {
            sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + 210, 210, 42, 40));
            float tempY = coord.y;
            while(tempY > 0)
                tempY -= 42;
            tempY += 42;
            float temp = coord.y;
            while(temp > 0)
                temp -= 42;
            if(temp != 0)
                coord.y -= tempY;
        }
        if(dir == Entity::Direction::Down)
        {
            sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + 252, 252, -42, -40));
            float tempY = coord.y;
            while(tempY > 0)
                tempY -= 42;
            tempY += 42;
            float addY = (42 - tempY);
            coord.y += addY;
        }
    }
    Entity::update();
}
// Метод для взаимодействия с картой
void PacMan::interactionWithMap(Map& map)
{
    bool fl(false);
    for(int i = coord.y / 42; i < (coord.y + height) / 42; i++)
    {
        for(int j = coord.x / 42 + 1; j < (coord.x + 42 + width) / 42; j++)
        {
            if (coord.x + 21 < 0) {
                coord.x = 19 * 42;
                fl = true;
            } else if (coord.x > 19 * 42)
                coord.x = 0;
            else if ((map(i, j) == 1 || map(i, j) == 4) && !fl) {
                if (dy > 0)
                    coord.y = static_cast<float>(i) * 42 - height;
                if (dy < 0)
                    coord.y = static_cast<float>(i) * 42 + height;
                if (dx > 0)
                    coord.x = static_cast<float>(j - 1) * 42 - width;
                if (dx < 0)
                    coord.x = static_cast<float>(j - 1) * 42 + width;
            }
        }
    }
    for(int i = coord.y / 42; i < (coord.y + height) / 42; i++)
    {
        for(int j = coord.x / 42 + 1; j < (coord.x + 42 + width) / 42; j++)
        {
            if (map(i, j) == 2 && ((((coord.y) - (i * 42) < 2) && ((coord.y) - (i * 42) > -2)) && (((coord.x) - (j * 42 - 42) > -2) && ((coord.x) - (j * 42 - 42) < 2))))
            {
                map.setPointsMinusOne();
                score += 20;
                map(i, j) = 0;
                pointSound.play();
            }
            else if (map(i, j) == 3 && ((((coord.y) - (i * 42) < 2) && ((coord.y) - (i * 42) > -2)) && (((coord.x) - (j * 42 - 42) > -2) && ((coord.x) - (j * 42 - 42) < 2))))
            {
                energizer = true;
                Ghost::setUnPower(true);
                map(i, j) = 0;
                if(energizerMusic.getStatus() != sf::Music::Playing)
                    energizerMusic.play();
                countKillingGhosts = 0;
                energizerTime.restart();
            }
            else if ((map(i, j) == 5 || map(i, j) == 6 || map(i, j) == 7 || map(i, j) == 8) && ((((coord.y) - (i * 42) < 2) && ((coord.y) - (i * 42) > -2)) && (((coord.x) - (j * 42 - 42) > -2) && ((coord.x) - (j * 42 - 42) < 2))))
            {
                score += 200;
                map.setMinusFruit(map(i, j));
                map(i, j) = 0;
                fruitSound.play();
            }
        }
    }
}
// Метод для установки финального количества очков
void PacMan::setFinalScore()
{
    score += health * 1000;
    if(health)
    {
        score *= 1 / (loadAliveTime + aliveTime.getElapsedTime().asSeconds() - Menu::getAllPauseTime());
        score *= 50;
    }
}
// Метод для получения количества очков
int PacMan::getScore() {
return score;
}
// Метод для получения количества жизней
int PacMan::getHealth() {
    return health;
}
// Метод для взаимодействия с привидениями
void PacMan::interactionWithGhost(Ghost& ghost)
{
    if(health && !energizer && ghost.getHealth() && (((coord.x - ghost.getCoord().x) < 0.5) && ((coord.x - ghost.getCoord().x) > -0.5)) && (((coord.y - ghost.getCoord().y) < 0.5) && (coord.y - ghost.getCoord().y) > -0.5))
    {
        failSound.play();
        health--;
        if(health == 0)
        {
            energizerTime.restart();
        }
        else
        {
            coord = {42 * 0, 42 * 11};
        }
        Ghost::restartPursuitTime();
    }
    if(health && energizer)
    {
        if(energizerTime.getElapsedTime().asSeconds() > 5)
        {
            energizer = false;
            Ghost::setUnPower(false);
            energizerMusic.pause();
        }
        else if(ghost.getHealth() && (((coord.x - ghost.getCoord().x) < 0.5) && ((coord.x - ghost.getCoord().x) > -0.5)) && (((coord.y - ghost.getCoord().y) < 0.5) && (coord.y - ghost.getCoord().y) > -0.5))
        {
            killingGhostSound.play();
            ghost.setHealth();
            countKillingGhosts *= 2;
            score += countKillingGhosts * 100;
        }
        Ghost::restartPursuitTime();
    }
    if(!health)
    {
        speed = 0;
        dir = Entity::Direction::Neutral;
        if(energizerTime.getElapsedTime().asSeconds() < 1)
            sprite.setTextureRect(sf::IntRect(42 * 5,42 * 5, 42, 42));
        if(energizerTime.getElapsedTime().asSeconds() > 1 && energizerTime.getElapsedTime().asSeconds() < 2)
            sprite.setTextureRect(sf::IntRect(42 * 6,42 * 5, 42, 42));
        if(energizerTime.getElapsedTime().asSeconds() > 2 && energizerTime.getElapsedTime().asSeconds() < 3)
            sprite.setTextureRect(sf::IntRect(42 * 7 + 5,42 * 5, 42, 42));
        if(energizerTime.getElapsedTime().asSeconds() > 3 && energizerTime.getElapsedTime().asSeconds() < 4)
            sprite.setTextureRect(sf::IntRect(42 * 8,42 * 5, 42, 42));
        if(energizerTime.getElapsedTime().asSeconds() > 4 && energizerTime.getElapsedTime().asSeconds() < 4.5)
            sprite.setTextureRect(sf::IntRect(42 * 9,42 * 5, 42, 42));
    }
}
// Метод для получения состояния силы
bool PacMan::getEnergizer() {
    return energizer;
}
// Метод для получения количества времени силы
float PacMan::getEnergizerTime() {
    return energizerTime.getElapsedTime().asSeconds();
}
// Метод для получения времени существования
float PacMan::getAliveTime() {
    return aliveTime.getElapsedTime().asSeconds();
}
// Метод для сброса объекта на начальное состояние
void PacMan::resetPacman()
{
    energizer = false;
    score = 0;
    health = 3;
    speed = 0;
    dx = 0;
    dy = 0;
    dir = Direction::Neutral;
    coord = {42 * 4, 42 * 3};
    picture = {0, 0};
    currentFrame = 0;
    sprite.setTextureRect(sf::IntRect (picture.x, picture.y, width, height));
    sprite.setPosition(coord.x, coord.y);
    energizerTime.restart();
    aliveTime.restart();
    loadAliveTime = 0;
}
// Метод для сохранения объекта в бинарный файл
void PacMan::savePacman(std::ofstream& file)
{
    file.write(reinterpret_cast<char*>(&coord.x), sizeof(coord.x));
    file.write(reinterpret_cast<char*>(&coord.y), sizeof(coord.y));
    file.write(reinterpret_cast<char*>(&picture.x), sizeof(picture.x));
    file.write(reinterpret_cast<char*>(&picture.y), sizeof(picture.y));
    file.write(reinterpret_cast<char*>(&currentFrame), sizeof(currentFrame));
    file.write(reinterpret_cast<char*>(&speed), sizeof(speed));
    file.write(reinterpret_cast<char*>(&dx), sizeof(dx));
    file.write(reinterpret_cast<char*>(&dy), sizeof(dy));
    file.write(reinterpret_cast<char*>(&dir), sizeof(dir));
    file.write(reinterpret_cast<char*>(&energizer), sizeof(energizer));
    file.write(reinterpret_cast<char*>(&score), sizeof(score));
    file.write(reinterpret_cast<char*>(&health), sizeof(health));
    float time(aliveTime.getElapsedTime().asSeconds());
    file.write(reinterpret_cast<char*>(&time), sizeof(time));
}
// Метод для загрузки объекта в бинарный файл
void PacMan::loadPacman(std::ifstream &file)
{
    file.read(reinterpret_cast<char*>(&coord.x), sizeof(coord.x));
    file.read(reinterpret_cast<char*>(&coord.y), sizeof(coord.y));
    file.read(reinterpret_cast<char*>(&picture.x), sizeof(picture.x));
    file.read(reinterpret_cast<char*>(&picture.y), sizeof(picture.y));
    file.read(reinterpret_cast<char*>(&currentFrame), sizeof(currentFrame));
    file.read(reinterpret_cast<char*>(&speed), sizeof(speed));
    file.read(reinterpret_cast<char*>(&dx), sizeof(dx));
    file.read(reinterpret_cast<char*>(&dy), sizeof(dy));
    file.read(reinterpret_cast<char*>(&dir), sizeof(dir));
    file.read(reinterpret_cast<char*>(&energizer), sizeof(energizer));
    file.read(reinterpret_cast<char*>(&score), sizeof(score));
    file.read(reinterpret_cast<char*>(&health), sizeof(health));
    file.read(reinterpret_cast<char*>(&loadAliveTime), sizeof(loadAliveTime));
}
// Метод для получения загруженного времени
float PacMan::getLoadAliveTime()
{
    return loadAliveTime;
}
// Метод для перезапуска времени силы
void PacMan::restartEnergizer()
{
    if(energizerMusic.getStatus() != sf::Music::Playing)
        energizerMusic.play();
    energizerTime.restart();
}
// Метод для остановки музыки во время силы
void PacMan::stopMusic()
{
    energizerMusic.stop();
}
// Метод для получения музыки во время силы
bool PacMan::getEnergizerMusicStatusPlaying()
{
    return energizerMusic.getStatus() == sf::Music::Playing;
}
// Метод для управления громкостью музыки и звуков
void PacMan::setAudio(int Sound, int Music)
{
    if(Sound == 0)
    {
        pointSound.setVolume(0);
        fruitSound.setVolume(0);
        failSound.setVolume(0);
        killingGhostSound.setVolume(0);
    }
    else if(Sound == 1)
    {
        pointSound.setVolume(30);
        fruitSound.setVolume(100);
        failSound.setVolume(60);
        killingGhostSound.setVolume(60);
    }
    if(Music == 0)
        energizerMusic.setVolume(0);
    else if(Music == 1)
        energizerMusic.setVolume(20);
}
// Деструктор по умолчанию
PacMan::~PacMan() = default;
