#include "mainwindow.h"
#include "ui_mainwindow.h"
//Moje
#include <sys/types.h>
#include <cstring>
#include <time.h>
#include <string>
#include <io.h>
#include <fstream>
#include <stdlib.h>
using namespace std;
int licznik;
int alert;
string* Nazwy;
string* Sciezki;
time_t* Daty;
size_t* Wielkosc;
string typ;
string sciezka;
string nowasciezka;
#include <QMessageBox>
//Koniec Moje


void ZamienZeWzgleduNaDate(int index1, int index2)
{
    time_t tmp = Daty[index1];
    string tmp2 = Nazwy[index1];
    Daty[index1] = Daty[index2];
    Nazwy[index1] = Nazwy[index2];
    Daty[index2] = tmp;
    Nazwy[index2] = tmp2;
}
void ZamienZeWzgleduNaWielkosc(int index1, int index2)
{
    size_t tmp = Wielkosc[index1];
    string tmp2 = Nazwy[index1];
    Wielkosc[index1] = Wielkosc[index2];
    Nazwy[index1] = Nazwy[index2];
    Wielkosc[index2] = tmp;
    Nazwy[index2] = tmp2;
}
void listowanie()
{
    //wyciągniecie nazwy
    int liczba_plikow = 0;
    _finddata_t liczbaplikow;

    long uchwyt_0 = _findfirst((sciezka+"*" +"."+typ).c_str(), &liczbaplikow);

    if (uchwyt_0 != -1)
    {
        liczba_plikow++;
        while (_findnext(uchwyt_0, &liczbaplikow) != -1)
        {
            liczba_plikow++;
        }
    }
    alert=liczba_plikow;
    _findclose(uchwyt_0);
    //===========================
    Nazwy = new string[liczba_plikow];
    _finddata_t nazwyplikow;
    long uchwyt_1 = _findfirst((sciezka+"*" +"."+typ).c_str(), &nazwyplikow);
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

    long uchwyt_2 = _findfirst((sciezka+"*" +"."+typ).c_str(), &datymodyfikacji);
    licznik = 0;
    if (uchwyt_2 != -1)
    {
        fstream plik;

        Daty[licznik] = datymodyfikacji.time_write;
        licznik++;
        while (_findnext(uchwyt_2, &datymodyfikacji) != -1)
        {
            fstream plik;

            Daty[licznik] = datymodyfikacji.time_write;

            licznik++;
        }

    }
    _findclose(uchwyt_2);
    //WIELKOŚĆ
    Wielkosc = new size_t[liczba_plikow];
    _finddata_t wielkosci;

    long uchwyt_3 = _findfirst((sciezka+"*" +"."+typ).c_str(), &wielkosci);
    licznik = 0;
    if (uchwyt_3 != -1)
    {
        fstream plik;

        Wielkosc[licznik] = wielkosci.size;
        licznik++;
        while (_findnext(uchwyt_3, &wielkosci) != -1)
        {
            fstream plik;

            Wielkosc[licznik] = wielkosci.size;

            licznik++;
        }

    }






}

void sortowanieZeWzglenduNaDateOdNajstarszego(int lewy, int prawy)//KOREKTA
{
    if (lewy >= prawy) return;
    time_t pivotValue = Daty[prawy];
    int granica = lewy - 1;
    int i = lewy;
    while (i<  prawy)
    {
        if (Daty[i] < pivotValue)
        {
            granica++;
            if (granica != i)
            {
                ZamienZeWzgleduNaDate(granica, i);
            }
        }
        i++;
    }
    granica++;
    if (granica != prawy)
    {
        ZamienZeWzgleduNaDate(granica, prawy);
    }
    sortowanieZeWzglenduNaDateOdNajstarszego( lewy, granica - 1);
    sortowanieZeWzglenduNaDateOdNajstarszego(granica + 1, prawy);
}
void sortowanieZeWzglenduNaDateOdNajnowszego(int lewy, int prawy)
{
    sortowanieZeWzglenduNaDateOdNajstarszego(lewy, prawy);
    int j=prawy/2;
    for(int i=0;i<=j; i++)
    ZamienZeWzgleduNaDate(lewy+i, prawy-i);
}

void sortowanieOdNajmniejszczego(int lewy, int prawy)
{
    if (lewy >= prawy) return;
    size_t pivotValue = Wielkosc[prawy];
    int granica = lewy - 1;
    int i = lewy;
    while (i < prawy)
    {
        if (Wielkosc[i] < pivotValue)
        {
            granica++;
            if (granica != i)
            {
                ZamienZeWzgleduNaWielkosc(granica, i);
            }
        }
        i++;
    }
    granica++;
    if (granica != prawy)
    {
        ZamienZeWzgleduNaWielkosc(granica, prawy);
    }
    sortowanieOdNajmniejszczego( lewy, granica - 1);
    sortowanieOdNajmniejszczego(granica + 1, prawy);
}
void sortowanieOdNajwiekszego(int lewy, int prawy)//KOREKTA
{
    sortowanieOdNajmniejszczego(lewy, prawy);
    int j=prawy/2;
    for(int i=0;i<=j; i++)
    ZamienZeWzgleduNaWielkosc(lewy+i, prawy-i);
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


        rename(Sciezki[i-1].c_str(), nowa.c_str());
    }
}





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->katalogwej->setPlaceholderText("Podaj katalog wejściowy");
    ui->katalogwyj->setPlaceholderText("Podaj katalog wyjściowy");
    ui->typpliku->setPlaceholderText("Podaj typ pliku");


}

MainWindow::~MainWindow()
{

    delete ui;
}



void MainWindow::on_Sortuj_clicked()
{
    QString typplikuq= ui->typpliku-> text();
    QString katalogwejq= ui->katalogwej-> text();
    QString katalogwyjq= ui->katalogwyj-> text();
    sciezka=katalogwejq.toStdString();
    nowasciezka=katalogwyjq.toStdString();
    typ=typplikuq.toStdString();
    listowanie();
    //Możliwość wyboru
    QString opcjaq=ui->wyborSortowania->currentText();
    string opcja=opcjaq.toStdString();


//Wybór sortowania
    if(opcja==("Od najnowszego do najstarszego"))
       sortowanieZeWzglenduNaDateOdNajstarszego(0, licznik-1);
    if(opcja=="Od najstarszego do najnowszego")
       sortowanieZeWzglenduNaDateOdNajnowszego(0, licznik-1);
    if(opcja=="Od najmniejszego do największego")
       sortowanieOdNajmniejszczego(0, licznik-1);
    if(opcja=="Od największego do najmniejszego")
      sortowanieOdNajwiekszego(0, licznik-1);
    //Tworzenie nowych sicieżek
    Sciezki = new string[licznik];
    for (int i = 0; i < licznik; i++)
        {
            Sciezki[i]=sciezka + Nazwy[i] ;
        }
    //Zmiana nazwy posortowanych elemntów
    SortowanieZeZmianaNazwy();
    if (alert==0)
        QMessageBox::information(this, "UWAGA","Barak plików do sortowania");

}
