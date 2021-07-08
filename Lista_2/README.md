
## Zadanie 2
Zaprogramuj skrypt *getdev*, który uruchomiony z argumentem będącym ścieżką dostępu do punktu montowania wypisze informacje o urządzeniu blokowym skonfigurowanym do montowania w danym miejscu wraz z parametrami montowania, np. jeśli w pliku ```/etc/fstab``` znajduje się wiersz:
UUID=b121b129-3402-5fd3-ea55-431f03747cc9 /boot ext2 defaults 0 2

to polecenie getdev /boot wypisze:
```
Device: UUID=b121b129-3402-5fd3-ea55-431f03747cc9
Filesystem type: ext2
Mount options: defaults
Dump freqency: 0
Fsck pass number: 2
```

## Zadanie 4
(proste sito Erastotenesa)

## Zadanie 5
Podczas generowania kluczy RSA warto obserwować ilość dostępnej entropii w systemie. Jądro Linuksa ujawnia informacje dotyczące generatora losowego w katalogu ```/proc/sys/kernel/random/```
W pliku *poolsize* jest zapisany rozmiar puli losowości, zaś w pliku *entropy_avail* — aktualna entropia
tej puli. Napisz skrypt *watch-entropy*, który będzie co sekundę wypisywał wiersz postaci
```
Available entropy: entropy_avail /poolsize
```

## Zadanie 7
Jeśli musimy skopiować duży plik lub katalog, to może się on nie zmieścić w wybranym systemie plików. Polecenie ```du(1)``` podaje łączny rozmiar zbioru plików. Polecenie ```df(1)``` ujaw-
nia zamontowane systemy plików oraz, m. in., ilość wolnego miejsca w tych systemach. Napisz skrypt *where-fits*, którego argumentami powinny być nazwy plików i katalogów, który wypisze listę zamontowanych systemów plików, w których podane pliki i katalogi się (jednocześnie) zmieszczą.