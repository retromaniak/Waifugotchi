// znaki przechowujace imie postaci
char imieWaifu[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int dUro = 0;       // zmienna dla dnia urodzin
int mUro = 0;       // zmienna dla miesiaca urodzin
int rUro = 0;       //
//                                 plik plaNam (imie)
byte plPlec = 0;                // plik plaPle (plec)
byte typOka = 1;                // typ oka

int plBornD = 0;                // plik plaBoD (dzien narodzin)
int plBornM = 0;                // plik plaBoM (miesiac narodzin)
int plBornY = 0;                // plik plaBoY (rok narodzin)

int plDeadD = 0;                // plik plaDeD (dzien smierci)
int plDeadM = 0;                // plik plaDeM (miesiac smierci)
int plDeadY = 0;                // plik plaDeY (rok smierci)

unsigned int stZdro = 10000;    // plik plaZdr (poziom zdrowia) 10000 = 100%
unsigned int stJedz = 10000;    // plik plaJed (poziom najedzenia) 10000 = 100%
unsigned int stHigi = 10000;    // plik plaHig (poziom higieny) 10000 = 100%
unsigned int stZaba = 10000;    // plik plaZab (poziom zabawienia) 10000 = 100%
unsigned int stDysc = 10000;    // plik plaDys (poziom dyscypliny) 10000 = 100%

unsigned int stKasa = 10000;    // plik plaKas (ilosc gotowki) 10000 = 100 PLN
unsigned int stBato = 10000;    // plik plaBat (efekt batonika) 10000 = 100%
unsigned int stAnty = 10000;    // plik plaAnt (poziom zelu antyb) 10000 = 100%

byte ekUbra[4] = {1, 0, 0, 0};  // plik plaUbr (ubranie/tors 1,2,3,4)
byte ekItem[4] = {0, 0, 0, 0};  // plik plaItm (rybka, lampka, batonik, zel antyb)
byte ekJedz[4] = {0, 0, 0, 0};  // plik plaItj (chleb, salatka, czekolada, karmelki)

byte ustawienia[10] = {         // plik devSet, wszystkie wartosci od 0 do 9
    1,  // [0]odswiezanie ekranu    0 pelne       1 czesciowe
    0,  // []czas uspienia          0 5 minut     1 minuta
    0,  // []alarmowanie            0 dyskretne   1 ciche
    0,  //[]
    0,  //[]
    0,  //[]
    0,  //[]
    0,  //[]
    0,  //[]
    0   //[]
};

// funkcja sprawdza czy istnieje utworzona postac - w trakcie uruchamiania urzadzenia
// decyduje ona czy uruchomic menu tworzenia postaci, zwraca zmienna byte - 0 w przypadku braku postaci,
// 2 w przypadku jezeli postac istnieje i zyje, 1 w przypadku gdy postac istnieje, ale nie zyje
byte jestPostac() {
    Serial.println("Sprawdzam czy istnieje postac...");
    File file = SPIFFS.open("/creSta"); // otwarcie pliku
    if (!file || file.isDirectory()) {  // sprawdzenie czy plik istnieje i nie jest katalogiem
        Serial.println("Brak danych");
        return 0;                       // jezeli pliku nie ma = brak postaci = zwraca 0
    }

    Serial.println("Odczyt z pliku:");
    int odczytInt = 0;                  // tymczasowa zmienna na odczytane dane
    if (file.available()) {             // jezeli plik jest dostepny
        odczytInt = int(file.read());   // odczytuje bajt z pliku i zamieniam go na int
        Serial.println(char(odczytInt));// wyswietlam znak w monitorze portu
        if (int(odczytInt) == 50) {     // dane z pliku pobrane są jako byte, więc 2=50, 1=49, 0=48
            file.close();               // zamykanie pliku
            Serial.println("Postac istnieje i zyje.");
            return 2;                   // funkcja jestPostac zwraca 2
        } else {
            file.close();               // zamknij plik
            Serial.println("Postac nie zyje.");
            return 1;                   // funkcja jestPostac zwraca 1
        }
    }
}

// funkcja odczytuje stan postaci i przypisuje wartosci z plikow do zmiennych (statystyki, ekwipunek, pieniądze)
// w zaleznosci od przechowywanych danych odczytuje znak po znaku lub liczbę (int)

bool rStanPostac() {

    // pojedyncza sekcja odczytu
    Serial.println("Wczytuje imie postaci...");
    File file = SPIFFS.open("/plaNam");         // otwarcie pliku
    if (!file || file.isDirectory()) {          // sprawdzenie istnienia pliku i tego czy nie jest katalogiem
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        for (int i = 0; i < 10; i++) {
            imieWaifu[i] = char(file.read());   // odczyt znak po znaku
            Serial.println(imieWaifu[i]);
        }
        Serial.println(" ");
    }
    file.close();                               // zamknij plik



    Serial.println("Wczytuje plec postaci...");
    file = SPIFFS.open("/plaPle");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        plPlec = file.parseInt();
        Serial.println(plPlec);
    }
    file.close();


    Serial.println("Wczytuje zdrowie postaci...");
    file = SPIFFS.open("/plaZdr");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        stZdro = file.parseInt();
        Serial.println(stZdro);
    }
    file.close();


    Serial.println("Wczytuje typ oka...");
    file = SPIFFS.open("/typOka");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        typOka = file.parseInt();
        Serial.println(typOka);
    }
    file.close();


    Serial.println("Wczytuje najedzenie postaci...");
    file = SPIFFS.open("/plaJed");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        stJedz = file.parseInt();
        Serial.println(stJedz);
    }
    file.close();


    Serial.println("Wczytuje higiene postaci...");
    file = SPIFFS.open("/plaHig");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        stHigi = file.parseInt();
        Serial.println(stHigi);
    }
    file.close();


    Serial.println("Wczytuje zabawienie postaci...");
    file = SPIFFS.open("/plaZab");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        stZaba = file.parseInt();
        Serial.println(stZaba);
    }
    file.close();


    Serial.println("Wczytuje dyscypline postaci...");
    file = SPIFFS.open("/plaDys");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        stDysc = file.parseInt();
        Serial.println(stDysc);
    }
    file.close();


    Serial.println("Wczytuje stan konta postaci...");
    file = SPIFFS.open("/plaKas");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        stKasa = file.parseInt();
        Serial.println(stKasa);
    }
    file.close();

    Serial.println("Wczytuje dzien urodzenia...");
    file = SPIFFS.open("/plaBoD");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        plBornD = file.parseInt();
        Serial.println(plBornD);
    }
    file.close();

    Serial.println("Wczytuje miesiac urodzenia...");
    file = SPIFFS.open("/plaBoM");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        plBornM = file.parseInt();
        Serial.println(plBornM);
    }
    file.close();

    Serial.println("Wczytuje rok urodzenia...");
    file = SPIFFS.open("/plaBoY");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        plBornY = file.parseInt();
        Serial.println(plBornY);
    }
    file.close();


    Serial.println("Wczytuje dzien smierci...");
    file = SPIFFS.open("/plaDeD");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        plDeadD = file.parseInt();
        Serial.println(plDeadD);
    }
    file.close();

    Serial.println("Wczytuje miesiac smierci...");
    file = SPIFFS.open("/plaDeM");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        plDeadM = file.parseInt();
        Serial.println(plDeadM);
    }
    file.close();

    Serial.println("Wczytuje rok smierci..."); //pppppp
    file = SPIFFS.open("/plaDeY");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        plDeadY = file.parseInt();
        Serial.println(plDeadY);
    }
    file.close();




    Serial.println("Wczytuje poziom batonika...");
    file = SPIFFS.open("/plaBat");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        stBato = file.parseInt();
        Serial.println(stBato);
    }
    file.close();




    Serial.println("Wczytuje poziom zelu...");
    file = SPIFFS.open("/plaAnt");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        stAnty = file.parseInt();
        Serial.println(stAnty);
    }
    file.close();




    Serial.println("Wczytuje ubrania...");
    file = SPIFFS.open("/plaUbr");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        ekUbra[0] = int(file.read()) - 48;
        ekUbra[1] = int(file.read()) - 48;
        ekUbra[2] = int(file.read() - 48);
        ekUbra[3] = int(file.read() - 48);
        Serial.println(ekUbra[0]);
        Serial.println(ekUbra[1]);
        Serial.println(ekUbra[2]);
        Serial.println(ekUbra[3]);
    }
    file.close();




    Serial.println("Wczytuje przedmioty...");
    file = SPIFFS.open("/plaItm");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        ekItem[0] = int(file.read()) - 48;
        ekItem[1] = int(file.read()) - 48;
        ekItem[2] = int(file.read()) - 48;
        ekItem[3] = int(file.read()) - 48;
        Serial.println(ekItem[0]);
        Serial.println(ekItem[1]);
        Serial.println(ekItem[2]);
        Serial.println(ekItem[3]);
    }
    file.close();


    if (ekItem[2]) {
        ekItem[2] = 0;
        stBato = 10000;
    }
    if (ekItem[3]) {
        ekItem[3] = 0;
        stAnty = 10000;
    }



    Serial.println("Wczytuje jedzenie...");
    file = SPIFFS.open("/plaItj");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        ekJedz[0] = int(file.read()) - 48;
        ekJedz[1] = int(file.read()) - 48;
        ekJedz[2] = int(file.read()) - 48;
        ekJedz[3] = int(file.read()) - 48;
        Serial.println(ekJedz[0]);
        Serial.println(ekJedz[1]);
        Serial.println(ekJedz[2]);
        Serial.println(ekJedz[3]);
    }
    file.close();


    Serial.println("Wczytuje ustawienia...");
    file = SPIFFS.open("/devSet");
    if (!file || file.isDirectory()) {
        Serial.println("Brak pliku");
        return false;
    }
    Serial.println("Odczyt z pliku:");
    if (file.available()) {
        ustawienia[0] = int(file.read()) - 48;
        ustawienia[1] = int(file.read()) - 48;
        ustawienia[2] = int(file.read()) - 48;
        ustawienia[3] = int(file.read()) - 48;
        ustawienia[4] = int(file.read()) - 48;
        ustawienia[5] = int(file.read()) - 48;
        ustawienia[6] = int(file.read()) - 48;
        ustawienia[7] = int(file.read()) - 48;
        ustawienia[8] = int(file.read()) - 48;
        ustawienia[9] = int(file.read()) - 48;
    }
    Serial.println(ustawienia[0]);
    Serial.println(ustawienia[1]);
    Serial.println(ustawienia[2]);
    Serial.println(ustawienia[3]);
    Serial.println(ustawienia[4]);
    Serial.println(ustawienia[5]);
    Serial.println(ustawienia[6]);
    Serial.println(ustawienia[7]);
    Serial.println(ustawienia[8]);
    Serial.println(ustawienia[9]);
    file.close();
    return true;
}

