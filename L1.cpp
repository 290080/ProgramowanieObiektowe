#include <iostream>

using namespace std;

const int n = 10;

int znajdzPuste(string *tabNazwisko) {
    for (int i = 0; i < n; i++) {
        if (tabNazwisko[i].empty()) {
            return i;
        }
    }
}

int znajdzNazwisko(string nazwisko,  string *tabNazwisko) {
    for (int i = 0; i < n; i++) {
        if (tabNazwisko[i] == nazwisko) {
            return i;
        }
    }
}

void dodajOsobe(int *tabIndex, int index, string *tabImie, string imie, string *tabNazwisko, string nazwisko) {
    int i = znajdzPuste(tabNazwisko);
    tabImie[i] = imie;
    tabNazwisko[i] = nazwisko;
    tabIndex[i] = index;
}

void ustawObecnosc(string *tabNazwisko, bool *tabObecnosc, string nazwisko, bool obecnosc) {
    int i = znajdzNazwisko(nazwisko, tabNazwisko);
    tabObecnosc[i] = obecnosc;
}

void drukujListe(int *tabIndex, string *tabImie, string *tabNazwisko, bool *tabObecnosc) {
    cout << endl << "Nr INDEKSU    IMIE    NAZWISKO   OBECNOSC" << endl;
    for (int i = 0; i < n; i++) {
        if (!tabNazwisko[i].empty()) {
            cout << tabIndex[i] << "    " << tabImie[i] << "    " << tabNazwisko[i] << "    " << tabObecnosc[i] << endl;
        }
    }
}

void przesun(int index, int *tabIndex, string *tabImie, string *tabNazwisko, bool *tabObecnosc) {
    for (int i = index; i < n-1; i++) {
        tabNazwisko[i] = tabNazwisko[i + 1];
        tabImie[i] = tabImie[i + 1];
        tabObecnosc[i] = tabObecnosc[i + 1];
        tabIndex[i] = tabIndex[i + 1];
    }
}

void usunOsobe(string nazwisko, int *tabIndex, string *tabImie, string *tabNazwisko, bool *tabObecnosc) {
    int i = znajdzNazwisko(nazwisko, tabNazwisko);
    przesun (i, tabIndex, tabImie, tabNazwisko, tabObecnosc);
}

void edytujOsobe(string nazwisko, int *tabIndex, string *tabImie, string *tabNazwisko, bool *tabObecnosc, int newIndex, string newImie, string newNazwisko, bool newObecnosc) {
    int i  = znajdzNazwisko(nazwisko, tabNazwisko);
    tabImie[i] = newImie;
    tabNazwisko[i] = newNazwisko;
    tabIndex[i] = newIndex;
    tabObecnosc[i] = newObecnosc;
}

int main() {
    int tabIndex[n];
    string tabImie[n];
    string tabNazwisko[n];
    bool tabObecnosc[n];

    dodajOsobe(tabIndex, 123456, tabImie, "Katarzyna", tabNazwisko, "Kowalska");
    ustawObecnosc(tabNazwisko, tabObecnosc, "Kowalska", 1);

    dodajOsobe(tabIndex, 234567, tabImie, "Malgorzata", tabNazwisko, "Nowak");
    ustawObecnosc(tabNazwisko, tabObecnosc, "Nowak", 0);

    dodajOsobe(tabIndex, 345678, tabImie, "Sandra", tabNazwisko, "Migielska");
    ustawObecnosc(tabNazwisko, tabObecnosc, "Migielska", 1);

    dodajOsobe(tabIndex, 456789, tabImie, "Pola", tabNazwisko, "Tyburska");
    ustawObecnosc(tabNazwisko, tabObecnosc, "Tyburska", 1);

    usunOsobe("Kowalska", tabIndex, tabImie, tabNazwisko, tabObecnosc);

    edytujOsobe("Nowak", tabIndex, tabImie, tabNazwisko, tabObecnosc, 123456, "Patryk", "Marek", 0);

    drukujListe(tabIndex, tabImie, tabNazwisko, tabObecnosc);

    return 0;
}
