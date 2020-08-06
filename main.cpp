#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>

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
void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string noweHaslo = "";
    cout << "Podaj nowe haslo: ";
    cin>>noweHaslo;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if (itr -> id == idZalogowanegoUzytkownika)
        {
            itr -> haslo = noweHaslo;
            cout << "Haslo zostalo zmienione." << endl << endl;
            system("pause");
        }
    }
    zapiszDaneUzytkownikaDoPliku(uzytkownicy);

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

void zapiszDoPlikuTymczasowego (Adresat aktuanyAdresat)
{

    fstream plikTymczasowy;
    plikTymczasowy.open("KsiazkaAdresowaTymczasowy.txt", ios::out | ios::app);

    plikTymczasowy << aktuanyAdresat.idAdresata<< "|" << aktuanyAdresat.idUzytkownika << "|" << aktuanyAdresat.imie << "|" << aktuanyAdresat.nazwisko << "|" << aktuanyAdresat.numerTelefonu << "|" << aktuanyAdresat.email << "|" << aktuanyAdresat.adres << "|" << endl;
    plikTymczasowy.close();
}

void zapiszEdytowanyKontaktDoPlikuTymczasowego (vector <Adresat> adresat, int edytowaneID)
{
    fstream plikTymczasowy;
    plikTymczasowy.open("KsiazkaAdresowaTymczasowy.txt", ios::out | ios::app);

    for (vector <Adresat> :: iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if ( itr -> idAdresata == edytowaneID)
        {
            plikTymczasowy << itr -> idAdresata << "|" << itr -> idUzytkownika << "|" << itr ->  imie << "|" << itr ->  nazwisko << "|" << itr ->  numerTelefonu << "|" << itr ->  email << "|" << itr ->  adres << "|" << endl;
        }
    }
    plikTymczasowy.close();
}

void zapiszEdytowaneDaneDoPliku(vector <Adresat> adresat, int edytowaneID)
{

    int nrLinii = 1;
    string linia;
    bool czyLiczbaRownaID = false;
    Adresat pusty;
    fstream plikZDanymi;
    plikZDanymi.open("KsiazkaAdresowa.txt", ios::in);

    while (getline(plikZDanymi,linia,'|'))
    {
        if (linia == "")
        {
            return;
        }
        switch(nrLinii)
        {
        case 1:
            if  (atoi(linia.c_str()) == edytowaneID)
            {
                czyLiczbaRownaID = true;
            }
            else
            {
                pusty.idAdresata = atoi(linia.c_str());
            };
            break;
        case 2:
            if (czyLiczbaRownaID == false)
            {
                pusty.idUzytkownika = atoi(linia.c_str());
            }
            break;
        case 3:
            if (czyLiczbaRownaID == false)
            {
                pusty.imie = linia;
            }
            break;
        case 4:
            if (czyLiczbaRownaID == false)
            {
                pusty.nazwisko = linia;
            }
            break;
        case 5:
            if (czyLiczbaRownaID == false)
            {
                pusty.numerTelefonu = linia;
            }
            break;
        case 6:
            if (czyLiczbaRownaID == false)
            {
                pusty.email = linia;
            }
            break;
        case 7:
            if (czyLiczbaRownaID == false)
            {
                pusty.adres = linia;
            }
            break;
        }
        if (nrLinii == 7)
        {
            if (czyLiczbaRownaID == false)
            {
                zapiszDoPlikuTymczasowego(pusty);
            }
            else
            {
                zapiszEdytowanyKontaktDoPlikuTymczasowego(adresat, edytowaneID);
            }
            czyLiczbaRownaID = false;
            nrLinii = 0;
        }
        nrLinii ++;
    }
    plikZDanymi.close();
    remove ("KsiazkaAdresowa.txt");
    rename ("KsiazkaAdresowaTymczasowy.txt","KsiazkaAdresowa.txt");
}

void edytujImie(vector <Adresat> &adresat, int edytowaneID)
{

    string imieDoEdycji;
    cout << "Podaj nowe imie: ";
    cin >> imieDoEdycji;

    for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if (itr -> idAdresata == edytowaneID)
        {
            itr -> imie = imieDoEdycji;
        }
    }
    cout << "Zmienione imie: " << imieDoEdycji << endl;
    zapiszEdytowaneDaneDoPliku(adresat, edytowaneID);

}

