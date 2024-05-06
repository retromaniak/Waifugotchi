
// TABELA DOSTEPNYCH ZNAKOW NAZWY
byte nameChars[64] = {
    /* */ 32,   /*A*/ 65,   /*a*/ 97,   /*B*/ 66,   /*C*/ 67,   /*c*/ 99,   /*D*/ 68,   /*E*/ 69,
    /*e*/ 101,  /*F*/ 70,   /*G*/ 71,   /*H*/ 72,   /*I*/ 73,   /*J*/ 74,   /*K*/ 75,   /*L*/ 76,
    /*l*/ 108,  /*M*/ 77,   /*N*/ 78,   /*n*/ 110,  /*O*/ 79,   /*o*/ 111,  /*P*/ 80,   /*Q*/ 81,
    /*R*/ 82,   /*S*/ 83,   /*s*/ 115,  /*T*/ 84,   /*U*/ 85,   /*V*/ 86,   /*W*/ 87,   /*X*/ 88,
    /*Y*/ 89,   /*Z*/ 90,   /*z*/ 122,  /*x*/ 120,  /*0*/ 48,   /*1*/ 49,   /*2*/ 50,   /*3*/ 51,
    /*4*/ 52,   /*5*/ 53,   /*6*/ 54,   /*7*/ 55,   /*8*/ 56,   /*9*/ 57,   /*.*/ 46,   /*@*/ 64,
    /*!*/ 33,   /*?*/ 63,   /*:*/ 58,   /*-*/ 45,   /*+*/ 43,   /*=*/ 61,   /*<*/ 60,   /*>*/ 62,
    /*#*/ 35,   /*[*/ 91,   /*]*/ 93,   /***/ 42,   /*$*/ 36,   /*(*/ 40,   /*)*/ 41,   /*_*/ 95
};

