/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/


#ifndef C_FILE_CICLICO_H_INCLUDED
#define C_FILE_CICLICO_H_INCLUDED
#include "c_file_base.h"

class c_file_ciclico : public c_file_base   ///SEPARATA DA C_FILE_BASE PER FUTURE AGGIUNTE DI METODI DI CRIPTAZIONE COME XOR BINARIO
{
protected:
    void make_v_p();
    void make_v_m();            ///Somma e diff ciclica
public:
    c_file_ciclico();
    c_file_ciclico(std::string path_text, std::string psw, bool is_psw_path);
};


#endif // C_FILE_CICLICO_H_INCLUDED
