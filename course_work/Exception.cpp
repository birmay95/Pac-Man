#include "Exception.h"
#include "Game.h"
//Конструктор без параметров
Exception::Exception(): code(0) {}
//Конструктор с параметрами
Exception::Exception(int Code, std::string mes): code(Code), message(mes) {}
//Метод для обработки исключения
void Exception::processEvent(bool saving)
{
    std::cerr << "Event " << code << ": " << what();
    if(saving)
        Game::windowClose(saving);
}
//Перегрузка метода для вывода сообщения исключения
const char *Exception::what()
{
    return message.c_str();
}
//Деструктор по умолчанию
Exception::~Exception() = default;
//Конструктор с параметрами
ExceptionWindowClose::ExceptionWindowClose(int Code, std::string mes) : Exception(Code, mes) {}
//Деструктор по умолчанию
ExceptionWindowClose::~ExceptionWindowClose() = default;
//Конструктор с параметрами
ExceptionLongTimeNoActive::ExceptionLongTimeNoActive(int Code, std::string mes) : Exception(Code, mes) {}
//Деструктор по умолчанию
ExceptionLongTimeNoActive::~ExceptionLongTimeNoActive() = default;
//Конструктор с параметрами
ExceptionFileOpening::ExceptionFileOpening(int Code, std::string mes) : Exception(Code, mes) {}
//Деструктор по умолчанию
ExceptionFileOpening::~ExceptionFileOpening() = default;
