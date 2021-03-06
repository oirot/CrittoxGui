/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/


#ifndef MODF_H_INCLUDED
#define MODF_H_INCLUDED

#include <string>

class modf
{
protected:
    std::string text, psw;
    char* mod;
    unsigned long int num_text, num_psw;
    int *punt_int_text, *punt_int_psw, *imod;
    void sizeS();                       ///Inizializza np e nt
    void Conv_IntChar();                       ///Conversione da intero nel corrispondente carattere ascii
    void Conv_CharInt();                       ///Conversione da carattere a corrispondente codice ascii intero
    int som(int, int) const;            ///Somma ciclica
    int dif(int, int) const;            ///Differenza ciclica
public:
    static unsigned long int gap;
    modf(std::string, std::string);               ///Costruttore
    modf();                             ///Costruttore aggiunto per inizializzare vettori
    virtual void codp();                ///Algoritmo di criptazione che addiziona ciclicamente
    virtual void codm();                ///Algoritmo di criptazione che sottrae ciclicamente
    std::string t() const;                   ///Ritorna text
    std::string p() const;                   ///   "    psw
    char* m() const;                    ///   "    mod (puntatore al primo elemento del vettore)
    unsigned long int n_p() const;                    ///   "    np
    unsigned long int n_t() const;                    ///   "    nt
    int* it() const;                    ///   "    itext (puntatore al primo elemento del vettore)
    int* ip() const;                    ///   "    ipsw         "        "        "        "
    int* im() const;                    ///   "    imod         "        "        "        "
    std::string ms() const;                  ///   "    mod sotto forma di stringa
};

#endif // MODF_H_INCLUDED
