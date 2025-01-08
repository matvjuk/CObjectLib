#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// Определение типов доступа
typedef enum {
    PRIVATE,
    PROTECTED,
    PUBLIC
} MemberType;

// Структура для описания члена класса
typedef struct {
    char* name;         // Имя члена
    MemberType type;    // Тип члена (публичный, защищенный или приватный)
    size_t offset;      // Смещение в структуре
} Member;

// Структура для интерфейса
typedef struct {
    void (*print)(void*);  // Метод интерфейса
    void (*getName)(void*); // Метод интерфейса
} Interface;

// Структура для обработчиков событий
typedef struct {
    void (*callback)(void*);  // Указатель на функцию обратного вызова
    void* userData;            // Пользовательские данные для обратного вызова
    int priority;              // Приоритет обработчика
    int filter;                // Фильтр для обработки (например, тип события)
} EventHandler;

// Структура для событий
typedef struct {
    EventHandler* handlers;     // Массив обработчиков событий
    int handlerCount;           // Количество обработчиков
} Event;

// Структура Class
typedef struct Class {
    char* name;                          // Имя класса
    size_t size;                         // Размер объекта
    void (*constructor)(void*, void**);  // Указатель на конструктор
    void (*destructor)(void*);           // Указатель на деструктор
    void (**methods)(void*, void**);     // Динамический массив указателей на методы
    Member* members;                      // Динамический массив членов класса
    int method_count;                     // Количество методов
    int member_count;                     // Количество членов
    struct Class** base;                  // Динамический массив указателей на базовые классы
    int base_count;                       // Количество базовых классов
    Interface** interfaces;               // Динамический массив указателей на интерфейсы
    int interface_count;                  // Количество интерфейсов
    void (**friends)(void*);              // Динамический массив дружественных функций
    int friend_count;                     // Количество дружественных функций
} Class;

Class* CreateClass(const char* name, size_t size);

void RegisterClass(Class* cls,
    void (*constructor)(void*, void**),
    void (*destructor)(void*),
    void (**methods)(void*, void**),
    int method_count,
    Member* members,
    int member_count,
    Class** bases,
    int base_count,
    Interface** interfaces,
    int interface_count,
    void (**friends)(void*),
    int friend_count);

void* CreateInstance(Class* cls, void** args);
void DeleteInstance(Class* cls, void* instance);
void* GetField(Class* cls, void* instance, const char* fieldName);
void* GetPrivateField(Class* cls, void* instance, const char* fieldName);
Event* CreateEvent();
void AddEventHandler(Event* event, void (*callback)(void*), void* userData, int priority, int filter);
void TriggerEvent(Event* event, int eventType);
void DeleteEvent(Event* event);
