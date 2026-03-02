// Opdracht 3:
// a)	Geef de gebruiker de mogelijkheid om een string inclusief spaties in te voeren via scanf. Zie de format specifiers in de reference
// b)	Zorg dat er een maximaal aantal karakters ingevoerd mag worden die overeenkomt met de char array waarin de karakters komen te staan.
// c)	Laat de gebruiker het volgende invoeren: Temperatuur : 24 (of een andere waarde). De temperatuur is hier de key en 24 de value. Parse met sscanf vervolgens de ingelezen “string” waarbij zowel de key als de value in een 2 verschillende variabelen komen. Gebruik geen atoi.
// d)	Vraag aan de gebruiker om nieuwe invoer als de value geen numerieke waarde is.
// e)	De gebruiker kan ook invoeren Brandstof : benzine of “Brandstof” : “LPG” ook diesel of kerosine zijn toegestane waardes. Geef aan dat een ongeldige brandstof is ingevuld bij een andere waarde

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARS 45

typedef struct {
    char key[MAX_CHARS];
    char value[MAX_CHARS];
} KeyValue;

// Functie om te checken of een string numeriek is
int is_numeric(const char *str) {
    if (str[0] == '\0') return 0;  // Lege string
    
    int i = 0;
    // Optioneel minteken
    if (str[0] == '-') i = 1;
    
    // Controleer of alle karakters digits zijn
    while (str[i] != '\0') {
        if (!isdigit(str[i])) return 0;
        i++;
    }
    
    return i > 0;  // Minstens één digit moet er zijn
}

// Functie om te checken of een brandstof geldig is
int is_valid_fuel(const char *fuel) {
    const char *valid_fuels[] = {"benzine", "LPG", "diesel", "kerosine"};
    int fuel_count = 4;
    
    for (int i = 0; i < fuel_count; i++) {
        if (strcmp(fuel, valid_fuels[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Functie om de waarde te valideren op basis van de key
int is_valid_value(const char *key, const char *value) {
    // Verwijder leading/trailing spaties van key
    int start = 0, end = strlen(key) - 1;
    while (start <= end && isspace(key[start])) start++;
    while (end >= start && isspace(key[end])) end--;
    
    char key_trimmed[MAX_CHARS];
    strncpy(key_trimmed, key + start, end - start + 1);
    key_trimmed[end - start + 1] = '\0';
    
    // Controleer op Brandstof
    if (strcmp(key_trimmed, "Brandstof") == 0) {
        return is_valid_fuel(value);
    }
    
    // Voor andere keys moet value numeriek zijn
    return is_numeric(value);
}

int main(void) {
    char invoer[MAX_CHARS + 1];
    KeyValue data;
    int ch;
    int valid = 0;

    while (!valid) {
        printf("Voer invoer in (format: key : value): ");
        
        // Lees max 45 karakters inclusief spaties
        scanf("%45[^\n]", invoer);
        
        // Ruim de rest van de input op
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        // Parse met sscanf
        if (sscanf(invoer, "%45[^:] : %45s", data.key, data.value) == 2) {
            // Controleer of value geldig is op basis van key
            if (is_valid_value(data.key, data.value)) {
                printf("Key: %s\n", data.key);
                printf("Value: %s\n", data.value);
                valid = 1;
            } else {
                // Geef passende foutmelding
                int start = 0, end = strlen(data.key) - 1;
                while (start <= end && isspace(data.key[start])) start++;
                while (end >= start && isspace(data.key[end])) end--;
                char key_trimmed[MAX_CHARS];
                strncpy(key_trimmed, data.key + start, end - start + 1);
                key_trimmed[end - start + 1] = '\0';
                
                if (strcmp(key_trimmed, "Brandstof") == 0) {
                    printf("Error: Ongeldige brandstof. Geldige waardes: benzine, LPG, diesel, kerosine\n");
                } else {
                    printf("Error: Value moet numeriek zijn. Probeer opnieuw.\n");
                }
            }
        } else {
            printf("Ongeldig formaat. Gebruik: key : value\n");
        }
    }

    return 0;
}