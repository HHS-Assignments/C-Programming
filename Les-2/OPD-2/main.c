// Opdracht 2:
// Maak een nieuwe versie van kopieerString die controleert of de destination buffer groot genoeg is.

#include <stdio.h>
#include <string.h>

char* stringcopy(const char *src, char *dest, int dest_size);

int main(){
    char str1[14] = "Hello, World!";
    char str2[14];  

    stringcopy(str1, str2, strlen(str1));

    printf("Str 1: %s\n", str1);
    printf("Str 2: %s\n", str2);
    return 0;
}

char* stringcopy(const char *src, char *dest, int dest_size) {
    int i;
    if (strlen(src) + 1 > dest_size) {
        printf("Error: Source string is too large for destination buffer.\n");
        return NULL;
    }else{
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
    }
}