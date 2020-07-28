#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
struct Adresat
{
    int idAdresata, idUzytkownika;
    string imie, nazwisko, numerTelefonu, email, adres;
};

struct Uzytkownik
{
    int id;
    string login, haslo;
};

string konwerjsaIntNaString (int liczba)
{
    ostringstream ss;
    ss << liczba;
    string lancuch = ss.str();
    return lancuch;
}

void sprawdzIstnieniePlikuZewnetrznego ()
{
    char nazwaPlikuKontaktow[ ] = "KsiazkaAdresowa.txt";

    string linia="";
    fstream plik;
    plik.open(nazwaPlikuKontaktow, fstream::in | fstream::out);
    if (!plik)
    {
        cout << "Tworze plik KsiazkaAdresowa.";
        Sleep(1000);
        plik.open(nazwaPlikuKontaktow,  fstream::in | fstream::out | fstream::trunc);
        plik.close();
    }
    else
    {
        plik.close();
    }
}
void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string login, haslo;
    int id;
    string liniaZDanymiUzytkownika = "";
    Uzytkownik Osoba;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        while(itr -> login == login)
        {
            cout << "Podany uztkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> login;
        }
    }

    cout << "Podaj haslo: ";
    cin >> haslo;

    if (uzytkownicy.empty() == true)
    {
        Osoba.id = 1;
    }
    else
    {
        Osoba.id = uzytkownicy.back().id + 1;
    }

    Osoba.login = login;
    Osoba.haslo = haslo;

    uzytkownicy.push_back(Osoba);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> id) + '|';
            liniaZDanymiUzytkownika += itr -> login + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
    }
    cout<< "Konto zalozone." <<endl;
    Sleep(1000);
}
int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string loginUzytkownika, hasloUzytkownika;
    bool znalezionyUzytkownik = 0;
    int proby = 0;
    cout << "Podaj login: ";
    cin >>  loginUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> login == loginUzytkownika)
        {
            znalezionyUzytkownik = 1;
            for(int iloscProb = 0; iloscProb < 3; iloscProb++)
            {
                proby = iloscProb + 1;
                cout << "Podaj haslo. Pozostalo prob " << 3 - iloscProb << ":";
                cin >> hasloUzytkownika;
                if (itr -> haslo == hasloUzytkownika)
                {
                    cout<< "Jestes zalogowany."<<endl;
                    return itr -> id;
                }
            }
            if( proby == 3)
            {
                cout << "Podales bledne haslo.Wprowadz ponownie haslo." << endl;
            }
        }
    }

    if(!znalezionyUzytkownik)
    {
        cout << "Nie ma uzytkownika z takim loginem." << endl;
    }

    Sleep(1500);
    return 0;
}
void zapiszDaneUzytkownikaDoPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string liniaZDanymiUzytkownika = "";
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> id) + '|';
            liniaZDanymiUzytkownika += itr -> login + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku." << endl;
        system("pause");
    }
}
void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    string linia;
    string dane;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int iloscUzytkownikow = 0;
    fstream plik;
    Uzytkownik pusty;

    uzytkownicy.clear();
    plik.open("Uzytkownicy.txt",ios::in);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            uzytkownicy.push_back(pusty);
            iloscUzytkownikow++;
            ileZnakowWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (int i = 0; i < linia.size(); i++)
            {
                ileZnakowWyjac = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscPionowychKresek++;
                    dane = linia.substr (poczatek,ileZnakowWyjac);
                    switch (iloscPionowychKresek)
                    {
                    case 1:
                        uzytkownicy[iloscUzytkownikow - 1].id = atoi(dane.c_str());
                        break;
                    case 2:
                        uzytkownicy[iloscUzytkownikow - 1].login = dane;
                        break;
                    case 3:
                        uzytkownicy[iloscUzytkownikow - 1].haslo = dane;
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
        }
        plik.close();
    }
}
void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika, int iloscUzytkownikow)
{

    system("cls");
    string noweHaslo;
    int pozycjaOsoby = 0;
    cout << "Wprowadz nowe haslo: " << endl;
    while(true)
    {
        cin >> noweHaslo;
        for (vector <Uzytkownik> :: iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            if (itr -> id == idZalogowanegoUzytkownika)
            {
                if (itr -> haslo == noweHaslo)
                {
                    system("cls");
                    cout << "Wprowadz nowe haslo:" << endl;
                }
                else
                {
                    itr -> haslo = noweHaslo;
                    uzytkownicy[pozycjaOsoby].haslo = noweHaslo;
                    cout << "Haslo zostalo zmienione."<< endl;
                    Sleep(2000);
                    return;
                }
            }
        }
    }
}
int wylogujUzytkownika (vector <Adresat> &adresat, int idZalogowanegoUzytkownika)
{

    char wyborFunkcji;
    cout << "Czy na pewno chcesz sie wylogowac (t/n)?" << endl;

    while (true)
    {
        cin >> wyborFunkcji;
        if (wyborFunkcji == 't')
        {
            idZalogowanegoUzytkownika = 0;
            adresat.clear();
            cout << "Poprawnie wylogowano.";
            Sleep(2000);
            return idZalogowanegoUzytkownika;
        }
        else if (wyborFunkcji == 'n')
        {
            return idZalogowanegoUzytkownika;
        }
        else
        {
            system("cls");
            cout << "Czy na pewno chcesz sie wylogowac (t/n)?" << endl;
        }
    }
}
void zapiszDoPlikuTymczasowego (Adresat poprawionyAdresat) {

    fstream plikTymczasowy;
    plikTymczasowy.open("KsiazkaAdresowaTymczasowa.txt", ios::out | ios::app);

    plikTymczasowy << poprawionyAdresat.idAdresata<< "|" << poprawionyAdresat.idUzytkownika << "|" << poprawionyAdresat.imie << "|" << poprawionyAdresat.nazwisko << "|" << poprawionyAdresat.numerTelefonu << "|" << poprawionyAdresat.email << "|" << poprawionyAdresat.adres << "|" << endl;
    plikTymczasowy.close();
}

