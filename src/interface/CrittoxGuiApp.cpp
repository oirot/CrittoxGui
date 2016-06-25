/***************************************************************
 * Name:      CrittoxGuiApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: Aiello Vittorio ()
 * License: GNU GPLv3
 **************************************************************/


#include "CrittoxGuiApp.h"
#include "CrittoxGuiMain.h"

#include <wx/image.h>


IMPLEMENT_APP(Crittox_guiApp);

bool Crittox_guiApp::OnInit()
{
    ///inizializzazione
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Crittox_guiFrame* Frame = new Crittox_guiFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    return wxsOK;

}

