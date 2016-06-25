/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/

#ifndef SHARON
#define SHARON

#include "c_file.h"

/**impostare un massimo per caratteri per riga di 2^32 perchè senno non funziona num_for_line e cercare
eventualmente altre limitazioni
altra limitazione: il block non può essere multiplo della lunghezza del file
probabile altra modalità, con riprocessamento se la password e più lunga del messaggio con la restante psw*/



//Costruttori classe
c_file::c_file(std::string file_path, std::string psw_path, bool is_psw_path):c_file_ciclico(file_path, psw_path, is_psw_path){};

c_file::c_file()
{
    ///do nothign
};

//Funzioni per criptare e decriptare
void c_file::cripp()
{
    modf::gap=0;
    make_v_p();
}

void c_file::cripm()
{
    modf::gap=0;
    make_v_m();
}

#endif // SHARON
