#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <cstring>
#include <time.h>
#include <string>
#include <io.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

int licznik;
string* Nazwy;
time_t* Daty;

void listowanie();

int main()
{

	listowanie();
	for (int i = 2; i < licznik; i++)
	{
		cout << Nazwy[i] << "  ";
		cout << asctime(gmtime(&Daty[i]));
	}
	int x;
	
	cout << "Plikow w folderze Dane jest: " << licznik-2;
	
	cout << endl;


	cin >> x;
	
	
	return 0;

	
}
void listowanie()
{
	//wyciągniecie nazwy
	int liczba_plikow = 0;
	_finddata_t liczbaplikow;
	long uchwyt_0 = _findfirst("C:/Users/norbe/OneDrive/Pulpit/Katalog/*.*", &liczbaplikow);

	if (uchwyt_0 != -1)
	{
		liczba_plikow++;
		while (_findnext(uchwyt_0, &liczbaplikow) != -1)
		{
			liczba_plikow++;
		}
	}
	_findclose(uchwyt_0);
	//===========================
	Nazwy = new string[liczba_plikow];
	_finddata_t nazwyplikow;
	long uchwyt_1 = _findfirst("C:/Users/norbe/OneDrive/Pulpit/Katalog/*.*", &nazwyplikow);
	licznik = 0;
	if (uchwyt_1 != -1)
	{
		fstream plik;
		plik.open(nazwyplikow.name, ios::in);
		Nazwy[licznik] = nazwyplikow.name;

		licznik++;
		while (_findnext(uchwyt_1, &nazwyplikow) != -1)
		{
			fstream plik;
			plik.open(nazwyplikow.name, ios::in);
			Nazwy[licznik] = nazwyplikow.name;

			licznik++;
		}

	}
	_findclose(uchwyt_1);
	//=======================================
	//DATA MOGYFIKACJI
	Daty = new time_t[liczba_plikow];
	_finddata_t datymodyfikacji;
	long uchwyt_2 = _findfirst("C:/Users/norbe/OneDrive/Pulpit/Katalog/*.*", &datymodyfikacji);
	licznik = 0;
	if (uchwyt_2 != -1)
	{
		fstream plik;
		//plik.open(datymodyfikacji.time_write, ios::in);
		Daty[licznik] = datymodyfikacji.time_write;
		licznik++;
		while (_findnext(uchwyt_2, &datymodyfikacji) != -1)
		{
			fstream plik;
			//plik.open(datymodyfikacji.time_write, ios::in);
			Daty[licznik] = datymodyfikacji.time_write;

			licznik++;
		}

	}
	_findclose(uchwyt_2);
}