// funkcja zapisu do pliku
void writeFile(fs::FS & fs, const char * path, const char * message) {
    Serial.printf("Zapis do pliku: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("- problem z otwarciem pliku");
        return;
    }
    if (file.print(message)) {
        Serial.println("- zapisano");
    } else {
        Serial.println("- problem z zapisem");
    }
    file.close();
}

// funkcja kasowania pliku
void deleteFile(fs::FS & fs, const char * path) {
    Serial.printf("Usuwanie: %s\r\n", path);
    if (fs.remove(path)) {
        Serial.println("- usunieto");
    } else {
        Serial.println("- niepowodzenie");
    }
}

// funkcja kasowania wszystkich plikow
void clrFiles() {
    deleteFile(SPIFFS, "/creSta");
    deleteFile(SPIFFS, "/plaNam");
    deleteFile(SPIFFS, "/plaPle");
    deleteFile(SPIFFS, "/plaBoD");
    deleteFile(SPIFFS, "/plaBoM");
    deleteFile(SPIFFS, "/plaBoY");
    deleteFile(SPIFFS, "/plaDeD");
    deleteFile(SPIFFS, "/plaDeM");
    deleteFile(SPIFFS, "/plaDeY");
    deleteFile(SPIFFS, "/plaZdr");
    deleteFile(SPIFFS, "/plaJed");
    deleteFile(SPIFFS, "/plaHig");
    deleteFile(SPIFFS, "/plaZab");
    deleteFile(SPIFFS, "/plaDys");
    deleteFile(SPIFFS, "/plaKas");
    deleteFile(SPIFFS, "/plaBat");
    deleteFile(SPIFFS, "/plaAnt");
    deleteFile(SPIFFS, "/plaUbr");
    deleteFile(SPIFFS, "/plaItm");
    deleteFile(SPIFFS, "/plaJed");
    deleteFile(SPIFFS, "/devSet");
    deleteFile(SPIFFS, "/modSta");
    deleteFile(SPIFFS, "/typOka");
    deleteFile(SPIFFS, "/netFlg");
}


