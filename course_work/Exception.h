#ifndef SEM_3_EXCEPTION_H
#define SEM_3_EXCEPTION_H
#include <iostream>
class Game;
//Базовый класс исключений
class Exception : public std::exception {
protected:
    int code; //Код исключения
    std::string message; //Сообщение исключения
public:
    //Конструктор без параметров
    Exception();
    //Конструктор с параметрами
    Exception(int Code, std::string mes);
    //Метод для обработки исключения
    void processEvent(bool saving);
    //Перегрузка метода для вывода сообщения исключения
    const char* what();
    //Деструктор по умолчанию
    ~Exception() override; };
//Класс исключения закрытия окна
class ExceptionWindowClose : public Exception {
public:
    //Конструктор с параметрами
    ExceptionWindowClose(int Code, std::string mes);
    //Деструктор по умолчанию
    ~ExceptionWindowClose() override; };
//Класс исключения долгого бездействия
class ExceptionLongTimeNoActive : public Exception {
public:
    //Конструктор с параметрами
    ExceptionLongTimeNoActive(int Code, std::string mes);
    //Деструктор по умолчанию
    ~ExceptionLongTimeNoActive() override; };
//Класс исключения открытия файла
class ExceptionFileOpening : public Exception
{
public:
    //Конструктор с параметрами
    ExceptionFileOpening(int Code, std::string mes);
    //Деструктор по умолчанию
    ~ExceptionFileOpening() override;
};
#endif //SEM_3_EXCEPTION_H
