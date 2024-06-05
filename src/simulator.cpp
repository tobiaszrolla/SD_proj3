#include <iostream>
#include "/home/tobiasz/SD_proj3/include/HashTable.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable1.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable2.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable3.hpp"

using namespace std;
void menu(HashTable* hash_table)
{
    bool wyjscie = false;
    char choise;
    int key;
    string value;
    while(!wyjscie)
    {
        wyjscie = false;
        cout<<"Dodaj element: 1"<<endl
        <<"usuń element: 2"<<endl
        <<"Pokaż HashTable: 3"<<endl
        <<"wyjscie: 4"<<endl;
        cin>>choise;
        switch (choise)
        {
        case '1':
            cout<<"Podaj klucz"<<endl;
            cin>>key;
            cout<<"Podaja wartość"<<endl;
            cin>>value;
            hash_table->insert(key,value);
            break;
        case '2':
            cout<<"Podaj klucz"<<endl;
            cin>>key;
            hash_table->remove(key);
            break;
        case '3':
            cout<<endl<<"Display"<<endl<<endl;
            hash_table->display();
            cout<<endl;
            break;
        case '4':
            wyjscie = true;
            break;
        default:
            break;
        }
    }
};
int main()
{
    bool wyjscie = false;
    char key;
    while(!wyjscie)
    {
        wyjscie = false;
        HashTable1 hash1;
        HashTable2 hash2;
        HashTable3 hash3;
        HashTable* hash_table = &hash1;
        cout<<"HashTable adresowanie otwarte 1:"<<endl<<
        "HashTable kukułcze 2:"<<endl<<
        "HashTable z dzewem AVL 3:"<<endl<<
        "Wyscie 4:"<<endl;
        cin>>key;
        switch (key)
        {
        case '1':
            menu(hash_table);
            break;
        case '2':
            hash_table = &hash2;
            menu(hash_table);
            break;
        case '3':
            hash_table = &hash3;
            menu(hash_table);
            break;
        case '4':
            wyjscie = true;
            break;
        default:
            break;
        }

    }
    return 0;
}

