
#include <stdio.h>

#include <trees.h>
#include "mytree.h"


int main() {
    const ExValue values[50] = { };
    const int32_t class = extree_predict(&mytree, values, 50);
    printf("class=%d\n", class);
}
