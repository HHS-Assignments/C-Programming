# Opdracht 3

struct vak {
char naam[20];
int ECTS;
};

a) Maak een hardcoded array vakken in de main en print een lijst van alle vakken
b) Maak een void functie (met een pointer naar de vakken als parameter) die de mogelijkheid
geeft aan de gebruiker om een vak een andere naam en een ander aantal studiepunten te
geven. De gebruiker typt de index in van het vak dat hij wil wijzigen. In de main wordt nu de
nieuwe naam en nieuwe ECTS geprint in de lijst van vakken
c) Maak een void functie (met als parameter de struct van het vak dat je gaat aanpassen) die de
mogelijkheid geeft aan de gebruiker om een vak een andere naam en een ander aantal
studiepunten te geven. De gebruiker typt de index in van het vak dat hij wil wijzigen. In de
main wordt ook nu de nieuwe naam en nieuwe ECTS geprint in de lijst van vakken
d) Optioneel: kan je van de vorige functie ook een variant zonder parameter maar alleen met
een return type maken