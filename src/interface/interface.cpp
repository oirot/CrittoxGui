/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/

#include "interface.h"

#include <stdexcept>

#include "../func/funcs.h"


interface::interface(filesAdv specs, boolFlags flags, unsigned int block):specs(specs), flags(flags), block(block)
{
    ///TROVO QUALE COSTRUTTORE DEVO CHIAMARE (LO SO È ORRENDO MA ERANO LE 3:15 ED AVEVO SONNO)
    if(flags.simple&&flags.hand) type=0;
    else if(flags.simple && !flags.hand) type=1;
    else if(flags.hand && flags.is_enc) type=2;
    else if(!flags.hand && flags.is_enc) type=3;
    else if(flags.hand && !flags.is_enc) type=4;
    else if(!flags.hand && !flags.is_enc) type=5;
    switch(type)
    {
    case(0):
        try{puntCFile= new c_file(specs.file, specs.psw, false);}
        catch(...){throw;}
        break;
    case(1):
        try{puntCFile= new c_file(specs.file, specs.psw);}
        catch(...){throw;}
        break;
    case(2):
        try{puntCFileS= new c_file_synod(specs.file, specs.psw, specs.synodFile, false);}
        catch(...){throw;}
        break;
    case(3):
        try{puntCFileS= new c_file_synod(specs.file, specs.psw, specs.synodFile);}
        catch(...){throw;}
        break;
    case(4):
        try{puntCFileS= new c_file_synod(specs.file, specs.psw, this->block, false);}
        catch(...){throw;}
        break;
    case(5):
        try{puntCFileS= new c_file_synod(specs.file, specs.psw, this->block);}
        catch(...){throw;}
        break;
    }
};


bool interface::doIt() const
{
    switch(type)
    {
    case(5):
    case(4):
            try{
                flags.way ? puntCFileS->cripp() : puntCFileS->cripm();
                scrivi(specs.synodFile, puntCFileS->sinodo(), puntCFileS->num_finale());
                scrivi(specs.endFile, puntCFileS->finale(), puntCFileS->num_finale());}
            catch(...){throw;}
            break;
    case(3):
    case(2):
            try{
                flags.way ? puntCFileS->cripp() : puntCFileS->cripm();
                scrivi(specs.endFile, puntCFileS->finale(), puntCFileS->num_finale());}
            catch(...){throw;}
            break;
    default:
            try{
                flags.way ? puntCFile->cripp() : puntCFile->cripm();
                scrivi(specs.endFile, puntCFile->finale(), puntCFile->num_finale());}
            catch(...){throw;}
            break;
    }
    return true;
}
