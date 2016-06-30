/***************************************************************
 * Name:      CrittoxGuiMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: Aiello Vittorio ()
 * License:
 **************************************************************/

//Lunghezza minima password
#define MIN_PSW_LENGTH 5

#include "CrittoxGuiMain.h"

#include <fstream>

#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
#include <wx/msgdlg.h>
#include <wx/icon.h>

#include "Error.h"
#include "../func/funcs.h"
#include "interface.h"

#define HELP_MSG "This is an app that aims to crypt and decrypt text files. It can handle only ascii printable character (from '032' to '126').\nYou have to\
 insert the file you wanto to encrypt in the \"File to process path\" and where you want to save the encrypted text in \"Processed file path\". At\
 the right and center it has a radio button labeled whith \"Way round\" you have to chose one of them to crypt and the other to decrypt the same\
 file. When done the start button should be enabled, click on it to perform the task.\n\
It has two main modes to operate on files.\n\
The simple mode perforsm only a shift in the alphabet order using the key/psw you immitted in the \"Password\" field or you wrote in the first\
 line of a \"*.txt\" file. The file can be used switching on the \"by file\" radio button above the \"Password\" text.\n\
The advanced mode tries to gain more security by adding pseudorandom character to the text files in order to compromise a statistical analysis\
 of the files. It saves the position of the pseudorandom character in a file \"*.syn\". While decrypting a file that has been encrypted using\
 the advanced mode you have to select the previus generated \"*.syn\" file (you can share it via unsicure channel because it is encrypted by\
 binary XOR with the hash (sha512) of the key/psw) in the \"Synod file path\" field that is enabled by clicking on the \"Advanced\" switch. The\
 \"Block size:\" parameter told the aproximatively lenght of the encrypted file in advanced mode and give information to the app about the\
 number character to add to the encrypted file.\n\
In simple mode you need only set the file fields (\"File to process path\", \"Processed file path\") and give a key/psw (of lenght >= 5) and then\
 the start button should be enabled. In the advanced one you need also to entry the \"Synod file path\" field and specificate if you want to\
 encrypt or decrypt the file using the radio buttons in down and right labeled whit \Operation\".\n\
Hope you enjoy this!"

using namespace std;

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

///IDs
const long Crittox_guiFrame::ID_TXT_TITLE = wxNewId();
const long Crittox_guiFrame::ID_FileProcess = wxNewId();
const long Crittox_guiFrame::ID_FILEEND = wxNewId();
const long Crittox_guiFrame::ID_FILESYNODEC = wxNewId();
const long Crittox_guiFrame::ID_FILEPSWD = wxNewId();
const long Crittox_guiFrame::ID_TEXTPSWD = wxNewId();
const long Crittox_guiFrame::ID_STATICTEXT1 = wxNewId();
const long Crittox_guiFrame::ID_STATICTEXT2 = wxNewId();
const long Crittox_guiFrame::ID_SYNODTXT = wxNewId();
const long Crittox_guiFrame::ID_STATICTEXT4 = wxNewId();
const long Crittox_guiFrame::ID_BUTTON1 = wxNewId();
const long Crittox_guiFrame::ID_BUTTON3 = wxNewId();
const long Crittox_guiFrame::ID_RADIOPSW = wxNewId();
const long Crittox_guiFrame::ID_RADIOWAY = wxNewId();
const long Crittox_guiFrame::ID_RADIOMODE = wxNewId();
const long Crittox_guiFrame::ID_RADIOP = wxNewId();
const long Crittox_guiFrame::ID_SPINBLOCK = wxNewId();
const long Crittox_guiFrame::ID_STATICTEXT3 = wxNewId();
const long Crittox_guiFrame::ID_FILESYNODENC = wxNewId();
const long Crittox_guiFrame::ID_PANEL1 = wxNewId();
const long Crittox_guiFrame::idMenuQuit = wxNewId();
const long Crittox_guiFrame::idMenuAbout = wxNewId();
const long Crittox_guiFrame::ID_STATUSBAR1 = wxNewId();

///evnt table
BEGIN_EVENT_TABLE(Crittox_guiFrame,wxFrame)

END_EVENT_TABLE()