void edytujNazwisko(vector <Adresat> &adresat, int edytowaneID)
{

    string nazwiskoDoEdycji;
    cout << "Podaj nowe nazwisko: ";
    cin >> nazwiskoDoEdycji;

    for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if (itr -> idAdresata == edytowaneID)
        {
            itr -> nazwisko = nazwiskoDoEdycji;
        }
    }
    cout << "Zmienione nazwisko: " << nazwiskoDoEdycji << endl;
    zapiszEdytowaneDaneDoPliku(adresat, edytowaneID);

}

void edytujNumerTelefonu(vector <Adresat> &adresat, int edytowaneID)
{

    string numerDoEdycji;
    cout << "Podaj nowy numer telefonu: ";


    for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if (itr -> idAdresata == edytowaneID)
        {
            itr -> numerTelefonu = numerDoEdycji;
        }
    }
    cout << "Zmieniony numer telefonu: " << numerDoEdycji << endl;
    zapiszEdytowaneDaneDoPliku(adresat, edytowaneID);

}

void edytujEmail(vector <Adresat> &adresat, int edytowaneID)
{

    string emailDoEdycji;
    cout << "Podaj nowy adres email: ";


    for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if (itr -> idAdresata == edytowaneID)
        {
            itr -> email = emailDoEdycji;
        }
    }
    cout << "Zmieniony email: " << emailDoEdycji << endl;
    zapiszEdytowaneDaneDoPliku(adresat, edytowaneID);
}

void edytujAdres(vector <Adresat> &adresat, int edytowaneID)
{

    string adresDoEdycji;
    cout << "Podaj nowy adres: ";
    cin >> adresDoEdycji;

    for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if (itr -> idAdresata == edytowaneID)
        {
            itr -> adres = adresDoEdycji;
        }
    }
    cout << "Zmieniony adres: " << adresDoEdycji << endl;
    zapiszEdytowaneDaneDoPliku(adresat, edytowaneID);
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

bool sprawdzCzyIdIstnieje (vector <Adresat> adresat,int edytowaneID)
{

    bool potwierdz = false;
    for (vector <Adresat> :: iterator itr = adresat.begin(); itr != adresat.end(); itr++)
    {
        if (itr -> idAdresata == edytowaneID)
        {
            potwierdz = true;
        }
    }
    return potwierdz;
}

