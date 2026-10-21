// ----- Inkluderer nødvendige header-filer -----
#include "startPage.h"

// ----- Definerer callback-funksjoner til alle knapper -----
void StartWindow::callbackNormal() {
    difficulty = "Normal";
}

void StartWindow::callbackHard() {
    difficulty = "Hard";
}

void StartWindow::callbackExtreme() {
    difficulty = "Extreme";
}

void StartWindow::callbackQuit() {
    quit = "Yes";
}

void StartWindow::callbackScores() {
    scoresPage = true;
}

// ----- Definerer funksjon som fungerer som overgang fra åpningsvindu til nedtelling -----
void StartWindow::startGame() {
    buttonNormal.setVisible(false); // Sørger for at åpningsvinduets knapper skjules
    buttonHard.setVisible(false);
    buttonExtreme.setVisible(false);
    countdown(); // Funksjon som setter i gang nedtelling til spillstart kalles
}

// ----- Definerer nedtellings-funksjon -----
void StartWindow::countdown() {
    // NB! Deler av denne funksjonaliteten er hentet direkte fra forelesningsslides.
        draw_image({400, 150}, threeIm, 200, 200);
        next_frame();
        wait_for(1.0); // Gjør at programmet venter et sekund med å vise neste frame.
        draw_image({400, 150}, twoIm, 200, 200);
        next_frame();
        wait_for(1.0);
        draw_image({400, 150}, oneIm, 200, 200);
        next_frame();
        wait_for(1.0);
        draw_image({300, 150}, seagullIm, 400, 200);
        next_frame();
        wait_for(1.0);
        buttonQuit.setVisible(true); // Sørger for at knapp som gjør at man kan gå ut av spillrunde 
        // og tilbake til åpningsvinduet, blir synlig.
}

// ----- Definerer funksjon som tegner spillbakgrunn -----
void StartWindow::background() {
    // Tegner skyer og bakke med konstant y-koordinat og x-koordinat som endres for 
    // hver nye frame, slik at det ser ut som de beveger seg.
    draw_image({cloud1Xcoord, 100}, cloudIm, 200, 100);
    draw_image({cloud2Xcoord, 150}, cloudIm, 200, 100); 
    // To bakke-bilder tegnes samtidig, med vinduets bredde i forskjell i x-koordinat
    // slik at hele spillvinduet har bakke hele tiden.
    draw_image({groundXcoord, 425}, groundIm, 1000, 75);
    draw_image({groundXcoord+1000, 425}, groundIm, 1000, 75);
    // Sjekker om hver av skyenes x-koordinater er større enn vinduets bredde, og dermed ute av syne. Hvis
    // det er tilfelle, minkes x-koordinatene slik at skyene dukker opp på andre side av vinduet. Ellers
    // økes hver av skyenes x-koordinat med et fast heltall hver frame.
    {if (cloud1Xcoord > 1000) { //Endre til mer universelt? Lagre windowwith i variabel?
        cloud1Xcoord = -199;
    }
    else if (cloud2Xcoord > 1000) {
        cloud2Xcoord = -199;
    }
    else {
        // Øker skyenes x-koordinater med ulikt antall slik at det ser ut som de beveger seg med ulik hastighet.
        cloud1Xcoord += 2;
        cloud2Xcoord += 3;
    }}
    // Sjekker om bakke-x-koordinat er mindre enn -*bakke-bildets bredde* (som er bredden til vinduet). Hvis det 
    // er tilfellet, settes bakke-x-koordinat til 0. Ellers minker bakke-x-koordinat med et fast heltall per frame.
    // Minker for at det skal se ut som at spiller beveger seg framover.
    if (groundXcoord <= -1000) {
        groundXcoord = 0;
    }
    else {
        groundXcoord -= 4;
    }  
}

