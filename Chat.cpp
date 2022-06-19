#include "Chat.h"
#include <iostream>
#include "string.h"

Chat::Chat() {
    data_count = 0;
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    
    uint* pass = sha1(_pass, pass_length*sizeof(char));
    
    uint p = *pass;
    data[data_count] = AuthData(_login, pass);
    data_count++;
    
    //и кладем запись в хештаблицу
    users_hash_massive.add(_login, p);

}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    
    // Нужно вернуть true в случае успешного логина
    std::string name;
    std::string input_name = _login;
    uint sta_hash = users_hash_massive.find(_login);

    if (sta_hash == -1)
    {
        std::cout << "No such user.\n";
        return false;
    }

    uint* pass_trial = sha1(_pass, pass_length * sizeof(char));
    if (*pass_trial == sta_hash)
        return true;

    return false;        
}

/*

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    data[data_count++] = AuthData(_login, sha1(_pass, pass_length));
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    // Нужно вернуть true в случае успешного логина
    int i = 0;
    for(; i<data_count; i++) {
        AuthData& ad = data[i];
        if (!strcmp(ad.login, _login)) {
            break;
        }
    }
    if(i >= data_count) return false;

    uint* digest = sha1(_pass, pass_length);

    bool cmpHashes = !memcmp(
                        data[i].pass_sha1_hash,
                        digest,
                        SHA1HASHLENGTHBYTES);
    delete[] digest;

    return cmpHashes;
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    // Нужно вернуть true в случае успешного логина
    std::string name;
    std::string input_name = _login;
    int index = -1;
    for (int i = 0; i < data_count; i++)
    {
        name = data[i].login;
        if (input_name.compare(name) == 0)
            index = i;
    }
    if (index < 0)
    {
        std::cout << "No such user.\n";
        return false;
    }

    uint* pass_trial = sha1(_pass, pass_length * sizeof(char));
    if (*pass_trial == *data[index].pass_sha1_hash)
        return true;

    return false;

}

*/