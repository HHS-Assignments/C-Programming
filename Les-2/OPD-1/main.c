// Opdracht: 1:
// Maak een functie kopieerString die hetzelfde doet als de strcpy functie. Maak een eigen implementie zonder gebruik van een standaard C functie.

#include <stdio.h>
#include <string.h>

char* stringcopy(const char *src, char *dest);

int main(){
    char str1[14] = "Hello, World!";
    char str2[14];  

    stringcopy(str1, str2);

    printf("Str 1: %s\n", str1);
    printf("Str 2: %s\n", str2);
    return 0;
}

char* stringcopy(const char *src, char *dest) {
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}