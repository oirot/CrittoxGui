/***************************************************************
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: 2016 Aiello Vittori
 * License: GNU GPLv3
 **************************************************************/

#ifndef ERROR_H
#define ERROR_H

//(*Headers(Error)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
//*)

class Error: public wxDialog
{
	public:

		Error(wxWindow* parent, std::string);
		virtual ~Error();

		//(*Declarations(Error)
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxStaticBox* StaticBox1;
		//*)

	protected:

		//(*Identifiers(Error)
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(Error)
		void OnButton1Click(wxCommandEvent& event);
		//*)
		wxString err;

		DECLARE_EVENT_TABLE()
};

#endif