// TWORZENIE POSTACI
void ustPostac() {
    // zerowanie zmiennych
    byte st = 0;
    byte sel = 0;
    char plSetNm[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    byte plCharSet[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    byte plSetSx = 1;

    while (st < 4) { // do zakonczenia tworzenia postaci wykonuj:
        checkKeys();
        // funkcje nawigacji, wcisniecia klawiszy:
        if (keyx == 1) { // dowolny klawisz
            keyx = 0;
            if (st == 1) { // ustawianie imienia
                if (keyu) {
                    keyu = 0;
                    plCharSet[sel]++;
                    if (plCharSet[sel] >= 64) {
                        plCharSet[sel] = 0;
                    }
                    /*
                        while ((plSetNm[sel] < 32) || ((plSetNm[sel] > 32) && (plSetNm[sel] < 48)) || ((plSetNm[sel] > 57) && (plSetNm[sel] < 65)) || (plSetNm[sel] > 90)) {
                        plSetNm[sel]++;
                        }
                    */
                }
                if (keyd) {
                    keyd = 0;
                    if (plCharSet[sel] > 0) {
                        plCharSet[sel]--;
                    } else {
                        plCharSet[sel] = 63;
                    }
                    /*
                        while ((plSetNm[sel] < 32) || ((plSetNm[sel] > 32) && (plSetNm[sel] < 48)) || ((plSetNm[sel] > 57) && (plSetNm[sel] < 65)) || (plSetNm[sel] > 90)) {
                        plSetNm[sel]--;
                        }
                    */
                }
                if (keyl) {
                    keyl = 0;
                    if (sel == 0) sel = 10;
                    sel--;
                }
                if (keyr) {
                    keyr = 0;
                    sel++;
                    if (sel == 10) sel = 0;
                }
                if (keyc) {
                    keyc = 0;
                    st = 2;
                }
            } else if (st == 2) { // ustawianie plci
                if (keyu) {
                    keyu = 0;
                    plSetSx++;
                    if (plSetSx > 3) plSetSx = 1;
                }
                if (keyd) {
                    keyd = 0;
                    plSetSx--;
                    if (plSetSx < 1) plSetSx = 3;
                }
                if (keyl) {
                    keyl = 0;
                    plSetSx--;
                    if (plSetSx < 1) plSetSx = 3;
                }
                if (keyr) {
                    keyr = 0;
                    plSetSx++;
                    if (plSetSx > 3) plSetSx = 1;
                }
                if (keyc) {
                    keyc = 0;
                    st = 3;
                }

            }
            // FUNKCJE RYSOWANIA ANALOGICZNIE DO FUNKCJI NAWIGACJI POWYZEJ
            if (st == 0) { // TLO
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_postac_bits, 128, 296, GxEPD_BLACK);
                txtPrint(3, 1, 0, 25, "NOWA");
                txtPrint(3, 1, 0, 45, "POSTAc");
                txtPrint(1, 1, 0, 60, "USTAW NAZWe I PlEc");
                txtPrint(1, 1, 0, 70, "NOWEJ POSTACI ZA");
                txtPrint(1, 1, 0, 80, "POMOCa PRZYCISKoW");
                txtPrint(1, 1, 0, 90, "KIERUNKOWYCH, ORAZ");
                txtPrint(1, 1, 0, 100, "ZAAKCEPTUJ");
                txtPrint(1, 1, 0, 110, "PRZYCISKIEM");
                txtPrint(1, 1, 0, 120, "CENTRALNYM.");
                display.nextPage();
                st = 1;
            }
            if (st == 1) { // NAZWA
                display.setPartialWindow(0, 130, 128, 160);
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_postac_bits, 128, 296, GxEPD_BLACK);
                txtPrint(3, 1, 0, 150, "IMIe:");    // funkcja wypisuje tekst zadanej wielkosci, fontu, przeciwnie do fntSel przekazuje tez tekst

                fntSel(0, 2, 2, 215);
                display.print(char(nameChars[plCharSet[0]]));
                fntSel(0, 2, 14, 215);
                display.print(char(nameChars[plCharSet[1]]));
                fntSel(0, 2, 26, 215);
                display.print(char(nameChars[plCharSet[2]]));
                fntSel(0, 2, 38, 215);
                display.print(char(nameChars[plCharSet[3]]));
                fntSel(0, 2, 50, 215);
                display.print(char(nameChars[plCharSet[4]]));
                fntSel(0, 2, 62, 215);
                display.print(char(nameChars[plCharSet[5]]));
                fntSel(0, 2, 74, 215);
                display.print(char(nameChars[plCharSet[6]]));
                fntSel(0, 2, 86, 215);
                display.print(char(nameChars[plCharSet[7]]));
                fntSel(0, 2, 98, 215);
                display.print(char(nameChars[plCharSet[8]]));
                fntSel(0, 2, 110, 215);
                display.print(char(nameChars[plCharSet[9]]));

                arrowDraw(false, 3 + (sel * 12), 192);
                arrowDraw(true,  3 + (sel * 12), 224);
                display.nextPage();
            }
            if (st == 2) { // PLEC
                display.setPartialWindow(0, 130, 128, 160);
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_postac_bits, 128, 296, GxEPD_BLACK);
                txtPrint(3, 1, 0, 150, "PlEc:");

                if (plSetSx == 1) display.drawXBitmap(0, 160, plec1_bits, 128, 128, GxEPD_BLACK);
                if (plSetSx == 2) display.drawXBitmap(0, 160, plec2_bits, 128, 128, GxEPD_BLACK);
                if (plSetSx == 3) display.drawXBitmap(0, 160, plec3_bits, 128, 128, GxEPD_BLACK);
                display.nextPage();
            }
            if (st == 3) { // ZAPISYWANIE USTAWIEN DO PLIKOW
                display.setFullWindow();
                st = 4;
                String tmpSt = String(plSetSx);
                writeFile(SPIFFS, "/plaPle", tmpSt.c_str());
                tmpSt = String(rtc.getDay());
                plBornD = rtc.getDay();
                writeFile(SPIFFS, "/plaBoD", tmpSt.c_str());
                Serial.println(tmpSt);
                tmpSt = String(rtc.getMonth() + 1);
                plBornM = rtc.getMonth() + 1;
                writeFile(SPIFFS, "/plaBoM", tmpSt.c_str());
                Serial.println(tmpSt);
                tmpSt = String(rtc.getYear());
                writeFile(SPIFFS, "/plaBoY", tmpSt.c_str());
                Serial.println(tmpSt);
                plBornY = rtc.getYear();
                int tmpTSH = rtc.getHour(true) * 12;
                int tmpTSM = rtc.getMinute() / 5;
                int timeStamp = tmpTSH + tmpTSM;
                String timeSTStr = String(timeStamp);
                writeFile(SPIFFS, "/modSta", timeSTStr.c_str());
                Serial.println(timeSTStr);

                writeFile(SPIFFS, "/plaDeD", "0");
                writeFile(SPIFFS, "/plaDeM", "0");
                writeFile(SPIFFS, "/plaDeY", "0");
            }
        }
    }
    String nazwa = String(char(nameChars[plCharSet[0]]));
    for (int i = 1; i < 10; i++) {
        nazwa += char(nameChars[plCharSet[i]]);
    }

    // ZAPISYWANIE WARTOSCI DOMYSLNYCH/POCZATKOWYCH WSZYSTKICH POZOSTALYCH PLIKOW
    writeFile(SPIFFS, "/creSta", "2");      // postac zyje
    writeFile(SPIFFS, "/plaNam", nazwa.c_str());
    writeFile(SPIFFS, "/plaZdr", "4900");   // zdrowie
    writeFile(SPIFFS, "/plaJed", "4800");   // najedzenie
    writeFile(SPIFFS, "/plaHig", "4700");   // higiena
    writeFile(SPIFFS, "/plaZab", "4600");   // zabawa
    writeFile(SPIFFS, "/plaDys", "4500");   // dyscyplina
    writeFile(SPIFFS, "/plaKas", "80000");  // pieniadze
    writeFile(SPIFFS, "/plaBat", "0");      // batonik
    writeFile(SPIFFS, "/plaAnt", "0");      // zel antybakteryjny

    // LOSOWANIE TYPU OKA
    byte losujOko = random(5) + 1;
    if (losujOko == 1) {
        writeFile(SPIFFS, "/typOka", "1");
    } else if (losujOko == 2) {
        writeFile(SPIFFS, "/typOka", "2");
    } else if (losujOko == 3) {
        writeFile(SPIFFS, "/typOka", "3");
    } else if (losujOko == 4) {
        writeFile(SPIFFS, "/typOka", "4");
    } else if (losujOko == 5) {
        writeFile(SPIFFS, "/typOka", "5");
    } else {
        writeFile(SPIFFS, "/typOka", "1");
    }

    writeFile(SPIFFS, "/plaUbr", "1000");  // ubrania
    writeFile(SPIFFS, "/plaItm", "0000");  // przedmioty
    writeFile(SPIFFS, "/plaItj", "2222");  // jedzenie
    writeFile(SPIFFS, "/devSet", "1000000000");
    writeFile(SPIFFS, "/netFlg", "0");
}
