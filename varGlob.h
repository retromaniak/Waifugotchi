/*
    W TYM PLIKU ZNAJDUJĄ SIĘ DEFINICJE ZMIENNYCH GLOBALNYCH
*/

bool flagaSnu = false;
bool softReset = 0;
bool hardReset = 0;

bool menu = false;
int sel = 1;
byte sklSel = 1;

boolean dbgMode = true;
boolean serMode = true;
boolean batMode = false;

int batLev = 100;

bool alertZdro = true;
bool alertJedz = true;
bool alertHigi = true;
bool alertZaba = true;
bool alertDysc = true;

byte keyu = 0;
byte keyd = 0;
byte keyl = 0;
byte keyr = 0;
byte keyc = 0;
byte keyx = 0;

byte st = 0;

int sumaStat = 0;

byte ekrOds = 1;
byte ekrFFr = 1;
unsigned long ekrTOu = 8000;

bool isDead = false;
byte tmpEtapGry = 1;
byte wyborKierunku = 0;

// Zmienne globalne przechowujące aktualną planszę
byte plansza[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
byte ktoZaczyna = 0;
byte graFlaga = 0;
byte trudnosc = 70;

int wifiMode = 0;
char otrzymanyZnak = 0;