// ----- Definerer funksjon for selve spill-funksjonaliteten (spill-runden) ----- 
// actualGame() tar inn referanse til Player-objekt som parameter. Gjør at verdien til medlemsvariabel 
// heartCounter til dette Player-objektet kan endres ettersom spilleren mister liv. Dette Player-objektets
// medlemsvariabel "difficulty" brukes til å variere spillfunksjonalitet etter valgt vanskelighetsgrad.
// Funksjonen kalles hver frame.
void StartWindow::actualGame(Player &player) {

    // Funksjonalitet som gjør at spiller kan hoppe
    player.jump(is_key_down(KeyboardKey::SPACE));

    // Bakgrunn tegnes
    background();

    // Spiller tegnes 
    player.hitBird(is_key_down(KeyboardKey::ENTER)); // Setter riktig bilde til å bruke i tegning av 
    // spiller etter om spilleren slår eller ikke
    TDT4102::Point bottomLeftCorner {player.xCoord, player.yCoord};
    draw_image(bottomLeftCorner, player.ImToShow, player.playerImWidth, player.playerImHeight); // Bilde brukes her
    
    // Tegner hjerter etter antall liv spiller har igjen
    drawHearts(player.heartCounter);

    // Funksjonalitet som gjør at fugler stuper
    if (enemy(difficulty)) // Dersom enemy returnerer true skal ny fugl stupe, 
    //kode i if-setning kjøres. 
    {
        Seagull seagull; // Nytt Seagull-objekt opprettes.
        int index = seagull.xCoordGenerator(); // Bruker Seagull-medlemsfunksjon til å generere tilfeldig
            // indeks for StartWindow sin medlemsvariabel initxCoords, som inneholder mulige initielle
            // x-koordinater for fugler.
        seagull.xInit = initxCoords.at(index); // "Initialiserer" Seagull-medlemsvariabler xInit og xCoord 
        seagull.xCoord = initxCoords.at(index); // til vector-verdi ved denne tilfeldige inteksen.
        seagull.deltaX = std::abs(deltaXs.at(index)); // Initiell avstand i x-retning fugl skal bevege seg.
        seagull.changeInX = (deltaXs.at(index))/seagull.deltaX; // Hvis deltaXs-verdi<450, = -1, hvis >550, 
        // = +1. Brukes til å gjøre at Seagull-bilde forflyttes riktig x-retning, i retning spiller.
        seagull.diveDecayConst = (seagull.deltaY)/seagull.deltaX; // "Stigningstall" bane fugl beveger seg 
        // etter, hvor mye y minker per +/- 1 i x-verdi.

        // Legger til opprettet Seagull-objekt i vector seagullsInWindow, i bestemt deque etter
        // farten fuglen stuper med.
        if (index == 0 || index == 5) {
            // For fugler med lavest fart
            player.seagullsInWindow.at(0).push_back(seagull); 
        }
        else if (index == 1 || index == 4) {
            // For fugler med middels fart
            player.seagullsInWindow.at(1).push_back(seagull); 
        }
        else {
            // For fugler med høyest fart
            player.seagullsInWindow.at(2).push_back(seagull); 
        }
    }

    // Itererer gjennom vector som inneholder deques med Seagull-objekter i vindu.
    for (int i = 0; i < 3; i++) 
    {   
        // Itererer gjennom deque med Seagull-objekter som har lik fart
        for (int j = 0; j < player.seagullsInWindow.at(i).size(); j++) {
            seagullIsHit(is_key_down(KeyboardKey::ENTER), player.seagullsInWindow.at(i).at(j), player); // Kaller
            // funksjon som sjekker om fugl er truffet eller ikke.
            dive(player.seagullsInWindow.at(i).at(j), player, i); // Kaller funksjon som tegner måker.
        }
    } 

    // Funksjonalitet for kråker

    // Plasserer ut kråke ved tilfeldige frames dersom vanskelighetsgrad er "Extreme"
    if (difficulty == "Extreme" && enemy(difficulty) && framesSinceLastCrow > 200) {
        framesSinceLastCrow = 0;
        Crow crow;
        player.crowsInWindow.push_back(crow);
    } 
     // Itererer gjennom deque som inneholder Crow-objekter i vindu.
    for (int i = 0; i < player.crowsInWindow.size(); i++) {   
        crowIsHit(player.crowsInWindow.at(i), player); // Kaller funksjon som sjekker om kråke er truffet eller ikke.
        creep(player.crowsInWindow.at(i), player); // Kaller funksjon som tegner kråker.
        if (player.hasLost) {
            break;
        }
    }  
    // Øker tellere
    framesSinceLastCrow++;

    // Øker spillers poengsum med 1 (altså 1 per frame)
    player.score++;

    // Endrer boolsk medlemsvariabel til Player-objekt, hasLost, til true dersom alle liv er brukt opp
    if (player.heartCounter == 0) {
        player.hasLost = true;
    }

    // Neste frame vises
    next_frame();
}

