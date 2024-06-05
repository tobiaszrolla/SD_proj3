#include "../include/HashTable1.hpp"

int HashTable1::hashFunction(int key)
{
    /*
        określa index na podtawie reszty
        z dzielenia przez size;
    */
    return key % size;
}

void HashTable1::revrite()
{
    /*
        Przepisuje tablice hashującą 
        Gdy skończy się rozmiar;
    */
    size *= 2;
    HashNode* old_table = table;
    table = new HashNode[size];
    for (int i = 0; i < size/2; i++) {
            if (old_table[i].key != -1 && !old_table[i].is_deleted) {
                insert(old_table[i].key, old_table[i].value);
            }
        }
    delete[] old_table;
}
HashTable1::HashTable1(): size(80000), count(0)
{
    /*
        Domyślny konstruktor
    */
    table = new HashNode[size];
}
HashTable1::HashTable1(const HashTable1 &other): size(other.size), count(other.count) {
    table = new HashNode[size];
    for (int i = 0; i < size; ++i) {
        table[i] = other.table[i];
    }
}
HashTable1& HashTable1::operator=(const HashTable1& other)
{
    /*
        Przeciążenie = okazało
        się zbędne
    */
    if (this == &other) return *this;
        
        delete[] table;
        
        size = other.size;
        count = other.count;
        table = new HashNode[size];
        for (int i = 0; i < size; ++i) {
            table[i] = other.table[i];
        }
        
        return *this;
}
HashTable1::~HashTable1()
{
    /*
        Usuwa dynamicznie 
        alokowaną tablice
    */
    delete[] table;
}

void HashTable1::insert(int key, std::string value)
{
    /*
        Dodawanie elementu 1 sprawdzienie czy nie przekroczyliśmy lodefactor*
        size jeśli powiększ tablice 2: funkcja hashująca 
        3: zmiana wartości indexu jeśli miejsce zajęte
    */
    if(count >= size*loadfactor)
    {
        this->revrite();
    }
    int first_index = hashFunction(key);
    int index_iter = first_index;
    while(table[index_iter].key != -1 && !table[index_iter].is_deleted)
    {
        index_iter = (index_iter + 1)%size;
    }
    table[index_iter].key = key;
    table[index_iter].value = value;
    table[index_iter].is_deleted = false;
    count++;

    
}

void HashTable1::remove(int key)
{
    /*
        Na podstawie podanego klucza 
        jeśli nie usunięte usuń
    */
    int index = hashFunction(key);
    while (table[index].key != -1)
    {
        if(table[index].key == key && !table[index].is_deleted)
        {
            table[index].is_deleted = true;
            count--;
            return;
        }
        index = index + 1 % size;
    }
    
}

void HashTable1::display()
{
    /*
        Wyświetl wszystkie klucze 
        i wartości w tablicy
    */
    for(int i = 0; i < size; i++)
    {
        if(table[i].key != -1 && !table[i].is_deleted)
        {
            std::cout<<table[i].key<<"\t"<<table[i].value<<std::endl;
        }
        
    }
}
HashTable1* HashTable1::clone() const{
    return new HashTable1(*this);
}
