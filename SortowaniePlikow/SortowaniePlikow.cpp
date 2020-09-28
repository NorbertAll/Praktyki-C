//#define _CRT_SECURE_NO_WARNINGS
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
string* Sciezki;
time_t* Daty;
void listowanie();
void sortowanie(int lewy, int prawy);
void Zamien(int index1, int index2);
void SortowanieZeZmianaNazwy();
string sciezka="C:/Users/norbe/OneDrive/Pulpit/Katalog/";
string nowasciezka = "C:/Users/norbe/OneDrive/Pulpit/Seg/";
int main()
{
	
	listowanie();
	
	
	for (int i = 0; i < licznik; i++)
	{
		cout << Nazwy[i] << "  "<<endl;
	}
	sortowanie(0, licznik-1);
	cout << endl;
	for (int i = 0; i < licznik; i++)
	{
		cout << Nazwy[i] << "  " << endl;
	}
	Sciezki = new string[licznik];
	for (int i = 0; i < licznik; i++)
	{
		Sciezki[i]=sciezka + Nazwy[i] ;
	}
	for (int i = 0; i < licznik; i++)
	{
		cout << Sciezki[i] << "  " << endl;
	}
	int x;
	
	cout << "Plikow w folderze Dane jest: " << licznik;

	cout << endl;
	SortowanieZeZmianaNazwy();

	cin >> x;


	return 0;


}
void listowanie()
{
	//wyciągniecie nazwy
	int liczba_plikow = 0;
	_finddata_t liczbaplikow;
	long uchwyt_0 = _findfirst("C:/Users/norbe/OneDrive/Pulpit/Katalog/*.txt", &liczbaplikow);

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
	long uchwyt_1 = _findfirst("C:/Users/norbe/OneDrive/Pulpit/Katalog/*.txt", &nazwyplikow);
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
	long uchwyt_2 = _findfirst("C:/Users/norbe/OneDrive/Pulpit/Katalog/*.txt", &datymodyfikacji);
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
void sortowanie(int lewy, int prawy)
{
	if (lewy >= prawy) return;
	time_t pivotValue = Daty[prawy];
	int granica = lewy - 1;
	int i = lewy;
	while (i < prawy)
	{
		if (Daty[i] < pivotValue)
		{
			granica++;
			if (granica != i)
			{
				Zamien(granica, i);
			}
		}
		i++;
	}
	granica++;
	if (granica != prawy)
	{
		Zamien(granica, prawy);
	}
	sortowanie( lewy, granica - 1);
	sortowanie(granica + 1, prawy);

}
void Zamien(int index1, int index2)
{
	time_t tmp = Daty[index1];
	string tmp2 = Nazwy[index1];
	Daty[index1] = Daty[index2];
	Nazwy[index1] = Nazwy[index2];
	Daty[index2] = tmp;
	Nazwy[index2] = tmp2;
}
void SortowanieZeZmianaNazwy()
{
	string nowa;
	
	for (int i = 1; i < licznik+1; i++) 
	{
		string zera="";
		for (int j = to_string(licznik).length() - to_string(i).length(); j != 0; j--)
			zera = zera + "0";
		nowa = nowasciezka + zera + to_string(i) + ".txt";

		cout << nowa;
		cout << endl;
		rename(Sciezki[i-1].c_str(), nowa.c_str());
	}
	
	
}