
#include <stdio.h>

#include <emtrees.h>
#include "mytree.h"

int main() {
    const EmtreesValue values[50] = { };
    const int32_t class = emtrees_predict(&myclassifier, values, 50);
    printf("class=%d\n", class);
}