// ----- Funksjonalitet for at fuglene skal kunne stupe -----

// Funksjon som returnerer true hvis en fugl skal stupe ned i gjeldende frame og false ellers.
// Tar inn difficulty som parameter (frekvensen av fuglestup varierer med vanskelighetsgrad).
bool StartWindow::enemy(std::string difficulty) {
    // (Mye av kode hentet fra øvingsforelesningsslides (Øvingsforelesn. 3))
    std::random_device rd; // Genererer et seed (frø)
    std::default_random_engine generator(rd()); // Gir videre generator dette frøet som parameter

    // Hvis lavest vanskelighetsgrad stuper fugler med én frekvens.
    if (difficulty == "Normal") {
        int min = 1; 
        int max = 100; // max-verdi kan endres for å gi lavere eller høyere "stupefrekvens"
        std::uniform_int_distribution<int> dist(min, max); // Uniform fordeling, alle heltallsverdier
        // fra og med min til og med max har like stor sannsynlighet for å bli trukket.
        int num = dist(generator); // Tar inn generator som argument, og genererer en tilfeldig verdi fra
        // den uniforme fordelingen.
        if (num == 1) {
            // 1/max sannsynlighet for at fugl skal starte et stup i gjeldende frame. 
            return true;
        }
        return false;
    }
    // For de to neste vanskelighetsgradene stuper fuglene med en raskere frekvens.
    // Trenger ikke bruke else-statement siden videre kode kun kjøres dersom programmet ikke går inn i
    // if-setning (siden vi bruker return-nøkkelord i if-setning over).
    int min = 1;
    int max = 200;
    std::uniform_int_distribution<int> dist(min, max);
    int num = dist(generator);
    if (num == 1 || num == 2) {
        return true;
    }

    return false;
}

// Funksjon som tegner stupende fugler.
// Tar inn referanse til Player-objekt og et Seagull-objekt som parameter. Kan dermed endre verdien 
// til eks. Player-objektets medlemsvariabel heartCounter og Seagull-objektets medlemsvariable 
// xCoord og yCoord. Siste parameter er indeksen til deque-en der dette Seagull-objektet 
// befinner seg i seagullsInWindow-vectoren.
void StartWindow::dive(Seagull &seagull, Player &player, int index) {
        // Kode i denne if-setningen kjøres hvis aktuell fugl fortsatt vises i vinduet.
        if (seagull.yCoord < 500) {
            seagull.xCoord -= 2*seagull.changeInX; // x-koordinat til fugl-bilde endres med 2 i retning spiller.
            seagull.yCoord += (2*seagull.diveDecayConst); // y-koordinat økes med 2*"stigningstall" som regnet ut
            TDT4102::Point seagullPos = {seagull.xCoord, seagull.yCoord}; // Point brukt i tegning av bilde
            draw_image(seagullPos, seagull.ImToShow, seagull.width, seagull.height); // Tegner bilde av fugl
        }
        // Kode i denne kjøres når fugl er ute av vinduet
        else {
            // Hvis spiller ikke har "slått vekk" fugl, minker Player-objektets heartCounter med 1.
            if (!seagull.isHit) {
                player.heartCounter--;
            }
            // Fjerner aktuell fugl fra den dequen i seagullsInWindow-vectoren
            // som inneholder Seagulls-objekter i vinduet med lik fart. På den måten fjernes
            // fugl som er ute av vinduet fra vector, siden dersom farten er lik er den som startet
            // først, og dermed er lengst foran i deque-en, ute av vinduet først.
            player.seagullsInWindow.at(index).pop_front();
        }
}

