#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "../Headers/hash.h"


void test_hashtable_new() {
    HashTable ht1 = hashtable_new(10);
    HashTable *ht = &ht1;

    assert(ht->tableSize == 10);
}



void test_hashtable_addElement() {
    HashTable ht1 = hashtable_new(10);
    HashTable *ht = &ht1;

    assert(ht->tableSize == 10);
    ht = hashtable_addElement(ht, "Manipal");
    assert(hashtable_lookup(ht, "Manipal") == 1);

    ht = hashtable_addElement(ht, "Udupi");
    assert(hashtable_lookup(ht, "Udupi") == 1);

    ht = hashtable_addElement(ht, "Mangalore");
    assert(hashtable_lookup(ht, "Mangalore") == 1);
}

void test_hashtable_delElement() {
    HashTable ht1 = hashtable_new(10);
    HashTable *ht = &ht1;

    assert(ht->tableSize == 10);
    ht = hashtable_addElement(ht, "Manipal");
    assert(hashtable_lookup(ht, "Manipal") == 1);

    ht = hashtable_addElement(ht, "Udupi");
    assert(hashtable_lookup(ht, "Udupi") == 1);

    ht = hashtable_addElement(ht, "Mangalore");
    assert(hashtable_lookup(ht, "Mangalore") == 1);

    ht = hashtable_delElement(ht, "Mangalore");
    assert(hashtable_lookup(ht, "Mangalore") == 0);

    ht = hashtable_delElement(ht, "Udupi");
    assert(hashtable_lookup(ht, "Udupi") == 0);

    ht = hashtable_delElement(ht, "Manipal");
    assert(hashtable_lookup(ht, "Manipal") == 0);


}

int main(){
    test_hashtable_new();
    test_hashtable_addElement();
    test_hashtable_delElement();
    
    return 0;
}