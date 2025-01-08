# CObjectLib
CObjectLib is an object-oriented library for the C programming language that allows developers to create and manage objects using the concepts of classes, inheritance, interfaces, generics, and events. The library provides high flexibility and extensibility, allowing users to easily add functionality and respond to events in their applications.

### Название библиотеки: **CObjectLib**

### Краткое описание
**CObjectLib** — это объектно-ориентированная библиотека для языка программирования C, предоставляющая разработчикам возможность создавать и управлять объектами с использованием концепций классов, наследования, интерфейсов, обобщенных типов и событий. Библиотека обеспечивает высокую гибкость и расширяемость, позволяя пользователям легко добавлять функциональность и реагировать на события в своих приложениях.

---

### Оглавление

1. [Установка](#установка)
2. [Основные структуры](#основные-структуры)
3. [Создание классов](#создание-классов)
4. [Интерфейсы](#интерфейсы)
5. [Обобщенные классы](#обобщенные-классы)
6. [Система событий и сигналов](#система-событий-и-сигналов)
7. [Примеры использования](#примеры-использования)
8. [Обработка ошибок и логирование](#обработка-ошибок-и-логирование)
9. [Документация API](#документация-api)
10. [Лицензия](#лицензия)

---

### Установка

1. Скачайте библиотеку из репозитория.
2. Скомпилируйте библиотеку с помощью компилятора C.
3. Включите заголовочный файл `CObjectLib.h` в свой проект.

### Основные структуры

#### Class

```c
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
```

#### Member

```c
typedef struct {
    char* name;         // Имя члена
    MemberType type;    // Тип члена
    size_t offset;      // Смещение в структуре
} Member;
```

#### Interface

```c
typedef struct {
    void (*print)(void*);  // Метод интерфейса
    void (*getName)(void*); // Метод интерфейса
} Interface;
```

#### Event

```c
typedef struct {
    EventHandler* handlers;     // Массив обработчиков событий
    int handlerCount;           // Количество обработчиков
} Event;
```

### Создание классов

#### Пример создания класса

```c
Class* myClass = CreateClass("MyClass", sizeof(MyClass));
RegisterClass(myClass, MyClassConstructor, MyClassDestructor, myClassMethods, methodCount, myClassMembers, memberCount, baseClasses, baseCount, NULL, 0);
```

### Интерфейсы

Интерфейсы позволяют определять контракты для классов.

#### Пример реализации интерфейса

```c
Interface myInterface;
myInterface.print = MyClassPrint;
myInterface.getName = MyClassGetName;
```

### Обобщенные классы

Обобщенные классы могут использоваться для создания классов, работающих с различными типами данных.

#### Пример использования обобщенного класса

```c
GenericList* list = CreateGenericList(10);
AddToGenericList(list, (void*)myInstance);
```

### Система событий и сигналов

Система событий позволяет добавлять обработчики событий и вызывать их при необходимости.

#### Пример добавления обработчика события

```c
Event* myEvent = CreateEvent();
AddEventHandler(myEvent, MyEventHandler, userData, priority, filter);
```

### Примеры использования

```c
int main() {
    Class* point2DClass = CreateClass("Point2D", sizeof(Point2D));
    // Регистрация и создание экземпляров...
}
```

### Обработка ошибок и логирование

#### Пример обработки ошибок

```c
void HandleError(ErrorCode code) {
    // Обработка ошибок...
}
```

### Документация API

- **CreateClass**: Создает новый класс.
- **RegisterClass**: Регистрирует класс с конструктором, деструктором, методами и членами.
- **CreateInstance**: Создает экземпляр класса.
- **DeleteInstance**: Удаляет экземпляр класса.
- **GetField**: Получает значение члена класса по имени.
- **CreateEvent**: Создает новое событие.
- **AddEventHandler**: Добавляет обработчик события.
- **TriggerEvent**: Вызывает все обработчики события.

### Лицензия

Эта библиотека лицензирована под MIT License. Пожалуйста, ознакомьтесь с файлом LICENSE для получения дополнительной информации.

---

### Заключение

Эта документация предоставляет пользователям библиотеки **CObjectLib** четкие указания по установке, использованию и интеграции в проекты. Поддержка интерфейсов, обобщенных классов и системы событий делает библиотеку гибкой и мощной для разработки на C. Вы можете продолжать развивать эту библиотеку, добавляя новые возможности и улучшения на основе отзывов пользователей.
