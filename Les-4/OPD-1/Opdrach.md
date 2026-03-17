# Opgave 1:
a) Maak een simpele socket server applicatie (met WinSock) die een antwoord geeft op een
verzoek van een client.
b) Maak ook de client applicatie en test deze samen met de server. Alles draait op 1 PC. Visual
Studio kan je meerdere keren open hebben staan zodat je zowel de client als de server
tegelijkertijd in in Visual Studio runnen. Je kan nu ook breakpoints zetten ivm debuggen.
c) Laat zien dat je ook met blocking recv prima meerdere clients en 1 server kan hebben. Iedere
client krijg op zijn verzoek een keurig antwoord. Multithreading is ook niet nodig voor dit
resultaat
d) Voor een machine-2-machine communicatie is een key-value bericht handiger dan vrije tekst.
Dit geldt ook voor het antwoord. Laat zien dat op deze manier de temperatuur of
luchtvochtigheid kan doorgeven. Als antwoord kan je terug krijgen op welke snelheid een
ventilator moet draaien. NB: JSON is nog krachtiger maar lastiger. JSON wordt niet via een
standaard library en/of functies ondersteunt maar via
https://github.com/DaveGamble/cJSON Als je cJSON.h en cJSON.c include in je project kan je
met JSON werken.