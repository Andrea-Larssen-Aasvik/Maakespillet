// Inkluderer nødvendig headerfil
#include "player.h"

// -----Definerer medlemsfunksjoner for Player-klasse-----

// Funksjon for at spiller skal kunne hoppe.
// Den boolske parameteren jumps som jump() tar inn vil alltid være is_key_down(KeyboardKey::SPACE), som har
// boolsk verdi true eller false ettersom SPACE-tast er nede i gjeldende frame.
void Player::jump(bool jumps) {
    if (jumps) // Kode som utløses dersom SPACE-tast er nede (jumps har verdi true)
    {   
        // Spiller hopper oppover (countJump er initialisert til 0 for Player-objekt)
        if (countJump < 100) {
            yCoord -= 2; // Forflytter spiller opp i vindu
            countJump++; // Øker countJump med 1
        }
        // Spiller beveger seg ned mot bakke igjen (sjekken med yCoord er lagt til for at neste 
        // else-if skal kunne utløses)
        else if (countJump >= 100 && yCoord <= 348) { 
            yCoord += 2; // Forflytter spiller ned i vindu
            countJump++; // Øker countJump med 1
        }
        // Når spiller er på bakken, settes countJump til 0 igjen, slik at nytt hopp
        // er mulig å sette i gang.
        else if (yCoord == 350) {
            countJump = 0;
        }  
    }
    else if (yCoord <= 350) // "else if"-setning som håndterer hvis space-tast slippes "i luften"
    {   
        // Hvis spiller er på bakken, settes countJump til 0 igjen, slik at nytt hopp
        // er mulig å sette i gang.
        if (yCoord == 350) {
            countJump = 0;
        }
        // Hvis i luften, forflyttes spiller ned i vinduet (økende y-koordinat) og countJump økes med 1.
        else {
            yCoord += 2;
            countJump++;
        } 
    }
    // Her kunne det stått en siste else-setning som utløses hvis SPACE-tast ikke er nede
    // og spiller ikke er i luften, men det trengs ikke siden spillerens y-koordinat i det tilfellet
    // skal forbli den samme, og funksjonen ikke skal gjøre noe.
}

// Funksjon for å slå til fugl
// Tar inn boolsk verdi "hit" (når denne funksjonen kalles på i programmet, brukes alltid is_key_down()
// som parameter, der parameter til denne igjen er ENTER-tasten,
// så hit er true hvis ENTER-tast er nede og false ellers).
void Player::hitBird(bool hit) {
    // Fase 1 - sette i gang slag
    if (hit && (countHit > 20) && (!lastFrameWasHit)) // Kan kun utløses hvis 
    // ENTER-tast er nede (altså hit har verdi true). countHit er initialisert til 21 for Player-objekter,
    // og lastFrameWasHit er initialisert til false.
    {
        ImToShow = ImHit; // Bilde som skal vises av spiller er "slag"-karakter
        countHit = 0; // countHit settes til 0
        lastFrameWasHit = true; // Gjør at programmet vet at forrige frame var ENTER-tast nede
    }
   
    // Fase 2 - fortsette å holde "slag"-karakter synlig i noen frames
    else if (countHit <= 4) // Tallet 4 valgt for at slag karakter fortsatt skal vises i 4 frames etter "slagstart" 
    { 
        ImToShow = ImHit; // "slag"-karakter vises
        countHit++; // countHit økes med 1
    }
    else {
        // Fase 3 - ikke holde "slag"-karakter synlig, men telle til neste gang det er mulig å slå
        if (countHit <= 20) // Gjør at spiller må vente noen frames før den kan slå igjen (eller rettere sagt,
        // før slag-karakter vises igjen)
        {
            countHit++; // countHit-økes med 1
        }
        // Følgende kjøres både i fase 3 av slag og når det ikke er utløst et slag; da vises vanlig karakter 
        ImToShow = Im; 
    }
    // Dersom ENTER-tast nede blir denne true, hvis ikke false. Gjør at spiller må slippe tast før den kan
    // slå igjen.
    lastFrameWasHit = hit;
}

// ----- Konstruktør for Player-objekt -----
Player::Player(std::string difficulty) : 
// Initialiseringsliste (for objekter med konstruktører som tar inn parametre)
Im("Imagefiles/"+difficulty+".png"),
ImHit("Imagefiles/"+difficulty+"Hit.png")
{  
    // Alle andre medlemsvariabler er initialisert i klassedefinisjon 
}