/* Opdracht 2:
Maak een spel hoger lager met een beperkt aantal beurten. Print na afloop ook alle ingevoerde
getallen en vraag of de speler nogmaals wil spelen. Maak een random getal tussen een (door de
gebruiker) te kiezen ondergrens en een te kiezen bovengrens met de rand functie uit de stdlib:
https://en.cppreference.com/w/c/numeric/random/rand
Verberg de complexiteit van het maken van een random getal in een functie */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomGetal(int ondergrens, int bovengrens) {
    return ondergrens + rand() % (bovengrens - ondergrens + 1);
}

int main() {
    char nogmaals;
    srand(time(NULL));
    
    do {
        int ondergrens, bovengrens, getal, gok;
        int gokken[100];
        int aantal = 0;
        
        printf("\nGeef ondergrens: ");
        scanf("%d", &ondergrens);
        printf("Geef bovengrens: ");
        scanf("%d", &bovengrens);
        
        getal = randomGetal(ondergrens, bovengrens);
        printf("\nRaad het getal tussen %d en %d!\n", ondergrens, bovengrens);
        
        for (int i = 0; i < 7; i++) {
            printf("Gok %d: ", i + 1);
            scanf("%d", &gok);
            gokken[aantal] = gok;
            aantal++;
            
            if (gok == getal) {
                printf("Goed geraden!\n");
                break;
            } else if (gok < getal) {
                printf("Hoger!\n");
            } else {
                printf("Lager!\n");
            }
        }
        
        if (gok != getal) {
            printf("Het getal was %d\n", getal);
        }
        
        printf("Je gokken: ");
        for (int i = 0; i < aantal; i++) {
            printf("%d ", gokken[i]);
        }
        printf("\n");
        
        printf("\nNogmaals spelen? (j/n): ");
        scanf(" %c", &nogmaals);
        
    } while (nogmaals == 'j' || nogmaals == 'J');
    
    return 0;
}