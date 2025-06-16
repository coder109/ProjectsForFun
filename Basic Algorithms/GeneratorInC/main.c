#include <stdio.h>
#include <stdbool.h>

#define GENERATOR(DATATYPE, DATANAME, FUNCTION, CHECKER_FUNCTION) \
DATATYPE DATANAME; \
bool generator_fn() { \
    if(!CHECKER_FUNCTION(DATANAME)) { \
        return false; \
    } else { \
        DATANAME = FUNCTION(DATANAME); \
        return true; \
    } \
} \
DATATYPE next_fn() {\
    generator_fn();\
    return DATANAME;\
}

int change_function(int x) {
    return x + 1;
}

bool check_function(int x) {
    return x < 10;
}

GENERATOR(int, x, change_function, check_function);

int main(int argc, char **argv) {
    x = 0;
    int count = 0;
    while(count < 20) {
        printf("%d ", next_fn());
        count++;
    }
    return 0;
}