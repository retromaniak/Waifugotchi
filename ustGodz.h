// funkcja rysuje strzalke przy ustawieniach godziny, daty, imienia

void arrowDraw(bool dwn, byte x, byte y) {
    if (dwn) {    // w dol
        display.drawLine(x + 4, y + 4, x + 4, y + 4, GxEPD_BLACK);
        display.drawLine(x + 3, y + 3, x + 5, y + 3, GxEPD_BLACK);
        display.drawLine(x + 2, y + 2, x + 6, y + 2, GxEPD_BLACK);
        display.drawLine(x + 1, y + 1, x + 7, y + 1, GxEPD_BLACK);
        display.drawLine(x + 0, y + 0, x + 8, y + 0, GxEPD_BLACK);
    } else {   // w gore
        display.drawLine(x + 4, y + 0, x + 4, y + 0, GxEPD_BLACK);
        display.drawLine(x + 3, y + 1, x + 5, y + 1, GxEPD_BLACK);
        display.drawLine(x + 2, y + 2, x + 6, y + 2, GxEPD_BLACK);
        display.drawLine(x + 1, y + 3, x + 7, y + 3, GxEPD_BLACK);
        display.drawLine(x + 0, y + 4, x + 8, y + 4, GxEPD_BLACK);
    }
}

