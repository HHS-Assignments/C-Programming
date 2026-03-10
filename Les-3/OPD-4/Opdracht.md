# Opdracht 4

struct teamlid {
int id;
char naam[20];
char opleiding[10];
};  
Maak een programma waarin je een team kan samenstellen.
a) Maak een programma waarin je een team kan samenstellen. Het aantal teamleden wordt
vooraf aangegeven. Gebruik malloc om geheugen te alloceren waarin de teamleden worden
opgeslagen. Het id is een volgnummer en uniek voor ieder teamlid
b) Geef de gebruiker de mogelijkheid om te zoeken naar een teamlid met een bepaalde
opleiding. Alleen de teamleden die daaraan voldoen worden geprint.
c) Gebruik een functie int generatieId() die het unieke nummer genereert. Gebruik
een static variabele in deze functie. Het eerst teamlid krijgt als id 1000.
d) Optioneel: Kan je het programma aanpassen zodat aan het eind er toch nog een extra
teamlid kan worden toegevoegd aan een team? Er is dan een nieuwe geheugen allocatie
nodig en daarin komen dan ook de al bestaande teamleden in te staan.