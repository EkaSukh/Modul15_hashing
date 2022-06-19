#include "HashTable_Chat.h"

HashTable::HashTable() {
    count = 0;
    mem_size = 10;
    array = new Pair[mem_size];
}

HashTable::~HashTable() {
    delete[] array;
}

//������� ��� �� login
int HashTable::hash(char name[LOGINLENGTH], int offset) {
    //��������� ������� ��������� H(K) = [M*{A*K}]
    const int M = 10;
    const float A = 0.1;

    //����� �� ������
    int sum = 0;
    for (int i = 0; i < LOGINLENGTH; i++) {
        sum += name[i];
    }

    //�������������� 
    float part1 = ((float)sum * A);
    int part2 = sum * A;
    float part3 = part1 - part2;

    int part4 = M * part3;

    return (part4 + offset * offset) % mem_size;
}

void HashTable::resize() {
    //��������� ������
    Pair* old_array = array;
    int old_size = mem_size;

    //����������� ������
    mem_size *= 2;
    count = 0;
    //������� ����� ������
    array = new Pair[mem_size];

    //������� ������ ������ � �����
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

    //������ �� �����
    delete[] old_array;
}

void HashTable::add(char name[LOGINLENGTH], uint newvall) {    
    //�������� �� ������������� ��������� ������
    if (count >= mem_size - 3)
        resize();

    int index = -1, i = 0;
    // ����� ����� �� ���� i �� 0 �� ������� �������
    for (;i < mem_size; i++) {
        index = hash(name, i);

        if (array[index].status != enPairStatus::engaged) {
            // ������� ������ ������, �������� ��
            break;
        }
    }
    if (i >= mem_size) return; // ��� ���������, ��� �����

    // ������ � ��������� ������ ����
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
    // ����� ����� �� ���� i �� 0 �� ������� �������
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