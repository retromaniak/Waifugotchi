
void minSleep() {               // uspienie na 5 minut
    display.hibernate();                        // uspij ekran
    esp_sleep_enable_timer_wakeup(300000000);   // timer wybudzenia
    esp_deep_sleep_start();                     // rozpocznij
}

void micSleep() {               // uspienie na 5 minut
    display.hibernate();                        // uspij ekran
    esp_sleep_enable_timer_wakeup(1000000);   // timer wybudzenia
    esp_deep_sleep_start();                     // rozpocznij
}


byte preWake(bool sRst) {       // funkcja przed pelnym wybudzeniem
    byte ret = 0;               // flaga resetowania zasilania
    Serial.println("Sprawdzam kiedy ostatnio modyfikowano statystyki");
    File file = SPIFFS.open("/modSta");     // otwieram plik
    if (!file || file.isDirectory()) {      // jezeli plik nie istnieje lub jest katalogiem
        Serial.println("Brak danych");
    }
    Serial.println("Odczyt z pliku:");
    int odczytTS = 0;                       // zmienna do odczytu timestamp
    if (file.available()) {                 // jezeli plik dostepny
        odczytTS = file.parseInt();         // odczytaj zmienna int
        file.close();                       // zamknij plik
    }
    Serial.println(odczytTS);

    // wylicz timestamp dla aktualnej godziny
    int tmpTSH = rtc.getHour(true) * 12;
    int tmpTSM = rtc.getMinute() / 5;
    int timeStamp = tmpTSH + tmpTSM;
    Serial.println(timeStamp);


    while (timeStamp < odczytTS) timeStamp += 288; // przy zmianie z 23:55 na 0:00

    if (timeStamp > odczytTS) { // jezeli inny timestamp
        obnizStaty(timeStamp - odczytTS); // obnizanie statow tyle razy ile minelo przedzialow 5 minutowych
        Serial.println("obnizono");
    }



    // SPRAWDZ KIEDY OSTATNIO OBNIZONO STATYSTYKI
    //   ODCZYT PLIKU statMod
    //   PORÓWNANIE CZASU Z PLIKU Z CZASEM AKTUALNYM
    // JEZELI MINELO WIECEJ NIZ 5 MINUT OD OSTATNIEGO OBNIZENIA
    // OBNIZ STATYSTYKI

    if (sRst) {
        ret = 1;              // to jest reset zasilania, wykonaj pelne wybudzenie
    }
    return ret;               // zwrot z funkcji - info o tym czy jest to reset zasilania
}


void fullWake(bool sRst, bool hRst) {       // wykonuje pełne wybudzenie (wraz z ekranem)
    display.init(115200, true, 50, false);    // inicjalizacja ekranu
    display.setRotation(0);                   // orientacja ekranu
    display.setFullWindow();                  // pierwsza klatka musi byc pelna
    display.setTextColor(GxEPD_BLACK);        // kolor tekstu
    keyx = 1;                                 // zmienna odpowiedzialna za dowolny klawisz, wymusza odswiezenie ekranu
    if (sRst) ustGodzine();                   // jezeli jest to reset zasilania - ustaw godzine i date

    if (!jestPostac()) ustPostac();           // jezeli nie ma postaci - pokaz tworzenie postaci
    if (jestPostac() == 1) {                  // jezeli postac nie zyje
        isDead = true;
    }
    rStanPostac();                            // odczytaj stan postaci
    byte chkHr = rtc.getHour(true);           // sprawdz godzine
    if (ekItem[1] == 1) {                     // jezeli gracz ma lampke
        if ((chkHr < 7) || (chkHr >= (slpHr + 1))) { // jest noc, nie wybudzaj urzadzenia
            display.firstPage();                // rozpocznij rysowanie
            display.fillScreen(GxEPD_WHITE);    // wypelnij ekran na bialo
            display.drawXBitmap(0, 0, zzz_bits, 128, 296, GxEPD_BLACK); // rysuj grafike snu
            display.nextPage();                 // wyslij bufor na ekran
            flagaSnu = true;                    // ustawienie flagi
            Serial.println("Jest noc");
            // dobranoc
        }
    } else {                     // jezeli gracz nie ma lampki
        if ((chkHr < 7) || (chkHr >= (slpHr))) {  // jest noc, nie wybudzaj urzadzenia
            display.firstPage();                // rozpocznij rysowanie
            display.fillScreen(GxEPD_WHITE);    // wypelnij ekran na bialo
            display.drawXBitmap(0, 0, zzz_bits, 128, 296, GxEPD_BLACK); // rysuj grafike snu
            display.nextPage();                 // wyslij bufor na ekran
            flagaSnu = true;                    // ustawienie flagi
            Serial.println("Jest noc");
            // dobranoc
        }
    }
}

void print_wakeup_reason() {      // sprawdzanie przyczyny wybudzenia z uspienia
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason) {        // w zaleznosci od przyczyny wybudzenia przedluzam timeout ekranu lub wymuszam ustawienie daty i godziny
        case ESP_SLEEP_WAKEUP_EXT0 : {
                Serial.println("Wybudzenie RTC_IO");
                softReset = 0;
                ekrTOu = millis() + 60000;
                break;
            }
        case ESP_SLEEP_WAKEUP_EXT1 : {
                Serial.println("Wybudzenie RTC_CNTL");
                softReset = 0;
                break;
            }
        case ESP_SLEEP_WAKEUP_TIMER : {
                Serial.println("Wybudzenie po czasie");
                softReset = 0;
                break;
            }
        case ESP_SLEEP_WAKEUP_TOUCHPAD : {
                Serial.println("Wybudzenie dotykiem");
                softReset = 0;
                break;
            }
        case ESP_SLEEP_WAKEUP_ULP : {
                Serial.println("Wybudzenie przez ULP");
                softReset = 1;
                break;
            }
        default : {
                Serial.printf("Wybudzenie bez zwiazku z deep sleep: %d\n", wakeup_reason);

                ekrTOu = millis() + 60000;
                softReset = 1;

                break;
            }
    }
}

void callback() {
    // placeholder dla wybudzania
}
