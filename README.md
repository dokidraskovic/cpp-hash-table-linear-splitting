# Heš Tabela sa Linearnim Rasporedom - C++

Konzolna aplikacija u C++-u koja implementira **heš tabelu sa baketima i dinamičkim udvostručavanjem** (linear splitting hashing). Koristi se za čuvanje podataka o studentima (indeks, ime, položeni ispiti) sa svim standardnim operacijama heš tabele.

# Struktura podataka

# Heš tabela

Tabela se sastoji od niza **baketa** (Baket), pri čemu svaki baket može da sadrži `b` elemenata sortirano po ključu. Inicijalna veličina tabele je `2^p` baketa.

Svaki element tabele (`Elem`) sadrži:
- `indeks` - broj indeksa studenta (ključ)
- `ime` - ime i prezime studenta
- `ListaP` - ulančana lista šifri položenih ispita

# Adresna funkcija

Koristi se **linearni raspored sa podeljenom sekvencom** (`SplitSequenceLinearHashing`), implementiran kao polimorfna klasa koja nasleđuje apstraktnu klasu `AddressFunction`:

```
adresa = (h + s1 * i) % n    // za pozitivne vrednosti
adresa = (h + s2 * i) % |n|  // za negativne vrednosti
```

# Dinamičko rešavanje kolizija

Kada je baket pun pri ubacivanju novog elementa, tabela se **udvostručava** bit-pomeranjem: svaki baket na poziciji `i` dobija dva naslednika na pozicijama `2i` i `2i+1`, a novi element se umeće u odgovarajući od ta dva baketa prema vrednosti ključa.

# Format ulaznih podataka (CSV)

```
Indeks,Student,Ispiti
20190727,Andrea Mandic,13S111PP2
19950415,Nevena Jahic,13S113PS 13S112POS
```

Dostupni su priloženi fajlovi različitih veličina: 5, 10, 50, 150, 500, 1000, 5000, 10000, 50000 i 100000 zapisa.

# Opcije tokom rada

| Opcija | Opis |
|--------|------|
| `1` | Pretraga studenta po indeksu |
| `2` | Ubacivanje novog studenta |
| `3` | Brisanje studenta po indeksu |
| `4` | Brisanje svih studenata |
| `5` | Broj umetnutih ključeva |
| `6` | Veličina tabele (broj baketa) |
| `7` | Ispis cele tabele |
| `8` | Popunjenost tabele (faktor punjenja) |
| `9` | Dodavanje ispita studentu |
| `10` | Brisanje ispita studentu |
| `0` | Kraj programa |

# Arhitektura projekta

```
HashTable/
├── AddressFunction.h           # Apstraktna klasa adresne funkcije
├── SplitSequenceLinearHashing.h # Konkretna implementacija adresne funkcije
├── HashTable.h                 # Definicija klase HashTable, Baket, Elem
├── HashTable.cpp               # Implementacija svih metoda
├── main.cpp                    # Konzolni interfejs
└── students_N.csv              # Ulazni podaci (N = 5 do 100000)
```

# Pokretanje

# Zahtevi
- Windows operativni sistem
- Visual Studio (preporučuje se 2022)

# Koraci
1. Otvori `HashTable.sln` u Visual Studio-u
2. Kompajliraj projekat (`Ctrl+Shift+B`)
3. Pokreni sa `Ctrl+F5`
4. Unesi parametre `b` (kapacitet baketa) i `k` (inicijalna veličina tabele kao stepen dvojke)
5. Odaberi unos iz CSV fajla ili sa standardnog ulaza

