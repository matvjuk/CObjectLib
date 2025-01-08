// Функция для создания класса
Class* CreateClass(const char* name, size_t size) {
    Class* cls = (Class*)malloc(sizeof(Class));
    cls->name = strdup(name);
    cls->size = size;
    cls->constructor = NULL;
    cls->destructor = NULL;
    cls->methods = NULL;
    cls->members = NULL;
    cls->method_count = 0;
    cls->member_count = 0;
    cls->base = NULL;
    cls->base_count = 0;
    cls->interfaces = NULL;
    cls->interface_count = 0;
    cls->friends = NULL;
    cls->friend_count = 0;
    return cls;
}

// Функция для регистрации класса
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
    int friend_count) {
    cls->constructor = constructor;
    cls->destructor = destructor;

    cls->methods = (void (**)(void*, void**))malloc(sizeof(void*) * method_count);
    for (int i = 0; i < method_count; i++) {
        cls->methods[i] = methods[i];
    }
    cls->method_count = method_count;

    cls->members = (Member*)malloc(sizeof(Member) * member_count);
    for (int i = 0; i < member_count; i++) {
        cls->members[i] = members[i];
    }
    cls->member_count = member_count;

    cls->base = (Class**)malloc(sizeof(Class*) * base_count);
    for (int i = 0; i < base_count; i++) {
        cls->base[i] = bases[i];
    }
    cls->base_count = base_count;

    cls->interfaces = (Interface**)malloc(sizeof(Interface*) * interface_count);
    for (int i = 0; i < interface_count; i++) {
        cls->interfaces[i] = interfaces[i];
    }
    cls->interface_count = interface_count;

    cls->friends = (void (**)(void*))malloc(sizeof(void*) * friend_count);
    for (int i = 0; i < friend_count; i++) {
        cls->friends[i] = friends[i];
    }
    cls->friend_count = friend_count;
}

// Функция для создания экземпляра класса с параметрами конструктора
void* CreateInstance(Class* cls, void** args) {
    void* instance = malloc(cls->size);
    if (cls->constructor) {
        cls->constructor(instance, args);
    }
    return instance;
}

// Функция для удаления экземпляра класса
void DeleteInstance(Class* cls, void* instance) {
    if (cls->destructor) {
        cls->destructor(instance);
    }
    free(instance);
}

// Функция для доступа к публичным и защищенным полям
void* GetField(Class* cls, void* instance, const char* fieldName) {
    for (int i = 0; i < cls->member_count; i++) {
        if (strcmp(cls->members[i].name, fieldName) == 0 &&
            (cls->members[i].type == PUBLIC || cls->members[i].type == PROTECTED)) {
            return (char*)instance + cls->members[i].offset; // Возвращаем указатель на поле
        }
    }

    for (int i = 0; i < cls->base_count; i++) {
        void* field = GetField(cls->base[i], instance, fieldName);
        if (field) {
            return field;
        }
    }

    return NULL; // Поле не найдено
}

void* GetPrivateField(Class* cls, void* instance, const char* fieldName) {
    for (int i = 0; i < cls->member_count; i++) {
        if (strcmp(cls->members[i].name, fieldName) == 0 && cls->members[i].type == PRIVATE) {
            return (char*)instance + cls->members[i].offset; // Возвращаем указатель на приватное поле
        }
    }
    return NULL; // Поле не найдено
}

// Система событий

// Функция для создания события
Event* CreateEvent() {
    Event* event = (Event*)malloc(sizeof(Event));
    event->handlers = NULL;
    event->handlerCount = 0;
    return event;
}

// Функция для добавления обработчика события с фильтром и приоритетом
void AddEventHandler(Event* event, void (*callback)(void*), void* userData, int priority, int filter) {
    event->handlers = (EventHandler*)realloc(event->handlers, sizeof(EventHandler) * (event->handlerCount + 1));
    event->handlers[event->handlerCount].callback = callback;
    event->handlers[event->handlerCount].userData = userData;
    event->handlers[event->handlerCount].priority = priority;
    event->handlers[event->handlerCount].filter = filter;
    event->handlerCount++;
}

// Функция для вызова обработчиков события
void TriggerEvent(Event* event, int eventType) {
    // Сортируем обработчики по приоритету
    for (int i = 0; i < event->handlerCount - 1; i++) {
        for (int j = 0; j < event->handlerCount - i - 1; j++) {
            if (event->handlers[j].priority < event->handlers[j + 1].priority) {
                // Меняем местами приоритеты
                EventHandler temp = event->handlers[j];
                event->handlers[j] = event->handlers[j + 1];
                event->handlers[j + 1] = temp;
            }
        }
    }

    // Вызываем обработчики с соответствующим фильтром
    for (int i = 0; i < event->handlerCount; i++) {
        if (event->handlers[i].filter == eventType || event->handlers[i].filter == -1) { // -1 означает, что обработчик вызывается для всех типов
            event->handlers[i].callback(event->handlers[i].userData);
        }
    }
}

// Функция для освобождения памяти для события
void DeleteEvent(Event* event) {
    free(event->handlers);
    free(event);
}
