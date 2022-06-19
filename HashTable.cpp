#include "HashTable_Chat.h"

HashTable::HashTable() {
    count = 0;
    mem_size = 10;
    array = new Pair[mem_size];
}

HashTable::~HashTable() {
    delete[] array;
}

//создает хэш от login
int HashTable::hash(char name[LOGINLENGTH], int offset) {
    //константы функции умножени€ H(K) = [M*{A*K}]
    const int M = 10;
    const float A = 0.1;

    //сумма от логина
    int sum = 0;
    for (int i = 0; i < LOGINLENGTH; i++) {
        sum += name[i];
    }

    //преобразовани€ 
    float part1 = ((float)sum * A);
    int part2 = sum * A;
    float part3 = part1 - part2;

    int part4 = M * part3;

    return (part4 + offset * offset) % mem_size;
}

void HashTable::resize() {
    //сохран€ем старое
    Pair* old_array = array;
    int old_size = mem_size;

    //увеличиваем пам€ть
    mem_size *= 2;
    count = 0;
    //создаем новый массив
    array = new Pair[mem_size];

    //заносим старый массив в новый
    int index;
    for (int j = 0; j < old_size; j++)
    {
        Pair old = old_array[j];
        if (old.status != enPairStatus::free)
        {
            for (int i = 0; i < mem_size; i++)
            {
                index = hash(old.login, i);
                if (array[index].status != enPairStatus::engaged)
                {
                    array[index] = Pair(old.login, old.sta_hash);
                    count++;
                    break;
                }
            }
        }
    }

    //чистим за собой
    delete[] old_array;
}

void HashTable::add(char name[LOGINLENGTH], uint newvall) {    
    //проверка на необходимость увеличить массив
    if (count >= mem_size - 3)
        resize();

    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (;i < mem_size; i++) {
        index = hash(name, i);

        if (array[index].status != enPairStatus::engaged) {
            // найдена пуста€ €чейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную €чейку пару
    array[index] = Pair(name, newvall);
    count++;
    
}

void  HashTable::printLine()
{
    for (int i = 0; i < mem_size; i++) {
        if (array[i].status == enPairStatus::free)
            std::cout << i << " " << "_____ " << "\n ";
        else if (array[i].status == enPairStatus::deleted)
            std::cout << i << " " << "deleted " << "\n ";
        else
            std::cout << i << " " << array[i].login << " pass: " << array[i].sta_hash << "\n ";
    }
}


void HashTable::del(char name[LOGINLENGTH]) {

    int index;

    for (int i = 0; i < mem_size; i++)
    {
        index = hash(name, i);
        if (array[index].status == enPairStatus::free)
            return;
        if (array[index].status == enPairStatus::engaged)
        {
            if (!strcmp(array[index].login, name))
            {
                array[index].status = enPairStatus::deleted;
                count--;
            }
        }
    }
}


uint HashTable::find(char name[LOGINLENGTH]) {
    
    int index = -1;
    // берем пробы по всем i от 0 до размера массива
    for (int i = 0; i < mem_size; i++)
    {
        index = hash(name, i);
        if (array[index].status == enPairStatus::free)
            return 0;
        if (array[index].status == enPairStatus::engaged)
        {
            if (!strcmp(array[index].login, name))
                return array[index].sta_hash;
        }
    }

    return 0;
}