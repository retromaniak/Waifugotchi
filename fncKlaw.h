void shortSnd() {

    if (ustawienia[0] == 1) {
        digitalWrite(SPPIN, HIGH);    // beep
        delay(1);
        digitalWrite(SPPIN, LOW);     // cisza
    }
}
void alertSnd() {
    if (ustawienia[0] == 1) {
        digitalWrite(SPPIN, HIGH);    // beep
        if (ustawienia[2]) {
            delay(50);
        } else {
            delay(8);
        }
        digitalWrite(SPPIN, LOW);     // cisza
    }
}
void errSnd() {
    if (ustawienia[0] == 1) {
        digitalWrite(SPPIN, HIGH);    // beep
        if (ustawienia[2]) {
            delay(40);
        } else {
            delay(4);
        }
        digitalWrite(SPPIN, LOW);     // cisza
        delay(100);
        digitalWrite(SPPIN, HIGH);    // beep
        if (ustawienia[2]) {
            delay(70);
        } else {
            delay(10);
        }
        digitalWrite(SPPIN, LOW);     // cisza
    }
}

void checkKeys() { // sprawdzanie klawiszy
    keyu = 0;   // reset flagi
    keyd = 0;   // reset flagi
    keyl = 0;   // reset flagi
    keyr = 0;   // reset flagi
    keyc = 0;   // reset flagi

    // SPRAWDZANIE KOLEJNYCH PRZYCISKOW I USTAWIENIE TIMEOUTU EKRANU
    if (digitalRead(BUPIN) == HIGH) {
        keyu = 1;
        keyx = 1;   // dowolny klawisz
        Serial.println("U");
        shortSnd();

        if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
            ekrTOu = millis() + 60000;
        } else {
            ekrTOu = millis() + 300000;
        }
    }
    if (digitalRead(BDPIN) == HIGH) {
        keyd = 1;
        keyx = 1;
        Serial.println("D");
        shortSnd();

        if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
            ekrTOu = millis() + 60000;
        } else {
            ekrTOu = millis() + 300000;
        }
    }
    if (digitalRead(BLPIN) == HIGH) {
        keyl = 1;
        keyx = 1;
        Serial.println("L");
        shortSnd();

        if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
            ekrTOu = millis() + 60000;
        } else {
            ekrTOu = millis() + 300000;
        }
    }
    if (digitalRead(BRPIN) == HIGH) {
        keyr = 1;
        keyx = 1;
        Serial.println("R");
        shortSnd();

        if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
            ekrTOu = millis() + 60000;
        } else {
            ekrTOu = millis() + 300000;
        }
    }
    if (digitalRead(BCPIN) == HIGH) {
        keyc = 1;
        keyx = 1;
        Serial.println("C");
        shortSnd();

        if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
            ekrTOu = millis() + 60000;
        } else {
            ekrTOu = millis() + 300000;
        }
    }

    // SPRAWDZENIE PRZYCISKOW Z PORTU SZEREGOWEGO
    if (Serial.available() > 0) {
        byte tmpByte = Serial.read();
        if (tmpByte == 'W') {
            keyu = 1;
            keyx = 1;
            shortSnd();

            if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
                ekrTOu = millis() + 60000;
            } else {
                ekrTOu = millis() + 300000;
            }
        }
        if (tmpByte == 'X') {
            keyd = 1;
            keyx = 1;
            shortSnd();

            if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
                ekrTOu = millis() + 60000;
            } else {
                ekrTOu = millis() + 300000;
            }
        }
        if (tmpByte == 'A') {
            keyl = 1;
            keyx = 1;
            shortSnd();

            if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
                ekrTOu = millis() + 60000;
            } else {
                ekrTOu = millis() + 300000;
            }
        }
        if (tmpByte == 'D') {
            keyr = 1;
            keyx = 1;
            shortSnd();

            if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
                ekrTOu = millis() + 60000;
            } else {
                ekrTOu = millis() + 300000;
            }
        }
        if (tmpByte == 'S') {
            keyc = 1;
            keyx = 1;
            shortSnd();

            if (ustawienia[1]) {   // w zaleznosci od ustawienia timeoutu ustaw jego wartosc
                ekrTOu = millis() + 60000;
            } else {
                ekrTOu = millis() + 300000;
            }
        }
    }
    if (keyx) {
        ekrOds = 1; // wymuszenie odswiezenia ekranu
        //ekrTOu = millis() + 120000;
    }
}
