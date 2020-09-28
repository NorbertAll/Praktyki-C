#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/types.h>
#include <cstring>
#include <time.h>
#include <string>
#include <io.h>
#include <fstream>
#include <stdlib.h>
using namespace std;
int licznik;//stare
string* Nazwy;
string* Sciezki;//stare
string* Camery;
string* Camerysciezki;
string* Liczbaplikow;
int* Plikowwcamera;
string typ;//stare
int parametr;
int liczbacamer;
string katalogg;
string nowasciezka;//stare
string ca = "Camera ";
#include <QMessageBox>

void listowanie()
{
    //wyciągniecie nazwy
    int liczba_plikow = 0;
    _finddata_t liczbaplikow;

    long uchwyt_0 = _findfirst((katalogg+"*").c_str(), &liczbaplikow);

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
    long uchwyt_1 = _findfirst((katalogg+"*").c_str(), &nazwyplikow);
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
}
void listacamer()
{
    liczbacamer=0;
    for (int n = 0; n < licznik; n++)
        for (int i = 0; i < licznik; i++)
        {
            string k = to_string(n);
            if (Nazwy[i] == (ca + k))
            {
                liczbacamer++;
            }
        }
    Camery = new string[liczbacamer];
    Camerysciezki = new string[liczbacamer];
    int j = 0;

    for (int n = 0; n < licznik; n++)
        for (int i = 0; i < licznik; i++)
        {
            string k = to_string(n);
            if (Nazwy[i] == (ca + k))
            {
                Camery[j] = Nazwy[i];
                Camerysciezki[j] = katalogg + Nazwy[i]+"\\"+"*";
                j++;
            }
        }
    //==================
    Plikowwcamera = new int[liczbacamer];


    for (int i = 0; i < liczbacamer; i++)
    {
        _finddata_t liczbaplikow;
        int liczba_plikow = 0;
        long uchwyt_0 = _findfirst(Camerysciezki[i].c_str(), &liczbaplikow);

        if (uchwyt_0 != -1)
        {
            liczba_plikow++;
            while (_findnext(uchwyt_0, &liczbaplikow) != -1)
            {
                liczba_plikow++;
            }
        }
        _findclose(uchwyt_0);
        Plikowwcamera[i] = liczba_plikow-2;
    }
    //==========
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->katalog->setPlaceholderText("Podaj katalog");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString katalogq= ui->katalog-> text();
    katalogg=katalogq.toStdString();
    QString parametrq= ui->parametrq-> text();
    parametr=parametrq.toInt();
    listowanie();
    listacamer();
    string tekst="";
    for(int i=0; i<liczbacamer; i++)
    {
        tekst=tekst+Camery[i]+": "+to_string(Plikowwcamera[i])+"files"+"\n";

    }


        const char *wyswietl= tekst.c_str();

        //QMessageBox::information(this, "Sturktura", wyswietl);
        ui->ekran->setText(wyswietl);

   // );
    //TextView ekran = (TextView) findViewById(R.id.my_text_view);
   // ekran.setText("pies");
   // Camery[0].c_str()

}
