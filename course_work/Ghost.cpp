#include "Ghost.h"
#include "Map.h"
#include "Menu.h"
//Состояние силы Pac-Man'a
bool Ghost::unPower = false;
//Состояние преследования Pac-Man'a
bool Ghost::pursuit = false;
//Время преследования Pac-Man'a
sf::Clock Ghost::pursuitTime;
//Конструктор с параметрами
Ghost::Ghost(sf::String F, float X, float Y, float X_image, float Y_image, float W, float H, std::string Name)
: Entity(F, X, Y, X_image, Y_image, W, H), target(0, 0)
{
    name = Name;
    pursuitMusic.openFromFile("audioCourseWork/pursuitMusic.wav");
    pursuitMusic.setVolume(30);
}
//Метод для поиска в ширину
std::vector<Coordinates<float> > Ghost::bfs(Map &map, Coordinates<float> aim)
{
    std::vector<std::vector<int> > dist(HEIGHT_MAP - 1, std::vector<int>(WIDTH_MAP, INF));
    std::vector<std::vector<Coordinates<int> > > from(HEIGHT_MAP - 1, std::vector<Coordinates<int> >(WIDTH_MAP, {-1, -1}));
    std::queue<Coordinates<int> > q;
    std::vector<Coordinates<float> > way;
    dist[static_cast<int>(coord.y/42)][static_cast<int>(coord.x/42 + 1)] = 0;
    q.emplace(coord.x/42 + 1, coord.y/42);

    std::vector<int> dy = {-1, 0, 1, 0};
    std::vector<int> dx = {0, 1, 0, -1};

    while(!q.empty())
    {
        Coordinates<int> startPoint = q.front();
        q.pop();

        for(int i = 0; i < dy.size(); i++)
        {
            Coordinates<int> temp(startPoint.x + dx[i], startPoint.y + dy[i]);
            if(3 <= temp.y && temp.y < HEIGHT_MAP - 1 && 1 <= temp.x && temp.x < WIDTH_MAP &&
               map(temp) != 1 && dist[temp.y][temp.x] > dist[startPoint.y][startPoint.x] + 1)
            {
                dist[temp.y][temp.x] = dist[startPoint.y][startPoint.x] + 1;
                from[temp.y][temp.x] = startPoint;
                q.push(temp);
            }
        }
    }
    if(dist[static_cast<int>(aim.y/42)][static_cast<int>(aim.x/42 + 1)] != INF)
    {
        Coordinates<float> coordWay(aim.x/42 + 1, aim.y/42);
        while (coordWay.y != -1 && coordWay.x != -1)
        {
            if(map(coordWay) != 1)
                way.push_back(coordWay);
            Coordinates<int> intToFloatTemp = from[static_cast<int>(coordWay.y)][static_cast<int>(coordWay.x)];
            coordWay = {static_cast<float>(intToFloatTemp.x), static_cast<float>(intToFloatTemp.y)};
        }
        std::reverse(way.begin(), way.end());
    }
    return way;
}
//Метод для генерации случайных координат на карте
Coordinates<float> Ghost::randomCoordinates(Map& map)
{
    Coordinates<float> temp;
    do
    {
        temp = {static_cast<float>(rand() % 19 + 1), static_cast<float>(rand() % 18 + 3)};
    }while(map(temp) == 1 || ((temp.y == 9 || temp.y == 13) && (temp.x == 1 || temp.x == 2 || temp.x == 3 || temp.x == 17 || temp.x == 18 || temp.x == 19)));
    return temp;
}
//Метод для обновления положения привидения на карте
void Ghost::update(float aliveTime, float spawn, Map &map, Coordinates<float> pacman, int healthPacman)
{
    if (!health && coord == Coordinates<float>(42 * 9, 42 * 11))
    {
        health = 1;
        return;
    }
    currentFrame += 0.005;
    if (currentFrame > 2)
        currentFrame -= 2;
    if(pursuitTime.getElapsedTime().asSeconds() <= 10)
        pursuit = false;
    else if(pursuitTime.getElapsedTime().asSeconds() <= 15)
        pursuit = true;
    else
        pursuitTime.restart();
    if(pursuitTime.getElapsedTime().asSeconds() > 10 && pursuitTime.getElapsedTime().asSeconds() < 10.005)
    {
        pursuitMusic.stop();
        pursuitMusic.play();
    }
    if(!pursuit)
        pursuitMusic.pause();
    Coordinates<int> right, left, up, down, neutral;
    if (!unPower && health)
    {
        if (name == "Red") {
            right = {294, 0};
            left = {210, 0};
            up = {0, 42};
            down = {84, 42};
            neutral = {126, 0};
        }
        if (name == "Pink") {
            right = {8 * 42, 42};
            left = {6 * 42, 42};
            up = {42, 2 * 42};
            down = {3 * 42, 2 * 42};
            neutral = {4 * 42, 42};
        }
        if (name == "Cyan") {
            right = {0, 3 * 42};
            left = {7 * 42, 2 * 42};
            up = {2 * 42, 3 * 42};
            down = {4 * 42, 3 * 42};
            neutral = {5 * 42, 2 * 42};
        }
        if (name == "Orange") {
            right = {42, 4 * 42};
            left = {8 * 42, 3 * 42};
            up = {3 * 42, 4 * 42};
            down = {5 * 42, 4 * 42};
            neutral = {6 * 42, 3 * 42};
        }
    }
    else if (unPower && health)
    {
        right = left = up = down = neutral = {7 * 42, 4 * 42};
    }
    else if(!health)
    {
        right = {2 * 42, 5 * 42};
        left = {42, 5 * 42};
        up = {3 * 42, 5 * 42};
        down = {4 * 42, 5 * 42};
        neutral = {0, 5 * 42};
    }
    if(aliveTime < spawn)
    {
        speed = 0;
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + neutral.x, neutral.y, 42, 40));
        return;
    }
    if(!health)
        currentFrame = 0;
    if((name == "Pink") && dir == Direction::Right && !unPower)
        sprite.setTextureRect(sf::IntRect(right.x - 42 * int(currentFrame) * 8, 42 * int(currentFrame) + right.y, 42, 40));
    else if (dir == Direction::Right)
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + right.x, right.y, 42, 40));
    if ((name == "Orange") && dir == Direction::Left && !unPower)
        sprite.setTextureRect(sf::IntRect(left.x - 42 * int(currentFrame) * 8, 42 * int(currentFrame) + left.y, 42, 40));
    else if (dir == Direction::Left)
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + left.x, left.y, 42, 40));
    if (dir == Direction::Up)
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + up.x, up.y, 42, 40));
    if (dir == Direction::Down)
        sprite.setTextureRect(sf::IntRect(42 * int(currentFrame) + down.x, down.y, 42, 40));
    std::vector<Coordinates<float> > way;
    bool fl(false);
    if(!unPower && !pursuit && healthPacman)
    {
        if (dir == Direction::Right) {
            for (int i = coord.x / 42 + 1, j = coord.y / 42; map(j, i) != 1; i++) {
                if ((static_cast<float>(i * 42 - 42) - pacman.x <= 42) && (static_cast<float>(i * 42 - 42) - pacman.x >= 0) && pacman.y == coord.y) {
                    pursuit = true;
                    fl = true;
                }
            }
        } else if (dir == Direction::Left) {
            for (int i = coord.x / 42 + 1, j = coord.y / 42; map(j, i) != 1; i--) {
                if ((static_cast<float>(i * 42 - 42) - pacman.x >= -42) && (static_cast<float>(i * 42 - 42) - pacman.x <= 0) && pacman.y == coord.y) {
                    pursuit = true;
                    fl = true;
                }
            }
        } else if (dir == Direction::Up) {
            for (int i = coord.x / 42 + 1, j = coord.y / 42; map(j, i) != 1; j--) {
                if ((static_cast<float>(j * 42) - pacman.y >= -42) && (static_cast<float>(j * 42) - pacman.y <= 0) && pacman.x == coord.x) {
                    pursuit = true;
                    fl = true;
                }
            }
        } else if (dir == Direction::Down) {
            for (int i = coord.x / 42 + 1, j = coord.y / 42; map(j, i) != 1; j++) {
                if ((static_cast<float>(j * 42) - pacman.y <= 42) && (static_cast<float>(j * 42) - pacman.y >= 0) && pacman.x == coord.x) {
                    pursuit = true;
                    fl = true;
                }
            }
        }
    }
    if(!health && healthPacman)
        way = bfs(map, {42 * 9, 42 * 11});
    else if(pursuit && pacman.x >= 0 && healthPacman)
        way = bfs(map, pacman);
    else
    {
        if(target == Coordinates<float>(0, 0) || coord == target)
        {
            target = randomCoordinates(map);
            target.x = target.x * 42 - 42;
            target.y *= 42;
        }
        way = bfs(map, target);
    }
    way[0].x -= 1;
    if(((way[0].y * 42 - coord.y) == 0 && (way[0].x * 42 - coord.x) == 0) || dir == Direction::Right || dir == Direction::Down)
    {
        way.erase(way.begin());
        way[0].x -= 1;
    }
    if((way[0].y * 42 - coord.y) > 0 && (way[0].x * 42 - coord.x) == 0)
        dir = Entity::Direction::Down;
    if((way[0].y * 42 - coord.y) == 0 && (way[0].x * 42 - coord.x) > 0)
        dir = Entity::Direction::Right;
    if((way[0].y * 42 - coord.y) == 0 && (way[0].x * 42 - coord.x) < 0)
        dir = Entity::Direction::Left;
    if((way[0].y * 42 - coord.y) < 0 && (way[0].x * 42 - coord.x) == 0)
        dir = Entity::Direction::Up;
    speed = 0.25;
    Entity::update();
    if(fl)
        pursuit = false;
}
//Метод для столкновения привидения с картой
void Ghost::interactionWithMap(Map& map)
{
    for(int i = coord.y / 42; i < (coord.y + height) / 42; i++)
    {
        for(int j = coord.x / 42 + 1; j < (coord.x + 42 + width) / 42; j++)
        {
            if (map(i, j) == 1) {
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
}
//Метод для получения состояния преследования
bool Ghost::getPursuit() {
    return pursuit;
}
//Метод для обнуления количества жизней
void Ghost::setHealth() {
    health = 0;
}
//Метод для перезапуска время преследования
void Ghost::restartPursuitTime() {
    pursuitTime.restart();
}
//Метод для получения времени преследования
float Ghost::getPursuitTime() {
    return pursuitTime.getElapsedTime().asSeconds();
}
//Метод для получения количества жизней
int Ghost::getHealth() {
    return health;
}
//Метод для установки состояния преследования
void Ghost::setUnPower(bool temp) {
unPower = temp;
}
//Метод для сброса до начала игры
void Ghost::resetGhost()
{
    unPower = false;
    pursuit = false;
    target = {0, 0};
    dir = Direction::Neutral;
    speed = 0;
    dx = 0;
    dy = 0;
    health = 1;
    currentFrame = 0;
    if(name == "Orange")
    {
        coord = {42 * 9,  42 * 11};
        picture = {6 * 42, 3 * 42};
    }
    if(name == "Pink")
    {
        coord = {42 * 9, 42 * 11};
        picture = {4 * 42, 42};
    }
    if(name == "Red")
    {
        coord = {42 * 8, 42 * 11};
        picture = {126, 0};
    }
    if(name == "Cyan")
    {
        coord = {42 * 10, 42 * 11};
        picture = {5 * 42, 2 * 42};
    }
    sprite.setTextureRect(sf::IntRect (picture.x, picture.y, width, height));
    sprite.setPosition(coord.x, coord.y);
    pursuitTime.restart();
}
//Метод для сохранения в бинарный файл
void Ghost::saveGhost(std::ofstream &file)
{
    file.write(reinterpret_cast<char*>(&coord.x), sizeof(coord.x));
    file.write(reinterpret_cast<char*>(&coord.y), sizeof(coord.y));
    file.write(reinterpret_cast<char*>(&picture.x), sizeof(picture.x));
    file.write(reinterpret_cast<char*>(&picture.y), sizeof(picture.y));
    file.write(reinterpret_cast<char*>(&target.x), sizeof(target.x));
    file.write(reinterpret_cast<char*>(&target.y), sizeof(target.y));
    file.write(reinterpret_cast<char*>(&currentFrame), sizeof(currentFrame));
    file.write(reinterpret_cast<char*>(&speed), sizeof(speed));
    file.write(reinterpret_cast<char*>(&dx), sizeof(dx));
    file.write(reinterpret_cast<char*>(&dy), sizeof(dy));
    file.write(reinterpret_cast<char*>(&dir), sizeof(dir));
    file.write(reinterpret_cast<char*>(&health), sizeof(health));
}
//Метод для считывания с бинарного файла
void Ghost::loadGhost(std::ifstream &file)
{
    file.read(reinterpret_cast<char*>(&coord.x), sizeof(coord.x));
    file.read(reinterpret_cast<char*>(&coord.y), sizeof(coord.y));
    file.read(reinterpret_cast<char*>(&picture.x), sizeof(picture.x));
    file.read(reinterpret_cast<char*>(&picture.y), sizeof(picture.y));
    file.read(reinterpret_cast<char*>(&target.x), sizeof(target.x));
    file.read(reinterpret_cast<char*>(&target.y), sizeof(target.y));
    file.read(reinterpret_cast<char*>(&currentFrame), sizeof(currentFrame));
    file.read(reinterpret_cast<char*>(&speed), sizeof(speed));
    file.read(reinterpret_cast<char*>(&dx), sizeof(dx));
    file.read(reinterpret_cast<char*>(&dy), sizeof(dy));
    file.read(reinterpret_cast<char*>(&dir), sizeof(dir));
    file.read(reinterpret_cast<char*>(&health), sizeof(health));
}
//Метод для получения статуса музыки
bool Ghost::getPursuitMusicStatusPlaying()
{
    return pursuitMusic.getStatus() == sf::Music::Playing;
}
//Метод для управления музыкой
void Ghost::setMusic(bool Music)
{
    if(Music)
        pursuitMusic.setVolume(30);
    else
        pursuitMusic.setVolume(0);
}
//Деструктор по умолчанию
Ghost::~Ghost() = default;
