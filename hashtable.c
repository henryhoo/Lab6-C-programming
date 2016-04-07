#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
/**
 * Allocate and initialize an empty hashtable with a table array of size max_size
 * with each slot initialized to NULL.
 * The caller is responsible for freeing the hashtable and its contents later.
 * Parameters:
 *      max_size - The number of entires in the hashtable
 * Returns:
 *      A pointer to the newly allocated and initialized hashtable
 *      which the caller is responsible for later freeing, or NULL
 *      if max_size <= 0
 */
hashtable_t *create_hashtable(int max_size){
    hashtable_t *newtable = malloc(sizeof(hashtable_t));
    newtable->table_len = max_size;
    newtable->table = malloc(max_size*sizeof(hashtable_t*));
//    memset(&newtable->table, 0, max_size*sizeof(hashtable_t*));
    return newtable;
}

/**
 * Free a previously allocated hashtable and all the contents of the entries
 * Parameters:
 *      table - The hashtable to free
 * Returns:
 *      Nothing
 * Remarks:
 *      When freeing the hashtable, you must free the array holding the table,
 *      the chains of nodes and the keys in each node as well
 */
void free_hashtable(hashtable_t *table){
    hashtable_ent_t *walk = *table->table;
    hashtable_ent_t *next = NULL;
    while(*table->table){
        while(walk)
        {
            next = walk->next;
            free(walk);
            walk = next;
        }
        table->table++;
    }
    free(walk);
    free(next);
}

/**
 * Get a value from the table based on the key specified. A key will be located at
 * the hash table[hash(key) % table_len]. If there is no match, this value would be NULL.
 * If there are multiple key collisions, you must search the linked list of collision
 * to see if a node exists with the given key.
 * Parameters:
 *      table   - Pointer to the hashtable structure
 *      key     - Pointer to a string key
 *      value   - Pointer to a double that will be set to the value in the table
 *                  corresponding to the key if the key is found. Ignored if the
 *                  key is not found.
 * Returns:
 *      0 for success, or -1 if any of the parameters are NULL or the key isn't in the table
 */
int get(hashtable_t *table, const char *key, double *value){
    
    int index = hash(key)%table->table_len;
    hashtable_ent_t *p=*table->table;
    if (index>0) {
        for (int i = 0; i < index; i++) {
            /* code */
            p=*++table->table;
        }
    }

    while(p){
        if (strcmp(p->key, key) == 0) {
            /* code */
            value=&(p->value);
            return 0;
        }
        p=p->next;
    }
    return -1;
}

/**
 * Set the specified key to the given value, adding the key to the table
 * if the KEY doesn't already exist. You must store the value in the table
 * array as table[hash(key) % table_len]. If there is a collision with the
 * hash, add a new node to the linked list at the hash location.
 *
 * Parameters:
 *      table - Pointer to the hashtable in which we are setting the value
 *      key - Pointer to the string that is the key
 *      value - Value we are setting the given key equal to
 * Returns:
 *      -1 if the parameters were invalid, or if the set operation failed
 *      such as if an insertion failed because of a malloc() failure.
 
 0 if the operation succeeds.
 * Remarks:
 *      If the key doesn't already exist in the table, add it
 */
int set(hashtable_t *table, const char *key, double value){
    if (table==NULL||key==NULL) {
        /* code */
        return -1;
    }
    int flag = 0;
    int index = hash(key)%table->table_len;
    hashtable_ent_t *p=*table->table;
    if (index>0) {
        for (int i = 0; i < index; i++) {
            /* code */
            p=*++table->table;
        }
    }
    while(p){
        if (strcmp(p->key, key) == 0) {
            /* code */
            p->value=value;
            flag = 1;
            return 0;
        }
        p=p->next;
    }
    if (flag==0) {
        /* code */
        hashtable_ent_t  *new = malloc(sizeof(hashtable_ent_t));
        if (new==NULL) {
            /* code */
            return -1;
        }
        else{
            new->key=(char *)key;
            new->value=value;
            p->next = new;
            return 0;
        }
    }
    return -1;
}

/**
 * Check if a given string key is already in the table.
 * Parameters:
 *      table - Pointer to the hashtable we are checking
 *      key - Pointer to the string that may be a key in table
 * Returns:
 *      1 if the key exists, 0 if the key does not exist, -1 if the
 *      parameters were NULL or an error occured while
 * Remarks:
 *      Remember to check that the strings themselves are equal, not the
 *      pointers since the pointers are not the key
 */
int key_exists(hashtable_t *table, const char *key){
    if (table==NULL||key==NULL) {
        /* code */
        return -1;
    }
    int index = hash(key)%table->table_len;
    hashtable_ent_t *p=*table->table;
    if (index>0) {
        for (int i = 0; i < index; i++) {
            /* code */
            p=*++table->table;
        }
    }
    while(p){
        if (strcmp(p->key, key) == 0) {
            /* code */
            return 1;
        }
        p=p->next;
    }
    return 0;
}

/**
 * Remove a given key from the table if it exists
 * Returns:
 *      -1 if the key didn't exist, the parameters were invalid
 *      or there was another error
 *		0 if the key was successfully removed
 * Remarks:
 *      Since this hashtable handles collision by chaining, it is possible
 *      for deletions to occur anywhere in the chain (start, end, or middle).
 *      Remember to deallocate memory in the node and the node itself and reset
 *      the node back to an initial state so later we can reuse the node
 */
int remove_key(hashtable_t *table, const char *key){
    if (table==NULL||key==NULL) {
        /* code */
        return -1;
    }
    int index = hash(key)%table->table_len;
    hashtable_ent_t *p=*table->table;
    if (index>0) {
        for (int i = 0; i < index; i++) {
            /* code */
            p=*++table->table;
        }
    }
    if (strcmp(p->key, key) == 0) {
        /* code */
        hashtable_ent_t *next = *table->table;
        if(next->next!=NULL){
            *table->table=next->next;}
        else{
            *table->table=NULL;}
        free(next);
        return 0;
    }
    else{
        while(p){
            if (strcmp(p->next->key, key) == 0) {
                /* code */
                
                if(p->next->next!=NULL){
                    p->next=p->next->next;
                    free(p->next);
                }
                else{
                    free(p->next);
                    p->next=NULL;
                }
                return 0;
            }
            p=p->next;
        }
    }
    return -1;
    
}
