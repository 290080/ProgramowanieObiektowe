#include <iostream>

using namespace std;

//========= Klasa osoby ===========

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

//========= Klasa listy Obecnosci ============

class ListaObecnosci {
    bool tabObecnosc[10];
    Osoba tabOsob[10];

    int znajdzPusteMiejsce() {
        for (int i = 0; tabOsob[i].getNazwisko() == ""; i++) {
            return i;
        }
        return -1;
    }

    int znajdzOsobe(string nazwisko) {
        for (int i = 0; tabOsob[i].getNazwisko() == nazwisko; i++) {
            return i;
        }
        return -1;
    }

public:
    void dodajOsobe(Osoba nowa_osoba) {
        int i = znajdzPusteMiejsce();
        tabOsob[i] = nowa_osoba;
    }

    void drukujListe() {
        cout << endl << "Nr INDEKSU    IMIE    NAZWISKO   OBECNOSC" << endl;
        for (int i = 0; tabOsob[i].getNazwisko() != ""; i++) {
            cout << tabOsob[i].getIndeks() << "    " << tabOsob[i].getImie() << "    " << tabOsob[i].getNazwisko() << "    " << tabObecnosc[i] << endl;
        }
    }

    void ustawObecnosc(string nazwisko, bool nowa_obecnosc) {
        int i = znajdzOsobe(nazwisko);
        int j = znajdzPusteMiejsce();
        tabOsob[j] = tabOsob[i];
        tabObecnosc[j] = nowa_obecnosc;

        cout << "ustawiam obecnosc \n";
    }
};

//=========== Klasa interfejsu uzytkownika =============

class InterfejsUzytkownika {
    Osoba *tablicaOsob;
    ListaObecnosci *tablicaList;
    int ileOsob, ileList;
    int wybor;

    int znajdzPuste() {
        for (int i = 0; i < ileOsob; i++) {
            if (tablicaOsob[i].getNazwisko().empty()) {
                return i;
            }
        }
        return -1;
    }

    int znajdzNazwisko(string nazwisko) {
        for (int i = 0; i < ileOsob; i++) {
            if (tablicaOsob[i].getNazwisko() == nazwisko) {
                return i;
            }
        }
        return -1;
    }

    void utworzOsobe() {
        int indeks;
        string imie;
        string nazwisko;
        Osoba nowa_osoba;

        cout << "Podaj indeks: ";
        cin >> indeks;
        nowa_osoba.setIndeks(indeks);

        cout << "Podaj imie: ";
        cin >> imie;
        nowa_osoba.setImie(imie);

        cout << "Podaj nazwisko: ";
        cin >> nazwisko;
        nowa_osoba.setNazwisko(nazwisko);

        int i = znajdzPuste();
        tablicaOsob[i] = nowa_osoba;
    }

    void dodajOsobe() {
        string nazwisko;
        int lista;

        cout << "Kogo chcesz dodac (podaj nazwisko): ";
        cin >> nazwisko;

        cout << "Do ktorej listy: ";
        cin >> lista;

        int i = znajdzNazwisko(nazwisko);
        tablicaList[lista].dodajOsobe(tablicaOsob[i]);
    }

    void ustawObecnosc() {
        string nazwisko;
        int lista;
        bool obecnosc;

        cout << "Komu chcesz ustawic obecnosc (podaj nazwisko): ";
        cin >> nazwisko;

        cout << "W ktorej liscie: ";
        cin >> lista;

        cout << "Ustaw obecnosc: ";
        cin >> obecnosc;

        tablicaList[lista].ustawObecnosc(nazwisko, obecnosc);
    }

    void przesun(int index) {
        for (int i = index; i < ileOsob-1; i++) {
            tablicaOsob[i].setIndeks( tablicaOsob[i + 1].getIndeks() );
            tablicaOsob[i].setNazwisko( tablicaOsob[i + 1].getNazwisko() );
            tablicaOsob[i].setImie( tablicaOsob[i + 1].getImie() );
        }
        tablicaOsob[ileOsob-1].setIndeks( 0 );
        tablicaOsob[ileOsob-1].setNazwisko( "" );
        tablicaOsob[ileOsob-1].setImie( "" );
    }

    void usunOsobe() {
        string nazwisko;

        cout << "Kogo chcesz usunac (podaj nazwisko): ";
        cin >> nazwisko;

        int i = znajdzNazwisko(nazwisko);
        przesun (i);
    }

    void edytujOsobe() {
        string nazwisko;
        int nowy_indeks;
        string nowe_nazwisko;
        string nowe_imie;
        Osoba nowa_osoba;

        cout << "Kogo chcesz edytowac (podaj nazwisko): ";
        cin >> nazwisko;
        int i = znajdzNazwisko(nazwisko);

        cout << "Podaj nowy indeks: ";
        cin >> nowy_indeks;
        tablicaOsob[i].setIndeks(nowy_indeks);

        cout << "Podaj nowe imie: ";
        cin >> nowe_imie;
        tablicaOsob[i].setImie(nowe_imie);

        cout << "Podaj nowe nazwisko: ";
        cin >> nowe_nazwisko;
        tablicaOsob[i].setNazwisko(nowe_nazwisko);
    }

    void wyswietlListe() {
        int lista;
        cout << "Ktora liste chcesz wyswietlic: ";
        cin >> lista;

        system("clear");

        tablicaList[lista].drukujListe();
    }

public:

    InterfejsUzytkownika(Osoba *tbos, int os, ListaObecnosci *tbls, int ls) : tablicaOsob(tbos), ileOsob(os), tablicaList(tbls), ileList(ls) {}

    //============== Petla ===============

    void petla() {
        while(true) {
            cout << "=============================\n";
            cout << "========== M E N U ==========\n \n";

            cout << "1. Utworz osobe\n";
            cout << "2. Dodaj osobe do listy\n";
            cout << "3. Ustaw obecnosc osoby na liscie\n";
            cout << "4. Usun osobe z listy\n";
            cout << "5. Zmien dane osoby\n";
            cout << "6. Wyswietl liste\n \n";

            cout << "Wybierz: ";
            cin >> wybor;

            system("clear");

            switch(wybor) {
                case 1:
                    utworzOsobe();
                    system("clear");
                    break;
                case 2:
                    dodajOsobe();
                    system("clear");
                    break;
                case 3:
                    ustawObecnosc();
                    system("clear");
                    break;
                case 4:
                    usunOsobe();
                    system("clear");
                    break;
                case 5:
                    edytujOsobe();
                    system("clear");
                    break;
                case 6:
                    wyswietlListe();
                    break;
                default: 
                    system("clear");
                    cout << endl << "Brak takiej opcji." << endl;
                    break;
            };
        }
    };
};

//============ MAIN ============

int main() {

    Osoba tablicaOsob[10];
    ListaObecnosci tablicaList[2];
    InterfejsUzytkownika ui(tablicaOsob, 10, tablicaList, 2);

    ui.petla();

    return 0;
}
