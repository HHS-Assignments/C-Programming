#include <stdio.h>
#include <stdlib.h>

// ========== STRUCT DEFINITIE ==========
// Een node in de linked list
struct node {
    int data;
    struct node* next;
};

// ========== FUNCTIE a) ==========
// Zet een array om naar een linked list (kopie van data)
struct node* arrayToLinkedList(int array[], int size) {
    if (size == 0) {
        return NULL;
    }
    
    // Maak de eerste node
    struct node* head = (struct node*)malloc(sizeof(struct node));
    head->data = array[0];
    head->next = NULL;
    
    // Maak de rest van de nodes
    struct node* current = head;
    for (int i = 1; i < size; i++) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = array[i];
        newNode->next = NULL;
        
        current->next = newNode;
        current = newNode;
    }
    
    return head;
}

// Hulpfunctie: print de linked list
void printLinkedList(struct node* head) {
    printf("Linked List: ");
    struct node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Hulpfunctie: geef aantal nodes in de linked list
int listLength(struct node* head) {
    int count = 0;
    struct node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// ========== FUNCTIE b) ==========
// Verwijder een node op basis van positie (1-gebaseerd)
struct node* deleteNodeByPosition(struct node* head, int position) {
    if (head == NULL) {
        printf("Linked list is leeg!\n");
        return NULL;
    }
    
    // Verwijder het eerste element (position 1)
    if (position == 1) {
        struct node* temp = head;
        head = head->next;
        free(temp);
        printf("Node op positie %d verwijderd.\n", position);
        return head;
    }
    
    // Zoek de node voor de te verwijderen node
    struct node* current = head;
    int count = 1;
    
    while (current->next != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    
    // Check of we de node hebben gevonden
    if (current->next == NULL || count != position - 1) {
        printf("Positie %d bestaat niet!\n", position);
        return head;
    }
    
    // Verwijder de node
    struct node* temp = current->next;
    current->next = temp->next;
    free(temp);
    printf("Node op positie %d verwijderd.\n", position);
    
    return head;
}

// ========== FUNCTIE c) ==========
// Verwijder het eerste negatieve getal
struct node* deleteFirstNegative(struct node* head) {
    if (head == NULL) {
        printf("Linked list is leeg!\n");
        return NULL;
    }
    
    // Check het eerste element
    if (head->data < 0) {
        struct node* temp = head;
        head = head->next;
        printf("Eerste negatieve getal (%d) verwijderd.\n", temp->data);
        free(temp);
        return head;
    }
    
    // Zoek het eerste negatieve getal
    struct node* current = head;
    while (current->next != NULL && current->next->data >= 0) {
        current = current->next;
    }
    
    // Verwijder het getal als het gevonden is
    if (current->next != NULL) {
        struct node* temp = current->next;
        current->next = temp->next;
        printf("Eerste negatieve getal (%d) verwijderd.\n", temp->data);
        free(temp);
    } else {
        printf("Geen negatieve getallen gevonden!\n");
    }
    
    return head;
}

// ========== FUNCTIE d) (OPTIONEEL) ==========
// Verwijder alle negatieve getallen
struct node* deleteAllNegative(struct node* head) {
    if (head == NULL) {
        return NULL;
    }
    
    // Verwijder negatieve getallen aan het begin
    while (head != NULL && head->data < 0) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }
    
    // Verwijder negatieve getallen in het midden/einde
    if (head != NULL) {
        struct node* current = head;
        while (current->next != NULL) {
            if (current->next->data < 0) {
                struct node* temp = current->next;
                current->next = temp->next;
                free(temp);
            } else {
                current = current->next;
            }
        }
    }
    
    printf("Alle negatieve getallen verwijderd.\n");
    return head;
}

// ========== FUNCTIE e) ==========
// Voeg een getal toe op bepaalde plek (1-gebaseerd)
struct node* insertAtPosition(struct node* head, int data, int position) {
    // Voeg in op positie 1
    if (position == 1) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = data;
        newNode->next = head;
        printf("Getal %d ingevoegd op positie 1.\n", data);
        return newNode;
    }
    
    // Zoek de positie
    struct node* current = head;
    int count = 1;
    
    while (current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    
    // Check of positie geldig is
    if (current == NULL) {
        printf("Positie %d is te ver!\n", position);
        return head;
    }
    
    // Voeg de node in
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = current->next;
    current->next = newNode;
    printf("Getal %d ingevoegd op positie %d.\n", data, position);
    
    return head;
}

// ========== FUNCTIE f) ==========
// Voeg een getal toe op de laatste plek
struct node* insertAtEnd(struct node* head, int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    
    // Als list leeg is
    if (head == NULL) {
        return newNode;
    }
    
    // Zoek het einde
    struct node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Voeg toe aan het einde
    current->next = newNode;
    printf("Getal %d ingevoegd aan het einde.\n", data);
    
    return head;
}

// ========== FUNCTIE g) ==========
// Verwijder een getal van de eerste plek
struct node* deleteFromStart(struct node* head) {
    if (head == NULL) {
        printf("Linked list is leeg!\n");
        return NULL;
    }
    
    struct node* temp = head;
    printf("Getal %d verwijderd van het begin.\n", temp->data);
    head = head->next;
    free(temp);
    
    return head;
}

// Hulpfunctie: geheugen vrijgeven
void freeLinkedList(struct node* head) {
    struct node* current = head;
    while (current != NULL) {
        struct node* temp = current;
        current = current->next;
        free(temp);
    }
}

// ========== MAIN ==========
int main(void) {
    printf("=== OPDRACHT 2: LINKED LISTS ===\n\n");
    
    // Test array
    int array[] = {10, 20, -5, 30, -15, 40, 50};
    int size = 7;
    
    printf("--- a) Array naar Linked List ---\n");
    struct node* list = arrayToLinkedList(array, size);
    printLinkedList(list);
    printf("\n");
    
    // ========== FUNCTIE b) TEST ==========
    printf("--- b) Node verwijderen op positie 3 ---\n");
    list = deleteNodeByPosition(list, 3);
    printLinkedList(list);
    printf("\n");
    
    // ========== FUNCTIE c) TEST ==========
    printf("--- c) Eerste negatieve getal verwijderen ---\n");
    list = deleteFirstNegative(list);
    printLinkedList(list);
    printf("\n");
    
    // ========== FUNCTIE d) TEST ==========
    printf("--- d) Alle negatieve getallen verwijderen ---\n");
    list = deleteAllNegative(list);
    printLinkedList(list);
    printf("\n");
    
    // ========== FUNCTIE e) TEST ==========
    printf("--- e) Getal toevoegen op positie 2 ---\n");
    list = insertAtPosition(list, 25, 2);
    printLinkedList(list);
    printf("\n");
    
    // ========== FUNCTIE f) TEST ==========
    printf("--- f) Getal toevoegen aan het einde ---\n");
    list = insertAtEnd(list, 100);
    printLinkedList(list);
    printf("\n");
    
    // ========== FUNCTIE g) & h) QUEUE DEMONSTRATIE ==========
    printf("--- h) QUEUE DEMONSTRATIE (FIFO: First In, First Out) ---\n");
    struct node* queue = NULL;
    
    printf("Voeg getallen toe aan queue (insertAtEnd):\n");
    queue = insertAtEnd(queue, 1);
    queue = insertAtEnd(queue, 2);
    queue = insertAtEnd(queue, 3);
    printLinkedList(queue);
    
    printf("\nVerwijder van het begin (deleteFromStart - FIFO):\n");
    queue = deleteFromStart(queue);
    printLinkedList(queue);
    queue = deleteFromStart(queue);
    printLinkedList(queue);
    queue = deleteFromStart(queue);
    printLinkedList(queue);
    printf("\n");
    
    // ========== FUNCTIE i) STACK VRAAG ==========
    printf("--- i) Welke functie is nodig voor een STACK? ---\n");
    printf("Voor een STACK (LIFO: Last In, First Out) zou je nodig hebben:\n");
    printf("  - insertAtStart() of insertAtBeginning()\n");
    printf("     (om toe te voegen aan het BEGIN van de linked list)\n");
    printf("\nMet insertAtStart() en deleteFromStart() kun je een STACK maken\n");
    printf("omdat getallen LIFO (Last In, First Out) worden verwerkt.\n");
    printf("\n");
    
    // Opruimen
    freeLinkedList(list);
    freeLinkedList(queue);
    
    printf("=== Programma beeindigd ===\n");
    return 0;
}
