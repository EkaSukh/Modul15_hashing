#pragma once
#pragma warning(disable : 4996)
#include <string.h>
#include <iostream>
#define SIZE 10
#define LOGINLENGTH 10

typedef unsigned int uint;

class HashTable { // ���-�������
public:
    HashTable();
    ~HashTable();
    void add(char name[LOGINLENGTH], uint newval);  // ���������� ��������
    void  printLine();
    void resize();

    void del(char name[LOGINLENGTH]);
    uint find(char name[LOGINLENGTH]);

private:

    enum enPairStatus {
        free, // ��������
        engaged, //�����
        deleted //������
    };

    struct Pair { // ���� ����-��������

        Pair() : // ����������� �� ���������
            login(""),
            sta_hash(-1),
            status(enPairStatus::free) {

        }
        Pair(char name[], uint hash) : // ����������� �����������
            sta_hash(hash),
            status(enPairStatus::engaged){ 
            strcpy(login, name);
            
        }
        Pair& operator = (const Pair& other) { //  �������� ������������
            sta_hash = other.sta_hash;
            strcpy(login, other.login);
            status = other.status;

            return *this;
        }
        char login[LOGINLENGTH]; // ��� ������ (����)
        uint sta_hash; // ���������� ������ (��������)

        enPairStatus status; // ��������� ������
    };

    int hash(char name[LOGINLENGTH], int offset); // ���-�������
    
    

    Pair* array; // ������ ������
    int count; // ���������� ���������
    int mem_size;//�������� ������ �������
};


