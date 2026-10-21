// *HEADERFIL FOR SPILLER*

#pragma once

// Inkluderer nødvendige headerfiler/biblioteker
#include "AnimationWindow.h"
#include "birds.h"
#include <deque>
#include <vector>

// Definerer Player-klasse
class Player {
    public: // (skal kunne brukes av funksjonalitet utenfor klassen)
        // Konstruktør
        Player(std::string difficulty); // Tar inn valgt vanskelighetsgrad som parameter

        // Medlemsvariabler
        int score = 0; // Variabler for spillerstatus
        int heartCounter = 3;
        bool hasLost = false;
        TDT4102::Image ImToShow; // Bilde av spiller (Image-objekt) som skal tegnes 
        const int playerImWidth = 100; // Brukt i tegning av spiller-bilde
        const int playerImHeight = 100;
        int xCoord = 450; // x-koordinat øverste venstre hjørne av spillerbilde
        int yCoord = 350; // y-koordinat øverste venstre hjørne av spillerbilde
        int countJump = 0; // Brukt i jump()
         std::vector<std::deque<Seagull>> seagullsInWindow = {{}, {}, {}}; // Vector med deques, der deres elementer videre
        // er Seagull-objekter som "befinner seg" i vinduet. Seagull-objektene legges til fortløpende etter-
        // som de opprettes, og skilles i ulike deques etter farten deres.
        std::deque<Crow> crowsInWindow = {}; // Deque med Crow-objekter som "befinner seg" i vinduet. 
        
        // Deklarerer medlemsfunksjoner 
        void jump(bool jumps); // Funksjon for at spiller skal kunne hoppe
        void hitBird(bool hit); // Funksjon for å slå til fugl

    private: // Setter medlemmer som kun brukes i klassefunksjonalitet som private
        const TDT4102::Image Im; // Bilder: Image-objekter
        const TDT4102::Image ImHit;
        
        int countHit = 21; // Brukt i hitBird()
        bool lastFrameWasHit = false;
};
