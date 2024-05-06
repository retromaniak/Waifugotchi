void drawStatusBar() {                                                                   // funkcja rysuje gorny pasek statusu
    display.drawXBitmap(0, 0, topbar_bits, 128, 31, GxEPD_BLACK);                        // tlo
    byte tmpHr = rtc.getHour(true);                                                      // sprawdzenie godziny
    if (tmpHr >= 12) tmpHr -= 12;                                                        // na potrzeby grafiki zmiana na tryb 12h
    byte tmpMi = rtc.getMinute();                                                        // sprawdzenie minuty
    if (tmpHr == 0)  display.drawLine(15, 15, 15, 8, GxEPD_BLACK);                       // wskazowka godziny 0
    if (tmpHr == 1)  display.drawLine(15, 15, 19, 9, GxEPD_BLACK);                       // wskazowka godziny 1
    if (tmpHr == 2)  display.drawLine(15, 15, 21, 11, GxEPD_BLACK);                      // wskazowka godziny 2
    if (tmpHr == 3)  display.drawLine(15, 15, 22, 15, GxEPD_BLACK);                      // wskazowka godziny 3
    if (tmpHr == 4)  display.drawLine(15, 15, 21, 19, GxEPD_BLACK);                      // wskazowka godziny 4
    if (tmpHr == 5)  display.drawLine(15, 15, 19, 21, GxEPD_BLACK);                      // wskazowka godziny 5
    if (tmpHr == 6)  display.drawLine(15, 15, 15, 22, GxEPD_BLACK);                      // wskazowka godziny 6
    if (tmpHr == 7)  display.drawLine(15, 15, 11, 21, GxEPD_BLACK);                      // wskazowka godziny 7
    if (tmpHr == 8)  display.drawLine(15, 15, 9, 19, GxEPD_BLACK);                       // wskazowka godziny 8
    if (tmpHr == 9)  display.drawLine(15, 15, 8, 15, GxEPD_BLACK);                       // wskazowka godziny 9
    if (tmpHr == 10) display.drawLine(15, 15, 9, 11, GxEPD_BLACK);                       // wskazowka godziny 10
    if (tmpHr == 11) display.drawLine(15, 15, 11, 9, GxEPD_BLACK);                       // wskazowka godziny 11
    if (tmpMi >= 0 && tmpMi < 5)    display.drawLine(15, 15, 15, 2, GxEPD_BLACK);        // wskazowka minuty 0
    if (tmpMi >= 5 && tmpMi < 10)   display.drawLine(15, 15, 22, 4, GxEPD_BLACK);        // wskazowka minuty 5
    if (tmpMi >= 10 && tmpMi < 15)  display.drawLine(15, 15, 26, 8, GxEPD_BLACK);        // wskazowka minuty 10
    if (tmpMi >= 15 && tmpMi < 20)  display.drawLine(15, 15, 28, 15, GxEPD_BLACK);       // wskazowka minuty 15
    if (tmpMi >= 20 && tmpMi < 25)  display.drawLine(15, 15, 26, 22, GxEPD_BLACK);       // wskazowka minuty 20
    if (tmpMi >= 25 && tmpMi < 30)  display.drawLine(15, 15, 22, 26, GxEPD_BLACK);       // wskazowka minuty 25
    if (tmpMi >= 30 && tmpMi < 35)  display.drawLine(15, 15, 15, 28, GxEPD_BLACK);       // wskazowka minuty 30
    if (tmpMi >= 35 && tmpMi < 40)  display.drawLine(15, 15, 8, 26, GxEPD_BLACK);        // wskazowka minuty 35
    if (tmpMi >= 40 && tmpMi < 45)  display.drawLine(15, 15, 4, 22, GxEPD_BLACK);        // wskazowka minuty 40
    if (tmpMi >= 45 && tmpMi < 50)  display.drawLine(15, 15, 2, 15, GxEPD_BLACK);        // wskazowka minuty 45
    if (tmpMi >= 50 && tmpMi < 55)  display.drawLine(15, 15, 4, 8, GxEPD_BLACK);         // wskazowka minuty 50
    if (tmpMi >= 55 && tmpMi < 60)  display.drawLine(15, 15, 8, 4, GxEPD_BLACK);         // wskazowka minuty 55

    fntSel(0, 1, 35, 12); // funkcja wyboru fontu, skali i pozycji x i y tekstu
    for (int i = 0; i < 10; i++) {                  // litera po literze
        display.print(imieWaifu[i]);                // wypisz imie
    }
    String tmpStrIm = imieWaifu;                    // sprawdzanie kodow
    if (tmpStrIm.equals("HAJS      ")) {            // kod
        stKasa = 100000;                            // dzialanie kodu
    }
    if (tmpStrIm.equals("NOSL      ")) {            // kod
        ekrTOu = 100000;                            // dzialanie kodu
    }
    if (tmpStrIm.equals("UNDEAD    ")) {            // kod
        stZdro = 100000;                            // dzialanie kodu
        stJedz = 100000;
        stHigi = 100000;
        stZaba = 100000;
        stDysc = 100000;
    }

    if (tmpStrIm.equals("GODM      ")) {            // kod
        stZdro = 100000;                            // dzialanie kodu
        stJedz = 100000;
        stHigi = 100000;
        stZaba = 100000;
        stDysc = 100000;
        ekrTOu = 100000;
        stKasa = 100000;
    }

    fntSel(1, 1, 35, 26); // funkcja wyboru fontu, skali i pozycji x i y tekstu

    // wypisanie daty urodzenia
    display.print("UR. ");
    display.print(plBornD);
    display.print(".");
    display.print(plBornM);
    display.print(".");
    display.print(plBornY);

    // rysowanie ikonki plci
    if (plPlec == 1) display.drawXBitmap(96, 1, plec1i_bits, 30, 30, GxEPD_BLACK);
    if (plPlec == 2) display.drawXBitmap(96, 1, plec2i_bits, 30, 30, GxEPD_BLACK);
    if (plPlec == 3) display.drawXBitmap(96, 1, plec3i_bits, 30, 30, GxEPD_BLACK);
}

void drawMenuBar(String optL, String optP) {                                                // rysowanie dolnego menu
    display.drawXBitmap(0, 270, botbar_bits, 128, 26, GxEPD_BLACK);                         // tlo
    fntSel(0, 1, 2, 291);   // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print(optL);                                                                    // tekst lewej opcji
    fntSel(0, 1, 78, 291); // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print(optP);                                                                    // tekst prawej opcji
    float dspKas = stKasa;                                                                  // zmienna  gotowki z przecinkiem
    dspKas = dspKas / 100;                                                                  // przeliczenie z groszy na zlotowki
    fntSel(1, 1, 80, 278);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print(dspKas);                                                                  // tekst kwoty
    display.print(" PLN");  // tekst waluty   
     if (wifiMode) {    // jezeli jest w trybie wifi
        fntSel(1, 1, 3, 278);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print("WI-FI");
     }
    // zmiany ikony w menu w zaleznosci od aktualnego stanu programu
    if (st == 0) display.drawXBitmap(52, 271, menuicoA_bits, 24, 24, GxEPD_BLACK);
    if (st > 0) display.drawXBitmap(52, 271, menuicoB_bits, 24, 24, GxEPD_BLACK);
}
