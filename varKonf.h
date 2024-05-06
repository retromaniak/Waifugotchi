/*
    W TYM PLIKU ZNAJDUJĄ SIĘ ZMIENNE DOTYCZĄCE USTAWIEN/KONFIGURACJI
*/

// TO USTAWIENIE OKREŚLA, CZY PO RESECIE ZASILANIA RESETOWAĆ RÓWNIEŻ ROZGRYWKĘ
const bool gameReset = 0;

// SEN
const byte slpHr = 21;        // DOMYŚLNA GODZINA SNU
const byte wakHr = 8;         // DOMYŚLNA GODZINA POBUDKI

const int stJDodChl = 4000;     // ile najedzenia dodaje chleb
const int stJDodSal = 3000;     // ile najedzenia dodaje salatka
const int stJDodCze = 2000;     // ile najedzenia dodaje czekolada
const int stJDodKar = 1500;     // ile najedzenia dodaja karmelki



// STATYSTYKI I EFEKTY
// Poziom wzbudzający alarm:
const int stZdrAlaC = 4000; // zdrowia
const int stJedAlaC = 4000; // jedzenia
const int stHigAlaC = 4000; // higieny
const int stZabAlaC = 4000; // zabawy
const int stDysAlaC = 4000; // dyscypliny

// zmienne (uzywane jako stan wyzwalacza falszywego alarmu przy braku dyscypliny)
int stZdrAla = 4000;   // zdrowia
int stJedAla = 4000; // jedzenia
int stHigAla = 4000; // higieny
int stZabAla = 4000; // zabawy
int stDysAla = 4000; // dyscypliny

// Obnizanie statystyk co 5 minut o:
const int stZdrObn = 200; // zdrowia
const int stJedObn = 200; // jedzenia
const int stHigObn = 200; // higieny
const int stZabObn = 200; // zabawy
const int stDysObn = 200; // dyscypliny
const int stBatObn = 1000; // batonika
const int stZelObn = 1000; // zelu

// Minimalny poziom statystyk w nocy:
const int stZdrMin = 2000; // zdrowia
const int stJedMin = 2000; // jedzenia
const int stHigMin = 2000; // higieny
const int stZabMin = 2000; // zabawy
const int stDysMin = 2000; // dyscypliny

// Suma statystyk ponizej ktorej postac umiera (0%  0-50000  100%):
const int stProgSm = 5000; // 10%
const int stHappy = 40000; // suma statystyk potrzebna do usmiechu
const int stSad = 15000;   // suma statystyk potrzebna do smutku

// Poziom uzupelniania statystyk pojedynczą czynnością:
const int stZdrDod = 7500; // zdrowia
const int stHigDod = 7500; // higieny
const int stZabDod = 500; // zabawy
const int stDysDod = 7500; // dyscypliny


const int cena[3][4] = {        // ceny produktow
    {200, 450, 400, 350},           // jedzenia
    {800, 600, 400, 500},           // itemow
    {2000, 5000, 10000, 20000},     // ubran
};