void edytujKontakt(vector <Adresat> &adresat)
{

    system("cls");
    wyswietlCalaKsiazkeAdresowa(adresat);
    int edytowaneID;
    cout << "Pod ktorym numerem ID znajduje sie osoba, ktora chcesz edytowac: ";
    cin >> edytowaneID;

    if (sprawdzCzyIdIstnieje(adresat, edytowaneID) == 1)
    {
        char wybor;
        while (true)
        {

            cout << "1.Edytuj imie." << endl;
            cout << "2.Edytuj nazwisko." << endl;
            cout << "3.Edytuj numer telefonu." << endl;
            cout << "4.Edytuj adres emailowy." << endl;
            cout << "5.Edytuj adres kontaktowy." << endl;
            cout << "6.Zakoncz edycje." << endl<<endl;
            cin >> wybor;

            if (wybor == '1')
            {
                edytujImie(adresat,edytowaneID);
            }
            else if (wybor == '2')
            {
                edytujNazwisko(adresat,edytowaneID);
            }
            else if (wybor == '3')
            {
                edytujEmail(adresat,edytowaneID);
            }
            else if (wybor == '4')
            {
                edytujNumerTelefonu(adresat, edytowaneID);
            }
            else if (wybor == '5')
            {
                edytujAdres(adresat, edytowaneID);
            }
            else if (wybor == '6')
            {
                break;
            }
        }
    }
    else
    {
        system("cls");
        cout << "Nie znaleziono osoby o podanym numerze ID." << endl;
    }
}
void usuwanieZPliku(int iloscOsob, int idDoUsuniecia)
{

    int nrLinii = 1;
    string linia;
    bool czyLiczbaRownaID = false;
    Adresat usuwanyAdresat;
    fstream plikZDanymi;
    plikZDanymi.open("KsiazkaAdresowa.txt", ios::in);

    while (getline(plikZDanymi,linia,'|'))
    {
        if (linia == "")
        {
            return;
        }
        switch(nrLinii)
        {
        case 1:
            if  (atoi(linia.c_str()) == idDoUsuniecia)
            {
                czyLiczbaRownaID = true;
            }
            else
            {
                usuwanyAdresat.idAdresata = atoi(linia.c_str());
            };
            break;
        case 2:
            if (czyLiczbaRownaID == false)
            {
                usuwanyAdresat.idUzytkownika = atoi(linia.c_str());
            }
            break;
        case 3:
            if (czyLiczbaRownaID == false)
            {
                usuwanyAdresat.imie = linia;
            }
            break;
        case 4:
            if (czyLiczbaRownaID == false)
            {
                usuwanyAdresat.nazwisko = linia;
            }
            break;
        case 5:
            if (czyLiczbaRownaID == false)
            {
                usuwanyAdresat.numerTelefonu = linia;
            }
            break;
        case 6:
            if (czyLiczbaRownaID == false)
            {
                usuwanyAdresat.email = linia;
            }
            break;
        case 7:
            if (czyLiczbaRownaID == false)
            {
                usuwanyAdresat.adres = linia;
            }
            break;
        }

        if (nrLinii == 7)
        {

            if (czyLiczbaRownaID == false)
            {
                zapiszDoPlikuTymczasowego (usuwanyAdresat);
            }
            czyLiczbaRownaID = false;
            nrLinii = 0;
        }
        nrLinii ++;
    }
    plikZDanymi.close();
    remove ("KsiazkaAdresowa.txt");
    rename ("KsiazkaAdresowaTymczasowy.txt","KsiazkaAdresowa.txt");
}
int znajdzOstatniNumerIDAdresata()
{

    int ostatnieID = 0;
    string linia;
    fstream plik;
    int nrLinii = 1;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()==false)
    {
        return ostatnieID;
    }

    while (getline(plik,linia,'|'))
    {

        switch(nrLinii)
        {
        case 1:
            if (atoi(linia.c_str()) == 0)
            {
                return ostatnieID;
            }
            else
            {
                ostatnieID = atoi(linia.c_str());
            }
            break;
        }

        if (nrLinii == 7)
        {
            nrLinii = 0;
        }
        nrLinii++;
    }
    plik.close();
    return ostatnieID;
}
void zapiszNowyKontaktDoPliku(Adresat pusty)
{

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik << pusty.idAdresata<< "|" << pusty.idUzytkownika << "|" << pusty.imie << "|" << pusty.nazwisko << "|" << pusty.numerTelefonu << "|" << pusty.email << "|" << pusty.adres << "|" << endl;
    }
    plik.close();
}

int usunKontakt (vector <Adresat> &adresat)
{
    int szukanyNumerID;
    int iloscOsob;
    char wyborFunkcji;
    cout << "Wyszukanie adresata. Podaj numer ID adresata: ";
    cin >> szukanyNumerID;

    system("cls");
    wyswietlCalaKsiazkeAdresowa(adresat);

    if (sprawdzCzyIdIstnieje(adresat,szukanyNumerID) == 1)
    {
        for (vector <Adresat>::iterator itr = adresat.begin(); itr != adresat.end() ; itr++)
        {
            if (itr -> idAdresata == szukanyNumerID)
            {
                cout << "Czy na pewno chcesz usunac " <<itr -> imie << " " << itr -> nazwisko << "?"<< endl;
                cout << "(t/n)";
            }
        }
        while(true)
        {
            cin >> wyborFunkcji;
            if (wyborFunkcji == 't')
            {
                for (vector <Adresat>:: iterator itr = adresat.begin(); itr != adresat.end() ; itr++)
                {
                    if (itr -> idAdresata == szukanyNumerID)
                    {
                        adresat.erase(itr);
                        itr--;
                    }
                }
                iloscOsob--;
                cout << "Usunieto wybrana osobe." << endl;
                usuwanieZPliku(iloscOsob, szukanyNumerID);
                cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
                getch();
                return iloscOsob;

            }
            else if (wyborFunkcji == 'n')
            {
                return iloscOsob;
            }
        }
    }
    else
    {
        system("cls");
        cout << "Nie znaleziono osoby o podanym numerze ID." << endl;
        cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
        getch();
        return iloscOsob;
    }
}


