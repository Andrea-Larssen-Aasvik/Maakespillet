// *HEADERFIL FOR MÅKE- OG KRÅKE-KLASSER*

#pragma once

// Inkluderer nødvendig headerfil
#include "AnimationWindow.h"

// Definisjon av Seagull-klasse 
class Seagull {
    public: // Setter alle klasse-medlemmer som public siden alle brukes i funksjonalitet
    // utenfor klassen.

        // Konstruktører
        Seagull();
       
        // Deklarerer medlemsvariabler (setter const-nøkkelord foran variabler som ikke skal endres, og som
        // det er mulig å initialisere i klassedefinisjonen)
        const TDT4102::Image Im; // Bilder: Image-objekter
        const TDT4102::Image ImDead;
        TDT4102::Image ImToShow;
        const int width = 50;  // Brukt i tegning av bilder
        const int height = 50;
        int xInit; // Brukt i tegning av stupende fugler og for å sjekke om fugler er truffet
        int xCoord;
        int yCoord = -50; // (Fuglebilde tegnes først "rett over" spillvindu)
        int deltaX;
        const int deltaY = 350; 
        int diveDecayConst;
        int changeInX;
        bool isHit = false;
        
        // Deklarerer medlemsfunksjon
        int xCoordGenerator();
        // Selv om selve dive-funksjonen(xCoordGenerator() brukes) er i StartWindow-klassen, 
        // plasseres så mye som mulig annen funksjonalitet i birds-klassen for å forhåpentligvis
        // få en ryddigere kode.
};


// Definisjon av Crow-klasse
class Crow {
    public:
        Crow();

        const TDT4102::Image Im; // Bilder: Image-objekter
        const TDT4102::Image ImDead;
        TDT4102::Image ImToShow;
        const int width = 50;  // Brukt i tegning av bilder
        const int height = 50;
        int xCoord = 1000;
        const int yCoord = 400; // For at den skal "stå" på samme bakkehøyde som spilleren (y = 450)
};






