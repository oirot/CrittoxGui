/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/


#ifndef C_FILE_BASE_H_INCLUDED
#define C_FILE_BASE_H_INCLUDED
#include <string>

class c_file_base
{
protected:
    std::string file_path, psw, *vett_file, *vett_file_mod;
    bool flag;                        ///rilevatore errori
    unsigned int num_gap;            ///num gap= numero di *\n e num_for_line= numero di carattere casuali da agg/lev per linea
public:
    c_file_base();
    c_file_base(std::string file_path, std::string psw_path, bool is_psw_path);                    ///costruttore per criptare senza file sinodo
    virtual void cripm()=0;
    virtual void cripp()=0;
    std::string* finale();                ///restituisce il vettore finale
    unsigned int num_finale () const;               ///restituisce numero elementi nel vettore finale
    bool status() const;

};


#endif // C_FILE_BASE_H_INCLUDED
