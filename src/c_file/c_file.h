/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/

#ifndef C_FILE_H_INCLUDED
#define C_FILE_H_INCLUDED                   ///Tutto da rivedere                    ///Devo rivedere le inclusioni, creare un altro file.h in cui includere tutto
#include "virtual/c_file_ciclico.h"
#include "../lowlevel/modf.h"
                                        ///Il numero di lettere della psw da un unsigned e il numero di gap da un unsigned
                                            ///Ma ci saranno delle limitazioni, a livello di controllo per impedire di processare file enormi
//Classe per criptare e decriptare usando la tecnica del cifrato romano
class c_file : public c_file_ciclico
{
public:
    c_file();
    c_file(std::string file_path, std::string psw_path, bool is_psw_path=true);                    ///costruttore per criptare senza file sinodo
    void cripm();
    void cripp();
};

#endif // C_FILE_H_INCLUDED
