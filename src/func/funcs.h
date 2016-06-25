/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/

#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#include "lista.h"

using namespace std;

void spa (int n);        ///Scrive tante linee (-) quanto il parametro in ingresso

int sizeL(root r);          ///Restituisce linghezza di una lista

int sizeS(string text);         ///Restituisce lunghezza di una stringa

root iniR (string text);                ///Trasforma una stringa in una lista di caratteri

string deR (root r);     ///Trasforma una lista di caratteri in una stringa (inverso iniR)

void ins(root r, int pos, char x);    ///Inserisce un elemento in una lista

void elim(root r, int pos);    ///Elimina elemento di una lista

unsigned int pazz(root r,unsigned int n);       ///Inserisce caratteri casuali all'interno di una lista (r root lista, n numero di caratteri da aggingere approssimativamente)

void depazz (root r, unsigned int n);  ///Funzione inversa a pazz

bool scrivi(string path,unsigned int* dati,unsigned int n);          ///n lunghezza vettore dati

bool scrivi(string path, string* dati, unsigned int n);

bool leggi(string path, unsigned int *dati);

bool leggi(string path, string *dati);

unsigned long int siz(string path);                          ///Restituisce lunghezza in byte di un file

unsigned int gap_scan(string path);            ///Restituisce quanti a capo ci sono nel file

unsigned int cont_s(string path);

#endif // FUNCS_H_INCLUDED
