
#include <stdio.h>

#include <trees.h>
#include "mytree.h"


int main() {
    const ExValue values[50] = { };
    const int32_t class = exforest_predict(&myclassifier, values, 50);
    printf("class=%d\n", class);
}
