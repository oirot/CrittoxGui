/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/


#ifndef C_FILE_SYNOD_H_INCLUDED
#define C_FILE_SYNOD_H_INCLUDED

#include "virtual/c_file_ciclico.h"

class c_file_synod : public c_file_ciclico
{
private:
    std::string sinodo_path;
    bool crip;
    unsigned int num_for_line, *vett_sinodo;      ///num gap= numero di *\n e num_for_line= numero di carattere casuali da agg/lev per linea
    const unsigned int block;
    void agg_random();
    void leva_random();
public:
    c_file_synod(std::string file_path, std::string psw_path, std::string sinodo_path, bool is_psw_path=true);       ///costruttore per criptare con file sinodo bool per il gap (true = si gap)
    c_file_synod(std::string file_path, std::string psw_path, unsigned int block, bool is_psw_path=true);
    c_file_synod();
    unsigned int* sinodo ();
    void cripm();
    void cripp();
    bool is_enc() const;
    unsigned int size_block() const;
};

#endif // C_FILE_SYNOD_H_INCLUDED
