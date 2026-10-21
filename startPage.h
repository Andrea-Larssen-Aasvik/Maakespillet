// *HEADERFIL FOR SPILLVINDU*

// Gjør at headerfil kun inkluderes én gang per kompilering
#pragma once 

// Inkluderer nødvendige headerfiler/biblioteker
#include "AnimationWindow.h"
#include "player.h"
#include "birds.h"
#include "widgets/Button.h"
#include <random>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>

// Definisjon av klassen StartWindow
// StartWindow-klassen arver fra AnimationWindow-klassen. 
class StartWindow : public TDT4102::AnimationWindow // Bruker nøkkelordet public; gjør at alle
// (public) medlemsfunksjoner og medlemsvariabler fra AnimationWindow som StartWindow-klassen arver, også blir 
// satt som public i StartWindow-klassen. 
{
    public: // Setter klassemedlemmer som må nås av funksjonalitet utenfor klassen som public
        
        // Deklarerer konstruktør
        StartWindow(); 

        // Public medlemsvariabler
        std::string difficulty = ""; //Initialiserer strengen difficulty til tom streng, 
        // endres etter bruker har valgt vanskelighetsgrad.  
        std::string quit = "No"; // Initialiserer strengen quit til "No", 
        // slik at spillet kjøres når bruker setter det i gang.
        bool scoresPage = false; // Initialiserer streng showScores til boolsk verdi false,
        // endres dersom bruker klikker på knapp buttonScores.
             
        // Deklarerer public medlemsfunksjoner (beskrevet i .cpp-fil)
        void startGame();
        void returnToStartPage();
        void gameOver(Player player);
        void actualGame(Player &player);
        void highscorePage(Player player);
         
    private: // Setter klassemedlemmer som kun skal nås av klassens medlemsfunksjoner som private

        // Deklarerer callbackfunksjoner til knapper
        void callbackNormal();
        void callbackHard();
        void callbackExtreme();
        void callbackQuit();
        void callbackScores();

        // Private medlemsvariabler
        TDT4102::Button buttonNormal; // Knapper: Button(Widget)-objekter
        TDT4102::Button buttonHard;
        TDT4102::Button buttonExtreme;
        TDT4102::Button buttonQuit;
        TDT4102::Button buttonScores;
        TDT4102::Audio audio;   // Lyd: Audio-objekt
        TDT4102::Image oneIm; // Bilder: Image-objekter
        TDT4102::Image twoIm;
        TDT4102::Image threeIm;
        TDT4102::Image seagullIm;
        TDT4102::Image cloudIm; 
        TDT4102::Image heartIm;
        TDT4102::Image gameOverIm;
        TDT4102::Image groundIm;
        TDT4102::Image goodJobIm;
        int cloud1Xcoord = 200; // x-koordinater brukt i tegning av skyer
        int cloud2Xcoord = 600; 
        int groundXcoord = 0; // x-koordinat brukt i tegning av bakke
        int tolerance = 70; // toleranse brukt i sjekk av om spiller har truffet måke (seagullIsHit()).
        int framesSinceLastCrow = 0;
        std::vector<int> initxCoords = {125, 300, 405, 545, 650, 825}; // Vector med mulige initielle 
        // x-koordinater for stupende fugler. Verdiene er regnet ut for hånd på forhånd.
        std::vector<int> deltaXs = {-350, -175, -70, 70, 175, 350}; // Vector med tilhørende deltaX
        std::filesystem::path highscorePath{"highscore.txt"}; // Filsti til fil med poengsummer
        std::vector<std::string> scores; // Vector med 3 høyeste poengsummer

        // Deklarerer private medlemsfunksjoner (beskrevet i .cpp-fil)
        void countdown();
        void background();
        bool enemy(std::string difficulty);
        void dive(Seagull &seagull, Player &player, int index);
        void seagullIsHit(bool hit, Seagull &seagull, Player &player);
        void crowIsHit(Crow &crow, Player &player);
        void creep(Crow &crow, Player &player);
        void drawHearts(int heartCounter);
};