// ----- Funksjonalitet for å sjekke om man har truffet måser eller ikke -----
// Funksjon tar inn boolsk verdi (etter om ENTER-tast er nede eller ikke), referanse til Seagull-objekt og
// referanse til Player-objekt.
void StartWindow::seagullIsHit(bool hit, Seagull &seagull, Player &player) {
    // Regner ut avstand i "planet" mellom spiller og fugl med Pytagoras for hypotenus. Bruker int
    // som datatype selv om tallet som regnes ut kan bli et flyttall siden en liten "avrundingsfeil" ikke har mye
    // å si her.
    int distance = 
    std::pow((std::pow((seagull.xCoord-player.xCoord), 2)+std::pow((seagull.yCoord-player.yCoord), 2)), 0.5);
    // Hvis ENTER-tast er nede, avstand mellom spiller og fugl er mindre enn en toleranse og fugl
    // ikke har kommet lengre ned i vinduet enn toppen av spillerens hode, vises bilde av
    // død fugl og boolsk medlemsvariabel isHit til aktuelt Seagull-objekt settes til true.
    if (hit && (distance < tolerance) && ((seagull.yCoord + seagull.height) < player.yCoord )) {
        seagull.ImToShow = seagull.ImDead;
        seagull.isHit = true;
    }
}

// ----- Funksjonalitet for kråker -----
void StartWindow::crowIsHit(Crow &crow, Player &player) {
    if (crow.xCoord > 410 && crow.xCoord < 540 && player.yCoord > (crow.yCoord-100)) { // Legger inn litt toleranse
        player.hasLost = true;
    }
    else if (crow.xCoord <= 400) {
        crow.ImToShow = crow.ImDead;
    }
}

void StartWindow::creep(Crow &crow, Player &player) {
        crow.xCoord -= 2;
        TDT4102::Point crowPos = {crow.xCoord, crow.yCoord}; // Point brukt i tegning av bilde
        draw_image(crowPos, crow.ImToShow, crow.width, crow.height); // Tegner bilde av fugl
        if (crow.xCoord <= -50) {
            player.crowsInWindow.pop_front();
        }
}

// ----- Funksjonalitet for å tegne antall liv man har igjen -----
// Tar inn heltall som parameter (i funksjonalitet der denne funksjonen brukes gis 
// Player-medlemsvariabel heartCounter inn som parameter).
void StartWindow::drawHearts(int heartCounter) {
    // Setter x- og y-koordinat til hjerte lengst til venstre.
    int xCoord = 100;
    int yCoord = 50;

    // Itererer antall ganger som liv igjen, tegner hvert hjerte, og øker x-koordinat til neste bilde hver gang.
    for (int i = 0; i < heartCounter; i++) {
        TDT4102::Point heartPos({xCoord, yCoord});
        draw_image(heartPos, heartIm, 30, 30);
        xCoord += 60;
    }
}

// ----- Definerer funksjon som gjør at startside opprettes igjen -----
void StartWindow::returnToStartPage() {
    difficulty = ""; // Difficulty "nullstilles" slik at vanskelighetsgrad kan velges på nytt.
    buttonScores.setVisible(false); // Knapp for å se highscores skjules.
    buttonNormal.setVisible(true); // Knapper for valg av vanskelighetsgrad settes synlige.
    buttonHard.setVisible(true);
    buttonExtreme.setVisible(true);
    buttonQuit.setVisible(false);
    quit = "No"; // StartWindow sin quit-medlemsvariabel tilbakestilles til initiell verdi "No", 
    // slik at spillet kan kjøres (og det senere er mulig å endre den til Yes hvis spiller vil avslutte spill-
    // runde og returnere til åpningsvindu.).
    scoresPage = false; // scoresPage tilbakestilles til initiell verdi false, slik at den etter endt
    // neste spill kan endres for å vise ledertavle.
}

