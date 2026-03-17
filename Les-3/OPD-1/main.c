#include <stdio.h>

// De functie heeft 2 parameters:
//   - de array van doubles
//   - de grootte van de array (want C weet zelf niet hoe groot een array is)
// Het return type is void omdat we niks teruggeven, we printen alleen.
void printArray(double array[], int grootte) {
    printf("[");

    // loop door alle elementen heen
    for (int i = 0; i < grootte; i++) {
        // print het getal afgerond op 2 decimalen
        printf("%.2f", array[i]);

        // zet een komma na elk getal, behalve na het laatste
        if (i < grootte - 1) {
            printf(", ");
        }
    }

    printf("]\n");
}

int main(void) {
    // test array 1: 3 getallen
    double getallen1[] = {5.89, 6.20, -2.13};
    printArray(getallen1, 3);[5.89, 6.20, -2.13]
[3.14]
[1.00, 2.50, 101.00, -0.50]
[1] + Done                  

    // test array 2: 1 getal
    double getallen2[] = {3.14};
    printArray(getallen2, 1);

    // test array 3: wat meer getallen
    double getallen3[] = {1.0, 2.5, 100.999, -0.5};
    printArray(getallen3, 4);

    return 0;
}