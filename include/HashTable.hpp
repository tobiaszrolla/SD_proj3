#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <iostream>
class HashTable
{
    public:
        ~HashTable()=default;
        virtual void display()=0;
        virtual void insert(int key, std::string value)=0;
        virtual void remove(int key)=0;
        virtual HashTable* clone() const = 0;
};
#endif /*HASHTABLE1_H_*/