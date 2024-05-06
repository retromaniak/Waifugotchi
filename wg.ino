#include <ESP32Time.h>        // Biblioteka do obsługi funkcji czasu
#include <GxEPD2_BW.h>        // Biblioteka do obsługi ekranu
#include <Fonts/cze.h>        // Font 5x7px w ktorym male litery sa odpowiedniki z ogonkami
#include <Fonts/witam.h>      // Font 3x5px w ktorym male litery sa odpowiedniki z ogonkami
#include "FS.h"               // biblioteka do obsługi systemu plików
#include "SPIFFS.h"           // SPI flash filesystem

/*
// konfigurator ekranu
GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(
            5,      //pin cs
            26,     //pin dc
            2,      //pin rst
            15      //pin busy
        ));
// konfiguracja pinów przycisków i buzzera
#define BUPIN 12  // Góra
#define BDPIN 13  // Dół
#define BLPIN 14  // Lewo
#define BRPIN 25  // Prawo
#define BCPIN 21  // Centralny
#define SPPIN 22  // Buzzer

*/

    // konfigurator ekranu
    GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(
            5,      //pin cs
            22,     //pin dc
            2,      //pin rst
            15      //pin busy
        ));
    // konfiguracja pinów przycisków i buzzera
    #define BUPIN 35  // Góra
    #define BDPIN 13  // Dół
    #define BLPIN 14  // Lewo
    #define BRPIN 25  // Prawo
    #define BCPIN 34  // Centralny
    #define SPPIN 26  // Buzzer


// utworzenie instancji RTC
ESP32Time rtc(0);

//WylaczenieWifi #include <painlessMesh.h>
#define   MESH_SSID       "WAIFUGOTCHIWIFI"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

// Prototypy
void sendMessage();
void receivedCallback(uint32_t from, String & msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback();
void nodeTimeAdjustedCallback(int32_t offset);
void delayReceivedCallback(uint32_t from, int32_t delay);

#include "xmpData.h" // dane bitmap
#include "varKonf.h" // ustawienia konfiguracyjne niedostępne dla użytkownika
#include "varGlob.h" // definicje zmiennych globalnych
#include "fncPlik.h" // funkcje odczytu, zapisu i usuwania plików
#include "fncKlaw.h" // funkcje obsługi klawiszy oraz wirtualnych klawiszy
#include "fncText.h" // funkcje wyboru fontu, wyświetlania napisów
#include "drwMenu.h" // rysowanie paska menu
#include "ustGodz.h" // ustawianie godziny i daty
#include "ustPost.h" // tworzenie postaci
#include "fncDeSl.h" // usypianie i wybudznie
#include "drwPost.h" // rysowanie postaci

// CZY FORMATOWAC PAMIEC SPIFFS JEZELI NIE UDA SIE JEJ URUCHOMIC?
#define FORMAT_SPIFFS_IF_FAILED true

//WylaczenieWifi Scheduler     userScheduler; // task
//WylaczenieWifi painlessMesh  mesh;

void sendMessage() ; // Prototyp




void setup()
{
    if (serMode) {                                  // jezeli aktywny jest tryb polaczenia UART
        Serial.begin(115200);                       // rozpoczecie pracy portu z predkością 115200
        delay(5);
    }
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_34, 1);   // ustawienie pinu wybudzania
    delay(500);
    // konfiguracja trybu pinow:
    pinMode(BUPIN, INPUT); //przycisk gora
    pinMode(BDPIN, INPUT); //przycisk dol
    pinMode(BLPIN, INPUT); //przycisk lewo
    pinMode(BRPIN, INPUT); //przycisk prawo
    pinMode(BCPIN, INPUT); //przycisk centralny
    pinMode(SPPIN, OUTPUT);
    print_wakeup_reason();                          // sprawdzenie przyczyny wybudzenia (np reset, automatyczne lub przyciskiem)
    delay(5);
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {   // rozpoczecie i sprawdzenie rozpoczecia pracy SPIFFS
        Serial.println("SPIFFS ERR");               // wyświetlenie bledu
        delay(1000);                                // czekaj
        return;
    } else {
        Serial.println("SPIFFS OK");                // wyświetlenie prawidlowego uruchomienia SPIFFS
    }
    rStanPostac();                                  // wczytanie statystyk postaci z systemu plikow do zmiennych
    byte res = preWake(softReset);                  // "male" uruchomienie - zaladowanie podstawowych danych, sprawdzanie czasu itd
    delay(5);
    if (gameReset) clrFiles();                      // czyszczenie plikow jezeli ustawiono resetowanie gry przy kazdym wybudzeniu
    fullWake(softReset, hardReset);                 // pelne wybudzenie
    if (!isDead) {              // jezeli postac nie jest martwa
        rStanPostac();
        calcStats();                                    // obliczanie statystyk
        if (flagaSnu) {                                 // jezeli jest noc
            minSleep();                                 // uspij
        }

        // jezeli jest aktywny dowolny alarm
        if (alertDysc || alertZdro || alertJedz || alertZaba || alertHigi) {
            alertSnd();                                 //aktywuj dzwiek alarmu
        }

        // jezeli jest aktywny alarm dyscypliny
        if (alertDysc) {
            stZdrAla =  random(9000);                   //losuj poziom ktory wyzwala alarm zdrowia
            stJedAla =  random(9000);                   //losuj poziom ktory wyzwala alarm jedzenia
            stHigAla =  random(9000);                   //losuj poziom ktory wyzwala alarm higieny
            stZabAla =  random(9000);                   //losuj poziom ktory wyzwala alarm zabawy
        }
    }

    if (wifiMode) {
        //WylaczenieWifi mesh.setDebugMsgTypes(ERROR | DEBUG);
        //WylaczenieWifi mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
        //WylaczenieWifi mesh.onReceive(&receivedCallback);
    } else {
        //WylaczenieWifi WiFi.mode(WIFI_OFF);
    }
}



