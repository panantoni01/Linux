## Zadanie 1
Napisz skrypt, który raz na minutę wypisuje komunikaty do logów systemowych
(zob. ```logger(1)```) oraz na standardowe wyjście. Uruchom go w tle i zakończ pracę w konsoli. Zobacz, że skrypt zostanie zakończony poprzez wysłanie sygnału SIGHUP w chwili zamknięcia sesji. Uruchom go ponownie za pomocą programu ```nohup(1)``` i zobacz, że teraz będzie działał nadal po zamknięciu sesji.
Gdzie są zapisywane komunikaty, które skrypt wypisuje na standardowe wyjście? Jak teraz zakończyć
jego działanie? Zapoznaj się z poleceniem trap powłoki. Zmień skrypt tak, żeby teraz nie korzystał ze standardowego strumienia wyjściowego, ignorował sygnał SIGHUP, a po otrzymaniu sygnału SIGUSR1 wypisywał do logów komunikat o otrzymaniu tego sygnału i kończył działanie.

## Zadanie 2
Napisz skrypt, którego zadaniem jest bezcelowe zużywanie mocy obliczeniowej procesora, np. poprzez wykonywanie w pętli jakichś obliczeń. Skrypt powinien uruchamiać podaną podczas wywołania liczbę podprocesów tak, aby dało się obciążyć wszystkie rdzenie procesora. Uruchamiaj go z różnymi wartościami **niceness** (użyj polecenia ```nice(1)```) lub na bieżąco zmieniaj *niceness* działającego procesu (użyj polecenia ```renice(1)```) i zobacz, jaki ma to wpływ na działanie systemu.

## Zadanie 3
Napisz w C prosty program *mystat*, który periodycznie (domyślnie raz na sekundę) odczytuje z pseudopliku */proc/stat* obciążenie procesora (zob. ```proc(5)```) i co jakiś czas (domyślnie co 1 minutę) zapisuje uśrednione/maksymalne/minimalne wartości obciążenia do ustalonego pliku (domyślnie */var/log/mystat.log*). Podane domyślne wartości powinny być możliwe do zmiany
za pomocą opcji -p lub --period, -i lub --interval oraz -f lub --logfile (użyj ```getopt_long(3)```).