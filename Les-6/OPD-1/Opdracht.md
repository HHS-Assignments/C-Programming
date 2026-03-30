Opdracht 1:
struct vak {
 char naam[20];
 int ECTS;
};

a)	Maak een array van bovenstaande struct. Laat de gebruiker een aantal vakken invullen tot een maximum van 10.
b)	Maak een andere variant waarbij de array alleen pointers naar de struct vak zijn. Gebruik malloc voor de geheugen allocatie van de struct
c)	Print met sizeof de gereserveerde ruimte voor beide arrays, direct na de declaratie. Geef ook een uitleg. NB. Dit getal moet verschillend zijn.
d)	Laat mbv het memory window zien dat beide data structuren er in het geheugen heel anders uit zien.
e)	Maak een functie die in de array van bovenstaande struct een bepaald vak vervangt
f)	Maak een functie die in de array van pointers naar bovenstaande struct een bepaald vak vervangt. NB. Voorkom een geheugenlek