Crittox_guiFrame::Crittox_guiFrame(wxWindow* parent,wxWindowID id)
{
    ///Inizializzazione
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(595,400));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(208,200), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Title = new wxStaticText(Panel1, ID_TXT_TITLE, _("Crittox Gui"), wxPoint(192,16), wxDefaultSize, wxALIGN_CENTRE, _T("ID_TXT_TITLE"));
    wxFont TitleFont(28,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Title->SetFont(TitleFont);
    FileProcess = new wxFilePickerCtrl(Panel1, ID_FileProcess, _T("~/"), wxEmptyString, _T("TXT files only |*.txt"), wxPoint(30,100), wxSize(300,30), wxFLP_CHANGE_DIR|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FileProcess"));
    FileEnd = new wxFilePickerCtrl(Panel1, ID_FILEEND, _T("~/"), wxEmptyString, _T("TXT files only | *.txt"), wxPoint(30,175), wxSize(300,30), wxFLP_CHANGE_DIR|wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEEND"));
    FileSynodDec = new wxFilePickerCtrl(Panel1, ID_FILESYNODEC, _T("~/"), wxEmptyString, _T("SYN files only|*.syn"), wxPoint(30,250), wxSize(300,30), wxFLP_CHANGE_DIR|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILESYNODEC"));
    FileSynodDec->Disable();
    FilePswd = new wxFilePickerCtrl(Panel1, ID_FILEPSWD, _T("~/"), wxEmptyString, _T("*TXT fille only|*.txt"), wxPoint(390,135), wxSize(175,30), wxFLP_FILE_MUST_EXIST|wxFLP_OPEN, wxDefaultValidator, _T("ID_FILEPSWD"));
    FilePswd->Disable();
    FilePswd->Hide();
    TextPswd = new wxTextCtrl(Panel1, ID_TEXTPSWD, _("PSWSD"), wxPoint(390,135), wxSize(175,30), wxTE_PASSWORD, wxDefaultValidator, _T("ID_TEXTPSWD"));
    TextPswd->SetMaxLength(500);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("File to process path"), wxPoint(30,70), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(15,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Where to save"), wxPoint(30,145), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(15,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    SynodText = new wxStaticText(Panel1, ID_SYNODTXT, _("Synod file path"), wxPoint(30,220), wxDefaultSize, 0, _T("ID_SYNODTXT"));
    SynodText->Disable();
    wxFont SynodTextFont(15,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    SynodText->SetFont(SynodTextFont);
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Password"), wxPoint(390,70), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    wxFont StaticText4Font(15,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText4->SetFont(StaticText4Font);
    ButtonStart = new wxButton(Panel1, ID_BUTTON1, _("Start"), wxPoint(390,320), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    ButtonHelp = new wxButton(Panel1, ID_BUTTON3, _("Help"), wxPoint(485,320), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    wxString __wxRadioBoxChoices_1[2] =
    {
    	_("By hand"),
    	_("By file")
    };
    BoxPsw = new wxRadioBox(Panel1, ID_RADIOPSW, wxEmptyString, wxPoint(390,80), wxSize(170,44), 2, __wxRadioBoxChoices_1, 1, wxNO_BORDER, wxDefaultValidator, _T("ID_RADIOPSW"));
    wxString __wxRadioBoxChoices_2[2] =
    {
    	_("Plus"),
    	_("Minus")
    };
    BoxWay = new wxRadioBox(Panel1, ID_RADIOWAY, _("Way round"), wxPoint(392,190), wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, 0, wxDefaultValidator, _T("ID_RADIOWAY"));
    wxString __wxRadioBoxChoices_3[2] =
    {
    	_("Simple"),
    	_("Advanced")
    };
    BoxMode = new wxRadioBox(Panel1, ID_RADIOMODE, _("Mode"), wxPoint(30,305), wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, 0, wxDefaultValidator, _T("ID_RADIOMODE"));
    wxString __wxRadioBoxChoices_4[2] =
    {
    	_("Encrypt"),
    	_("Decrypt")
    };
    BoxOp = new wxRadioBox(Panel1, ID_RADIOP, _("Operation"), wxPoint(392,245), wxDefaultSize, 2, __wxRadioBoxChoices_4, 1, 0, wxDefaultValidator, _T("ID_RADIOP"));
    BoxOp->Disable();
    Block = new wxSpinButton(Panel1, ID_SPINBLOCK, wxPoint(240,320), wxSize(80,27), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBLOCK"));
    Block->SetRange(3072, 5000000);
    Block->Disable();
    textBlock = new wxStaticText(Panel1, ID_STATICTEXT3, _("Block size"), wxPoint(242,298), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    textBlock->Disable();
    FileSynodEnc = new wxFilePickerCtrl(Panel1, ID_FILESYNODENC, _T("~/"), wxEmptyString, _T("SYN files only |*.syn"), wxPoint(30,250), wxSize(300,30), wxFLP_CHANGE_DIR|wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILESYNODENC"));
    FileSynodEnc->Disable();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    ///EVNT handlers
    Connect(ID_FileProcess,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&Crittox_guiFrame::OnFileProcessFileChanged);
    Connect(ID_FILEEND,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&Crittox_guiFrame::OnFileEndFileChanged);
    Connect(ID_FILESYNODEC,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&Crittox_guiFrame::OnFileSynodFileChanged);
    Connect(ID_FILEPSWD,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&Crittox_guiFrame::OnFilePswdFileChanged);
    Connect(ID_TEXTPSWD,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Crittox_guiFrame::OnTextPswdText);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Crittox_guiFrame::OnButtonStartClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Crittox_guiFrame::OnButtonHelpClick);
    Connect(ID_RADIOMODE,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&Crittox_guiFrame::OnBoxModeSelect);
    Connect(ID_SPINBLOCK,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&Crittox_guiFrame::OnBlockChange);
    Connect(ID_FILESYNODENC,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&Crittox_guiFrame::OnFileSynodEncFileChanged);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Crittox_guiFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Crittox_guiFrame::OnAbout);
    Connect(ID_RADIOWAY, wxEVT_COMMAND_RADIOBOX_SELECTED, (wxObjectEventFunction)&Crittox_guiFrame::OnBoxWaySelect);
    Connect(ID_RADIOP, wxEVT_COMMAND_RADIOBOX_SELECTED, (wxObjectEventFunction)&Crittox_guiFrame::OnBOxOpSelect);
    Connect(ID_RADIOPSW, wxEVT_COMMAND_RADIOBOX_SELECTED, (wxObjectEventFunction)&Crittox_guiFrame::OnBoxPswSelect);
    //Bool per le radio box
    wayMinus=false;
    pswByFile=false;
    advanced=false;
    isEnc=false;
    //bool per la validità dei parametri inseriti
    flagStart=false;
    flagPsw=false;
    flagFile=false;
    flagEndFile=false;
    flagSynFileEnc=false;
    flagSynFileDec=false;
    flagFirstSynDec=true;
    flagFirstPsw=true;
    blockValue=3072;
    ButtonStart->Disable();
}

///Praticamente fa tutto lui
///#########################################################################
void Crittox_guiFrame::OnButtonStartClick(wxCommandEvent& event)
{
    flagStart=true;
    filesAdv fileValues={file, endFile, psw, synFile};
    boolFlags flagValues={!advanced, !wayMinus, !pswByFile, isEnc};
    interface *crittox;
    crittox=new interface(fileValues, flagValues, blockValue);
    try
    {crittox->doIt();}
    catch(invalid_argument e)
    {
        launchErr(e.what());
        flagStart=false;
        return;
    }
    catch(...)
    {
        launchErr("Unknown error!");
        flagStart=false;
        return;
    }
    wxMessageBox("Done!");
    flagStart=false;
}


///RADIO EVENT
void Crittox_guiFrame::OnBoxModeSelect(wxCommandEvent& event)
{
    advanced=BoxMode->GetSelection();
    if(advanced)
    {
        SynodText->Enable();
        BoxOp->Enable();
        if(isEnc)
        {
            FileSynodEnc->Hide();
            FileSynodEnc->Disable();
            FileSynodDec->Enable();
            FileSynodDec->Show();
            Block->Disable();
            textBlock->Disable();
            ctrSynod();
        }
        else
        {
            FileSynodDec->Hide();
            FileSynodDec->Disable();
            FileSynodEnc->Enable();
            FileSynodEnc->Show();
            Block->Enable();
            textBlock->Enable();
        }
    }
    else
    {
        BoxOp->Disable();
        Block->Disable();
        textBlock->Disable();
        SynodText->Disable();
        FileSynodDec->Disable();
        FileSynodEnc->Disable();
    }
    ctrStart();
}

void Crittox_guiFrame::OnBoxPswSelect(wxCommandEvent& event)
{
    pswByFile=BoxPsw->GetSelection();
    if(pswByFile)
    {
        psw=FilePswd->GetPath();
        TextPswd->Disable();
        TextPswd->Hide();
        FilePswd->Enable();
        FilePswd->Show();
    }
    else
    {
        psw=TextPswd->GetValue();
        FilePswd->Hide();
        FilePswd->Disable();
        TextPswd->Enable();
        TextPswd->Show();
    }
    ctrPsw();
    ctrStart();
}

void Crittox_guiFrame::OnBOxOpSelect(wxCommandEvent& event)
{
    isEnc=BoxOp->GetSelection();
    if(isEnc)
    {
        FileSynodEnc->Disable();
        FileSynodEnc->Hide();
        FileSynodDec->Enable();
        FileSynodDec->Show();
        Block->Disable();
        textBlock->Disable();
        ctrSynod();
    }
    else
    {
        FileSynodDec->Disable();
        FileSynodDec->Hide();
        FileSynodEnc->Enable();
        FileSynodEnc->Show();
        Block->Enable();
        textBlock->Enable();
    }
    ctrStart();

}

void Crittox_guiFrame::OnBoxWaySelect(wxCommandEvent& event)
{
    wayMinus=BoxWay->GetSelection();
}

void Crittox_guiFrame::OnBlockChange(wxSpinEvent& event)
{
    blockValue=Block->GetValue();
}

///CONTROL FUNCTION
void Crittox_guiFrame::ctrPsw()
{
    if(pswByFile)
    {
        ifstream pswStream (psw.c_str());
        if(!pswStream.is_open())
        {
            if(!flagFirstPsw) launchErr("Bad password file.");
            return;
        }
        string ctrString;
        getline(pswStream, ctrString);
        pswStream.close();
        if(ctrString.size()>=MIN_PSW_LENGTH) flagPsw=true;
        else
        {
            flagPsw=false;
            launchErr("Too short password.");
        }
    }
    else
        if(psw.size()>=MIN_PSW_LENGTH) flagPsw=true;
        else flagPsw=false;
}

void Crittox_guiFrame::ctrSynod()
{
    //Misura di sicurezza per evitare che faccia casino quando chiamata per sbaglio
    if(isEnc)
    {
        ifstream synStream (synFile.c_str(), ios::binary);
        if(!synStream.is_open())
        {
            if(!flagFirstSynDec)
            {
                launchErr("Bad synod file: it does not open.");
            }
            return;
        }
        unsigned int synValue=0;
        synStream.read((char*)&synValue, sizeof(int));
        synStream.close();
        if(contFile==synValue) flagSynFileDec=true;
        else
        {
            flagSynFileDec=false;
            if(!flagFirstSynDec)
            {
                launchErr("Bad synod file: it does not match.");
            }
        }
    }
}

void Crittox_guiFrame::ctrStart()
{
    bool verStart=false;
    int numCase;
    if(advanced && isEnc) numCase=0;
    else if(advanced && !isEnc) numCase=1;
    else numCase=2;
    switch(numCase)
    {
    case(0):
        if(flagPsw && !flagStart && flagFile && flagEndFile && flagSynFileDec)
            verStart=true;
        break;
    case(1):
         if(flagPsw && !flagStart && flagFile && flagEndFile && flagSynFileEnc)
            verStart=true;
        break;
    case(2):
        if(flagPsw && (!flagStart) && flagFile && flagEndFile)
            verStart=true;
        break;
    }
    ButtonStart->Enable(verStart);
}

///Eventi di input
void Crittox_guiFrame::OnFileProcessFileChanged(wxFileDirPickerEvent& event)
{
    file=FileProcess->GetPath();
    contFile=gap_scan(file);
    if(contFile>0)
        flagFile=true;
    else
    {
        launchErr("Empty file to work on.");
        flagFile=false;
    }
    ctrStart();
}

void Crittox_guiFrame::OnFileEndFileChanged(wxFileDirPickerEvent& event)
{
    endFile=FileEnd->GetPath();
    flagEndFile=true;
    ctrStart();
}

void Crittox_guiFrame::OnFileSynodFileChanged(wxFileDirPickerEvent& event)    ///DEC is_enc=true
{
    synFile=FileSynodDec->GetPath();
    ctrSynod();
    flagFirstSynDec=false;
    ctrStart();
}

void Crittox_guiFrame::OnFileSynodEncFileChanged(wxFileDirPickerEvent& event)
{
    synFile=FileSynodEnc->GetPath();
    flagSynFileEnc=true;
    ctrStart();
}

void Crittox_guiFrame::OnTextPswdText(wxCommandEvent& event)
{
    psw=TextPswd->GetValue();
    ctrPsw();
    ctrStart();
}

void Crittox_guiFrame::OnFilePswdFileChanged(wxFileDirPickerEvent& event)
{
    psw=FilePswd->GetPath();
    ctrPsw();
    flagFirstPsw=false;
    ctrStart();
}

///Mostra messaggio di aiuto
void Crittox_guiFrame::OnButtonHelpClick(wxCommandEvent& event)
{
    wxMessageBox(HELP_MSG, "Help message");
}

///lancia errori
void Crittox_guiFrame::launchErr(string errMsg)
{
    Error *err= new Error(this, errMsg);
    err->ShowModal();
    delete err;
}

Crittox_guiFrame::~Crittox_guiFrame()
{
    //(*Destroy(Crittox_guiFrame)
    //*)
}

void Crittox_guiFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Crittox_guiFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = "CrittoxGui a GUI to crypt and decrypt text files.\nTo gain more info click on \"Help\" button";
    wxMessageBox(msg, _("Welcome to..."));
}
