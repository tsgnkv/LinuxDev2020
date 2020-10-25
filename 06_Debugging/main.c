#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *p;
    p = malloc(20);
    free(p);
    free(p);
    return 0;
}