void zapiszEdytowanaOsobeDoPlikuTymczasowego (vector <Adresat> adresat, int idDoEdycji) {
    fstream plikTymczasowy;
    plikTymczasowy.open("KsiazkaAdresowaTymczasowa.txt", ios::out | ios::app);

    for (vector <Adresat> :: iterator itr = adresat.begin(); itr != adresat.end(); itr++) {
        if ( itr -> idAdresata == idDoEdycji) {
            plikTymczasowy << itr -> idAdresata << "|" << itr -> idUzytkownika << "|" << itr ->  imie << "|" << itr ->  nazwisko << "|" << itr ->  numerTelefonu << "|" << itr ->  email << "|" << itr ->  adres << "|" << endl;
        }
    }
    plikTymczasowy.close();
}
void zapiszEdycjeDoPliku(vector <Adresat> adresat, int idDoEdycji) {

    int nr_linii = 1;
    string linia;
    bool czyLiczbaRownaID = false;
    Adresat daneDoWczytania;
    fstream plikZDanymi;
    plikZDanymi.open("KsiazkaAdresowa.txt", ios::in);

    while (getline(plikZDanymi,linia,'|')) {
        if (linia == "") {
            return;
        }
        switch(nr_linii) {
        case 1:
            if  (atoi(linia.c_str()) == idDoEdycji) {
                czyLiczbaRownaID = true;
            } else {
                daneDoWczytania.idAdresata = atoi(linia.c_str());
            };
            break;

        case 2:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.idUzytkownika = atoi(linia.c_str());
            }
            break;

        case 3:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.imie = linia;
            }
            break;

        case 4:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.nazwisko = linia;
            }
            break;

        case 5:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.numerTelefonu = linia;
            }
            break;

        case 6:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.email = linia;
            }
            break;

        case 7:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.adres = linia;
            }
            break;
        }
        if (nr_linii == 7) {
            if (czyLiczbaRownaID == false) {
                zapiszDoPlikuTymczasowego(daneDoWczytania);
            } else {
                zapiszEdytowanaOsobeDoPlikuTymczasowego(adresat, idDoEdycji);
            }
            czyLiczbaRownaID = false;
            nr_linii = 0;
        }
        nr_linii ++;
    }
    plikZDanymi.close();
    remove ("KsiazkaAdresowa.txt");
    rename ("KsiazkaAdresowaTymczasowa.txt","KsiazkaAdresowa.txt");
}
void wyswietlDaneAdresata (const Adresat &daneAdresata)
{

    cout << endl;
    cout << "Numer ID: " << daneAdresata.idAdresata << endl;
    cout << "Imie: " << daneAdresata.imie << endl;
    cout << "Nazwisko: " << daneAdresata.nazwisko << endl;
    cout << "Numer telefonu: " << daneAdresata.numerTelefonu << endl;
    cout << "E-mail: " << daneAdresata.email << endl;
    cout << "Adres: " << daneAdresata.adres << endl;
    cout << endl;


}
bool sprawdzCzyPodaneIdIstnieje (vector <Adresat> adresat,int idDoEdycji) {

    bool sprawdzacz = false;
    for (vector <Adresat> :: iterator itr = adresat.begin(); itr != adresat.end(); itr++) {
        if (itr -> idAdresata == idDoEdycji) {
            sprawdzacz = true;
        }
    }
    return sprawdzacz;
}
void edytujKontakt (vector <Adresat> &adresat)
{
    string imie, nazwisko, numerTelefonu, email, adres;
    char pozycjaMenu;

    int szukanyNumerID;
    bool znalezionyAdresat = 0;
    int pozycjaZnalezionejOsoby = 0;


    cout << "Wyszukanie adresata. Podaj numer jego ID: ";
    cin >> szukanyNumerID;

    for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if (itr -> idAdresata == szukanyNumerID)
        {
            znalezionyAdresat = 1;
            system("cls");
            cout << "Edycja kontaktu." << endl;
            cout << "Zmien imie: " << itr -> imie << endl;
            cout << "Zmien nazwisko: " << itr -> nazwisko << endl;
            cout << "Zmien Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Zmien E-mail: " << itr -> email << endl;
            cout << "Zmien Adres: " << itr -> adres << endl;
            cout << endl;
            cout << "1.Edytuj imie." << endl;
            cout << "2.Edytuj nazwisko." << endl;
            cout << "3.Edytuj numer telefonu." << endl;
            cout << "4.Edytuj adres emailowy." << endl;
            cout << "5.Edytuj adres kontaktowy." << endl;
            cout << "6.Edytuj wszystkie informacje." << endl;
            cout << "7.Zakoncz edycje." << endl<<endl;
            cin>> pozycjaMenu;

            switch(pozycjaMenu)
            {
            case '1':
                cout << "Podaj nowe imie: ";
                cin.sync();
                getline(cin,imie);
                adresat[pozycjaZnalezionejOsoby].imie = imie;
                break;
            case '2':
                cout << "Podaj nowe nazwisko: ";
                cin >>  nazwisko;
                adresat[pozycjaZnalezionejOsoby].nazwisko = nazwisko;
                break;
            case '3':
                cout << "Podaj nowy numer telefonu: ";
                cin >>  numerTelefonu;
                adresat[pozycjaZnalezionejOsoby].numerTelefonu = numerTelefonu;
                break;
            case '4':
                cout << "Podaj nowy e-mail: ";
                cin >>  email;
                adresat[pozycjaZnalezionejOsoby].email = email;
                break;
            case '5':
                cout << "Podaj nowy adres kontaktowy: ";
                cin.sync();
                getline(cin,adres);
                adresat[pozycjaZnalezionejOsoby].adres = adres;
                break;
            case '6':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin,numerTelefonu);
                cout << "Podaj nowy adres e-mailowy: ";
                cin >>  email;
                cout << "Podaj nowy adres kontaktowy: ";
                cin.sync();
                getline(cin,adres);

                adresat[pozycjaZnalezionejOsoby].numerTelefonu = numerTelefonu;
                adresat[pozycjaZnalezionejOsoby].email = email;
                adresat[pozycjaZnalezionejOsoby].adres = adres;
                break;
            case '7':
                system("pause");
                break;
            }
            cout << "Edycja kontaktu powiodla sie." << endl << endl;

        }
        pozycjaZnalezionejOsoby++;
    }

    if(!znalezionyAdresat)
    {
        cout << endl << "Nie znaleziono osoby o podanym ID." << endl << endl;
        system("pause");
    }
}
void usunLinieZPliku (int iloscOsob) {

    int idDoUsuniecia;
    int nr_linii = 1;
    string linia;
    bool czyLiczbaRownaID = false;
    Adresat usuwanyAdresat;
    fstream plikZDanymi;
    plikZDanymi.open("KsiazkaAdresowa.txt", ios::in);

    while (getline(plikZDanymi,linia,'|')) {
        if (linia == "") {
            return;
        }
        switch(nr_linii) {
        case 1:
            if  (atoi(linia.c_str()) == idDoUsuniecia) {
                czyLiczbaRownaID = true;
            } else {
                usuwanyAdresat.idAdresata = atoi(linia.c_str());
            };
            break;
        case 2:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.idUzytkownika = atoi(linia.c_str());
            }
            break;
        case 3:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.imie = linia;
            }
            break;
        case 4:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.nazwisko = linia;
            }
            break;
        case 5:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.numerTelefonu = linia;
            }
            break;
        case 6:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.email = linia;
            }
            break;
        case 7:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.adres = linia;
            }
            break;
        }

        if (nr_linii == 7) {

            if (czyLiczbaRownaID == false) {
                zapiszDoPlikuTymczasowego (usuwanyAdresat);
            }
            czyLiczbaRownaID = false;
            nr_linii = 0;
        }
        nr_linii ++;
    }
    plikZDanymi.close();
    remove ("KsiazkaAdresowa.txt");
    rename ("KsiazkaAdresowaTymczasowa.txt","KsiazkaAdresowa.txt");
}
int znajdzOstatniNumerIDAdresata ()
{
    string linia;
    string dane;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int najwiekszyNumerID = 0;
    int aktualnyNumerID = 0;
    int kolejnyNumerID = 0;
    fstream plik;

    plik.open("KsiazkaAdresowa.txt",ios::in);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            ileZnakowWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (int i = 0; i < linia.size(); i++)
            {
                ileZnakowWyjac = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscPionowychKresek++;
                    dane = linia.substr (poczatek, ileZnakowWyjac);
                    aktualnyNumerID = atoi(dane.c_str());
                    if ( iloscPionowychKresek == 1 )
                    {
                        if (aktualnyNumerID > najwiekszyNumerID)
                        {
                            najwiekszyNumerID = aktualnyNumerID;
                        }
                    }
                }
            }
        }
    }
    kolejnyNumerID = najwiekszyNumerID + 1;
    return kolejnyNumerID;

}
void zapiszNowaOsobeDoPliku(Adresat pomocnicza) {

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << pomocnicza.idAdresata<< "|" << pomocnicza.idUzytkownika << "|" << pomocnicza.imie << "|" << pomocnicza.nazwisko << "|" << pomocnicza.numerTelefonu << "|" << pomocnicza.email << "|" << pomocnicza.adres << "|" << endl;
    }
    plik.close();
}
void wyswietlAdresataZPodanymImieniem(Adresat szukanyAdresat, string imie, bool &wyszukanoAdresatow)
{
    if (imie == szukanyAdresat.imie)
    {
        wyswietlDaneAdresata(szukanyAdresat);
        wyszukanoAdresatow = 1;
    }
}

