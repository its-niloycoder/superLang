#include <string.h>
#include <stdio.h>
#include <math.h>

// strtok()

int MY_strcmp(const char *dest, const char *src) {
    while (*dest && (*dest == *src)) {
        dest++;
        src++;
    }
    return *(unsigned char *)dest - *(unsigned char *)src;
}

int main(int argc, char const *argv[])
{
    
    
    printf("RESULT: %d\n", strcmp(argv[1], argv[2]));
    printf("RESULT: %d\n", MY_strcmp(argv[1], argv[2]));
    return 0;
}
