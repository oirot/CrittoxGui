/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/


#include "c_file_synod.h"

#include <fstream>

#include "../func/funcs.h"
#include "../lowlevel/modf.h"

//Costruttori classe
c_file_synod::c_file_synod():block(0){};

c_file_synod::c_file_synod(std::string file_path, std::string psw_path, std::string sinodo_path, bool is_psw_path):c_file_ciclico(file_path, psw_path, is_psw_path), sinodo_path(sinodo_path), crip(true), block(0)
{   //Se il file è criptato caricare file sinodo
    std::fstream synod(sinodo_path.c_str(), ios::in);
    if(!synod.is_open())      ///se non si apre lancia eccezione
        throw invalid_argument("Synod file does not open");
    unsigned int ver=0;
    synod.read((char*)&ver, sizeof(int));
    if(ver!=num_gap) throw invalid_argument("Corrupted syn file");
    vett_sinodo= new unsigned int[num_gap];     ///Corrispondenza un numero nel file per riga
    for(unsigned int i=0; i<num_gap; i++) synod.read((char*)&vett_sinodo[i], sizeof(int)); ///carico vett_sinodo
    synod.close();
}

c_file_synod::c_file_synod(std::string file_path, std::string psw_path, unsigned int block, bool is_psw_path):c_file_ciclico(file_path, psw_path, is_psw_path), crip(false), block(block)
{
    unsigned long int num_tot;
    try{num_tot=this->block+(siz(file_path)%this->block);}
    catch(...) {throw;} ///da rivedere tutta la gestione degli errori
    num_for_line=(int)(num_tot/num_gap);
}

///METODO CHE AGGIUNGE I CARATTERI CASUALI
void c_file_synod::agg_random()
{
    root lista_mod[num_gap];
    vett_sinodo=new unsigned int[num_gap];
    for(unsigned int i=0; i<num_gap; i++)
    {
        lista_mod[i]=iniR(vett_file_mod[i]);
        vett_sinodo[i]=pazz(lista_mod[i], num_for_line);
        vett_file_mod[i]=deR(lista_mod[i]);
    }
}

///METODO CHE LEVA I CARATTERI CASUALI
void c_file_synod::leva_random()
{
    root lista_mod[num_gap];
    for(unsigned int i=0; i<num_gap; i++)
    {
        lista_mod[i]=iniR(vett_file[i]);
        depazz(lista_mod[i], vett_sinodo[i]);
        vett_file[i]=deR(lista_mod[i]);
    }
}

///METODI PER CRIPTARE
void c_file_synod::cripm()
{
    modf::gap=0;
    if(crip)    leva_random();
    make_v_m();
    if(!crip)     agg_random();
}

void c_file_synod::cripp()
{
    modf::gap=0;
    if(crip)    leva_random();
    make_v_p();
    if(!crip)     agg_random();
}

///METODI CHE RITORNANO COSE
unsigned int* c_file_synod::sinodo ()
{
    return vett_sinodo;
}

bool c_file_synod::is_enc() const
{
    return crip;
}

unsigned int c_file_synod::size_block() const
{
    return block;
}
