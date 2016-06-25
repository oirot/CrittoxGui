/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittorio
 * License: GNU GPLv3
 **************************************************************/

#ifndef LISTA_INCLUDED
#define LISTA_INCLUDED

using namespace std;

typedef struct lett    ///Lista di caratteri
{
    char a;
    struct lett* next;
}item;

typedef item* root;   ///Puntatore a lista di caratteri (root)


#endif // LISTA_INCLUDED