void szukajPoImieniu(vector <Adresat> &adresat)
{

    string imie = "";
    int iloscAdresatow=0;
    bool wyszukanoAdresatow = 0;
    cout << endl << "Podaj imie: ";
    cin >> imie;

    vector <Adresat> :: iterator poczatek;
    system("cls");
    for (poczatek = adresat.begin(); poczatek != adresat.end(); poczatek ++)
    {
        wyswietlAdresataZPodanymImieniem(*poczatek, imie, wyszukanoAdresatow);
    }
    if (iloscAdresatow == 1)
    {
        system("pause");
    }
    else
    {
        cout << "Nie znaleziono adresatow o danym imieniu" << endl;
        Sleep(2000);
    }
}
void wyswietlAdresataZIPodanymNazwiskiem(Adresat szukanyAdresat, string nazwisko, bool &wyszukanoAdresatow)
{
    if (nazwisko == szukanyAdresat.nazwisko)
    {
        wyswietlDaneAdresata(szukanyAdresat);
        wyszukanoAdresatow = 1;
    }
}

void szukajPoNazwisku(vector <Adresat> &adresat)
{
    string nazwisko= "";
    int iloscAdresatow;
    bool wyszukanoAdresatow = 0;
    cout << endl << "Podaj nazwisko: ";
    cin >> nazwisko;

    vector <Adresat> :: iterator poczatek;
    system("cls");
    for (poczatek = adresat.begin(); poczatek != adresat.end(); poczatek ++)
    {
        wyswietlAdresataZIPodanymNazwiskiem(*poczatek, nazwisko, wyszukanoAdresatow);
    }
    if (iloscAdresatow == 1)
    {
        system("pause");
    }
    else
    {
        cout << "Nie znaleziono adresatow o danym nazwisku" << endl;
        Sleep(2000);
    }
}
void wyswietlCalaKsiazkeAdresowa(vector <Adresat> &adresat)
{
    for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        wyswietlDaneAdresata(*itr);
    }
    system("pause");
}
void usunKontakt (vector <Adresat> &adresat)
{
    int szukanyNumerID;

    cout << "Wyszukanie adresata. Podaj numer ID adresata: ";
    cin >> szukanyNumerID;

    for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if (itr -> idAdresata == szukanyNumerID)
        {
            itr = adresat.erase(itr);
            cout << "Kontakt zostal usuniety." << endl << endl;
            system("pause");
            break;
        }
    }
}
int wczytajAdresatowZPliku(vector <Adresat> &adresat, int idZalogowanegoUzytkownika)
{

   int iloscOsob = 0;
    Adresat wczytywanaOsoba;
    string linia;
    fstream plik;
    int nr_linii = 1;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()==false) {
        return iloscOsob;
    }
    while (getline(plik,linia,'|')) {
        if (linia == "") {
            return iloscOsob;
        }
        switch(nr_linii) {
        case 1:
            wczytywanaOsoba.idAdresata = atoi(linia.c_str());
            break;
        case 2:
            wczytywanaOsoba.idUzytkownika = atoi(linia.c_str());
            break;
        case 3:
            wczytywanaOsoba.imie = linia;
            break;
        case 4:
            wczytywanaOsoba.nazwisko = linia;
            break;
        case 5:
            wczytywanaOsoba.numerTelefonu = linia;
            break;
        case 6:
            wczytywanaOsoba.email = linia;
            break;
        case 7:
            wczytywanaOsoba.adres = linia;
            break;
        }
        if (nr_linii == 7) {
            iloscOsob++;
            nr_linii = 0;

            if (wczytywanaOsoba.idUzytkownika == idZalogowanegoUzytkownika) {
                adresat.push_back(wczytywanaOsoba);
            }
        }
        nr_linii ++;
    }
    plik.close();
    return iloscOsob;
}
Adresat pobierzDaneAdresata () {

    Adresat wprowadzanyAdresat;

    cout << "Podaj imie: ";
    cin >> wprowadzanyAdresat.imie;
    cout << "Podaj nazwisko: ";
    cin >> wprowadzanyAdresat.nazwisko;
    cout << "Podaj adres email: ";
    cin >> wprowadzanyAdresat.email;
    cout << "Podaj numer telefonu: ";
    cin >> wprowadzanyAdresat.numerTelefonu;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, wprowadzanyAdresat.adres);


    return wprowadzanyAdresat;
}
void dodajAdresata(vector <Adresat> &adresat, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, numerTelefonu, email, adres;
    string liniaZDanymiAdresata = "";
    Adresat Osoba;

    cout << endl << "Zapisywanie nowego znajomego." << endl << endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin,numerTelefonu);
    cout << "Podaj e-mail: ";
    cin >> email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,adres);

    Osoba.idAdresata = znajdzOstatniNumerIDAdresata();
    Osoba.idUzytkownika = idZalogowanegoUzytkownika;
    Osoba.imie = imie;
    Osoba.nazwisko = nazwisko;
    Osoba.numerTelefonu = numerTelefonu;
    Osoba.email = email;
    Osoba.adres = adres;

    adresat.push_back(Osoba);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::app);

    if (plik.good() == true)
    {
        liniaZDanymiAdresata += konwerjsaIntNaString(Osoba.idAdresata) + '|';
        liniaZDanymiAdresata += konwerjsaIntNaString(Osoba.idUzytkownika) + '|';
        liniaZDanymiAdresata += Osoba.imie + '|';
        liniaZDanymiAdresata += Osoba.nazwisko + '|';
        liniaZDanymiAdresata += Osoba.numerTelefonu + '|';
        liniaZDanymiAdresata += Osoba.email + '|';
        liniaZDanymiAdresata += Osoba.adres + '|';

        plik << liniaZDanymiAdresata << endl;
        liniaZDanymiAdresata = "";

        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Danych nie udalo sie zapisac." << endl;
        system("pause");
    }

}
void zapisDanychDoPliku(vector <Adresat> &adresat, int idZalogowanegoUzytkownika)
{
    fstream plik;
    string liniaZDanymiAdresata = "";
int iloscOsob;
    usunLinieZPliku(idZalogowanegoUzytkownika);

    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good() == true)
    {
        for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
        {
            liniaZDanymiAdresata += konwerjsaIntNaString(itr -> idAdresata) + '|';
            liniaZDanymiAdresata += konwerjsaIntNaString(itr -> idUzytkownika) + '|';
            liniaZDanymiAdresata += itr -> imie + '|';
            liniaZDanymiAdresata += itr -> nazwisko + '|';
            liniaZDanymiAdresata += itr -> numerTelefonu + '|';
            liniaZDanymiAdresata += itr -> email + '|';
            liniaZDanymiAdresata += itr -> adres + '|';

            plik << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie zapisac danych." << endl;
        system("pause");
    }
}