// funkcja zapisu wszystkich statystyk i ustawien do plikow
void zapiszStaty() {
    Serial.println("zapisuje staty");

    String tmpVal = String(stZdro); // zdrowie
    writeFile(SPIFFS, "/plaZdr", tmpVal.c_str());

    tmpVal = String(stJedz); // jedzenie
    writeFile(SPIFFS, "/plaJed",  tmpVal.c_str());

    tmpVal = String(stHigi); // higiena
    writeFile(SPIFFS, "/plaHig",  tmpVal.c_str());

    tmpVal = String(stZaba); // zabawa
    writeFile(SPIFFS, "/plaZab",  tmpVal.c_str());

    tmpVal = String(stDysc); // dyscypl
    writeFile(SPIFFS, "/plaDys",  tmpVal.c_str());

    tmpVal = String(stBato); // baton
    writeFile(SPIFFS, "/plaBat",  tmpVal.c_str());

    tmpVal = String(stAnty); // zel
    writeFile(SPIFFS, "/plaAnt",  tmpVal.c_str());


    tmpVal = String(stKasa); // pieniadze
    writeFile(SPIFFS, "/plaKas", tmpVal.c_str());

    // ubrania
    tmpVal = String(ekUbra[0]) + String(ekUbra[1]) + String(ekUbra[2]) + String(ekUbra[3]);
    writeFile(SPIFFS, "/plaUbr", tmpVal.c_str());

    // uzywanie batonika i zelu (zerowanie ich ilosci w ekwipunku)
    if (ekItem[2]) {
        ekItem[2] = 0;
        stBato = 10000;
    }
    if (ekItem[3]) {
        ekItem[3] = 0;
        stAnty = 10000;
    }

    // posiadane przedmioty
    tmpVal = String(ekItem[0]) + String(ekItem[1]) + String(ekItem[2]) + String(ekItem[3]);
    writeFile(SPIFFS, "/plaItm", tmpVal.c_str());

    // posiadane jedzenie
    tmpVal = String(ekJedz[0]) + String(ekJedz[1]) + String(ekJedz[2]) + String(ekJedz[3]);
    writeFile(SPIFFS, "/plaItj", tmpVal.c_str());

    // zapis ustawien
    tmpVal = String(ustawienia[0]) + String(ustawienia[1]) + String(ustawienia[2]) + String(ustawienia[3]) + String(ustawienia[4]) + String(ustawienia[5]) + String(ustawienia[6]) + String(ustawienia[7]) + String(ustawienia[8]) + String(ustawienia[9]);
    writeFile(SPIFFS, "/devSet", tmpVal.c_str());
    Serial.println("zapisano");
    ekrOds = 1;

    int tmpTSH = rtc.getHour(true) * 12;
    int tmpTSM = rtc.getMinute() / 5;
    int timeStamp = tmpTSH + tmpTSM;
    String timeSTStr = String(timeStamp);   // utworzenie nowego timestampu
    writeFile(SPIFFS, "/modSta", timeSTStr.c_str());  // zapis nowego timestampu
    Serial.println(timeSTStr);
}

