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

void aktualizujPlikKontaktow(vector <Adresat> &adresat)
{
    int i=0;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out);
    if (plik.good() == true)
    {
        plik<<adresat[i].idAdresata<<"|"<<adresat[i].idUzytkownika<<"|"<<adresat[i].imie<<"|"<<adresat[i].nazwisko<<"|"<<adresat[i].numerTelefonu<<"|"<<adresat[i].email<<"|"<<adresat[i].adres<<"|";
        i++;
        while (i!=adresat.size())
        {
            plik<<endl<<adresat[i].idAdresata<<"|"<<adresat[i].idUzytkownika<<"|"<<adresat[i].imie<<"|"<<adresat[i].nazwisko<<"|"<<adresat[i].numerTelefonu<<"|"<<adresat[i].email<<"|"<<adresat[i].adres<<"|";
            i++;
        }

    }
    else
        cout << "wystapil problem z plikiem";
    plik.close();
    plik.clear();

}

void dopiszKontaktDoPliku(Adresat &adresat)
{
    int i=0;
    fstream plik;
    plik.open("kontakty.txt",ios::app);
    if (plik.good() == true)
    {
        plik.seekg(0, ios::end);
        if (plik.tellg() != 0)
        {
            plik << endl;
        }
        plik<<adresat.idAdresata<<"|"<<adresat.idUzytkownika<<"|"<<adresat.imie<<"|"<<adresat.nazwisko<<"|"<<adresat.numerTelefonu<<"|"<<adresat.email<<"|"<<adresat.adres<<"|";
        i++;
    }
    else
        cout << "wystapil problem z plikiem";
    plik.close();
    plik.clear();

}

void aktualizujPlikUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    int i=0;
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::out);
    if (plik.good() == true)
    {
        plik<<uzytkownicy[i].id<<"|"<<uzytkownicy[i].login<<"|"<<uzytkownicy[i].haslo<<"|";
        i++;
        while (i!=uzytkownicy.size())
        {
            plik<<endl<<uzytkownicy[i].id<<"|"<<uzytkownicy[i].login<<"|"<<uzytkownicy[i].haslo<<"|";
            i++;
        }

    }
    else
        cout << "wystapil problem z plikiem";
    plik.close();
    plik.clear();

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

void usunLinieZPliku (int idZalogowanegoUzytkownika)
{
    vector <string> linieDoUsuniecia;
    string linia;
    string dane;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku;
    bool znalezionaLinia;

    fstream plik;
    ofstream nowyPlik;

    linieDoUsuniecia.clear();
    plik.open("KsiazkaAdresowa.txt", ios::in);
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
                    dane = linia.substr (poczatek,ileZnakowWyjac);
                    idUzytkownikaZPliku = atoi(dane.c_str());
                    if ( iloscPionowychKresek == 2 && idZalogowanegoUzytkownika == idUzytkownikaZPliku)
                    {
                        linieDoUsuniecia.push_back(linia);
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
        }
        plik.close();
    }

    nowyPlik.open("PlikBezLinii.txt");
    plik.open("KsiazkaAdresowa.txt", ios::in);

    while (getline(plik,linia))
    {
        znalezionaLinia = 0;
        for( int i = 0; i < linieDoUsuniecia.size(); i++ )
        {
            if ( linia == linieDoUsuniecia[i])
            {
                znalezionaLinia = 1;
            }
        }
        if (znalezionaLinia == 0)
            nowyPlik << linia << endl;

    }

    nowyPlik.close();
    plik.close();
    remove("KsiazkaAdresowa.txt");
    rename("PlikBezLinii.txt","KsiazkaAdresowa.txt");
}

void zapiszAdresatowDoPliku (vector <Adresat> &adresat, string linia, int iloscAdresatow)
{

    string dane;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;

    Adresat pusty;
    adresat.push_back(pusty);

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
                adresat[iloscAdresatow - 1].idAdresata = atoi(dane.c_str());
                break;
            case 2:
                adresat[iloscAdresatow - 1].idUzytkownika = atoi(dane.c_str());
                break;
            case 3:
                adresat[iloscAdresatow - 1].imie = dane;
                break;
            case 4:
                adresat[iloscAdresatow - 1].nazwisko = dane;
                break;
            case 5:
                adresat[iloscAdresatow - 1].numerTelefonu = dane;
                break;
            case 6:
                adresat[iloscAdresatow - 1].email = dane;
                break;
            case 7:
                adresat[iloscAdresatow - 1].adres = dane;
                break;
            }
            poczatek = poczatek + ileZnakowWyjac + 1;
        }
    }
}

void wczytajAdresatowZPliku(vector <Adresat> &adresat, int idZalogowanegoUzytkownika)
{

    string linia;
    string dane;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku = 0;
    int iloscZnajomych = 0;
    fstream plik;

    adresat.clear();
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
                    idUzytkownikaZPliku = atoi(dane.c_str());
                    if ( iloscPionowychKresek == 2 && idZalogowanegoUzytkownika == idUzytkownikaZPliku)
                    {
                        iloscZnajomych++;
                        zapiszAdresatowDoPliku(adresat, linia, iloscZnajomych);
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
            sort(adresat.begin(), adresat.end());
            fstream plik("KsiazkaAdresowa.txt", ios::out);
            if (plik.is_open())
            {
                for_each(adresat.begin(), adresat.end(), [&](int liczba)
                {
                    plik << liczba << endl;
                });
                plik.close();
            }

        }
        plik.close();
    }
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

void zapisDanychDoPliku(vector <Adresat> &adresat, int idZalogowanegoUzytkownika)
{
    fstream plik;
    string liniaZDanymiAdresata = "";

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

    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    int iloscAdresatow = 0;

    wczytajUzytkownikowZPliku(uzytkownicy);

    char wyborFunkcji;

    while(true)
    {
        wczytajUzytkownikowZPliku(uzytkownicy);
        if(idZalogowanegoUzytkownika == 0)
        {

            wyswietlMenuLogowania();
            cin>>wyborFunkcji;
            switch(wyborFunkcji)
            {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
                break;
            case '9':
                exit(0);
                break;
            }
        }
        else
        {
            wczytajAdresatowZPliku(adresat, idZalogowanegoUzytkownika);
            wyswietlMenuGlowne();
            cin>> wyborFunkcji;

            switch(wyborFunkcji)
            {
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


