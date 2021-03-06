/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/


#include "modf.h"

///dipendendi dal charset utilizzato
#define MAX_CHARSET 126
#define MIN_CHARSET 32
#define DIFF_CHARSET 95

///Gap spostato, utilizzarlo per azzerare o cambiare il gab mettendolo nel file .cpp
#ifndef GAP
#define GAP
unsigned long int modf::gap=0;
#endif // GAP

modf::modf (std::string text, std::string psw):text(text), psw(psw)
{
    num_text=0;
    num_psw=0;
    sizeS();
    punt_int_text=new int [num_text];
    punt_int_psw=new int [num_psw];
    mod=new char [num_text+1];
    imod=new int [num_text];
    Conv_CharInt();
}

modf::modf()
{
    ///costruttore per inizializzare vettori
        ///do nothing
}

void modf::sizeS()      ///metodo per inizializzare in valori nt e np (numero di caratteri di psw e text)
{
    unsigned long int i=0;
    while(text[i++]!='\0') num_text++;
    i=0;
    while(psw[i++]!='\0') num_psw++;
}

void modf::Conv_CharInt()
{
    for(unsigned long int i=0; i<num_text; i++)
        punt_int_text[i]=text[i];
    for(int i=0; i<num_psw; i++)
        punt_int_psw[i]=psw[i];
}

void modf::Conv_IntChar()
{
    unsigned long int i;
    for(i=0; i<num_text; i++)
        mod[i]=imod[i];
    mod[i]='\0';
}

///ALGORITMI PER LA SOMMA E LA DIFFERENZA CICLICA

int modf::som(int a, int b) const
{
    if((a+b)<=MAX_CHARSET)
        return a+b;
    else
        return modf::som(a-DIFF_CHARSET, b);
}

int modf::dif(int a, int b) const
{
    if((a-b)>=MIN_CHARSET)
        return a-b;
    else
        return modf::dif(a+DIFF_CHARSET, b);
}
///FINE

void parse_txt()
{

}

///ALGORITMI CHE IMPLEMENTA SOMMA E DIFF CICLICA SU VETTORI
void modf::codp()
{
    bool i=false;
    unsigned long int k=gap, j=0;
    while(j<num_text)
    {
        if(!i) k=gap;
        else k=0;
        while(j<num_text && k<num_psw)
        {
            imod[j]=modf::som(punt_int_text[j], punt_int_psw[k]);
            j++;
            k++;
        }
        i=true;

    }
    Conv_IntChar();
    gap=k;
}



void modf::codm()
{
    unsigned long int j=0, k=gap;
    bool i=false;
    while(j<num_text)
    {
        if(!i) k=gap;
        else k=0;
        while(j<num_text && k<num_psw)
        {
            imod[j]=modf::dif(punt_int_text[j], punt_int_psw[k]);
            j++;
            k++;
        }
        i=true;
    }
    Conv_IntChar();
    gap=k;
}

///FINE

///METODI CHE RESTITUISCONO COSE
std::string modf::t() const
{
    return text;
}

std::string modf::p() const
{
    return psw;
}

char* modf::m() const
{
    return mod;
}

int* modf::it() const
{
    return punt_int_text;
}

int* modf::ip() const
{
    return punt_int_psw;
}

int* modf::im() const
{
    return imod;
}

unsigned long int modf::n_p() const
{
    return num_psw;
}

unsigned long int modf::n_t() const
{
    return num_text;
}

std::string modf::ms() const
{
    std::string a;
    a=mod;
    return a;
}
