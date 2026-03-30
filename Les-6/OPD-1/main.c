#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAKKEN 10

// Struct definitie
struct vak {
    char naam[20];
    int ECTS;
};

// ========== FUNCTIE a) ==========
// Gebruiker laat vakken invullen in een directe array
void vulArrayIn(struct vak vakArray[], int *aantalVakken) {
    int i = 0;
    char naam[20];
    
    printf("\n--- Invoer vakken (directe array) ---\n");
    printf("Voer vaknamen in (lege invoer om te stoppen):\n");
    
    while (i < MAX_VAKKEN) {
        printf("Naam vak %d: ", i + 1);
        scanf("%19s", naam);
        
        // Stop als gebruiker niets invoert (lege string heeft lengte 0)
        if (strlen(naam) == 0) {
            break;
        }
        
        strcpy(vakArray[i].naam, naam);
        printf("ECTS punten: ");
        scanf("%d", &vakArray[i].ECTS);
        
        i++;
        printf("\n");
    }
    
    *aantalVakken = i;
    printf("Totaal %d vakken ingevoerd.\n", *aantalVakken);
}

// ========== FUNCTIE b) ==========
// Pointer array met malloc voor elke struct
struct vak** vulPointerArrayIn(int *aantalVakken) {
    struct vak** vakPointers = (struct vak**)malloc(MAX_VAKKEN * sizeof(struct vak*));
    
    if (vakPointers == NULL) {
        printf("Geheugen allocatie mislukt!\n");
        return NULL;
    }
    
    int i = 0;
    char naam[20];
    
    printf("\n--- Invoer vakken (pointer array) ---\n");
    printf("Voer vaknamen in (lege invoer om te stoppen):\n");
    
    while (i < MAX_VAKKEN) {
        printf("Naam vak %d: ", i + 1);
        scanf("%19s", naam);
        
        // Stop als gebruiker niets invoert
        if (strlen(naam) == 0) {
            break;
        }
        
        // Alloceer geheugen voor een struct vak
        vakPointers[i] = (struct vak*)malloc(sizeof(struct vak));
        
        if (vakPointers[i] == NULL) {
            printf("Geheugen allocatie mislukt!\n");
            return NULL;
        }
        
        strcpy(vakPointers[i]->naam, naam);
        printf("ECTS punten: ");
        scanf("%d", &vakPointers[i]->ECTS);
        
        i++;
        printf("\n");
    }
    
    *aantalVakken = i;
    printf("Totaal %d vakken ingevoerd via pointers.\n", *aantalVakken);
    
    return vakPointers;
}

// ========== FUNCTIE c) ==========
// Grootte van arrays afdrukken met uitleg
void printGrootteArrays(struct vak vakArray[], struct vak** vakPointers) {
    printf("\n--- Geheugengrootte (sizeof) ---\n");
    
    // Directe array
    int grootteDirecte = sizeof(vakArray);
    printf("Directe array: sizeof = %d bytes\n", (int)sizeof(vakArray));
    printf("  (Dit is eigenlijk het adres van de array als pointer, dus %zu bytes)\n", sizeof(struct vak*));
    printf("  Voor 10 structs: 10 * %zu = %zu bytes (1 struct = naam[20] + int = 24 bytes)\n",
           sizeof(struct vak), 10 * sizeof(struct vak));
    
    // Pointer array
    printf("\nPointer array: sizeof = %zu bytes\n", sizeof(vakPointers));
    printf("  Dit is slechts een pointer naar het eerste element\n");
    printf("  De array zelf: 10 * %zu = %zu bytes (10 pointers)\n", 
           sizeof(struct vak*), 10 * sizeof(struct vak*));
    printf("  PLUS: %zu bytes per struct vak (naam[20] + int = 24 bytes)\n",
           sizeof(struct vak));
    
    printf("\nVERSCHIL:\n");
    printf("  - Directe array: alle data samenhangend in geheugen (continu)\n");
    printf("  - Pointer array: pointers in rij, data verspreid (fragmentarisch)\n");
}

