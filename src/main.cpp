#include <iostream>
#include "/home/tobiasz/SD_proj3/include/HashTable.hpp"
#include "/home/tobiasz/SD_proj3/include/HashTable1.hpp"

using namespace std;

int main()
{
    HashTable1 hash1;
    hash1.insert(8,"fafaf");
    hash1.insert(20,"3123faaassfsafasfasfafas");
    hash1.remove(9);
    hash1.display();
    return 0;
}