// cala funkcja ustawiania godziny
void ustGodzine() {
    byte st = 0;
    byte tmpSetHr = 12;
    byte tmpSetMi = 0;
    byte tmpSetDa = 1;
    byte tmpSetMo = 1;
    int tmpSetYe = 2024;

    while (st < 7) { // dopoki jest aktywny ekran ustawiania godziny
        checkKeys();   // czytaj klawisze

        if (keyx == 1) {    // wcisnieto dowolny klawisz
            keyx = 0;
            if (st == 0) {
            } else if (st == 1) { // godzina
                if (keyu) {
                    keyu = 0;
                    tmpSetHr++;   // dodaj godzine
                    if (tmpSetHr > 23) tmpSetHr = 0;
                }
                if (keyd) {
                    keyd = 0;
                    if (tmpSetHr == 0) tmpSetHr = 24;
                    tmpSetHr--;   // zmniejsz godzine
                }
                if (keyl) {
                    keyl = 0;
                    st = 2;   // zmiana zaznaczenia na minuty
                }
                if (keyr) {
                    keyr = 0;
                    st = 2;   // zmiana zaznaczenia na minuty
                }
                if (keyc) {
                    keyc = 0;
                    st = 3;   // zmiana ustawienia na date
                }
            } else if (st == 2) { // minuty
                if (keyu) {
                    keyu = 0;
                    tmpSetMi++;   // dodaj minuty
                    if (tmpSetMi > 59) tmpSetMi = 0;
                }
                if (keyd) {
                    keyd = 0;
                    if (tmpSetMi == 0) tmpSetMi = 60;
                    tmpSetMi--;   // zmniejsz minuty
                }
                if (keyl) {
                    keyl = 0;
                    st = 1;
                }
                if (keyr) {
                    keyr = 0;
                    st = 1;
                }
                if (keyc) {
                    keyc = 0;
                    st = 3;   // ustawienia daty
                }

            } else if (st == 3) { // dzien

                if (keyu) {
                    keyu = 0;
                    tmpSetDa++;
                    if (tmpSetDa > 31) tmpSetDa = 1;
                }
                if (keyd) {
                    keyd = 0;
                    if (tmpSetDa == 1) tmpSetDa = 32;
                    tmpSetDa--;
                }
                if (keyl) {
                    keyl = 0;
                    st = 5;
                }
                if (keyr) {
                    keyr = 0;
                    st = 4;
                }
                if (keyc) {
                    keyc = 0;
                    st = 6;
                }

            } else if (st == 4) { // miesiac

                if (keyu) {
                    keyu = 0;
                    tmpSetMo++;
                    if (tmpSetMo > 12) tmpSetMo = 1;
                }
                if (keyd) {
                    keyd = 0;
                    if (tmpSetMo == 1) tmpSetMo = 13;
                    tmpSetMo--;
                }
                if (keyl) {
                    keyl = 0;
                    st = 3;
                }
                if (keyr) {
                    keyr = 0;
                    st = 5;
                }
                if (keyc) {
                    keyc = 0;
                    st = 6;
                }

            } else if (st == 5) { // rok
                if (keyu) {
                    keyu = 0;
                    tmpSetYe++;
                    if (tmpSetYe > 2099) tmpSetYe = 2023;
                }
                if (keyd) {
                    keyd = 0;
                    if (tmpSetYe == 2023) tmpSetYe = 2100;
                    tmpSetYe--;
                }
                if (keyl) {
                    keyl = 0;
                    st = 4;
                }
                if (keyr) {
                    keyr = 0;
                    st = 3;
                }
                if (keyc) {
                    keyc = 0;
                    st = 6;
                }

            } else if (st == 6) {
            }


            // FUNKCJE RYSOWANIA, ANALOGICZNIE DO FUNKCJI NAWIGACJI POWYZEJ
            if (st == 0) {
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_data_bits, 128, 296, GxEPD_BLACK);

                txtPrint(3, 1, 0, 25, "GODZINA");
                txtPrint(3, 1, 0, 45, "I DATA");
                txtPrint(1, 1, 0, 60, "USTAW GODZINe ORAZ");
                txtPrint(1, 1, 0, 70, "DATe ZA POMOCa");
                txtPrint(1, 1, 0, 80, "PRZYCISKoW");
                txtPrint(1, 1, 0, 90, "KIERUNKOWYCH I");
                txtPrint(1, 1, 0, 100, "ZAAKCEPTUJ");
                txtPrint(1, 1, 0, 110, "PRZYCISKIEM");
                txtPrint(1, 1, 0, 120, "CENTRALNYM.");
                display.nextPage();
                st = 1;
            }
            if (st == 1) {
                display.setPartialWindow(0, 150, 128, 80);
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_data_bits, 128, 296, GxEPD_BLACK);
                txtPrint(3, 1, 0, 170, "GODZINA:");
                txtPrint(3, 0, 30, 215, "");
                if (tmpSetHr < 10) display.print("0");
                display.print(tmpSetHr);
                display.print(":");
                if (tmpSetMi < 10) display.print("0");
                display.print(tmpSetMi);
                arrowDraw(false, 36, 192);
                arrowDraw(true, 36, 224);

                display.nextPage();
            }
            if (st == 2) {
                display.setPartialWindow(0, 150, 128, 80);
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_data_bits, 128, 296, GxEPD_BLACK);
                txtPrint(3, 1, 0, 170, "MINUTY:");
                txtPrint(3, 0, 30, 215, "");
                if (tmpSetHr < 10) display.print("0");
                display.print(tmpSetHr);
                display.print(":");
                if (tmpSetMi < 10) display.print("0");
                display.print(tmpSetMi);
                arrowDraw(false, 73, 192);
                arrowDraw(true, 73, 224);
                display.nextPage();
            }
            if (st == 3) {
                display.setPartialWindow(0, 150, 128, 80);
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_data_bits, 128, 296, GxEPD_BLACK);
                txtPrint(3, 1, 0, 170, "DZIEn:");
                txtPrint(3, 0, 5, 215, "");
                if (tmpSetDa < 10) display.print(" ");
                display.print(tmpSetDa);
                display.print(".");
                if (tmpSetMo < 10) display.print("0");
                display.print(tmpSetMo);
                display.print(".");
                display.print(tmpSetYe);
                arrowDraw(false, 12, 192);
                arrowDraw(true, 12, 224);
                display.nextPage();
            }
            if (st == 4) {
                display.setPartialWindow(0, 150, 128, 80);
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_data_bits, 128, 296, GxEPD_BLACK);
                txtPrint(3, 1, 0, 170, "MIESIaC:");
                txtPrint(3, 0, 5, 215, "");
                if (tmpSetDa < 10) display.print(" ");
                display.print(tmpSetDa);
                display.print(".");
                if (tmpSetMo < 10) display.print("0");
                display.print(tmpSetMo);
                display.print(".");
                display.print(tmpSetYe);
                arrowDraw(false, 43, 192);
                arrowDraw(true, 43, 224);
                display.nextPage();
            }
            if (st == 5) {
                display.setPartialWindow(0, 150, 128, 80);
                display.firstPage();
                display.fillScreen(GxEPD_WHITE);
                display.drawXBitmap(0, 0, tlo_data_bits, 128, 296, GxEPD_BLACK);
                txtPrint(3, 1, 0, 170, "ROK:");
                txtPrint(3, 0, 5, 215, "");
                if (tmpSetDa < 10) display.print(" ");
                display.print(tmpSetDa);
                display.print(".");
                if (tmpSetMo < 10) display.print("0");
                display.print(tmpSetMo);
                display.print(".");
                display.print(tmpSetYe);
                arrowDraw(false, 88, 192);
                arrowDraw(true, 88, 224);
                display.nextPage();
            }
            if (st == 6) {
                display.setFullWindow();
                rtc.setTime(0, tmpSetMi, tmpSetHr, tmpSetDa, tmpSetMo, tmpSetYe);
                keyx = 1;
                st = 7;
            }
        }
    }
}