// funkcja obnizajaca statystyki
void obnizStaty(int ileRazy) {
    if (ileRazy < 24) {     // jezeli minelo wiecej niz 24*5 minut (2h) to nie obnizaj statow
        while (ileRazy > 0) {
            Serial.println("obnizam staty");
            ileRazy--;
            // kazda statystyka jest zabezpieczona przed osiagnieciem wartosci ujemnych
            if (ekItem[0]) {                    // jezeli ma rybke
                if (stZdro > (stZdrObn / 2)) {
                    stZdro -= (stZdrObn / 2);
                } else {
                    stZdro = 0;
                    if (flagaSnu) stZdro = stZdrMin;
                }
            } else {                            // jezeli nie ma rybki
                if (stZdro > stZdrObn) {
                    stZdro -= stZdrObn;
                } else {
                    stZdro = 0;
                    if (flagaSnu) stZdro = stZdrMin;
                }
            }
            if (stBato) {                        // jezeli dziala batonik
                if (stJedz > (stJedObn / 2)) {
                    stJedz -= (stJedObn / 2);
                } else {
                    stJedz = 0;
                    if (flagaSnu) stJedz = stJedMin;
                }
            } else {                            // jezeli nie dziala batonik
                if (stJedz > stJedObn) {
                    stJedz -= stJedObn;
                } else {
                    stJedz = 0;
                    if (flagaSnu) stJedz = stJedMin;
                }
            }
            if (stAnty) {                        // jezeli dziala zel
                if (stHigi > (stHigObn / 2)) {
                    stHigi -= (stHigObn / 2);
                } else {
                    stHigi = 0;
                    if (flagaSnu) stHigi = stHigMin;
                }
            } else {                            // jezeli nie dziala zel
                if (stHigi > stHigObn) {
                    stHigi -= stHigObn;
                } else {
                    stHigi = 0;
                    if (flagaSnu) stHigi = stHigMin;
                }
            }



            if (stZaba > stZabObn) {            // obnizanie zabawy
                stZaba -= stZabObn;
            } else {
                stZaba = 0;
                if (flagaSnu) stZaba = stZabMin;
            }

            if (stDysc > stDysObn) {            // obnizanie dyscypliny
                stDysc -= stDysObn;
            } else {
                stDysc = 0;
                if (flagaSnu) stDysc = stDysMin;
            }
            if (stBato > stBatObn) {            // obnizanie batonika
                stBato -= stBatObn;
            } else {
                stBato = 0;
            }
            if (stAnty > stZelObn) {            // obnizanie zelu
                stAnty -= stZelObn;
            } else {
                stAnty = 0;
            }
        }
    }
    
    zapiszStaty();  // funkcja zapisywania statow do pliku
    Serial.println("obnizono...");
}

