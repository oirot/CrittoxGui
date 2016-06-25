/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittori
 * License: GNU GPLv3
 **************************************************************/

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <string>

using namespace std;

typedef struct { string file;
                 string endFile;
                 string psw;
                 string synodFile;}filesAdv;

typedef struct {
                 bool simple;
                 bool way;
                 bool hand;
                 bool is_enc;}boolFlags;

#endif // TYPES_H_INCLUDED
