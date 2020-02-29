/*TODO:
 * Путем двух циклов перекидывать объекты местами
 * Переписать под список
 * ------------Вариант оптимизации-----------
 * Заранее создать массив хранящий все !Используемые! символы,
 * тем самым уменьшив кол-во обходов, но данный массив также требуется
 * сортировать. Для его сортировки предпочтительно использовать иной
 * метод - более быстрый.
*/

#include <iostream>
#include <fstream>
#include "value.h"
#include "get.h"

using namespace std;

static int r;
//Список
struct List
{
//Элемент списка
Value* val;
//Ссылка на следующий элемент
List* next;
};

//Функция добавления элемента в список
//Принимает указатель на начало списка и конец списка, а также размер списка
void add_element_to_list(List **begin,List **end, int size)
{
    for(int i(0); i < size; i++)
    {
        //Создаем ячейку в памяти для вставки
        List *insert = new List;
        //Выделяем память под значение в ячейке
        insert->val = new Value;
        //Инициализируем значение (Передаем классу кол-во разрядов)
        insert->val->Init(r);
        //Временная целочисленная переменная
        int temp_int;
        //Создаем объект класса Get для ввода значений
        Get get;
        //Запрашиваем значение
        cout << "Введите " << i + 1 <<  " элемент списка: ";
        //Вводим значение списка ограничив минимум нулем
        get.GetIntMin(&temp_int, 0);
        //Переводим на новою строку
        cout << endl;
        //Вставляем в значение ячейки
        insert->val->push(get.toString(temp_int));
        //Если список пуст
        if(!(*begin))
        {
            //Ставим в начало
            insert->next = nullptr;
            *begin = insert;
            *end = insert;
        }
        //Иначе
        else
        {
            //Ставим в конец списка
            insert->next = nullptr;
            (*end)->next = insert;
            *end = insert;
        }
    }
}

//Функция печати списка
//Принимает указатель на начало списка
void print_list(List *begin)
{
    //Указатель на элемент который будет напечатан, ставим его в начало списка
    List* print = begin;
    while (print != nullptr)
    {
        cout << "Value: " << print->val->pop() << " - and: " << endl;
        print = print->next;
    }
    cout << "Null" << endl;
}

//Функция сортировки
//Принимает указатели на начало и конец списка
void sort(List **begin,List **end)
{
    //Массив знаков содержащий все знаки в списке
    char temp_mass[10] = {'0', '1', '2',
                          '3', '4', '5',
                          '6', '7','8', '9'};
    //Пока не пройдем по всем разрядам
    for(int i(r); i > -1; i--)
    {
        //Создаем временные указатели и указываем на наш список
        List *temp_begin = *begin;
        List *temp_end = *end;
        //Основные же указатели обнуляем, получив два списка
        //Один из которыз пустой
        *begin = nullptr;
        *end = *begin;
        //Временый указатель для работы со списком
        List *temp = temp_begin;
        //Переменная-счетчик для массива знаков
        int k = 0;
        //Пока временный список не пуст
        while(temp_begin)
        {
            //Пока временный указатель не достигнет конца
            while(temp != nullptr)
            {
                //Если данный разряд из данного значения соответствует K'ому знаку
                if(temp->val->getChar(i) == temp_mass[k])
                {
                    //Создаем временные указатели
                    List *t = temp;
                    //Указатель на предыдущий элемент
                    List *t_prv = temp_begin;
                    //Если это начало временного списка
                    if(temp == temp_begin)
                    {
                        //Сдвигаем начало
                        temp_begin = temp_begin->next;
                    }
                    else
                    {
                        //Указатель на предыдущий элемент сдвигаем до
                        //нужной позиций
                        while(t_prv->next != t)
                        {
                            t_prv = t_prv->next;
                        }
                    }
                    //Перемещаем temp далее по списку
                    temp = temp->next;
                    //И указываем на него с предыдущего элемента
                    //тем самым вычеркнув из списка попавшийся элемент
                    t_prv->next = temp;
                    //Вставляем попавшийся в основной список
                    //Если основной список пуст
                    if(!(*begin))
                    {
                        //Вставляем в начало
                        t->next = nullptr;
                        *begin = t;
                        *end = t;
                    }
                    else
                    {
                        //Вставляем в конец
                        t->next = nullptr;
                        (*end)->next = t;
                        *end = t;
                    }
                }
                else
                {
                    //Идем к следующему элементу списка
                    temp = temp->next;
                }
            }
            //Смотрим следующий знак
            k++;
            //Возврощаемся в начало временного списка
            temp = temp_begin;
        }
    }
}

