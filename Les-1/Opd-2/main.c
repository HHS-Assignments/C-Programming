/* Opdracht 2:
Maak een spel hoger lager met een beperkt aantal beurten. Print na afloop ook alle ingevoerde
getallen en vraag of de speler nogmaals wil spelen. Maak een random getal tussen een (door de
gebruiker) te kiezen ondergrens en een te kiezen bovengrens met de rand functie uit de stdlib:
https://en.cppreference.com/w/c/numeric/random/rand
Verberg de complexiteit van het maken van een random getal in een functie */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int randomGetal(int bovengrens) {
    srand(time(NULL));
    int Random_Out = rand() % 100;
    return Random_Out;
}
bool hoog_laag(int Eigen_Getal, int Tegen_Getal, int gok) {
    if (Eigen_Getal > Tegen_Getal) {
        printf("Hoger\n");
        return true;
    }
    else if (Eigen_Getal < Tegen_Getal) {
        printf("Lager\n");
        return true;
    }
    else {
        printf("Goed geraden!\n");
        return false;
    }
}

int main() {
    int Eigen_Getal = randomGetal(100);
    int Tegen_Getal = randomGetal(100);
    int gok;
    printf("Je Eigen Getal:%d\n", Eigen_Getal);
    printf("Gok: \n1: Is het Hoger\n2: Is het Lager\n");
    scanf("%d", &gok);
    hoog_laag(Eigen_Getal, Tegen_Getal, gok);
    printf("het Getal: %d\n", Tegen_Getal);
    return 0;
}