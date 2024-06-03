#ifndef HASHTABLE1_H_
#define HASHTABLE1_H_
#include "HashTable.hpp"
/* Liniowe hashowanie*/
class HashTable1 :public HashTable
{
private:
    struct HashNode
    {
        int key;
        std::string value;
        bool is_deleted;
        HashNode(): value{""}, key{-1}, is_deleted{false}{}; 
    };
    //tablica HashNodów
    HashNode* table;
    //rozmiar i  zapełnienie
    int size;
    int count;
    //stopień zapełnienia 70 proc usprawnia działanie hash table
    const double loadfactor{0.7};
    //funkcja hashująca modulo
    int hashFunction(int key);
    //funkcja przepisująca tablice i zwiększająca rozmiar
    void revrite();
    
public:
    //konst destr
    HashTable1();
    //głębokie kopiowanie
    HashTable1(const HashTable1& other);
    //przeciążenie operatora =
    HashTable1& operator=(const HashTable1& other);
    ~HashTable1();
    //dodanie klucza z wartością
    void insert(int key, std::string value);
    //usunięcie klucza zwartoscią;
    void remove(int key);
    //display 
    void display();
    //clon aby dobrze kopiować metody virtualne
    HashTable1* clone() const;

};


#endif /*HASHTABLE1_H_*/