int main()
{
    //Переменная размера списка
    int size;
    //Спрашиваем число разрядов
    cout << "r = ";
    //Создаем объект класса Get для ввода значений
    Get get;
    //Принимаем число разрядов ограничив минимум 1
    get.GetIntMin(&r,1);
    //Спрашиваем размер списка
    cout << endl << "size = ";
    //Принимаем размер списка ограничив минимум 2
    get.GetIntMin(&size, 2);
    //Создаем указатели начала и конца для основного списка
    List *begin = nullptr;
    List *end = begin;
    //Добавляем элементы в список
    add_element_to_list(&begin, &end, size);
    //Сортируем
    sort(&begin, &end);
    //Выводим результат
    print_list(begin);
    return 0;
}

/*
//Ввод данных, выделение памяти и инициализация
void first_step()
{
    //Объект класса Get для исключения неверного ввода
    Get get;
    //Переменные для ввода пользователем кол-ва об. и разрядов
    int size, r;
    //Опрашиваем пользователя
    cout << "Введите количество объектов: ";
    get.GetIntMin(&size, 2);
    cout << "Введите количество разрядов: ";
    get.GetIntMin(&r, 1);
    //Создаем массив объектов заказанный пользователем
    Value *main_mass = new Value[size];
    //Доп_массив, пригодится позже
    Value *temp_mass = new Value[size];
    //Инициализируем(Прописываем кол-во разрядов каждому объекту
    for(int i(0); i < size; i++)
    {
        main_mass[i].Init(r);
    }
    //Временная строка для заполнения списка
    //(Заполнения каждого объекта)
    char *temp = new char[r];
    //Просим у пользователя эл-ты и кладем их
    for(int i(0); i < size; i++)
    {
        cout << endl << "Введите " << i << " элемент: ";
        cin.getline(temp,r);
        main_mass[i].push(temp);
    }
    char *mass_of_simvols = new char[size*r];
    int k = 0;
    for(int i(0); i < size; i++)
    {
        for (int j(0); j < r; j++)
        {
            mass_of_simvols[k] = (char)main_mass[i].getChar(j);
            k++;
        }
    }
    //Сортируем
    for(int i(r); i > -1; i--)
    {
        while ()
        {

        }
    }
}



            //Если символ совпал
            if(temp->val->getChar(i) == temp_mass[k])
            {
                //Создаем временные указатели
                List *t = temp;
                List *t_prv = temp_begin;
                //Указатель на предыдущий элемент сдвигаем до
                //нужной позиций
                while(t_prv->next != t)
                {
                    t_prv = t_prv->next;
                }
                //Если это начало списка
                if(temp == temp_begin)
                {
                    temp_begin = temp_begin->next;
                }
                //Перемещаем temp далее по списку
                temp = temp->next;
                //И указываем на него с предыдущего элемента
                //тем самым вычеркнув из списка попавшийся элемент
                t_prv->next = temp;
                //Вставляем попавшийся в основной список
                if(!(*begin))
                {
                    t->next = nullptr;
                    *begin = t;
                    *end = t;
                }
                else
                {
                    temp->next = nullptr;
                    (*end)->next = t;
                    *end = t;
                }
            }
            if(temp->next == nullptr || k == 10)
            {
                k = -1;
                temp = temp_begin;
            }
*/
