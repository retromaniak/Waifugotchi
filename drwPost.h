byte frame = 0;                     // klatka animacji
byte humor = 1;                     // wariant humoru
byte mruga = 1;                     // etap mrugania
byte patrzy = 0;                    // kierunek patrzenia


void calcStats() {          // licz statystyki

    if (ekItem[2]) {                // jezeli posiada batonik
        ekItem[2] = 0;                  // zjedz go
        stBato = 10000;                 // dodaj statystyke batonika
    }
    if (ekItem[3]) {                // jezeli posiada zel antyb.
        ekItem[3] = 0;                  // uzyj go
        stAnty = 10000;                 // dodaj statystyke zelu
    }

    // licz sume wszystkich statystyk
    sumaStat = stZdro + stJedz + stZaba + stHigi + stDysc;
    if (sumaStat < stProgSm) {
        writeFile(SPIFFS, "/creSta", "1");      // postac umiera
        String tmpSt = String(rtc.getDay());
        plDeadD = rtc.getDay();
        writeFile(SPIFFS, "/plaDeD", tmpSt.c_str());
        Serial.println(tmpSt);
        tmpSt = String(rtc.getMonth() + 1);
        plDeadM = rtc.getMonth() + 1;
        writeFile(SPIFFS, "/plaDeM", tmpSt.c_str());
        Serial.println(tmpSt);
        tmpSt = String(rtc.getYear());
        writeFile(SPIFFS, "/plaDeY", tmpSt.c_str());
        Serial.println(tmpSt);
        plDeadY = rtc.getYear();
        isDead = true;
    }

    if (stDysc <= stDysAla) {       // jezeli dyscyplina jest ponizej poziomu alarmowego
        alertDysc = true;               // wlacz alert
    } else {                        // jezeli dyscyplina nie jest ponizej poziomu alarmowego
        alertDysc = false;              // wylacz alert
        stZdrAla =  stZdrAlaC;          // przywroc oryginalne wartosci alertow
        stJedAla =  stJedAlaC;          // przywroc oryginalne wartosci alertow
        stHigAla =  stHigAlaC;          // przywroc oryginalne wartosci alertow
        stZabAla =  stZabAlaC;          // przywroc oryginalne wartosci alertow
        stDysAla =  stDysAlaC;          // przywroc oryginalne wartosci alertow
    }
    if (stZdro <= stZdrAla) {       // sprawdzenie czy osiagnieto stan alarmowy
        alertZdro = true;               // wlacz alert
    } else {
        alertZdro = false;              // wylacz alert
    }
    if (stJedz <= stJedAla) {       // sprawdzenie czy osiagnieto stan alarmowy
        alertJedz = true;               // wlacz alert
    } else {
        alertJedz = false;              // wylacz alert
    }
    if (stZaba <= stZabAla) {       // sprawdzenie czy osiagnieto stan alarmowy
        alertZaba = true;               // wlacz alert
    } else {
        alertZaba = false;              // wylacz alert
    }
    if (stHigi <= stHigAla) {       // sprawdzenie czy osiagnieto stan alarmowy
        alertHigi = true;               // wlacz alert
    } else {
        alertHigi = false;              // wylacz alert
    }
}

