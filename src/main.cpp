#include <iostream>
#include <ctime>
#include <time.h>
#include <fstream>
#include "/home/tobiasz/SD_proj3/include/HashTable.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable1.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable2.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable3.hpp"

/*
    Aplikacja testująca wykożystuje 
    metode wirtualną i metode clone
*/
using namespace std;
const int nr_structures{5000};
const int nr_str_copys{100};
const int key_range{50000};
const int valu_lenght{10};
int *addRandNumber(HashTable* hashtable)
{
   int *keys_table = new int[nr_structures];
   string char_set = "ABCDEFGHIJKLMNOPRSTUWXYZabcdefghijklmnoperstuwxyz1234567890";
   for(int i = 0; i<nr_structures; i++)
   {
    string new_string;
    for(int i = 0; i<valu_lenght; i++)
    {
        new_string += char_set[rand()%char_set.length()];
    }
    keys_table[i] = std::rand() % key_range; 
    hashtable->insert(keys_table[i],new_string);
   }
   return keys_table;
}
int insertTime(HashTable* hashtable)
{
    string char_set = "ABCDEFGHIJKLMNOPRSTUWXYZabcdefghijklmnoperstuwxyz1234567890";
    string new_string;
    for(int i = 0; i<valu_lenght; i++)
    {
        new_string += char_set[rand()%char_set.length()];
    }
    HashTable* test_table;
    int result = 0;
    for(int i = 0; i<nr_str_copys; i++)
    {
        test_table = hashtable->clone();
        int new_key = std::rand() % key_range;
        int start = clock();
        test_table->insert(new_key,new_string);
        result +=(clock() - start);
        delete test_table;
    }
    return result;

}
int removeTime(HashTable* hashtable, int *keys_tab)
{
    HashTable* test_table;
    int result = 0;
    for(int i = 0; i<nr_str_copys; i++)
    {
        test_table = hashtable->clone();
        int start = clock();
        test_table->remove(keys_tab[rand()%nr_structures]);
        result += (clock() - start);
        delete test_table;
    }
    return result;
}
int main()
{
    srand(time(NULL));
    
    ofstream data("../data.txt");
    int* keys_tab;
    long long int restab[11];
    long long int restab2[11];
    HashTable2 hash1;
    HashTable2 hash2;
    HashTable3 hash3;
    HashTable* hash = &hash1;
    char chouse_imp;
    cout<<"1: i defult adresacja otwarta"<<endl
    <<"2: kukułcze"<<endl
    <<"3: drzewo AVL"<<endl<<endl;
    cin>>chouse_imp;
    switch (chouse_imp)
    {
    case '1':
        break;
    case '2':
        hash = &hash2;
        break;
    case '3':
        hash = &hash3;
        break;
    default:
        break;
    }
    for(int j = 0; j < 11; j++)
    {
        keys_tab = addRandNumber(hash);
        restab[j] = insertTime(hash);
        restab2[j] = removeTime(hash, keys_tab);
    }
    delete[] keys_tab;
    for(int i = 0; i<10; i++)
        {
        cout<<restab[i]<<endl;
        data<<restab[i]<<endl;
        }
        cout<<endl;
        data<<endl;
        for(int i = 0; i<10; i++)
        {
        cout<<restab2[i]<<endl;
        data<<restab2[i]<<endl;
    }
    return 0;
}