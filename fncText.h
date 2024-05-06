
// funkcja wybierająca font, skalę oraz pozycję tekstu
void fntSel(byte fnts, byte scal, int txtx, int txty) {
    if (fnts == 0) display.setFont(&cze);          // 5x7
    if (fnts == 1) display.setFont(&witam);        // 3x5
    display.setTextSize(scal);
    display.setCursor(txtx, txty);
}



// funkcja dla wygodnego wypisywania tekstu o okreslonym rozmiarze i formatowaniu
//    txtFnt - okresla font, a w zasadzie font i jego skale
//              0 - font 3x5 bez skalowania
//              1 - font 5x7 bez skalowania
//              2 - font 3x5 ze skalowaniem x2
//              3 - font 5x5 ze skalowaniem x2
//    txtCen - okresla formatowanie (0=do lewej, 1=wysrodkowane)
//    txtX, txtY - okresla pozycje tekstu. (txtX jest ignorowany w przypadku srodkowania)
//    txtText - wyswietlany tekst
void txtPrint(byte txtFnt, bool txtCen, int txtX, int txtY, String txtText) {
    if (txtFnt == 0 || txtFnt == 2) display.setFont(&witam); // ustawienie fontu
    if (txtFnt == 1 || txtFnt == 3) display.setFont(&cze);   // ustawienie fontu
    if (txtFnt == 0 || txtFnt == 1) display.setTextSize(1);  // ustawienie skali
    if (txtFnt == 2 || txtFnt == 3) display.setTextSize(2);  // ustawienie skali
    if (!txtCen) {
        display.setCursor(txtX, txtY);                  // ustawienie kursora przy braku środkowania
    } else {
        byte xDlu = 0;
        if (txtFnt == 0) xDlu = (txtText.length() * 4); // srawdzanie szerokosci tekstu
        if (txtFnt == 1) xDlu = (txtText.length() * 6); // srawdzanie szerokosci tekstu
        if (txtFnt == 2) xDlu = (txtText.length() * 8); // srawdzanie szerokosci tekstu
        if (txtFnt == 3) xDlu = (txtText.length() * 12);// srawdzanie szerokosci tekstu
        display.setCursor(64 - (xDlu / 2), txtY);       // ustawienie kursora dla środkowania
    }
    display.print(txtText);                           // wypisanie tekstu
}