// ----- Definerer funksjon som gjør at "game over"-side vises -----
// Tar ikke inn Player-objekt som referanse siden funksjon ikke skal gjøre endringer i Player-objekt.
void StartWindow::gameOver(Player player) {
    buttonScores.setVisible(true); 
    
    std::string scoreString = std::to_string(player.score); // Lagrer poengsum som streng, slik at den kan tegnes
    std::ifstream inputStream {highscorePath}; // Initialiserer inputStream med filsti til highscore.txt
    
    if (difficulty != "") { //Kode kjøres bare første frame, etterpå er difficulty satt til "" igjen
        for (int i = 0; i < 3; i++) { // Er alltid 3 tall i highscores, 1 for hvert nivå
        std::string score;
        inputStream >> score;
        try {
            if (score == "") {
                throw std::invalid_argument("highscore.txt inneholder for få tall. Må initialiseres med 3 tall.");
            }
            else {
            if (difficulty == "Normal" && i == 0) {
                if (player.score > std::stoi(score)) {
                    score = scoreString;
                }
            }
            else if (difficulty == "Hard" && i == 1) {
                if (player.score > std::stoi(score)) {
                    score = scoreString;
                }
            }
            else if (difficulty == "Extreme" && i == 2) {
                if (player.score > std::stoi(score)) {
                    score = scoreString;
                }
            }
            }
        }
        catch (std::invalid_argument& error) {
            std::cout << error.what() << std::endl;
        }
        try {
            scores.at(i) = score;
            // Har ikke throw-setning her fordi jeg forventer at exception som kastes er std::out_of_range.
        }
        catch (std::out_of_range) {
                scores.push_back("0");
                scores.push_back("0");
                scores.push_back("0");
                scores.at(i) = score;
            }
        }
        std::ofstream oputputStream {highscorePath}; // Initialiserer outputStream med filsti til highscore.txt
        for (int i = 0; i<3; i++) {
            oputputStream << scores.at(i) << std::endl;
        }
    }
    difficulty = ""; // Tilbakestiller difficulty til "" slik at den kan velges igjen om bruker vil starte ny runde
    TDT4102::Point gameOverPos({300,50}); // Point som brukes for å tegne "Game over"-tittel
    draw_image(gameOverPos, gameOverIm, 400, 100); // Tegner "Game Over"-tittel
    draw_text({400, 170}, "Din poengsum:", TDT4102::Color::white, 30); // Tegner teksten "Din poengsum"
    draw_text({400, 250}, scoreString, TDT4102::Color::white, 125); // Tegner poengsum
    draw_image({700, 300}, goodJobIm, 200, 100);
    draw_text({750, 400}, "But good job!", TDT4102::Color::white, 20);
    next_frame(); // Sørger for at "Game over"-vindu holdes oppe eller videre vindu vises.
}

void StartWindow::highscorePage(Player player) {
    buttonScores.setVisible(false);
    draw_text({300, 175}, "Normal: "+scores.at(0), TDT4102::Color::white, 30);
    draw_text({300, 275}, "Hard: " +scores.at(1), TDT4102::Color::white, 30);
    draw_text({300, 375}, "Extreme: "+scores.at(2), TDT4102::Color::white, 30);
    TDT4102::Image highscoreIm("Imagefiles/highscore.png");
    draw_image({300,50}, highscoreIm, 400, 100);
    next_frame();
}

// ----- Konstruktør for StartWindow-objekt -----
StartWindow::StartWindow() :

// Kolon og så en "liste" separert med komma; initialiseringsliste før selve "kroppen" til konstruktøren.
// Her initialiseres noen medlemsvariabler med sine konstruktører. Vi gjør det i initialiseringslisten fordi
// konstruktørene har parametre (ikke default-konstruktør).
TDT4102::AnimationWindow(100, 100, 1000, 500, "Måkespillet"), // Konstruktør til foreldreklasse må kalles før
// andre medlemsvariabler til StartWindow-objektet initialiseres.
buttonNormal{{100,350}, 200, 100, "Normal"}, // Konstruktører til Button(Widget)-objekter kalles.
buttonHard{{400,350}, 200, 100, "Hard"}, 
buttonExtreme{{700,350}, 200, 100, "Extreme"},
buttonQuit{{900, 100}, 50, 50, "x"},
buttonScores{{100, 100}, 100, 50, "Highscores"},
audio("seagulls.mp3"), // Konstruktør til Audio-objekt kalles med lydfil med måkelyder som parameter.
oneIm("Imagefiles/one.png"), // Konstruktører til Image-objekter kalles. Riktig bilde-filnavn er parameter.
twoIm("Imagefiles/two.png"),
threeIm("Imagefiles/three.png"),
seagullIm("Imagefiles/seagullText.png"),
cloudIm("Imagefiles/cloud.png"), 
groundIm("Imagefiles/ground.png"),
heartIm("Imagefiles/heart.png"),
gameOverIm("Imagefiles/gameOver.png"),
goodJobIm("Imagefiles/goodJob.png")

