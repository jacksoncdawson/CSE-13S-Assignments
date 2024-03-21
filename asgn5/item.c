#include "item.h"

#include <stdio.h>
#include <string.h>

bool cmp(item *i1, item *i2) {
    if (strcmp(i1->key, i2->key) == 0) {
        return true;
    }
    return false;
}