void leczenie() {   // leczenie
    stZdro += stZdrDod; // zwieksz zdrowie
    if (stZdro > 10000) stZdro = 10000;
    zapiszStaty();
    keyx = 1;
    ekrOds = 1;
}

void wyczysc() {    // czyszczenie
    stHigi += stHigDod; // zwieksz higiene
    if (stHigi > 10000) stHigi = 10000;
    zapiszStaty();
    keyx = 1;
    ekrOds = 1;
}

void dyscyplina() {    // dyscyplinowanie
    stDysc += stDysDod; // zwieksz dyscypline
    if (stDysc > 10000) stDysc = 10000;
    zapiszStaty();
    keyx = 1;
    ekrOds = 1;

}

// zwieksz najedzenie/zdrowie/zabawe w zaleznosci od posilku (zakladka varKonf.h)
void jedzJedzenie(byte jedzenie) {
    ekJedz[jedzenie]--;
    if (jedzenie == 0) {
        stJedz += stJDodChl;
    }
    if (jedzenie == 1) {
        stJedz += stJDodSal;
    }
    if (jedzenie == 2) {
        stJedz += stJDodCze;
        stZdro -= 500;
        stZaba += 500;
    }
    if (jedzenie == 3) {
        stJedz += stJDodKar;
        stZdro -= 500;
        stZaba += 500;
    }
    if (stJedz > 10000) stJedz = 10000; // zabezpieczenie przed przekręceniem
    zapiszStaty();
}