void wyswietlMenuGlowne()
{
    system("cls");
    cout << "Ksiazka adresowa\n\n";
    cout << "1. Dodaj nowego adresata\n";
    cout << "2. Wyszukaj adresata po imieniu\n";
    cout << "3. Wyszukaj adresata po nazwisku\n";
    cout << "4. Wczytaj ksiazke adresowa\n";
    cout << "5. Usun adresata\n";
    cout << "6. Edytuj adresata\n";
    cout << "7. Zmien haslo"<<endl;
    cout << "8. Wyloguj sie"<<endl;
    cout << "9. Zakoncz program" << endl;
}

void wyswietlMenuLogowania()
{
    system("cls");
    cout << "1. Zarejestruj sie" << endl;
    cout << "2. Zaloguj sie" << endl;
    cout << "9. Zakoncz program" << endl;
}
int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresat;


    char wyborFunkcji;

     int iloscOsob = 0;
    int iloscUzytkownikow = 0;
    int idZalogowanegoUzytkownika = 0;

    wczytajUzytkownikowZPliku(uzytkownicy);



    while (true) {
        if (idZalogowanegoUzytkownika == 0) {

            wyswietlMenuLogowania();
            cin >> wyborFunkcji;

            switch (wyborFunkcji) {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
                if (idZalogowanegoUzytkownika !=0) {
                    iloscOsob = wczytajAdresatowZPliku(adresat, idZalogowanegoUzytkownika);
                }
                break;
            case '9':
                exit(0);
                break;
            }
        } else {
            wyswietlMenuGlowne();
            cin >> wyborFunkcji;

            switch (wyborFunkcji) {
            case '1':
                dodajAdresata(adresat, idZalogowanegoUzytkownika);
                break;
            case '2':
                szukajPoImieniu(adresat);
                break;
            case '3':
                szukajPoNazwisku(adresat);
                break;
            case '4':
                wyswietlCalaKsiazkeAdresowa(adresat);
                cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
              //  getch();
                break;
            case '5':
                 usunKontakt(adresat);
                 zapisDanychDoPliku(adresat, idZalogowanegoUzytkownika);
                break;
            case '6':
                edytujKontakt(adresat);
                zapisDanychDoPliku(adresat, idZalogowanegoUzytkownika);
                break;
            case '7':
                zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika, iloscUzytkownikow);
                zapiszDaneUzytkownikaDoPliku(uzytkownicy);
                break;
            case '8':
                idZalogowanegoUzytkownika = wylogujUzytkownika(adresat,idZalogowanegoUzytkownika);
                break;
            case '9':
                 idZalogowanegoUzytkownika =0;
                break;
            }
        }
    }
    return 0;
}
