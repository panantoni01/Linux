## Zadanie 3
Przygotuj pendrive zawierający pojedynczą partycję MS-DOS rozciągającą się od 2048 sektora do końca urządzenia i zawierającą system plików FAT32 (tj. zupełnie zwyczajny pendrive). W pierwszych 446 bajtach MBR umieść program, który w razie próby uruchomienia przez BIOS systemu z tego pendrive’a wykona następujące czynności:
1. wypisze na ekranie (przerwanie ```int10h```) menu złożone z opcji:
    1 ) License
    2 ) Reboot
2. wczyta z klawiatury znak;
3. jeśli wybrano '1', to wypisze na ekran zawartość sektora 1 (bezpośrednio następującego po MBR); w sektorze tym należy umieścić test ASCII zawierający skróconą (żeby zmieściła się w 512B) treść licencji MIT i odczytywać go do pamięci za pomocą ```int13h```;
4. jeśli wybrano '2', to uruchomi ponownie BIOS (skacząc pod adres 0xffff0);
5. powróci do punktu 1.
Przyda się w tym zadaniu jakiś dobry asembler, np. **nasm** i przyzwoity *hex editor*.