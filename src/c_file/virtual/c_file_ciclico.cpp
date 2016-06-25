/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/


#include "c_file_ciclico.h"

#include <string>

#include "../../lowlevel/modf.h"

c_file_ciclico::c_file_ciclico()
{

}

c_file_ciclico::c_file_ciclico(std::string path_text, std::string psw, bool is_psw_path):c_file_base(path_text, psw, is_psw_path){}

void c_file_ciclico::make_v_p()
{
    ///funzione per criptare secondo cifrato romano i vettori di stringhe
    for(unsigned int i=0; i<num_gap; i++)
    {
        modf help;     //variable di supporto
        help=modf (vett_file[i], psw);   //
        help.codp();
        vett_file_mod[i]=help.ms();
    }
}

void c_file_ciclico::make_v_m()
{
    for(unsigned int i=0; i<num_gap; i++)
    {
        modf help;
        help=modf (vett_file[i], psw);
        help.codm();
        vett_file_mod[i]=help.ms();
    }
}
