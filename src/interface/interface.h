
/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <string>

#include "../c_file/c_file.h"
#include "../c_file/c_file_synod.h"
#include "types.h"

///CLASSE PER RENDERE MENO CAOTICA LA SCELATA DELLA CLASSE GIUSTA E DEI METODI NEL GUIMAIN

class interface
{
private:
    bool stat;
    filesAdv specs;
    boolFlags flags;
    unsigned int block;
    c_file* puntCFile=NULL;
    c_file_synod* puntCFileS=NULL;
    int type;
public:
    interface(filesAdv specs, boolFlags flags, unsigned int block);
    bool doIt() const;
};

#endif // INTERFACE_H_INCLUDED
