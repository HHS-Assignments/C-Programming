/* Opdracht 4:
a) Maak een programma die de score berekent voor 1 speler die aan het bowlen is (zonder
spare of strike). Na iedere worp voer je via het toetsenbord het aantal omgegooide kegel in.
Standaard mag je 2x werpen per beurt. Denk goed na over hoeveel lussen je nodig hebt en
waarvoor iedere lus dient. Sla alle omgegooide pins op in een array.
b) Houd nu ook rekening met de correcte regels voor een spare en strike. Met welke waardes
heb je getest?
c) Twee spelers zijn nu aan het bowlen. Breid je programma van de vorige vraag uit. Als het
goed is heb je vooral een extra lus nodig. Het grootste deel van het programma blijft
hetzelfde
d) Uitdaging: Maak nu een variant waarbij het aantal worpen per beurt variabel is. Bijvoorbeeld
een klein kind dat nog niet zo goed is mag 3x gooien. Maak de code wel zo generiek mogelijk
en gebruik niet te veel if statements */

#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_WORPEN 21

int bereken_score(int worpen[], int aantal) {
    int score = 0, idx = 0;
    for (int frame = 0; frame < MAX_FRAMES; frame++) {
        if (worpen[idx] == 10) {
            score += 10 + worpen[idx + 1] + worpen[idx + 2];
            idx++;
        } else if (worpen[idx] + worpen[idx + 1] == 10) {
            score += 10 + worpen[idx + 2];
            idx += 2;
        } else {
            score += worpen[idx] + worpen[idx + 1];
            idx += 2;
        }
    }
    return score;
}

int speel_spel(char* naam) {
    int worpen[MAX_WORPEN] = {0}, idx = 0;
    printf("\n=== %s ===\n", naam);
    
    for (int frame = 1; frame <= MAX_FRAMES; frame++) {
        int pins = 10, max_worpen = (frame == 10) ? 3 : 2;
        printf("\nFrame %d:\n", frame);
        
        for (int w = 1; w <= max_worpen; w++) {
            int gepind;
            while (scanf("%d", &gepind) != 1 || gepind < 0 || gepind > pins) {
                printf("ERROR: voer 0-%d in: ", pins);
                while (getchar() != '\n');
            }
            
            printf("  Worp %d: %d pins\n", w, gepind);
            worpen[idx++] = gepind;
            pins -= gepind;
            
            if (gepind == 10 && w == 1 && frame < 10) {
                printf("  STRIKE!\n");
                break;
            }
            if (pins == 0 && w == 2 && frame < 10) {
                printf("  SPARE!\n");
                break;
            }
            if (frame == 10 && pins == 0) pins = 10;
        }
    }
    return bereken_score(worpen, idx);
}

int main() {
    printf("=== BOWLING ===\n");
    
    int spelers;
    printf("Aantal spelers (1-2): ");
    while (scanf("%d", &spelers) != 1 || spelers < 1 || spelers > 2) {
        printf("ERROR: voer 1 of 2 in: ");
        while (getchar() != '\n');
    }
    
    char naam1[50], naam2[50];
    int score1, score2 = 0;
    
    printf("Naam speler 1: ");
    scanf("%s", naam1);
    score1 = speel_spel(naam1);
    
    if (spelers == 2) {
        printf("\nNaam speler 2: ");
        scanf("%s", naam2);
        score2 = speel_spel(naam2);
    }
    
    printf("\n=== EINDSTAND ===\n");
    printf("%s: %d punten\n", naam1, score1);
    if (spelers == 2) {
        printf("%s: %d punten\n", naam2, score2);
        printf("Winnaar: %s\n", score1 > score2 ? naam1 : score2 > score1 ? naam2 : "Gelijkspel");
    }
    
    return 0;
}

// Testwaarden: Strike (10,3,4)=24 | Spare (7,3,4,2)=20 | Perfect game=300