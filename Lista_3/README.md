## Zadanie 4
Wykorzystaj program ```getopt(1)``` w skrypcie *hwb*, którego zadaniem jest wypisywanie na ekranie pozdrowień typu *„Hello, world!”*. Dla każdego argumentu *imię* program powinien wypisać wiersz postaci:
```
Hello, imię !
```

Program powinien obsługiwać przynajmniej następujące opcje:

**-c, --capitalize** wypisanie imienia bądź słowa world wielką literą;

**--color=[never | auto | always]** kolorowanie imion (nigdy, tylko gdy standardowy strumień wyjściowy jest konsolą, zawsze), por. podobną opcję programu ```ls(1)```;

**-g text , --greeting=text** zastąpienie słowa Hello podanym tekstem;

**-h, --help** wypisanie krótkiej ściągi;

**-v, --version** wypisanie nazwy i wersji programu oraz copyrightu;

**-w, --world** wypisanie dodatkowo wiersza ```Hello, world!```

## Zadanie 5
Wykorzystując funkcję ```getopt_long(3)``` zaprogramuj w C program *hwc* działający podobnie do skryptu z zadania 4.

## Zadanie 6
Napisz stronę podręcznika ```hwb(1)```. Zastosuj konwencje opisane w rozdziale DESCRIPTION na stronie ```man(1)``` (w szczególności umieść co najmniej rozdziały NAME, SYNOPSIS, DESCRIPTION, OPTIONS, EXIT STATUS, EXAMPLE, AUTHORS i SEE ALSO oraz przestrzegaj
konwencji zapisywania niektórych fraz kursywą i pismem pogrubionym).