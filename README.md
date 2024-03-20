# Symulator Sensorów

## Opis
Program napisany w C++, oparty o wielowątkowość oraz sockety z zachowaną strukturą obiektową.
Klasa Symulator odpowiada za tworzenie instancji symulatora - każdy składa się z zadanej w pliku konfiguracyjnym liczby socketów które później - po symulacji wyników i przypisaniu ich do odpowiednich jakości za pomocą klasyfikatora - w funkcji transmit nawiązują połączenie z odbiornikiem oraz wysyłają do niego "zaszyfrowaną" wiadomość.
Klasa Receiver tworzy instancje odbiornika - każdy składa się z jednego socketa, który nasłuchuje telegramu z naszego symulatora, następnie dekoduje go za pomocą funkcji decode oraz printuje wyniki. Printowane wyniki objęte są mutexem aby console logi nie kolidowały ze sobą na większej ilości wątków, bądź wysokich częstotliowściach symulacji. 
Klasa Classifier - bardzo prosta klasa, która za pomocą funkcji wywoływanej statycznie klasyfikuje i zwraca poprawną jakość dla zadanych wartości
W mainie tworzymy zadaną w pliku konfiguracyjnym ilość Odbiorników - aktywne, które nasłuchują na swoim przypisanym porcie oraz nieaktywne, które nie nasłuchują żadnego Symulatora. Następnie tworzymy zadaną w pliku konfiguracyjnym ilość symulatorów, do których przypisujemy sensor oraz porty na które będą wysyłane telegramy(od 0 do N). Każda instancja symulatora oraz odbiornika działa na osobnym wątku + każdy socket w symulatorze również wysyła X telegramów za pomocą wielu wątków.
Po treści zadania nie mogłem jednoznacznie wywnioskować czy program ma działać na zasadzie Serwer + Klient, dlatego też zrobiłem wszystko w jednym programie(wywołanie przez jednego main.exe), bo bardziej przejrzyście to wygląda i nie zmnienia wg. mnie w żaden sposób funkcjonalności

## Wymagania
- System operacyjny: Linux
- Kompilator obsługujący standard C++11 lub nowszy
- Biblioteka JSON (np. nlohmann/json) - [instrukcje instalacji](https://github.com/nlohmann/json#package-managers) - dołączony jest plik nagłówkowy do kodu źrodłowego, który powinien wystarczyć bez doinstalowywania żadnych dodatkowych pakietów

## Instalacja i Uruchomienie
1. Sklonuj lub pobierz repozytorium na swój lokalny komputer.
2. Skompiluj program za pomocą polecenia `make`.
3. Upewnij się, że pliki konfiguracyjne `receiverConfig.json` i `sensorConfig.json` są dostępne i poprawnie skonfigurowane.
4. Uruchom program, wykonując plik wykonywalny.

Opcjonalnie jakby jakimś cudem były problemy, dołączyłem plik main.exe, który można po prostu odpalić i program powinien działać.

## Autorzy

- Grzegorz Sawiński 
