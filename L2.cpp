#include <iostream>

using namespace std;

const int n = 10;

class Osoba {
private:
    int nr_indeksu;
    string imie;
    string nazwisko;

public:
    Osoba(int inx = 0, string im = "", string naz = "") : nr_indeksu(inx), imie(im), nazwisko(naz) {};

    void setIndeks(int nowy_indeks) { nr_indeksu = nowy_indeks; }
    void setImie (string nowe_imie) { imie = nowe_imie; }
    void setNazwisko (string nowe_nazwisko) { nazwisko = nowe_nazwisko; }

    int getIndeks() { return nr_indeksu; }
    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
};

int znajdzPuste(Osoba *tabOsoba) {
    for (int i = 0; i < n; i++) {
        if (tabOsoba[i].getNazwisko().empty()) {
            return i;
        }
    }
    return -1;
}

int znajdzNazwisko(string nazwisko,  Osoba *tabOsoba) {
    for (int i = 0; i < n; i++) {
        if (tabOsoba[i].getNazwisko() == nazwisko) {
            return i;
        }
    }
    return -1;
}

int znajdzPusteWsk(Osoba **lista) {
    for (int i = 0; i < n; i++) {
        if (lista[i] == nullptr) {
            return i;
        }
    }
    return -1;
}

void dodajOsobe(Osoba *tabOsoba, Osoba nowa_osoba) {
    int i = znajdzPuste(tabOsoba);
    tabOsoba[i] = nowa_osoba;
}

void ustawObecnosc(Osoba *tabOsoba, Osoba **listaOsob, bool *tabObecnosc, string nazwisko, bool obecnosc) {
    int i = znajdzNazwisko(nazwisko, tabOsoba);
    int j = znajdzPusteWsk(listaOsob);
    listaOsob[j] = &tabOsoba[i];
    tabObecnosc[j] = obecnosc;
}

void drukujListe(Osoba **tabOsoba, bool *tabObecnosc) {
    cout << endl << "Nr INDEKSU    IMIE    NAZWISKO   OBECNOSC" << endl;
    for (int i = 0; i < n; i++) {
        if (tabOsoba[i] != nullptr) {
            cout << tabOsoba[i]->getIndeks() << "    " << tabOsoba[i]->getImie() << "    " << tabOsoba[i]->getNazwisko() << "    " << tabObecnosc[i] << endl;
        }
    }
}

void przesun(int index, Osoba *tabOsoba, bool *tabObecnosc) {
    for (int i = index; i < n-1; i++) {
        tabOsoba[i].setIndeks( tabOsoba[i + 1].getIndeks() );
        tabOsoba[i].setNazwisko( tabOsoba[i + 1].getNazwisko() );
        tabOsoba[i].setImie( tabOsoba[i + 1].getImie() );
        tabObecnosc[i] = tabObecnosc[i + 1];
    }
}

void usunOsobe(string nazwisko, Osoba *tabOsoba, bool *tabObecnosc) {
    int i = znajdzNazwisko(nazwisko, tabOsoba);
    przesun (i, tabOsoba, tabObecnosc);
}

void edytujOsobe(Osoba *tabOsoba, bool *tabObecnosc, string nazwisko, Osoba nowa_osoba, bool nowa_obecnosc) {
    int i  = znajdzNazwisko(nazwisko, tabOsoba);
    tabOsoba[i] = nowa_osoba;
    tabObecnosc[i] = nowa_obecnosc;
}

int main() {
    Osoba tabOsoba[n];

    Osoba nowa_osoba(247833, "Jan", "Kowalski");

    dodajOsobe(tabOsoba, nowa_osoba);

    nowa_osoba.setIndeks(256374);
    nowa_osoba.setImie("Katarzyna");
    nowa_osoba.setNazwisko("Nowak");
    dodajOsobe(tabOsoba, nowa_osoba);

    nowa_osoba.setIndeks(239086);
    nowa_osoba.setImie("Paweł");
    nowa_osoba.setNazwisko("Pawlak");
    dodajOsobe(tabOsoba, nowa_osoba);

    nowa_osoba.setIndeks(263945);
    nowa_osoba.setImie("Stanisław");
    nowa_osoba.setNazwisko("Tyburski");
    dodajOsobe(tabOsoba, nowa_osoba);

    // =======  Lista nr 1 ==========

    Osoba *listaOsob1[n] = {nullptr};
    bool tabObecnosc1[n] = {false};

    ustawObecnosc(tabOsoba, listaOsob1, tabObecnosc1, "Tyburski", 1);
    ustawObecnosc(tabOsoba, listaOsob1, tabObecnosc1, "Pawlak", 0);
    ustawObecnosc(tabOsoba, listaOsob1, tabObecnosc1, "Nowak", 1);

    drukujListe(listaOsob1, tabObecnosc1);

    // =======  Lista nr 2 ==========

    Osoba *listaOsob2[n] = {nullptr};
    bool tabObecnosc2[n] = {false};

    ustawObecnosc(tabOsoba, listaOsob2, tabObecnosc2, "Nowak", 0);
    ustawObecnosc(tabOsoba, listaOsob2, tabObecnosc2, "Pawlak", 1);

    drukujListe(listaOsob2, tabObecnosc2);

    return 0;
}
