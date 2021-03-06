/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/

#include "lista.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

void spa (int n)          ///Scrive tante linee (-) quanto il parametro in ingresso
{
    cout<<endl;
    for(int i=0; i<n; i++)
        cout<<"-";
    cout<<endl;
}

int sizeL(root r)          ///Restituisce linghezza di una lista
{
    int i=0;
    if(r==NULL)
        return 0;
    else if(r->next==NULL)
        return 1;
    root l=r;
    while(l->next!=NULL)
    {
        l=l->next;
        i++;
    }
    return i+1;
}

int sizeS(string text)            ///Restituisce lunghezza di una stringa
{
    int i=0;
    while(text[i]!='\0') i++;
    return i;
}

root iniR (string text)                ///Trasforma una stringa in una lista di caratteri
{
    int x=sizeS(text), i;
    if (x==0) return NULL;
    root r= new item, l=r;
    for(i=0 ;i<x; i++)
    {
        l->a=text[i];
        if(i<x-1)
        {
            l->next=new item;
            l=l->next;
        }
        else
            l->next=NULL;
    }
    return r;
}

string deR (root r)     ///Trasforma una lista di caratteri in una stringa (inverso iniR)
{
    if (r==NULL) return "";
    string a;
    root l=r;
    while(l->next!=NULL)
    {
        a=a+l->a;
        l=l->next;
    }
    a=a+l->a;
    return a;
}

void ins(root r, int pos, char x)    ///Inserisce un elemento in una lista
{
    root l, p=r;
    int k=1;
    while(k<pos)
    {
        p=p->next;
        k++;
    }
    l=p->next;
    p->next=new item;
    p=p->next;
    p->a=x;
    p->next=l;
}

void elim(root r, int pos)    ///Elimina elemento di una lista
{
    root l;
    for(int i=0; i<pos-1; i++)
        r=r->next;
    l=r;
    r=r->next;
    l->next=r->next;
    delete r;
}

unsigned int pazz(root r,unsigned int n)       ///Inserisce caratteri casuali all'interno di una lista (r root lista, n numero di caratteri da aggingere approssimativamente)
{
    unsigned long int x=sizeL(r), k=0;
    if(x==0) return 0;
    unsigned int  y=n/x;
    root l=r;
    for(unsigned long int i=0; i<x; i++)
    {
        for(unsigned int j=0; j<y; j++)
            ins(l, i+k+1, (rand()%95)+32);
        k=k+y;
    }
    return y;
}

void depazz (root r, unsigned int n)  ///Funzione inversa a pazz
{                                                                         ///(r root lista, n numeri da togliere per lettera
    unsigned long int x=sizeL(r), k=1, y=x/(n+1);
    for(unsigned long int i=0; i<y; i++)
    {
        for(unsigned int j=0; j<n; j++)
            elim(r, k);
        k++;
    }
}

void scrivi(string path,unsigned int* dati,unsigned int n)          ///n lunghezza vettore dati
{
    ofstream file(path.c_str(), ios::binary|ios::trunc);
    if(file.is_open())
    {
        file.write((char*)&n, sizeof(int));
        for(unsigned int i=0; i<n; i++)
            file.write((char*)&dati[i], sizeof(int));
        file.close();
    }
    else throw invalid_argument("Can't write: bad file");
}

void scrivi(string path, string* dati, unsigned int n)
{
    ofstream file(path.c_str(), ios::trunc);
    if(file.is_open())
    {
        unsigned int i=0;
        for(; i<n-1; i++)
            file<<dati[i]<<"\n";
        file<<dati[i];
        file.close();
    }
    else throw invalid_argument("Can't write: bad file");
}

void leggi(string path, unsigned int *dati)
{
    unsigned int i=0, ver=0;
    ifstream file(path.c_str(), ios::binary);
    if(file.is_open())
    {
        file.read((char*)&ver, sizeof(int));
        while(file.good())
            file.read((char*)&dati[i++], sizeof(int));
    }
    else throw invalid_argument("Can't read: no file");
    if(ver!=i+1) throw invalid_argument("Read: corrupt syn file");
}

void leggi(string path, string *dati)
{
    unsigned int i=0;
    ifstream file(path.c_str());
    if(file.is_open())
    {
        while(file.good())
            getline(file, dati[i++]);
    }
    else throw invalid_argument("Can't read: no file");
}

unsigned long int siz(std::string path)                          ///Restituisce lunghezza in byte di un file
{
    ifstream file(path.c_str());
    if (!file.is_open())
    {
        throw invalid_argument("Siz: no file");
    }
    file.seekg(0, ios::end);
    return file.tellg();
}

unsigned int gap_scan(std::string path)
{
        unsigned int cont=0;
        char ch;
        ifstream file (path.c_str(), ios::in);
        if(!file.is_open())
            throw invalid_argument("Gap scan: no file");
        while(!file.eof())
        {
            file.get(ch);
            if(ch=='\n')
                cont++;
        }
        return cont;
}

unsigned int cont_s(std::string path)
{
    ifstream file(path.c_str(), ios::binary);
    unsigned int help, cont=0;
    while(file.good())
    {
        file.read((char*)&help, sizeof(int));
        cont++;
    }
    return cont;
}