void drawWaifu(byte etapGry) {          // rysuj waifu
    frame++;                            // zwieksz klatke animacji ust
    if (frame == 3) frame = 0;          // zabezpieczenie przed przekreceniem

    // rysowanie glowy w zaleznosci od plci
    if (plPlec == 1) display.drawXBitmap(0, 32, glowa1_bits, 128, 128, GxEPD_BLACK);
    if (plPlec == 2) display.drawXBitmap(0, 32, glowa2_bits, 128, 128, GxEPD_BLACK);
    if (plPlec == 3) display.drawXBitmap(0, 32, glowa3_bits, 128, 128, GxEPD_BLACK);

    // rysowanie torsu w zaleznosci od posiadanego ubrania
    if (ekUbra[0] == 1) display.drawXBitmap(0, 160, tors11_bits, 128, 110, GxEPD_BLACK);
    if (ekUbra[1] == 1)  display.drawXBitmap(0, 160, tors21_bits, 128, 110, GxEPD_BLACK);
    if (ekUbra[2] == 1) display.drawXBitmap(0, 160, tors31_bits, 128, 110, GxEPD_BLACK);
    if (ekUbra[3] == 1) display.drawXBitmap(0, 160, tors41_bits, 128, 110, GxEPD_BLACK);

    // rysowanie ust
    if (plPlec == 1) {
        if ( sumaStat <= stSad) {               // smutne
            if (frame == 0) display.drawXBitmap(48, 135, usta111_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta112_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta113_bits, 32, 8, GxEPD_BLACK);
        } else if (sumaStat >= stHappy) {       // wesole
            if (frame == 0) display.drawXBitmap(48, 135, usta131_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta132_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta133_bits, 32, 8, GxEPD_BLACK);
        } else {                                // neutralne
            if (frame == 0) display.drawXBitmap(48, 135, usta121_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta122_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta123_bits, 32, 8, GxEPD_BLACK);
        }
    }
    if (plPlec == 2) {
        if ( sumaStat <= stSad) {               // smutne
            if (frame == 0) display.drawXBitmap(48, 135, usta211_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta212_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta213_bits, 32, 8, GxEPD_BLACK);
        } else if (sumaStat >= stHappy) {       // wesole
            if (frame == 0) display.drawXBitmap(48, 135, usta231_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta232_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta233_bits, 32, 8, GxEPD_BLACK);
        } else {                                // neutralne
            if (frame == 0) display.drawXBitmap(48, 135, usta221_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta222_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta223_bits, 32, 8, GxEPD_BLACK);
        }
    }
    if (plPlec == 3) {
        if ( sumaStat <= stSad) {               // smutne
            if (frame == 0) display.drawXBitmap(48, 135, usta311_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta312_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta313_bits, 32, 8, GxEPD_BLACK);
        } else if (sumaStat >= stHappy) {       // wesole
            if (frame == 0) display.drawXBitmap(48, 135, usta331_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta332_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta333_bits, 32, 8, GxEPD_BLACK);
        } else {                                // neutralne
            if (frame == 0) display.drawXBitmap(48, 135, usta321_bits, 32, 8, GxEPD_BLACK);
            if (frame == 1) display.drawXBitmap(48, 135, usta322_bits, 32, 8, GxEPD_BLACK);
            if (frame == 2) display.drawXBitmap(48, 135, usta323_bits, 32, 8, GxEPD_BLACK);
        }
    }



    if (st == 0) {
        if (ekrTOu > 3000) {        // jezeli jest wiecej niz 3 sekundy do wygaszenia ekranu
            if (random(10) == 5) {      // losowanie wyzwalania mrugania oczami
                mruga = 1;              // wyzwalanie mrugania oczami
            }
            byte losuj = random(15);    // losowanie kierunku patrzenia
            if (losuj == 13) {
                patrzy = 2;             // prawo
            } else if (losuj == 14) {
                patrzy = 1;             // lewo
            } else {
                patrzy = 0;             // prosto
            }
        } else {                    // jezeli jest mniej niz 3 sekundy do wygaszenia ekranu
            mruga = 0;                  // nie mrugaj
            patrzy = 0;                 // patrz prosto
        }
    }

    if (etapGry) mruga = 0;             // jezeli trwa gra to nie mrugraj




    // PONIZEJ ZNAJDUJE SIE DUZA SEKCJA RYSOWANIA OCZU (L i P), UZWGLEDNIAJACA ZMIENNE:
    // mruga - aktualny moment mrugania oczami
    // plPlec - plec postaci
    // typOka - wylosowany typ/styl oka
    // etapGry - etap gry (dotyczy gry z patrzeniem)
    // patrzy - kierunek patrzenia

    if (mruga == 0) {
        if (plPlec == 1) {
            if (typOka == 1) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL111_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP111_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL121_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP121_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL131_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP131_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL111_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP111_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL121_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP121_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL131_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP131_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 2) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL112_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP112_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL122_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP122_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL132_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP132_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL112_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP112_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL122_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP122_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL132_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP132_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 3) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL113_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP113_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL123_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP123_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL133_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP133_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL113_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP113_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL123_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP123_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL133_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP133_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 4) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL114_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP114_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL124_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP124_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL134_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP134_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL114_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP114_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL124_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP124_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL134_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP134_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 5) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL115_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP115_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL125_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP125_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL135_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP135_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL115_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP115_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL125_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP125_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL135_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP135_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }

        }
        if (plPlec == 2) {
            if (typOka == 1) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL211_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP211_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL221_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP221_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL231_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP231_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL211_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP211_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL221_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP221_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL231_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP231_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 2) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL212_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP212_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL222_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP222_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL232_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP232_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL212_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP212_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL222_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP222_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL232_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP232_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 3) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL213_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP213_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL223_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP223_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL233_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP233_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL213_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP213_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL223_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP223_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL233_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP233_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 4) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL214_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP214_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL224_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP224_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL234_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP234_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL214_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP214_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL224_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP224_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL234_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP234_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 5) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL215_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP215_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL225_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP225_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL235_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP235_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            } else {
                if (etapGry == 1) {
                    display.drawXBitmap(26, 94, okoL215_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP215_bits, 32, 32, GxEPD_BLACK);
                }
                if (etapGry == 2) {
                    display.drawXBitmap(26, 94, okoL225_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP225_bits, 32, 32, GxEPD_BLACK);
                }
                if (etapGry == 3) {
                    display.drawXBitmap(26, 94, okoL235_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP235_bits, 32, 32, GxEPD_BLACK);
                }
            }

        }
        if (plPlec == 3) {

            if (typOka == 1) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL311_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP311_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL321_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP321_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL331_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP331_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL311_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP311_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL321_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP321_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL331_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP331_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 2) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL312_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP312_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL322_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP322_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL332_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP332_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL312_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP312_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL322_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP322_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL332_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP332_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 3) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL313_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP313_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL323_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP323_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL333_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP333_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL313_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP313_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL323_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP323_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL333_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP333_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 4) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL314_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP314_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL324_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP324_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL334_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP334_bits, 32, 32, GxEPD_BLACK);
                    }
                } else {
                    if (etapGry == 1) {
                        display.drawXBitmap(26, 94, okoL314_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP314_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 2) {
                        display.drawXBitmap(26, 94, okoL324_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP324_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (etapGry == 3) {
                        display.drawXBitmap(26, 94, okoL334_bits, 32, 32, GxEPD_BLACK);
                        display.drawXBitmap(70, 94, okoP334_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            }
            if (typOka == 5) {
                if (!etapGry) {
                    if (patrzy == 0) {
                        if (patrzy == 0) display.drawXBitmap(26, 94, okoL315_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 0) display.drawXBitmap(70, 94, okoP315_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 1) {
                        if (patrzy == 1) display.drawXBitmap(26, 94, okoL325_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 1) display.drawXBitmap(70, 94, okoP325_bits, 32, 32, GxEPD_BLACK);
                    }
                    if (patrzy == 2) {
                        if (patrzy == 2) display.drawXBitmap(26, 94, okoL335_bits, 32, 32, GxEPD_BLACK);
                        if (patrzy == 2) display.drawXBitmap(70, 94, okoP335_bits, 32, 32, GxEPD_BLACK);
                    }
                }
            } else {
                if (etapGry == 1) {
                    display.drawXBitmap(26, 94, okoL315_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP315_bits, 32, 32, GxEPD_BLACK);
                }
                if (etapGry == 2) {
                    display.drawXBitmap(26, 94, okoL325_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP325_bits, 32, 32, GxEPD_BLACK);
                }
                if (etapGry == 3) {
                    display.drawXBitmap(26, 94, okoL335_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP335_bits, 32, 32, GxEPD_BLACK);
                }
            }
        }
    }
    if (mruga > 0) {
        if ((mruga == 1) || (mruga == 3)) {

            if (plPlec == 1) {
                if (typOka == 1) {
                    display.drawXBitmap(26, 94, okoL141_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP141_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 2) {
                    display.drawXBitmap(26, 94, okoL142_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP142_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 3) {
                    display.drawXBitmap(26, 94, okoL143_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP143_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 4) {
                    display.drawXBitmap(26, 94, okoL144_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP144_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 5) {
                    display.drawXBitmap(26, 94, okoL145_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP145_bits, 32, 32, GxEPD_BLACK);
                }
            }
            if (plPlec == 2) {
                if (typOka == 1) {
                    display.drawXBitmap(26, 94, okoL241_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP241_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 2) {
                    display.drawXBitmap(26, 94, okoL242_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP242_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 3) {
                    display.drawXBitmap(26, 94, okoL243_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP243_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 4) {
                    display.drawXBitmap(26, 94, okoL244_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP244_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 5) {
                    display.drawXBitmap(26, 94, okoL245_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP245_bits, 32, 32, GxEPD_BLACK);
                }
            }
            if (plPlec == 3) {
                if (typOka == 1) {
                    display.drawXBitmap(26, 94, okoL341_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP341_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 2) {
                    display.drawXBitmap(26, 94, okoL342_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP342_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 3) {
                    display.drawXBitmap(26, 94, okoL343_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP343_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 4) {
                    display.drawXBitmap(26, 94, okoL344_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP344_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 5) {
                    display.drawXBitmap(26, 94, okoL345_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP345_bits, 32, 32, GxEPD_BLACK);
                }
            }
        }
        if (mruga == 2) {

            if (plPlec == 1) {
                if (typOka == 1) {
                    display.drawXBitmap(26, 94, okoL151_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP151_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 2) {
                    display.drawXBitmap(26, 94, okoL152_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP152_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 3) {
                    display.drawXBitmap(26, 94, okoL153_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP153_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 4) {
                    display.drawXBitmap(26, 94, okoL154_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP154_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 5) {
                    display.drawXBitmap(26, 94, okoL155_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP155_bits, 32, 32, GxEPD_BLACK);
                }
            }
            if (plPlec == 2) {
                if (typOka == 1) {
                    display.drawXBitmap(26, 94, okoL251_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP251_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 2) {
                    display.drawXBitmap(26, 94, okoL252_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP252_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 3) {
                    display.drawXBitmap(26, 94, okoL253_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP253_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 4) {
                    display.drawXBitmap(26, 94, okoL254_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP254_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 5) {
                    display.drawXBitmap(26, 94, okoL255_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP255_bits, 32, 32, GxEPD_BLACK);
                }
            }
            if (plPlec == 3) {
                if (typOka == 1) {
                    display.drawXBitmap(26, 94, okoL351_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP351_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 2) {
                    display.drawXBitmap(26, 94, okoL352_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP352_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 3) {
                    display.drawXBitmap(26, 94, okoL353_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP353_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 4) {
                    display.drawXBitmap(26, 94, okoL354_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP354_bits, 32, 32, GxEPD_BLACK);
                }
                if (typOka == 5) {
                    display.drawXBitmap(26, 94, okoL355_bits, 32, 32, GxEPD_BLACK);
                    display.drawXBitmap(70, 94, okoP355_bits, 32, 32, GxEPD_BLACK);
                }
            }
        }

        mruga++;                    // zwieksz klatke mrugania
        if (mruga == 4) mruga = 0;  // zabezpiecz przed przekreceniem
    }

}

void drawIcons() {          // rysuj ikony ostrzezen
    if (alertZdro) {            // czy istnieje alert
        display.fillRect(14, 243, 16, 24, GxEPD_WHITE);  // biale tlo
        display.drawXBitmap(14, 243, icoA_bits, 16, 24, GxEPD_BLACK); // ikona choroby
    }
    if (alertJedz) {            // czy istnieje alert
        display.fillRect(35, 243, 16, 24, GxEPD_WHITE);  // biale tlo
        display.drawXBitmap(35, 243, icoB_bits, 16, 24, GxEPD_BLACK); // ikona glodu
    }
    if (alertHigi) {            // czy istnieje alert
        display.fillRect(56, 243, 16, 24, GxEPD_WHITE);  // biale tlo
        display.drawXBitmap(56, 243, icoC_bits, 16, 24, GxEPD_BLACK); // ikona brudu
    }
    if (alertZaba) {            // czy istnieje alert
        display.fillRect(77, 243, 16, 24, GxEPD_WHITE);  // biale tlo
        display.drawXBitmap(77, 243, icoD_bits, 16, 24, GxEPD_BLACK); // ikona nudy
    }
    if (alertDysc) {            // czy istnieje alert
        display.fillRect(98, 243, 16, 24, GxEPD_WHITE);  // biale tlo
        display.drawXBitmap(98, 243, icoE_bits, 16, 24, GxEPD_BLACK); // ikona braku dysc
    }
    if (stAnty) {
        display.fillRect(100, 35, 12, 12, GxEPD_WHITE);  // biale tlo
        display.drawXBitmap(100, 35, icoZel_bits, 12, 12, GxEPD_BLACK); // ikona zelu
    }
    if (stBato) {
        display.fillRect(114, 35, 12, 12, GxEPD_WHITE);  // biale tlo
        display.drawXBitmap(114, 35, icoBat_bits, 12, 12, GxEPD_BLACK); // ikona batona
    }
}



void drawMenu(byte menuSel) {   // rysuj menu glowne
    display.fillRect(0, 32, 128, 264, GxEPD_WHITE); // biale tlo

    fntSel(1, 2, 15, 60);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 1) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("NAKARM");  // tekst opcji
    fntSel(1, 2, 15, 80);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 2) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("STATYSTYKI");  // tekst opcji
    fntSel(1, 2, 15, 100);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 3) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("LECZENIE");  // tekst opcji
    fntSel(1, 2, 15, 120);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 4) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("SKLEP");  // tekst opcji
    fntSel(1, 2, 15, 140);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 5) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("WYCZYsc");  // tekst opcji
    fntSel(1, 2, 15, 160);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 6) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("ZABAWA");  // tekst opcji
    fntSel(1, 2, 15, 180);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 7) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("DYSCYPLINA");  // tekst opcji
    fntSel(1, 2, 15, 200);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 8) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("SPOlECZNOsc");  // tekst opcji
    fntSel(1, 2, 15, 220);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (menuSel == 9) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("USTAWIENIA");  // tekst opcji
}

void drawSett(byte settSel) { // rysowanie menu ustawien
    display.fillRect(0, 32, 128, 264, GxEPD_WHITE);         // biale tlo
    fntSel(1, 2, 15, 60);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (settSel == 1) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    if (ustawienia[0] == 0) display.print("WYCISZENIE");    // opcja wylaczona
    if (ustawienia[0] == 1) display.print("DzW. WlaCZ.");   // opcja wlaczona
    fntSel(1, 2, 15, 80);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (settSel == 2) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    if (ustawienia[1] == 0) display.print("UsP. 5 MIN.");   // opcja wylaczona
    if (ustawienia[1] == 1) display.print("UsP. 1 MIN.");   // opcja wlaczona
    fntSel(1, 2, 15, 100);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (settSel == 3) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    if (ustawienia[2] == 0) display.print("ALARM CICHY ");  // opcja wylaczona
    if (ustawienia[2] == 1) display.print("ALARM GlOsNY");  // opcja wlaczona
}

void drawSpol(byte spolSel) { // rysowanie menu ustawien
    display.fillRect(0, 32, 128, 264, GxEPD_WHITE);         // biale tlo
    fntSel(1, 2, 15, 60);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (spolSel == 1) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("WYs. 100Zl");
    fntSel(1, 2, 15, 80);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (spolSel == 2) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("WYs. CHLEB");
    fntSel(1, 2, 15, 100);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (spolSel == 3) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("GRAJ W K&K");
    fntSel(1, 2, 15, 120);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    if (spolSel == 4) display.print("> ");  // jezeli ta opcja jest zaznaczona, dodaj znaczek
    display.print("OTRZ. PREZ");
}

void drawNakarm(byte foodSel) {
    display.drawXBitmap(0, 33, kuchnia_bits, 128, 128, GxEPD_BLACK);    // tlo
    display.drawXBitmap(0, 161, jedzenie1_bits, 128, 22, GxEPD_BLACK);  // grafika jedzenia 1
    display.drawXBitmap(0, 184, jedzenie2_bits, 128, 22, GxEPD_BLACK);  // grafika jedzenia 2
    display.drawXBitmap(0, 207, jedzenie3_bits, 128, 22, GxEPD_BLACK);  // grafika jedzenia 3
    display.drawXBitmap(0, 230, jedzenie4_bits, 128, 22, GxEPD_BLACK);  // grafika jedzenia 4
    if (foodSel == 1) display.drawRect(0, 161, 128, 22, GxEPD_BLACK);   // ramka zaznaczenia 1
    if (foodSel == 2) display.drawRect(0, 184, 128, 22, GxEPD_BLACK);   // ramka zaznaczenia 2
    if (foodSel == 3) display.drawRect(0, 207, 128, 22, GxEPD_BLACK);   // ramka zaznaczenia 3
    if (foodSel == 4) display.drawRect(0, 230, 128, 22, GxEPD_BLACK);   // ramka zaznaczenia 4
    fntSel(1, 2, 110, 175);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print(String(ekJedz[0])); // ilosc jedzenia 1
    fntSel(1, 2, 110, 198);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print(String(ekJedz[1])); // ilosc jedzenia 2
    fntSel(1, 2, 110, 221);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print(String(ekJedz[2])); // ilosc jedzenia 3
    fntSel(1, 2, 110, 244);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print(String(ekJedz[3])); // ilosc jedzenia 4
}

void drawStats() {          // rysowanie ekranu statystyk
    fntSel(1, 3, 5, 50);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    for (int i = 0; i < 10; i++) {      // dla kazdej litery
        display.print(imieWaifu[i]);    // wypisz imie
    }
    fntSel(0, 1, 30, 66);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print("UR. ");  // urodzono
    display.print(plBornD); // dzien
    display.print(".");
    display.print(plBornM); // miesiac
    display.print(".");
    display.print(plBornY); // rok
    fntSel(0, 1, 20, 97);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print("ZDROWIE");
    display.drawRect(13, 99, 102, 12, GxEPD_BLACK); // ramka paska zdr
    display.fillRect(14, 100, (stZdro / 100), 10, GxEPD_BLACK); // pasek zdr
    fntSel(0, 1, 20, 127);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print("NAJEDZENIE");
    display.drawRect(13, 129, 102, 12, GxEPD_BLACK); // ramka paska najedzenia
    display.fillRect(14, 130, (stJedz / 100), 10, GxEPD_BLACK); // pasek najedzenia
    fntSel(0, 1, 20, 157);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print("HIGIENA");
    display.drawRect(13, 159, 102, 12, GxEPD_BLACK); // ramka paska higieny
    display.fillRect(14, 160, (stHigi / 100), 10, GxEPD_BLACK); // pasek higieny
    fntSel(0, 1, 20, 187);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print("ZABAWA");
    display.drawRect(13, 189, 102, 12, GxEPD_BLACK); // ramka paska zabawy
    display.fillRect(14, 190, (stZaba / 100), 10, GxEPD_BLACK); // pasek zabawy
    fntSel(0, 1, 20, 217);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
    display.print("DYSCYPLINA");
    display.drawRect(13, 219, 102, 12, GxEPD_BLACK); // ramka paska dyscypl.
    display.fillRect(14, 220, (stDysc / 100), 10, GxEPD_BLACK); // pasek dyscypl.
}

// rysowanie sklepu (sklep, zaznaczenie)
void drawSklep(byte sklep, byte sel) {
    if (sklep == 1) {   // sklep z jedzeniem
        display.drawXBitmap(0, 33, teren1_bits, 128, 128, GxEPD_BLACK);     // tlo
        display.drawXBitmap(0, 161, jedzenie1_bits, 128, 22, GxEPD_BLACK);  // poz1
        display.drawXBitmap(0, 184, jedzenie2_bits, 128, 22, GxEPD_BLACK);  // poz2
        display.drawXBitmap(0, 207, jedzenie3_bits, 128, 22, GxEPD_BLACK);  // poz3
        display.drawXBitmap(0, 230, jedzenie4_bits, 128, 22, GxEPD_BLACK);  // poz4
        if (sel == 1) display.drawRect(0, 161, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 2) display.drawRect(0, 184, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 3) display.drawRect(0, 207, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 4) display.drawRect(0, 230, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        fntSel(1, 2, 110, 175);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekJedz[0]));
        fntSel(1, 2, 110, 198);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekJedz[1]));
        fntSel(1, 2, 110, 221);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekJedz[2]));
        fntSel(1, 2, 110, 244);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekJedz[3]));
    }
    if (sklep == 2) {
        display.drawXBitmap(0, 33, teren2_bits, 128, 128, GxEPD_BLACK); // sklep z przedmiotami
        display.drawXBitmap(0, 161, przedmiot1_bits, 128, 22, GxEPD_BLACK);  // poz1
        display.drawXBitmap(0, 184, przedmiot2_bits, 128, 22, GxEPD_BLACK);  // poz2
        display.drawXBitmap(0, 207, przedmiot3_bits, 128, 22, GxEPD_BLACK);  // poz3
        display.drawXBitmap(0, 230, przedmiot4_bits, 128, 22, GxEPD_BLACK);  // poz4
        if (sel == 1) display.drawRect(0, 161, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 2) display.drawRect(0, 184, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 3) display.drawRect(0, 207, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 4) display.drawRect(0, 230, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        fntSel(1, 2, 110, 175);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekItem[0])); // czy ma rybke
        fntSel(1, 2, 110, 198);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekItem[1])); // czy ma lampke
    }
    if (sklep == 3) {
        display.drawXBitmap(0, 33, teren3_bits, 128, 128, GxEPD_BLACK); // sklep z ubraniami
        display.drawXBitmap(0, 161, ubranie1_bits, 128, 22, GxEPD_BLACK);  // poz1
        display.drawXBitmap(0, 184, ubranie2_bits, 128, 22, GxEPD_BLACK);  // poz2
        display.drawXBitmap(0, 207, ubranie3_bits, 128, 22, GxEPD_BLACK);  // poz3
        display.drawXBitmap(0, 230, ubranie4_bits, 128, 22, GxEPD_BLACK);  // poz4
        if (sel == 1) display.drawRect(0, 161, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 2) display.drawRect(0, 184, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 3) display.drawRect(0, 207, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        if (sel == 4) display.drawRect(0, 230, 128, 22, GxEPD_BLACK); // ramka zaznaczenia
        fntSel(1, 2, 110, 175);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekUbra[0])); // czy ma ubr1
        fntSel(1, 2, 110, 198);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekUbra[1])); // czy ma ubr2
        fntSel(1, 2, 110, 221);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekUbra[2])); // czy ma ubr3
        fntSel(1, 2, 110, 244);  // funkcja wyboru fontu, skali i pozycji x i y tekstu
        display.print(String(ekUbra[3])); // czy ma ubr4
    }
}


void drawZabawa() { // ekran wyboru zabawy
    display.drawXBitmap(0, 33, zabawa_bits, 128, 238, GxEPD_BLACK); // tlo wyboru zabawy
}


// sprawdzanie czy dany gracz wygral (1 lub 2)
bool sprawdzWygrana(byte tempPlansza[9], byte gracz) {
    // sprawdzanie wierszy
    for (byte i = 0; i < 3; ++i) {
        if (tempPlansza[i * 3] == gracz && tempPlansza[i * 3 + 1] == gracz && tempPlansza[i * 3 + 2] == gracz) {
            return true;
        }
    }

    // sprawdzanie kolumnn
    for (byte i = 0; i < 3; ++i) {
        if (tempPlansza[i] == gracz && tempPlansza[i + 3] == gracz && tempPlansza[i + 6] == gracz) {
            return true;
        }
    }

    // sprawdzanie przekatnych
    if ((tempPlansza[0] == gracz && tempPlansza[4] == gracz && tempPlansza[8] == gracz) ||
            (tempPlansza[2] == gracz && tempPlansza[4] == gracz && tempPlansza[6] == gracz)) {
        return true;
    }
    return false;
}


void wykonajRuch() {
    // sprawdzanie pustych pol
    byte iloscDostepnychPol = 0;
    for (byte i = 0; i < 9; ++i) {
        if (plansza[i] == 0) {
            iloscDostepnychPol++;
        }
    }
    if (iloscDostepnychPol > 0) {
        // jezeli srodek wolny, to postaw na srodku
        if (plansza[4] == 0) {
            plansza[4] = 2;
            return;
        }

        byte losujTrudnosc = random(100);
        if (losujTrudnosc > trudnosc) {
            // jezeli dwa pola sa gracza i brakuje mu jednego do wygranej, to blokuj
            if ((plansza[0] == 1) && (plansza[1] == 1) && (plansza[2] == 0)) {
                plansza[2] = 2;
                return;
            }
            if ((plansza[0] == 1) && (plansza[1] == 0) && (plansza[2] == 1)) {
                plansza[1] = 2;
                return;
            }
            if ((plansza[0] == 0) && (plansza[1] == 1) && (plansza[2] == 1)) {
                plansza[0] = 2;
                return;
            }

            if ((plansza[3] == 1) && (plansza[4] == 1) && (plansza[5] == 0)) {
                plansza[5] = 2;
                return;
            }
            if ((plansza[3] == 1) && (plansza[4] == 0) && (plansza[5] == 1)) {
                plansza[4] = 2;
                return;
            }
            if ((plansza[3] == 0) && (plansza[4] == 1) && (plansza[5] == 1)) {
                plansza[3] = 2;
                return;
            }

            if ((plansza[6] == 1) && (plansza[7] == 1) && (plansza[8] == 0)) {
                plansza[8] = 2;
                return;
            }
            if ((plansza[6] == 1) && (plansza[7] == 0) && (plansza[8] == 1)) {
                plansza[7] = 2;
                return;
            }
            if ((plansza[6] == 0) && (plansza[7] == 1) && (plansza[8] == 1)) {
                plansza[6] = 2;
                return;
            }




            if ((plansza[0] == 1) && (plansza[3] == 1) && (plansza[6] == 0)) {
                plansza[6] = 2;
                return;
            }
            if ((plansza[0] == 1) && (plansza[3] == 0) && (plansza[6] == 1)) {
                plansza[3] = 2;
                return;
            }
            if ((plansza[0] == 0) && (plansza[3] == 1) && (plansza[6] == 1)) {
                plansza[0] = 2;
                return;
            }


            if ((plansza[1] == 1) && (plansza[4] == 1) && (plansza[7] == 0)) {
                plansza[7] = 2;
                return;
            }
            if ((plansza[1] == 1) && (plansza[4] == 0) && (plansza[7] == 1)) {
                plansza[4] = 2;
                return;
            }
            if ((plansza[1] == 0) && (plansza[4] == 1) && (plansza[7] == 1)) {
                plansza[1] = 2;
                return;
            }

            if ((plansza[2] == 1) && (plansza[5] == 1) && (plansza[8] == 0)) {
                plansza[8] = 2;
                return;
            }
            if ((plansza[2] == 1) && (plansza[5] == 0) && (plansza[8] == 1)) {
                plansza[5] = 2;
                return;
            }
            if ((plansza[2] == 0) && (plansza[5] == 1) && (plansza[8] == 1)) {
                plansza[2] = 2;
                return;
            }





            if ((plansza[0] == 1) && (plansza[4] == 1) && (plansza[8] == 0)) {
                plansza[8] = 2;
                return;
            }
            if ((plansza[0] == 1) && (plansza[4] == 0) && (plansza[8] == 1)) {
                plansza[4] = 2;
                return;
            }
            if ((plansza[0] == 0) && (plansza[4] == 1) && (plansza[8] == 1)) {
                plansza[0] = 2;
                return;
            }

            if ((plansza[2] == 1) && (plansza[4] == 1) && (plansza[6] == 0)) {
                plansza[6] = 2;
                return;
            }
            if ((plansza[2] == 1) && (plansza[4] == 0) && (plansza[6] == 1)) {
                plansza[4] = 2;
                return;
            }
            if ((plansza[2] == 0) && (plansza[4] == 1) && (plansza[6] == 1)) {
                plansza[2] = 2;
                return;
            }


            // jezeli komputer ma wygrana w jednym ruchu to dostaw
            if ((plansza[0] == 2) && (plansza[1] == 2) && (plansza[2] == 0)) {
                plansza[2] = 2;
                return;
            }
            if ((plansza[0] == 2) && (plansza[1] == 0) && (plansza[2] == 2)) {
                plansza[1] = 2;
                return;
            }
            if ((plansza[0] == 0) && (plansza[1] == 2) && (plansza[2] == 2)) {
                plansza[0] = 2;
                return;
            }

            if ((plansza[3] == 2) && (plansza[4] == 2) && (plansza[5] == 0)) {
                plansza[5] = 2;
                return;
            }
            if ((plansza[3] == 2) && (plansza[4] == 0) && (plansza[5] == 2)) {
                plansza[4] = 2;
                return;
            }
            if ((plansza[3] == 0) && (plansza[4] == 2) && (plansza[5] == 2)) {
                plansza[3] = 2;
                return;
            }

            if ((plansza[6] == 2) && (plansza[7] == 2) && (plansza[8] == 0)) {
                plansza[8] = 2;
                return;
            }
            if ((plansza[6] == 2) && (plansza[7] == 0) && (plansza[8] == 2)) {
                plansza[7] = 2;
                return;
            }
            if ((plansza[6] == 0) && (plansza[7] == 2) && (plansza[8] == 2)) {
                plansza[6] = 2;
                return;
            }






            if ((plansza[0] == 2) && (plansza[3] == 2) && (plansza[6] == 0)) {
                plansza[6] = 2;
                return;
            }
            if ((plansza[0] == 2) && (plansza[3] == 0) && (plansza[6] == 2)) {
                plansza[3] = 2;
                return;
            }
            if ((plansza[0] == 0) && (plansza[3] == 2) && (plansza[6] == 2)) {
                plansza[0] = 2;
                return;
            }


            if ((plansza[1] == 2) && (plansza[4] == 2) && (plansza[7] == 0)) {
                plansza[7] = 2;
                return;
            }
            if ((plansza[1] == 2) && (plansza[4] == 0) && (plansza[7] == 2)) {
                plansza[4] = 2;
                return;
            }
            if ((plansza[1] == 0) && (plansza[4] == 2) && (plansza[7] == 2)) {
                plansza[1] = 2;
                return;
            }

            if ((plansza[2] == 2) && (plansza[5] == 2) && (plansza[8] == 0)) {
                plansza[8] = 2;
                return;
            }
            if ((plansza[2] == 2) && (plansza[5] == 0) && (plansza[8] == 2)) {
                plansza[5] = 2;
                return;
            }
            if ((plansza[2] == 0) && (plansza[5] == 2) && (plansza[8] == 2)) {
                plansza[2] = 2;
                return;
            }





            if ((plansza[0] == 2) && (plansza[4] == 2) && (plansza[8] == 0)) {
                plansza[8] = 2;
                return;
            }
            if ((plansza[0] == 2) && (plansza[4] == 0) && (plansza[8] == 2)) {
                plansza[4] = 2;
                return;
            }
            if ((plansza[0] == 0) && (plansza[4] == 2) && (plansza[8] == 2)) {
                plansza[0] = 2;
                return;
            }

            if ((plansza[2] == 2) && (plansza[4] == 2) && (plansza[6] == 0)) {
                plansza[6] = 2;
                return;
            }
            if ((plansza[2] == 2) && (plansza[4] == 0) && (plansza[6] == 2)) {
                plansza[4] = 2;
                return;
            }
            if ((plansza[2] == 0) && (plansza[4] == 2) && (plansza[6] == 2)) {
                plansza[2] = 2;
                return;
            }



            // jezeli rog wolny to postaw na rogu
            if (plansza[0] == 0) {
                plansza[0] = 2;
                return;
            }
            if (plansza[6] == 0) {
                plansza[6] = 2;
                return;
            }
            if (plansza[2] == 0) {
                plansza[2] = 2;
                return;
            }
            if (plansza[8] == 0) {
                plansza[8] = 2;
                return;
            }
        } else {
            // jezeli brak innego pomyslu to postaw na pierwszym wolnym polu
            for (int po = 0; po < 9; po++) {
                if (plansza[po] == 0) {
                    plansza[po] = 2;
                    return;
                }
            }
        }
    } else {
        for (int po = 0; po < 9; po++) {
            plansza[po] = 0;
        }
        return;
    }
    keyx = 1;
}



void drawZabawaB() { // ekran zabawy w KK singleplayer
    display.drawXBitmap(0, 33, plansza_bits, 128, 238, GxEPD_BLACK); // tlo kolka i krzyzyka
    if (sel == 0) display.drawRect(4, 60, 40, 40, GxEPD_BLACK);
    if (plansza[0] == 1) display.drawXBitmap(4, 60, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[0] == 2) display.drawXBitmap(4, 60, krzyz_bits, 40, 40, GxEPD_BLACK);

    if (sel == 1) display.drawRect(44, 60, 40, 40, GxEPD_BLACK);
    if (plansza[1] == 1) display.drawXBitmap(44, 60, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[1] == 2) display.drawXBitmap(44, 60, krzyz_bits, 40, 40, GxEPD_BLACK);

    if (sel == 2) display.drawRect(84, 60, 40, 40, GxEPD_BLACK);
    if (plansza[2] == 1) display.drawXBitmap(84, 60, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[2] == 2) display.drawXBitmap(84, 60, krzyz_bits, 40, 40, GxEPD_BLACK);

    if (sel == 3) display.drawRect(4, 100, 40, 40, GxEPD_BLACK);
    if (plansza[3] == 1) display.drawXBitmap(4, 100, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[3] == 2) display.drawXBitmap(4, 100, krzyz_bits, 40, 40, GxEPD_BLACK);

    if (sel == 4) display.drawRect(44, 100, 40, 40, GxEPD_BLACK);
    if (plansza[4] == 1) display.drawXBitmap(44, 100, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[4] == 2) display.drawXBitmap(44, 100, krzyz_bits, 40, 40, GxEPD_BLACK);

    if (sel == 5) display.drawRect(84, 100, 40, 40, GxEPD_BLACK);
    if (plansza[5] == 1) display.drawXBitmap(84, 100, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[5] == 2) display.drawXBitmap(84, 100, krzyz_bits, 40, 40, GxEPD_BLACK);

    if (sel == 6) display.drawRect(4, 140, 40, 40, GxEPD_BLACK);
    if (plansza[6] == 1) display.drawXBitmap(4, 140, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[6] == 2) display.drawXBitmap(4, 140, krzyz_bits, 40, 40, GxEPD_BLACK);

    if (sel == 7) display.drawRect(44, 140, 40, 40, GxEPD_BLACK);
    if (plansza[7] == 1) display.drawXBitmap(44, 140, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[7] == 2) display.drawXBitmap(44, 140, krzyz_bits, 40, 40, GxEPD_BLACK);

    if (sel == 8) display.drawRect(84, 140, 40, 40, GxEPD_BLACK);
    if (plansza[8] == 1) display.drawXBitmap(84, 140, kolko_bits, 40, 40, GxEPD_BLACK);
    if (plansza[8] == 2) display.drawXBitmap(84, 140, krzyz_bits, 40, 40, GxEPD_BLACK);
}

void otrzZaproszenie() {
    Serial.println("OTRZYMANO ZAPROSZENIE DO GRY");
}
