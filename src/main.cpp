#include <iostream>
#include <ctime>
#include <time.h>
#include <fstream>
#include "/home/tobiasz/SD_proj3/include/HashTable.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable1.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable2.hpp"

using namespace std;
const int nr_structures{500};
const int nr_str_copys{50};
const int key_range{60000};
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
    /*HashTable2 hash;
    hash.insert(22,"341411dafa");
    hash.display();
    hash.remove(22);
    hash.display();*/   
    srand(time(NULL));
    
    ofstream data("../data.txt");
    int* keys_tab;
    long long int restab[10];
    long long int restab2[10];
    HashTable2 hash2;
    HashTable* hash = &hash2;
    for(int j = 0; j < 10; j++)
    {
        keys_tab = addRandNumber(hash);
        restab[j] = insertTime(hash);
        restab2[j] = removeTime(hash, keys_tab);
        delete keys_tab;
    }
    
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