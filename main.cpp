#include <iostream>
#include "HashTable_Chat.h"
#include "SHA_1.h"
#include "Chat.h"
#define LOGINLENGTH 10


int main()
{
    Chat ch;

    char name1[LOGINLENGTH] = "kate";
    char pass1[LOGINLENGTH] = "katepass";

    ch.reg(name1, pass1, sizeof(pass1));

    char name2[LOGINLENGTH] = "ivan";
    char pass2[LOGINLENGTH] = "ivanpass";

    ch.reg(name2, pass2, sizeof(pass2));
     
    char name3[LOGINLENGTH] = "Konsta";
    char pass3[LOGINLENGTH] = "Konstpass";

    ch.reg(name3, pass3, sizeof(pass3));

    bool scs = ch.login(name3, pass2, sizeof(pass2));
    std::cout << "scs = " << scs;

    //ch.users_hash_massive.printLine();
     
   /*
	HashTable ht;

    ht.add((char*)"apple", 10);
    ht.add((char*)"orange", 15);
    ht.add((char*)"banana", 2);
    ht.add((char*)"lemon", 6);
    ht.add((char*)"pear", 7);
 
    ht.printLine();
    std::cout << std::endl;

    ht.resize();
    ht.printLine();
    std::cout << std::endl;
*/
    //ht.add((char*)"ciwi", 4);
   // ht.add((char*)"mandarin", 9);   

   //int fruit_storage = ht.find((char*)"pear");
   //std::cout << "fruits in strorage " << fruit_storage <<
   //std::cout << std::endl;

   //ht.del((char*)"mandarin");
  //ht.printLine();

    
	return 0;
}