// ========== FUNCTIE e) ==========
// Vak vervangen in directe array
void vervangVakDirecte(struct vak vakArray[], int aantalVakken, int index) {
    if (index < 0 || index >= aantalVakken) {
        printf("Ongeldige index!\n");
        return;
    }
    
    printf("\nVervang vak %d (was: %s, %d ECTS)\n", index + 1, 
           vakArray[index].naam, vakArray[index].ECTS);
    printf("Nieuwe naam: ");
    scanf("%19s", vakArray[index].naam);
    printf("Nieuwe ECTS: ");
    scanf("%d", &vakArray[index].ECTS);
    printf("Vak vervangen!\n");
}

// ========== FUNCTIE f) ==========
// Vak vervangen in pointer array (geen geheugenlek)
void vervangVakPointer(struct vak** vakPointers, int aantalVakken, int index) {
    if (index < 0 || index >= aantalVakken) {
        printf("Ongeldige index!\n");
        return;
    }
    
    printf("\nVervang vak %d (was: %s, %d ECTS)\n", index + 1,
           vakPointers[index]->naam, vakPointers[index]->ECTS);
    
    // Geen geheugenlek: eerst oude geheugen vrijgeven
    free(vakPointers[index]);
    
    // Dan nieuw geheugen alloceren
    vakPointers[index] = (struct vak*)malloc(sizeof(struct vak));
    
    if (vakPointers[index] == NULL) {
        printf("Geheugen allocatie mislukt!\n");
        return;
    }
    
    printf("Nieuwe naam: ");
    scanf("%19s", vakPointers[index]->naam);
    printf("Nieuwe ECTS: ");
    scanf("%d", &vakPointers[index]->ECTS);
    printf("Vak vervangen!\n");
}

// Functie om vakken af te drukken
void printVakken(struct vak vakArray[], int aantalVakken) {
    printf("\n--- Vakken (directe array) ---\n");
    for (int i = 0; i < aantalVakken; i++) {
        printf("%d. %s - %d ECTS\n", i + 1, vakArray[i].naam, vakArray[i].ECTS);
    }
}

void printVakkenPointer(struct vak** vakPointers, int aantalVakken) {
    printf("\n--- Vakken (pointer array) ---\n");
    for (int i = 0; i < aantalVakken; i++) {
        printf("%d. %s - %d ECTS\n", i + 1, vakPointers[i]->naam, vakPointers[i]->ECTS);
    }
}

// Geheugen vrijgeven
void vrijVrij(struct vak** vakPointers, int aantalVakken) {
    for (int i = 0; i < aantalVakken; i++) {
        free(vakPointers[i]);
    }
    free(vakPointers);
}

// ========== MAIN ==========
int main(void) {
    struct vak vakArray[MAX_VAKKEN];
    int aantalDirecte = 0;
    int aantalPointer = 0;
    
    printf("=== OPDRACHT 1: STRUCTS EN ARRAYS ===\n");
    
    // a) Directe array vullen
    vulArrayIn(vakArray, &aantalDirecte);
    printVakken(vakArray, aantalDirecte);
    
    // b) Pointer array vullen
    struct vak** vakPointers = vulPointerArrayIn(&aantalPointer);
    if (vakPointers == NULL) {
        return 1;
    }
    printVakkenPointer(vakPointers, aantalPointer);
    
    // c) Grootte afdrukken
    printGrootteArrays(vakArray, vakPointers);
    
    // e) Vak vervangen in directe array
    if (aantalDirecte > 0) {
        printf("\n=== Vervang vak in directe array ===\n");
        vervangVakDirecte(vakArray, aantalDirecte, 0);
        printVakken(vakArray, aantalDirecte);
    }
    
    // f) Vak vervangen in pointer array
    if (aantalPointer > 0) {
        printf("\n=== Vervang vak in pointer array ===\n");
        vervangVakPointer(vakPointers, aantalPointer, 0);
        printVakkenPointer(vakPointers, aantalPointer);
    }
    
    // Opruimen
    vrijVrij(vakPointers, aantalPointer);
    
    printf("\n=== Programma beëindigd ===\n");
    return 0;
}
