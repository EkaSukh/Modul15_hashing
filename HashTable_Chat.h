#pragma once
#pragma warning(disable : 4996)
#include <string.h>
#include <iostream>
#define SIZE 10
#define LOGINLENGTH 10

typedef unsigned int uint;

class HashTable { // хеш-таблица
public:
    HashTable();
    ~HashTable();
    void add(char name[LOGINLENGTH], uint newval);  // добавление элемента
    void  printLine();
    void resize();

    void del(char name[LOGINLENGTH]);
    uint find(char name[LOGINLENGTH]);

private:

    enum enPairStatus {
        free, // свободен
        engaged, //зан€т
        deleted //удален
    };

    struct Pair { // пара ключ-значение

        Pair() : // конструктор по умолчанию
            login(""),
            sta_hash(-1),
            status(enPairStatus::free) {

        }
        Pair(char name[], uint hash) : // конструктор копировани€
            sta_hash(hash),
            status(enPairStatus::engaged){ 
            strcpy(login, name);
            
        }
        Pair& operator = (const Pair& other) { //  оператор присваивани€
            sta_hash = other.sta_hash;
            strcpy(login, other.login);
            status = other.status;

            return *this;
        }
        char login[LOGINLENGTH]; // им€ фрукта (ключ)
        uint sta_hash; // количество фрукта (значение)

        enPairStatus status; // состо€ние €чейки
    };

    int hash(char name[LOGINLENGTH], int offset); // хеш-функци€
    
    

    Pair* array; // массив данных
    int count; // количество элементов
    int mem_size;//исходный размер массива
};


