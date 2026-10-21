// Inkluderer nødvendige header-filer/biblioteker
#include "birds.h"
#include <random>

// -----Definisjon av Seagull-medlemsfunksjon-----

// Funksjon brukes til å generere tilfeldig initiell x-koordinat for fugl,
// ved at den genererer en tilfeldig indeks. Indeksen brukes til å hente ut et tall
// fra initxCoords-vectoren, medlemsvariabel i StartWindow-klassen.
int Seagull::xCoordGenerator() {
    // (Random-funksjonalitet hentet fra øvingsforelesningsslides (Øvingsforelesn. 3))
    std::random_device rd; // Genererer et seed (frø)
    std::default_random_engine generator(rd()); // Gir videre generator dette frøet som parameter
    int min = 0; // Mulige indekser til initxCoords-vector
    int max = 5;
    std::uniform_int_distribution<int> dist(min, max); // Uniform fordeling, alle heltallsverdier
        // fra og med min til og med max har like stor sannsynlighet for å bli trukket.
    int num = dist(generator); // Tar inn generator som argument, og genererer en tilfeldig verdi fra
        // den uniforme fordelingen.
    return num; // Returnerer tilfeldig indeks
}

// -----Konstruktør for Seagull-objekt-----
Seagull::Seagull() :
    // Initialiseringsliste (brukes til å initialisere objekter som har konstruktører med parametre)
    Im("Imagefiles/seagull.png"),
    ImDead("Imagefiles/seagullDead.png")
{   
    ImToShow = Im; // Initialiserer bilde som skal vises til vanlig bilde av fugl
}

// ----- Konstruktør for Crow-objekt -----
Crow::Crow() :
    // Initialiseringsliste (brukes til å initialisere objekter som har konstruktører med parametre)
    Im("Imagefiles/crow.png"),
    ImDead("Imagefiles/crowDead.png")
{   
    ImToShow = Im; // Initialiserer bilde som skal vises til vanlig bilde av fugl
}