void loop() {
    checkKeys();    // sprawdzanie wciskania klawiszy
    if (!isDead) {  // jezeli postac zyje
        calcStats(); // kalkulacje statystyk
        if (alertDysc) {
            stZdrAla =  stZdrAlaC;                   //losuj poziom ktory wyzwala alarm zdrowia
            stJedAla =  stJedAlaC;                   //losuj poziom ktory wyzwala alarm jedzenia
            stHigAla =  stHigAlaC;                   //losuj poziom ktory wyzwala alarm higieny
            stZabAla =  stZabAlaC;                   //losuj poziom ktory wyzwala alarm zabawy
        }

        if (st > 0) {                                // warunek na potrzeby gier i uspiania z otwartymi oczami postaci
            mruga = 0;                               // nie mrugaj
            patrzy = 0;                              // patrz prosto
        }

        if (keyx) keyx = 0;                          // resetowanie flagi wcisniecia dowolnego przycisku

        // ponizej funkcje nawigowania
        if (st == 0) {                      // EKRAN GLOWNY
            if (alertZdro) {                    // jezeli istnieje alert zdrowia
                if (keyl) {                         // jezeli wcisnieto przycisk w lewo
                    leczenie();                         // lecz postac
                }
            } else if (alertJedz) {             // jezeli istnieje alert jedzenia
                if (keyl) {                         // jezeli wcisnieto przycisk w lewo
                    st = 1;                             // nakarm
                }
            } else if (alertHigi) {             // jezeli istnieje alert higieny
                if (keyl) {                         // jezeli wcisnieto przycisk w lewo
                    wyczysc();                             // wyczysc
                }
            }
            if (alertZaba) {                    // jezeli istnieje alert zabawy
                if (keyr) {                         // jezeli wcisnieto przycisk w prawo
                    st = 5;                             // menu zabaw
                }
            } else if (alertDysc) {             // jezeli istnieje alert dyscypliny
                if (keyr) {                         // jezeli wcisnieto przycisk w prawo
                    dyscyplina();                       // dyscyplinuj
                }
            }

            if (keyc) {                         // jezeli wcisnieto przycisk srodkowy
                st = 1;                             // menu glowne
                sel = 1;                            // zaznaczona opcja = 1
            }

        } else if (st == 1) {               // MENU

            if (keyc) {
                if (sel == 1) st = 2;       // NAKARM
                if (sel == 2) st = 3;       // STATYSTYKI
                if (sel == 3) leczenie();   // LECZENIE
                if (sel == 4) st = 4;       // SKLEP
                if (sel == 5) wyczysc();    // WYCZYŚĆ
                if (sel == 6) st = 5;       // ZABAWA
                if (sel == 7) dyscyplina(); // DYSCYPLINA
                if (sel == 8) st = 6;       // SPOLECZNOSC
                if (sel == 9) st = 7;       // USTAWIENIA
                sel = 1;                 // zaznaczona opcja = 1
                sklSel = 1;              // zaznaczony sklep = 1
            }
            if (keyu) {                 // klawisz w gore
                sel--;                  // poprzednia opcja
                if (sel == 0) sel = 9;  // jezeli skrajnie gorna opcja, przejdz do ostatniej
            }
            if (keyd) {                 // klawisz w dol
                sel++;                  // kolejna opcja
                if (sel == 10) sel = 1; // jezeli skrajnie dolna opcja, przejdz do pierwszej
            }
            if (keyl) {                 // klawisz w lewo
                st = 0;                 // ekran glowny
            }
        } else if (st == 2) {           // NAKARM
            if (keyu) {                 // klawisz w gore
                sel--;                  // poprzednia opcja
                if (sel == 0) sel = 4;  // "przekrecenie" licznika
            }
            if (keyd) {                 // klawisz w dol
                sel++;                  // kolejna opcja
                if (sel == 5) sel = 1;  // "przekrecenie" licznika
            }
            if (keyl) {                 // klawisz w lewo
                st = 1;
            }
            if (keyr) {                 // klawisz w prawo
                st = 4;                 // przejdz do sklepu
                sel = 1;                // reset zaznaczenia
            }

            if (keyc) {                 // klawisz centralny
                if (ekJedz[sel - 1] > 0) {
                    jedzJedzenie(sel - 1);
                }
            }

        } else if (st == 3) { // STATYSTYKI
            if (keyl) {                 // klawisz w lewo
                st = 1;
            }
        } else if (st == 4) { // SKLEP
            if (keyu) {                 // klawisz w gore
                sel--;                  // poprzednia opcja
                if (sel == 0) sel = 4;     // "przekrecenie" licznika
            }
            if (keyd) {                 // klawisz w dol
                sel++;                  // kolejna opcja
                if (sel == 5) sel = 1;     // "przekrecenie" licznika
            }
            if (keyl) {                 // klawisz w lewo
                st = 1;                 // powrot do menu
            }
            if (keyr) {                 // klawisz w prawo
                sklSel++;                  // kolejny sklep
                if (sklSel > 3) sklSel = 1;     // "przekrecenie" licznika
                sel = 1;                 // powrot do menu
            }
            if (keyc) {                 // klawisz centralny

                if (sklSel == 1) {      // jezeli aktywny jest pierwszy sklep
                    // sprawdz czy posiada wiecej lub tyle samo pieniedzy ile kosztuje przedmiot, oraz czy ilosc przedmiotu jest mniejsza od 9
                    if ((stKasa >= cena[sklSel - 1][sel - 1]) && (ekJedz[sel - 1] < 9)) {
                        stKasa -= cena[sklSel - 1][sel - 1];    // odlicz pieniadze
                        ekJedz[sel - 1]++;                      // dodaj jedzenie
                    } else {
                        errSnd();                               // brak pieniedzy = dzwiek bledu
                    }

                }
                if (sklSel == 2) {      // jezeli aktywny jest drugi sklep
                    if ((stKasa >= cena[sklSel - 1][sel - 1]) && (ekItem[sel - 1] == 0)) {
                        stKasa -= cena[sklSel - 1][sel - 1];   // odlicz pieniadze
                        ekItem[sel - 1] = 1;                   // kup przedmiot
                    } else {
                        errSnd();                               // brak pieniedzy = dzwiek bledu
                    }

                }
                if (sklSel == 3) {      // jezeli aktywny jest trzeci sklep
                    if ((stKasa >= cena[sklSel - 1][sel - 1]) && (ekUbra[sel - 1] == 0)) {
                        stKasa -= cena[sklSel - 1][sel - 1];   // odlicz pieniadze
                        for (int i = 0; i < 4; i++) {          // dla wszystkich 4 ubran
                            if ((sel - 1) == i) {              // jezeli petla przechodzi przez kupowane ubranie
                                ekUbra[i] = 1;                      // dodaj je do ekwipunku
                            } else {                           // jezeli to inne ubranie niz kupowane
                                ekUbra[i] = 0;                      // zabierz je z ekwipunku
                            }
                        }
                    } else {
                        errSnd();                               // brak pieniedzy = dzwiek bledu
                    }

                }

            }
        } else if (st == 5) {   // ZABAWA
            if (keyl) {                 // klawisz w lewo
                st = 1;                 // wstecz
            }
            if (keyu) {                 // klawisz w gore
                st = 8;                 // patrzenie
            }
            if (keyd) {                 // klawisz w dol
                st = 9;                 // singleplayer kolko krzyzyk
                graFlaga = 0;
                for (int j = 0; j < 9; j++) {
                    plansza[j] = 0;
                }
                byte losu = random(100);
                if (losu > 50) {
                    ktoZaczyna = 1;
                } else {
                    ktoZaczyna = 2;
                    wykonajRuch();
                }
            }
            if (keyr) {                 // klawisz w prawo
                st = 6;                 // spolecznosc
            }
        } else if (st == 6) {   // SPOLECZNOSC
            if (!wifiMode) {
                writeFile(SPIFFS, "/netFlg", "1");
                micSleep();
            } else {
                if (keyc) {
                    st = 9 + sel;
                }
                if (keyu) {                 // klawisz w gore
                    sel--;                  // poprzednia opcja
                    if (sel == 0) sel = 4;     // "przekrecenie" licznika
                }
                if (keyd) {                 // klawisz w dol
                    sel++;                  // kolejna opcja
                    if (sel == 5) sel = 1;     // "przekrecenie" licznika
                }
            }
            if (keyl) {                 // klawisz w lewo
                st = 1;                 // wroc do menu
            }
        } else if (st == 7) { // USTAWIENIA

            if (keyc) {                 // klawisz centralny
                if (ustawienia[sel - 1]) { // jezeli ustawienie jest aktywne
                    ustawienia[sel - 1] = 0;    // wylacz ustawienie
                } else {                    // jezeli ustawienie nie jest aktywne
                    ustawienia[sel - 1] = 1;    // wlacz ustawienie
                }
            }
            if (keyu) {                 // klawisz w gore
                sel--;                  // poprzednia opcja
                if (sel == 0) sel = 9;     // "przekrecenie" licznika
            }
            if (keyd) {                 // klawisz w dol
                sel++;                  // kolejna opcja
                if (sel == 10) sel = 1;     // "przekrecenie" licznika
            }
            if (keyl) {                 // klawisz w lewo
                st = 1;                 // wroc do menu
                zapiszStaty();          // zapisz ustawienia i statystyki
            }
        } else if (st == 8) { // ZABAWA PATRZY

            if (tmpEtapGry == 1) {      // poczatkowy etap - czeka na wybor gracza
                if (keyl) {                 // klawisz w lewo
                    wyborKierunku = 1;      // okreslenie zmiennej wybranego kierunku (L)
                    if (random(100) < 50) {     // losowanie 50%
                        tmpEtapGry = 2;         // przejdz do etapu patrzenia w lewo
                    } else {
                        tmpEtapGry = 3;         // przejdz do etapu patrzenia w prawo
                    }
                }
                if (keyr) {                 // klawisz w prawo
                    wyborKierunku = 2;      // okreslenie zmiennej wybranego kierunku (P)
                    if (random(100) < 50) {     // losowanie 50%
                        tmpEtapGry = 2;         // przejdz do etapu patrzenia w lewo
                    } else {
                        tmpEtapGry = 3;         // przejdz do etapu patrzenia w prawo
                    }
                }
                if (keyc) {                 // klawisz centralny
                    tmpEtapGry = 1;             // reset "momentu" gry
                    wyborKierunku = 0;          // reset wybranego kierunku patrzenia
                    st = 1;                     // wroc do menu
                    sel = 6;                    // zaznaczona opcja
                }
            } else {                    // etap po wyborze kierunku patrzenia
                if (tmpEtapGry == (wyborKierunku + 1)) { // dobrze wybrano
                    tmpEtapGry = 1;             // reset "momentu" gry
                    wyborKierunku = 0;          // reset wybranego kierunku patrzenia
                    errSnd();                   // dzwiek
                    stKasa += 500;              // dodaj gotowke
                    stZaba += stZabDod;         // zwieksz stat zabawy
                    if (stZaba > 10000) stZaba = 10000; // zabezpieczenie przed przekreceniem
                    zapiszStaty();              // zapisz zmiany
                } else {                                // zle wybrano
                    tmpEtapGry = 1;             // reset "momentu" gry
                    wyborKierunku = 0;          // reset wybranego kierunku patrzenia
                    errSnd();                   // dzwiek
                    stKasa += 1;                // dodaj gotowke (1 grosz);
                    stZaba += stZabDod / 2;       // zwieksz stat zabawy o polowe tego co przy wygranej
                    if (stZaba > 10000) stZaba = 10000; // zabezpieczenie przed przekreceniem
                    zapiszStaty();              // zapisz zmiany
                }
            }
            keyx = 1;                // wywolanie dodatkowego odswiezenia ekranu aby przed powrotem do stanu poczatkowego wyswietlic jeszcze kierunek patrzenia
            ekrOds = 1;              // wywolanie dodatkowego odswiezenia ekranu aby przed powrotem do stanu poczatkowego wyswietlic jeszcze kierunek patrzenia

        } else if (st == 9) { // ZABAWA KOLKO KRZYZYK

            if (keyl) {                 // klawisz w lewo
                sel--;
                if (sel < 0) {
                    sel = 2;
                }
            }
            if (keyu) {                 // klawisz w gore
                sel -= 3;
                if (sel < 0) {
                    sel += 3;
                }
            }
            if (keyd) {                 // klawisz w dol
                sel += 3;
                if (sel > 8) {
                    sel -= 3;
                }
            }
            if (keyr) {                 // klawisz w prawo
                sel++;
                if (sel > 8) {
                    sel = 0;
                }
            }
            if (keyc) {                 // klawisz w prawo
                if (plansza[sel] == 0) {
                    plansza[sel] = 1;
                }
                if (graFlaga) {
                    st = 5;
                } else {
                    wykonajRuch();
                    if (sprawdzWygrana(plansza, 1)) { // czy wygral gracz
                        errSnd();
                        graFlaga = 1;
                        stKasa += 5000;              // dodaj gotowke
                        stZaba += stZabDod;         // zwieksz stat zabawy
                        if (stZaba > 10000) stZaba = 10000; // zabezpieczenie przed przekreceniem
                        zapiszStaty();              // zapisz zmiany
                    }
                    if (sprawdzWygrana(plansza, 2)) { // czy wygral komputer
                        errSnd();
                        graFlaga = 1;
                        st = 5;
                        stKasa += 500;              // dodaj gotowke
                        stZaba += stZabDod / 2;     // zwieksz stat zabawy
                        if (stZaba > 10000) stZaba = 10000; // zabezpieczenie przed przekreceniem
                        zapiszStaty();              // zapisz zmiany
                    }
                }
            }

            keyx = 1;                // wywolanie dodatkowego odswiezenia ekranu
            ekrOds = 1;              // wywolanie dodatkowego odswiezenia ekranu

        } else if (st == 11) { // WYSLIJ 100 PLN
            if (stKasa >= 100) {
                stKasa -= 100;
                //WylaczenieWifi mesh.sendBroadcast("$");
                zapiszStaty();
            }
            st = 8;

        } else if (st == 12) { // WYSLIJ CHLEB
            if (ekJedz[0] >= 1) {
                ekJedz[0] -= 1;
                //WylaczenieWifi mesh.sendBroadcast("F");
                zapiszStaty();
            }
            st = 8;
        } else if (st == 13) { // GRAJ

            //WylaczenieWifi mesh.sendBroadcast("K");
            st = 8;
        } else if (st == 14) { // OTRZYMAJ
            // odkodowuje ostatnia otrzymana wiadomosc
            if (otrzymanyZnak == '$') {

                stKasa += 100;
                zapiszStaty();
            }
            if (otrzymanyZnak == 'F') {
                if (ekJedz[0] < 9) {
                    ekJedz[0] += 1;
                    zapiszStaty();
                }
            }
            if (otrzymanyZnak == 'K') {
                otrzZaproszenie();
            }
            st = 8;
        }


        // ponizej funkcje rysowania
        if (ekrOds) { // jezeli nalezy odswiezyc ekran
            if (ekrFFr) { // pierwsza klatka musi byc pelna
                display.setFullWindow();     // pelna klatka przesiewana
                ekrFFr = 0;                 // zmiana flagi
            } else { // kolejne klatki nie musza robic pelnego przesiewu
                display.setPartialWindow(0, 0, 128, 296);     // szybka klatka

            }
            ekrOds = 0;                         // zmiana flagi
            display.firstPage();                // rozpoczecie rysowania na ekran
            display.fillScreen(GxEPD_WHITE);    // caly ekran na bialo (czysc)
            drawStatusBar();                    // rysuj gorny pasek

            if (st == 0) {                      // jezeli ekran glowny
                drawWaifu(0);                       // rysuj gorny pasek
                String napisL = " ";                // opcja menu lewa
                String napisR = " ";                // opcja menu prawa

                if (alertZdro) {                    // jezeli istnieje alert zdrowia
                    napisL = "LECZENIE";                // opcja menu lewa
                } else if (alertJedz) {             // jezeli istnieje alert jedzenia
                    napisL = "NAKARM";                  // opcja menu lewa
                } else if (alertHigi) {             // jezeli istnieje alert higieny
                    napisL = "WYCZYsc";                 // opcja menu lewa
                }
                if (alertZaba) {                    // jezeli istnieje alert zabawy
                    napisR = "ZABAWA";                  // opcja menu prawa
                } else if (alertDysc) {             // jezeli istnieje alert dyscypliny
                    napisR = "DYSCYPL.";                // opcja menu prawa
                }

                drawMenuBar(napisL, napisR);        // rysuj pasek menu z opcjami powyzej
                drawIcons();                        // rysuj ikony alertow
            } else if (st == 1) {               // menu glowne
                drawMenu(sel);                      // rysuj menu glowne
                drawMenuBar("WSTECZ", " ");         // rysuj pasek menu
            } else if (st == 2) {               // NAKARM
                drawNakarm(sel);                    // rysuj menu karmienia
                drawMenuBar("WSTECZ", "SKLEP");     // rysuj pasek menu
            } else if (st == 3) {               // STATYSTYKI
                drawStats();                        // rysuj statystyki
                drawMenuBar("WSTECZ", "");          // rysuj pasek menu
            } else if (st == 4) {               // SKLEP
                drawSklep(sklSel, sel);             // rysuj sklep
                drawMenuBar("WSTECZ", "KOLEJNY");   // rysuj pasek menu
            } else if (st == 5) {               // ZABAWA
                drawZabawa();                       // rysuj menu zabawy
                drawMenuBar("WSTECZ", "Wl. WIFI");  // rysuj pasek menu
            } else if (st == 6) {               // SPOLECZNOSC
                drawSpol(sel);                      // rysuj menu spolecznosci
                drawMenuBar("WSTECZ", "SKLEP");     // rysuj pasek menu
            } else if (st == 7) {               // USTAWIENIA
                drawSett(sel);                      // rysuj menu ustawien
                drawMenuBar("WSTECZ", "ZMIANA");    // rysuj pasek menu
            } else if (st == 8) {               // ZABAWA PATRZY
                drawWaifu(tmpEtapGry);              // rysuj postac (uwzglednia etap gry - kierunek patrzenia)
                drawMenuBar("LEWO", "PRAWO");       // rysuj pasek menu
            } else if (st == 9) {               // ZABAWA KOLKO KRZYZYK
                drawZabawaB();                      // rysuj zabawe w kolko i krzyzyk
                drawMenuBar(" ", " ");              // rysuj pasek menu
            } else if (st == 11) {

            } else if (st == 12) {

            } else if (st == 13) {

            } else if (st == 14) {

            }

            display.nextPage();              // wyrysuj bufor na ekranie
        }

        if (st == 0) {                      // tylko anim oczy/usta na ekranie glownym
            display.firstPage();            // rozpocznij rysowanie
            display.setPartialWindow(26, 94, 76, 49); // ustaw obszar odswiezania na oczy i usta
            drawWaifu(0);                   // aktualizuj waifu
            display.nextPage();             // wyrysuj bufor na ekranie
        }

        if (millis() > ekrTOu) {            // jezeli osiagnieto timeout uspienia
            if (st == 0) {                      // jezeli jest na ekranie glownym
                if ((mruga == 0) && (patrzy == 0)) {    // jezeli nie mruga i patrzy prosto
                    minSleep();                             // uspij
                }
            } else {                            // jezeli nie jest na ekranie glownym
                st = 0;                             // idz do ekranu glownego
                ekrTOu = millis() + 10000;          // dodaj jeszcze 10 sekund do uspienia
                ekrOds = 1;                         // odswiez ekran
            }
        }
        Serial.println(ekrTOu - millis());          // wypisz czas do uspienia ekranu w monitorze portu
    } else {    // jezeli postac nie zyje
        if (keyu) {     // czyszczenie plikow przyciskiem w gore
            clrFiles();
            delay(1000);
            minSleep(); // po uspieniu i wybudzeniu bedzie tworzona nowa postac
        }
        display.firstPage();
        display.setPartialWindow(0, 0, 128, 296);
        display.drawXBitmap(0, 0, nagrobek_bits, 128, 296, GxEPD_BLACK);  // tlo smierci
        fntSel(1, 3, 5, 150);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        for (int i = 0; i < 10; i++) {      // dla kazdej litery
            display.print(imieWaifu[i]);    // wypisz imie
        }
        fntSel(0, 1, 30, 166);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print("UR. ");  // urodzono
        display.print(plBornD); // dzien
        display.print(".");
        display.print(plBornM); // miesiac
        display.print(".");
        display.print(plBornY); // rok
        fntSel(0, 1, 30, 186);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print("ZM. ");  // zmarl
        display.print(plDeadD); // dzien
        display.print(".");
        display.print(plDeadM); // miesiac
        display.print(".");
        display.print(plDeadY); // rok
        display.nextPage();
        if (millis() > ekrTOu) {    // uspienie, timeout
            minSleep();
        }
    }
    //WylaczenieWifi Serial.println("Wczytuje flage wifi...");
    File file = SPIFFS.open("/netFlg");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
    }
    //WylaczenieWifi Serial.println("Odczyt z pliku:");
    if (file.available()) {
        wifiMode = file.parseInt();
    }
    file.close();

    if (wifiMode) {
        //WylaczenieWifi mesh.update();
        writeFile(SPIFFS, "/netFlg", "0");
    }
}

void sendMessage() {
    String msg = "Hello";
    Serial.printf("wiadomosc: %s\n", msg.c_str());
    //WylaczenieWifi mesh.sendBroadcast(msg);
}

void receivedCallback(uint32_t from, String & msg) {
    Serial.printf("Otrzymano %u msg=%s\n", from, msg.c_str());
    otrzymanyZnak = msg[0];
}
