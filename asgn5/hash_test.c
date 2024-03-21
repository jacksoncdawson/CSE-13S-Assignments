#include "hash.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create a hash table
    Hashtable *ht = hash_create();
    if (ht == NULL) {
        fprintf(stderr, "Failed to create hash table\n");
        return EXIT_FAILURE;
    }

    // Insert some key-value pairs into the hash table
    if (!hash_put(ht, "key1", 1)) {
        fprintf(stderr, "Failed to put key1\n");
    }
    if (!hash_put(ht, "key2", 2)) {
        fprintf(stderr, "Failed to put key2\n");
    }
    if (!hash_put(ht, "key3", 3)) {
        fprintf(stderr, "Failed to put key3\n");
    }

    // Destroy the hash table
    hash_destroy(&ht);
    if (ht != NULL) {
        fprintf(stderr, "Failed to destroy hash table\n");
    }

    return EXIT_SUCCESS;
}
