/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/


#include "c_file_base.h"

#include <fstream>

#include "../../func/funcs.h"
#include "../../lowlevel/modf.h"


/**impostare un massimo per caratteri per riga di 2^32 perchè senno non funziona num_for_line e cercare
eventualmente altre limitazioni
altra limitazione: il block non può essere multiplo della lunghezza del file
probabile altra modalità, con riprocessamento se la password e più lunga del messaggio con la restante psw*/



c_file_base::c_file_base(std::string file_path, std::string psw_path, bool is_psw_file):file_path(file_path)
{
    //inizializzo alcuni valori
    flag=false;
    //Apro i due stream
    if(is_psw_file)
    {
        fstream psw_file (psw_path.c_str(), ios::in);
        if(!psw_file.is_open()) throw invalid_argument("File error: no psw file");
        getline(psw_file, psw);            //carico la psw e chiudo il suo stream
        psw_file.close();
    }
    else psw=psw_path;
    try{
        num_gap=gap_scan(file_path);}       //conto il numero di stringhe che mi serviranno
    catch(int e){
        throw;}
    fstream cleartxt (file_path.c_str(), ios::in);
    //controllo siano aperti, se non lo sono viene lanciata un eccezione
    if(!cleartxt.is_open())
        throw invalid_argument("Cleartext does not open");
    vett_file= new std::string[num_gap];          //dichiaro il vettore che conterrà il testo in chiaro
    for(unsigned int i=0; i<num_gap; i++)
        getline(cleartxt, this->vett_file[i]);          //copio il file riga per riga in vett_fil
    cleartxt.close();
     //alloco i puntatori a vettori
    vett_file_mod= new std::string[num_gap];
    flag=true;
    if(!psw.size()) throw invalid_argument("Psw size: 0");
}

c_file_base::c_file_base()
{
    ///Costruttore per inizializzare vettori
    //do nothign
}

std::string* c_file_base::finale()
{
    return vett_file_mod;
}

unsigned int c_file_base::num_finale() const
{
    return num_gap;
}

bool c_file_base::status () const
{
    return flag;
}