int wczytajKontakt(vector <Adresat> &adresat, int idZalogowanegoUzytkownika)
{

    int iloscOsob = 0;
    Adresat wprowadzanyAdresat;
    string linia;
    fstream plik;
    int nrLinii = 1;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()==false)
    {
        return iloscOsob;
    }
    while (getline(plik,linia,'|'))
    {
        if (linia == "")
        {
            return iloscOsob;
        }
        switch(nrLinii)
        {
        case 1:
            wprowadzanyAdresat.idAdresata = atoi(linia.c_str());
            break;
        case 2:
            wprowadzanyAdresat.idUzytkownika = atoi(linia.c_str());
            break;
        case 3:
            wprowadzanyAdresat.imie = linia;
            break;
        case 4:
            wprowadzanyAdresat.nazwisko = linia;
            break;
        case 5:
            wprowadzanyAdresat.numerTelefonu = linia;
            break;
        case 6:
            wprowadzanyAdresat.email = linia;
            break;
        case 7:
            wprowadzanyAdresat.adres = linia;
            break;
        }
        if (nrLinii == 7)
        {
            iloscOsob++;
            nrLinii = 0;

            if (wprowadzanyAdresat.idUzytkownika == idZalogowanegoUzytkownika)
            {
                adresat.push_back(wprowadzanyAdresat);
            }
        }
        nrLinii ++;
    }
    plik.close();
    return iloscOsob;
}

Adresat pobierzDaneAdresata ()
{

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

    cout << "Czy podane dane sa prawidlowe (t/n)?" << endl;

    return wprowadzanyAdresat;
}

int dodajAdresata(vector <Adresat> &adresat, int iloscOsob, int idZalogowanegoUzytkownika)
{

    Adresat wprowadzanyAdresat;
    char wyborFunkcji;
    system("cls");
    while (wyborFunkcji != 't')
    {

        wprowadzanyAdresat = pobierzDaneAdresata();
        cin >> wyborFunkcji;
        system("cls");
    }

    if (iloscOsob == 0)
    {
        wprowadzanyAdresat.idAdresata = 1;
    }
    else
    {
        wprowadzanyAdresat.idAdresata = znajdzOstatniNumerIDAdresata() + 1;
    }

    wprowadzanyAdresat.idUzytkownika = idZalogowanegoUzytkownika;
    adresat.push_back(wprowadzanyAdresat);
    zapiszNowyKontaktDoPliku(wprowadzanyAdresat);
    iloscOsob++;

    return iloscOsob;
}

void wyswietlMenuGlowne()
{
    system("cls");
    cout << "Ksiazka adresowa"<<endl;
    cout << "1. Dodaj nowego adresata"<<endl;
    cout << "2. Wyszukaj adresata po imieniu"<<endl;
    cout << "3. Wyszukaj adresata po nazwisku"<<endl;
    cout << "4. Wczytaj ksiazke adresowa"<<endl;
    cout << "5. Usun adresata"<<endl;
    cout << "6. Edytuj adresata"<<endl;
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
    vector <Adresat> adresat;
    vector <Uzytkownik> uzytkownicy;

    int iloscOsob = 0;
    int iloscUzytkownikow = 0;
    int idZalogowanegoUzytkownika = 0;

    wczytajUzytkownikowZPliku(uzytkownicy);

    char wyborFunkcji;

    while (true)
    {
        if (idZalogowanegoUzytkownika == 0)
        {

            wyswietlMenuLogowania();
            cin >> wyborFunkcji;

            switch (wyborFunkcji)
            {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
                if (idZalogowanegoUzytkownika !=0)
                {
                    iloscOsob = wczytajKontakt(adresat, idZalogowanegoUzytkownika);
                }
                break;
            case '9':
                exit(0);
                break;
            }
        }
        else
        {
            wyswietlMenuGlowne();
            cin >> wyborFunkcji;

            switch (wyborFunkcji)
            {
            case '1':
                iloscOsob = dodajAdresata(adresat, iloscOsob, idZalogowanegoUzytkownika);
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
                getch();
                break;
            case '5':
                usunKontakt(adresat);
                break;
            case '6':
                edytujKontakt(adresat);
                break;
            case '7':
                zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '8':
                idZalogowanegoUzytkownika = wylogujUzytkownika(adresat,idZalogowanegoUzytkownika);
                break;
            case '9':
                exit(0);
                break;
            }
        }
    }
    return 0;
}