// I selve kroppen til konstruktøren gjøres resten av det konstruktøren til StartWindow-objektet skal gjøre
{
    // Knapp for lavest vanskelighetsgrad
    buttonNormal.setCallback(std::bind(&StartWindow::callbackNormal, this)); // Setter hvilken callback-funksjon 
    // som skal kalles etter knapp er klikket på. Siden callbackNormal() er en klassemetode, brukes std::bind()
    // for å binde denne callback-funksjonen til objektet konstruktøren lager (this), det vil si, fortelle 
    // programmet at callbackNormal()-medlemsfunksjonen skal kalles på akkurat dette objektet av klassen.
    // (Denne funksjonaliteten er hentet fra dokumentasjonen til AnimationWindow)
    buttonNormal.setLabelColor(TDT4102::Color::white); // Setter farge på knappens tekst
    buttonNormal.setButtonColor(TDT4102::Color::orange); // Setter farge på knapp
    buttonNormal.setButtonColorHover(TDT4102::Color::light_cyan); // Setter farge på knapp når musepeker er over
    buttonNormal.setButtonColorActive(TDT4102::Color::light_sky_blue); // Setter farge på knapp når trykket ned
    add(buttonNormal); // Gjør knapp synlig i vindu
    // Knapp for middels vanskelighetsgrad
    buttonHard.setCallback(std::bind(&StartWindow::callbackHard, this));
    buttonHard.setLabelColor(TDT4102::Color::white);
    buttonHard.setButtonColor(TDT4102::Color::orange);
    buttonHard.setButtonColorHover(TDT4102::Color::light_cyan);
    buttonHard.setButtonColorActive(TDT4102::Color::light_sky_blue);
    add(buttonHard);
    // Knapp for høyest vanskelighetsgrad
    buttonExtreme.setCallback(std::bind(&StartWindow::callbackExtreme, this));
    buttonExtreme.setLabelColor(TDT4102::Color::white);
    buttonExtreme.setButtonColor(TDT4102::Color::orange);
    buttonExtreme.setButtonColorHover(TDT4102::Color::light_cyan);
    buttonExtreme.setButtonColorActive(TDT4102::Color::light_sky_blue);
    add(buttonExtreme);
    // Knapp for å gå tilbake til åpningsvindu
    buttonQuit.setCallback(std::bind(&StartWindow::callbackQuit, this));
    buttonQuit.setLabelColor(TDT4102::Color::white);
    buttonQuit.setButtonColor(TDT4102::Color::orange);
    buttonQuit.setButtonColorHover(TDT4102::Color::light_cyan);
    buttonQuit.setButtonColorActive(TDT4102::Color::light_sky_blue);
    add(buttonQuit); 
    buttonQuit.setVisible(false); // Gjør at knapp ikke vises i vindu, endres "senere" i spillet.
    // Knapp for å gå fra "game over"-vindu til highscores-vindu
    buttonScores.setCallback(std::bind(&StartWindow::callbackScores, this));
    buttonScores.setLabelColor(TDT4102::Color::white);
    buttonScores.setButtonColor(TDT4102::Color::orange);
    buttonScores.setButtonColorHover(TDT4102::Color::light_cyan);
    buttonScores.setButtonColorActive(TDT4102::Color::light_sky_blue);
    add(buttonScores); 
    buttonScores.setVisible(false); // Gjør at knapp ikke vises i vindu, endres "senere" i spillet.
    // Setter bakgrunnsfarge til vindu
    setBackgroundColor(TDT4102::Color::light_blue);
    // Gjør at måkelyd spilles av
    play_audio(audio, 1); // Lydfil spilles av 1 gang
}
