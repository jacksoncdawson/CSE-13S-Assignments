#include "hash.h"

#include "badhash.h"

#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 1000

Hashtable *hash_create(void) {
    // Allocate memory for the hash table
    Hashtable *new_table = calloc(1, sizeof(Hashtable));
    if (new_table == NULL) {
        return NULL;
    }

    // Allocate memory for the array of linked lists
    new_table->table = calloc(HASH_TABLE_SIZE, sizeof(LL *));
    if (new_table->table == NULL) {
        free(new_table);
        return NULL;
    }

    // Initialize each linked list in the array
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        new_table->table[i] = list_create();

        // If a linked list fails to initialize, cleanup and return NULL
        if (new_table->table[i] == NULL) {
            // Cleanup previously allocated list pointers
            for (int j = 0; j < i; j++) {
                list_destroy(&new_table->table[j]);
            }
            free(new_table->table);
            free(new_table);
            return NULL;
        }
    }
    return new_table;
}

// Add a key-value pair to the hash table
bool hash_put(Hashtable *ht, char *key, int val) {

    // Hash the key to get the index in the hash table
    unsigned int index = hash(key) % HASH_TABLE_SIZE;
    LL *list = ht->table[index];

    // Check if the item already exists and update it
    item temp_item;
    strncpy(temp_item.key, key, sizeof(temp_item.key));
    item *found_item = list_find(list, cmp, &temp_item);

    if (found_item != NULL) {
        found_item->id = val; // Update the value if key is found
        return true;
    }

    // Otherwise, create a new item...
    item *new_item = calloc(1, sizeof(item));
    if (new_item == NULL) {
        return false;
    }
    strncpy(new_item->key, key, sizeof(new_item->key));
    new_item->id = val;

    // Add the new item to the linked list
    list_add(list, new_item);
    free(new_item);

    return true;
}

// Get a value from the hash table by key.
int *hash_get(Hashtable *ht, char *key) {
    if (ht == NULL) {
        return NULL;
    } else if (strlen(key) > 255) {
        return NULL;
    }

    // Hash the key to get the index in the hash table
    unsigned int index = hash(key) % HASH_TABLE_SIZE;
    LL *list = ht->table[index];

    // Find the item in the linked list
    item temp_item;
    strncpy(temp_item.key, key, sizeof(temp_item.key));
    item *found_item = list_find(list, cmp, &temp_item);

    if (found_item == NULL) {
        return NULL;
    }

    return &found_item->id;
}

// Destroy the hash table and free all associated memory.
void hash_destroy(Hashtable **ht) {
    if (ht == NULL || *ht == NULL) {
        return;
    }

    // Free all linked lists
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        list_destroy(&((*ht)->table[i]));
    }

    // Free the table of lists and the table itself
    free((*ht)->table);
    free(*ht);
    *ht = NULL;
}
