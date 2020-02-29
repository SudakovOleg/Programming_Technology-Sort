#ifndef VALUE_H
#define VALUE_H

//Класс для хранения лексикографического элемента
class Value
{
private:
    //Хранимая строка
    char *val;
    //Число разрядов
    int n;
public:
    Value();
    //Инициализатор
    void Init(int);
    //Метод получения одного разряда
    int getChar(int);
    //Метод для добавления строки
    void push(char*);
    //Получение всей строки
    char *pop();
    //Метод очистки
    void clear();
    ~Value();
};

#endif // VALUE_H
