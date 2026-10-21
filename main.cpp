// *KJØRES FOR Å STARTE SPILL*

// Inkluderer headerfil med funksjonalitet for spillvindu
#include "startPage.h" 


// Kode i main() er det som kjøres
int main() {
    // Opretter en instans av StartWindow-klassen
    // Samme instans brukes gjennom hele spillet
    // I konstruktøren til objektet blir spillets åpningsvindu "satt opp"
    // Merk: Medlemsvariabelen difficulty er initialisert til "" (en tom streng)
    StartWindow startWindow;
    TDT4102::Image titleIm("Imagefiles/title.png");
    TDT4102::Image titleSeagullIm("Imagefiles/seagull.png");

    // While-løkke som gjentas helt til brukeren trykker på knappen som lukker vinduet
    while(!startWindow.should_close()) {
        
        // Siden difficulty er initialisert til "", vil koden i følgende if-setning kjøres
        // helt til brukeren har valgt vanskelighetsgrad.

        if (startWindow.difficulty == "") {
            startWindow.draw_image({100, 50}, titleIm, 400, 200); // Tegner tittel
            startWindow.draw_image({700, 200}, titleSeagullIm, 100, 100); // Tegner måke
            startWindow.next_frame(); // Sørger for at åpningsvinduet forsetter å vises.

            // Dersom bruker velger vanskelighetsgrad, kalles funksjonen startGame()
            // Denne if-setningen er plassert "inni" den over fordi startGame() kun
            // skal kalles på dersom man fra før befinner seg i startvinduet. 
            if (startWindow.difficulty != "") {
                startWindow.startGame();
            }
            // Går videre til neste iterasjon i while-løkken, der det neste som kjøres er (*)
        }

        // (*) Bruker har valgt vanskelighetsgrad, og programmet går inn i else-setningen.
        else {
            // En instans av Player-klassen opprettes, 
            // med difficulty (vanskelighetsgraden) som parameter i konstruktøren.
            Player player(startWindow.difficulty);
            
            // Ny while-løkke kjøres. Siden 1 alltid har boolsk verdi "true",
            // forsetter iterasjonene helt til programmet eksplisitt bryter ut av den.
            while(1) {

                // startWindow-objektets quit-medlemsvariabel er initialisert til "No",
                // og første gang kjøres ikke koden i denne if-setningen.
                if (startWindow.quit == "Yes") {
                    // Spilles åpningsvindu "settes opp" igjen, og difficulty-variabel settes til "".
                    startWindow.returnToStartPage();
                    // Nøkkelordet "break" sørger for at programmet går ut av den indre while-løkken. 
                    // Koden i den ytre while-løkken kjøres. Nå kan brukeren velge vanskelighetsgrad på nytt
                    // eller avslutte spillet ved å klikke på knappen som lukker selve vinduet.
                    break;
                }
                // player-objektets hasLost-medlemsvariabel er initialisert til boolsk verdi "false",
                // heller ikke denne koden kjøres første iterasjon.
                else if (player.hasLost) {
                    // Dersom player-objektets medlemsvariabel "heartCounter" når verdi 0, endrer en annen medlems-
                    // variabel, "hasLost", boolsk verdi til true, og brukeren har tapt spillet. gameOver() endrer
                    // spillvinduet til å vise spillers poengsum og teksten "Game over". Dette vinduet vises
                    // til brukeren klikker på knappen oppe til høyre i spillvinduet (buttonQuit).
                    
                    if (startWindow.scoresPage) {
                        // Viser vindu med highscore-oversikt
                        startWindow.highscorePage(player);
                    }
                    else {
                        // Viser "game over"-side
                        startWindow.gameOver(player);
                    }
                }

                // actualGame() kalles på, og tar inn player-objektet som parameter, slik at
                // spillets funksjonalitet kan endres etter valgt vanskelighetsgrad (siden player-objektets
                // konstruktør tar inn den valgte vanskelighetsgraden som parameter i form av en streng) . 
                else {
                    startWindow.actualGame(player);
                }
                // Koden i denne indre while-løkken gjentas helt til quit-variabelen til startWindow-objektet 
                // endrer verdi til "Yes", som skjer dersom spilleren klikker på knappen oppe til høyre i
                // spillvinduet (buttonQuit).
            }   
        }
    }
    return 0;  
}

