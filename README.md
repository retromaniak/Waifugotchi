# Waifugotchi
Oto i ona we własnej osobie, moja praca inżynierska która narodziła się z żartu człowieka pogrążonego w depresji spowodowanej nieodpowiednimi wyborami życiowymi. Żart nie został zrozumiany i dlatego, jakimś cudem, człowiek ten został inżynierem. Prototyp został zrobiony na mocne 30%, dlatego jest piekielnie niereprezentatywny. Nie przedłużając jednak do waszych rąk dostarczam końcowe coś... Przynajmniej końcowe dla mnie gdyż nie planuje kontynuować pracy nad tym pierdolnikiem.

Do poprawy zostało wiele elementów, jest tu zaimplementowana obsługa połączenia za pomocą WiFi, jednak nie działa gdyż ESP ma zbyt mało RAMu. Podobno można to łatwo obejść ale mi się nie chciało dlatego macie to co macie.

Grafiki są zrobione na odpierdol, ale jak ktoś ma zmysł graficzny to może przysiąść do GIMPa i narysować własne po czym wyeksportować je do formatu .xdg, następnie otworzyć go w notatniku, skopiować jego zawartość i wkleić do miejsca w pliku xmpData.h w którym daną grafikę chcemy zastąpić.

Jak wspomniałem wcześniej, ja projektu już ruszać nie będę więc róbcie z tym co chcecie. Jedna tylko prośba, umówmy się że kod jest udostępniany na licencji GNU GPL, uszanujcie zasady tej licencji, nie mam nic przeciwko zarabianu na stworzonych urządzeniach, rozumiem że trzeba włożyć czas, pieniądze i własną pracę w stworzenie obudów, poskładanie tego do kupy i nadanie formy, jednak chciałbym abyście nie próbowali zarabiać na kodzie i jego modyfikacjach. Chciałbym aby był on dostępny dla wszystkich, i jeżeli pojawi się chęć dalszego jego rozwoju, udostępniany wszystkim zainteresowanym nieodpłatnie.

## Uruchomienie tego syfu na ESP32
Potrzebujecie:
- Jakieś ESP32
- Ekran E-papierowy, ja użyłem z tego linku wersję 2,9": https://pl.aliexpress.com/item/1005004644515880.html?gatewayAdapt=glo2pol
- 5 przycisków lub jeden przycisk 5-kierunkowy
- Arduino IDE
- Biblioteki Adafruit GFX
- Biblioteki Adafruit Bus IO
- Biblioteki Wi-Fi Manager
- Biblioteki ESP32Time
- Biblioteki ESP32 Wi-Fi Manager
- Biblioteki GxEDP2
- Biblioteki obsługującej ESP32

Jeżeli wszystko posiadacie to należy połączyć wszystko ze sobą jak na schemacie dostępnym w pliku inżynierka.pdf, wrzucić wszystkie pliki do jednego folderu o nazwie wg i uruchomić w arduino IDE plik wg.ino, podłączyć ESP, wgrać program i gotowe... Możecie się cieszyć wyglądającym jak gówno prototypem ale za to nie w pełni funkcjonalnym. Resztę pozostawiam waszej wyobraźni.

# Zakończenie
Na koniec chciałbym podziękować człowiekowi bez którego ten projekt nigdy by nie powstał, był on nieocenioną pomocą przy jego tworzeniu.

P.S. Tak, nie chciało mi się wrzucać commita przez terminal dlatego nie macie ładnych folderków w githubie.
