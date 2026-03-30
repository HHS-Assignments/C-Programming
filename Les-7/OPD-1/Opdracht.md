Opdracht 1:
Gegeven de volgende struct:
struct studieResultaat {
 int id;
 char vak[12];
 int ECTS;
 double cijfer;
};
a)	Maak hardcoded een array met minimaal 4 studieResultaten. Dit is je testdata.
b)	Sorteer met qsort deze op de naam van het vak. Maak hiervoor je eigen compare functie.
c)	Sorteer met qsort deze op ECTS en bij gelijk aantal op naam van het vak.
d)	Sorteer met qsort op andere zelfgekozen manier die in de praktijk zou kunnen voorkomen.
