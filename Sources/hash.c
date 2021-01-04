#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../Headers/hash.h"

HashTable hashtable_new(uint32_t size){
    HashTable ht;
    ht.tableSize = size;
    ht.tableAddress = (Node**) malloc(sizeof(Node*) * size);

    for (int i = 0; i < ht.tableSize; i++){
        ht.tableAddress[i] = NULL;
    }

    return ht;
}

static int32_t _hash_(char *data) {
    int32_t hashcode = 0;
    while(*data != '\0') {
        hashcode = (hashcode << 5) + *data++;
    }
    return hashcode;
}

static uint32_t _compression_(int32_t hashcode, uint32_t tableSize) {
    return (hashcode % tableSize);
}

static uint32_t _hashing_(char *data, uint32_t tableSize) {
    int32_t hashcode = _hash_(data);
    uint32_t index = _compression_(hashcode, tableSize);

    return index;
}

uint32_t hashtable_lookup(HashTable *ht, char *data) {
    assert(ht != NULL);
    Node *nodeAdd = ht->tableAddress[_hashing_(data, ht->tableSize)];

    while(nodeAdd != NULL) {
        if (!strcmp(nodeAdd->name, data)){
            break;
        } else {
            nodeAdd = nodeAdd->next;
        }
    }
    return (nodeAdd != NULL);
}

HashTable* hashtable_addElement(HashTable *ht, char *data) {
    assert(ht != NULL);
    if(!hashtable_lookup(ht, data)) {
        uint32_t bucket = _hashing_(data, ht->tableSize);
        Node *oldAdd = ht->tableAddress[bucket];
        ht->tableAddress[bucket] = (Node*)malloc(sizeof(Node));
        strcpy(ht->tableAddress[bucket]->name, data);
        ht->tableAddress[bucket]->next = oldAdd;
    }
    return ht;
}

HashTable* hashtable_delElement(HashTable *ht, char *data) {
    assert(ht != NULL);
    Node *nodeAdd = ht->tableAddress[_hashing_(data, ht->tableSize)];
    Node *temp, *prev = NULL;

    if(nodeAdd->next == NULL) {
       temp = nodeAdd;
       ht->tableAddress[_hashing_(data, ht->tableSize)]  = NULL; 
    } else {
       
        while(nodeAdd != NULL) {
            if (!strcmp(nodeAdd->name, data)){
                 if(ht->tableAddress[_hashing_(data, ht->tableSize)] == nodeAdd) {
                     temp = nodeAdd;
                     ht->tableAddress[_hashing_(data, ht->tableSize)] = nodeAdd->next;
                 } 
                else {
                       prev->next = nodeAdd->next;
                       temp = nodeAdd;
                }
                break;
                
            } else {
                prev = nodeAdd;
                nodeAdd = nodeAdd->next;
            }
        }
    }
    free(temp);

    return ht;
}