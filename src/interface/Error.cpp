/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittori
 * License: GNU GPLv3
 **************************************************************/

#include "Error.h"

//(*InternalHeaders(Error)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(Error)
const long Error::ID_STATICBOX1 = wxNewId();
const long Error::ID_STATICTEXT1 = wxNewId();
const long Error::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Error,wxDialog)
	//(*EventTable(Error)
	//*)
END_EVENT_TABLE()

Error::Error(wxWindow* parent, std::string error)
{
	//(*Initialize(Error)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(190,126));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("ERROR!"), wxPoint(50,8), wxSize(90,20), 0, _T("ID_STATICBOX1"));
	wxFont StaticBox1Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticBox1->SetFont(StaticBox1Font);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Label"), wxPoint(10,42), wxSize(176,40), 0, _T("ID_STATICTEXT1"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Cancel"), wxPoint(8,86), wxSize(64,30), 0, wxDefaultValidator, _T("ID_BUTTON1"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Error::OnButton1Click);
	//*)
	wxString err(error.c_str(), wxConvUTF8);
	StaticText1->SetLabel(err);
}

Error::~Error()
{
	//(*Destroy(Error)
	//*)
}


void Error::OnButton1Click(wxCommandEvent& event)
{
    this->EndModal(0);
}
