/***************************************************************
 * Name:      CrittoxGuiMain.h
 * Purpose:   Defines Application Frame
 * Author:    Aiello Vittorio (vittorio.aiello98@gmail.com)
 * Created:   2016-06-19
 * Copyright: Aiello Vittorio ()
 * License: GNU GPLv3
 **************************************************************/

#ifndef CRITTOXGUIMAIN_H
#define CRITTOXGUIMAIN_H

#include <wx/spinbutt.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/radiobox.h>


class Crittox_guiFrame: public wxFrame
{
    public:

        Crittox_guiFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Crittox_guiFrame();

    private:

        ///Handlers
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnRadioBox3Select(wxCommandEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnBoxModeSelect(wxCommandEvent& event);
        void OnBoxPswSelect(wxCommandEvent& event);
        void OnBOxOpSelect(wxCommandEvent& event);
        void OnBoxWaySelect(wxCommandEvent& event);
        void OnBlockChange(wxSpinEvent& event);
        void OnPanel1Paint1(wxPaintEvent& event);
        void OnFileProcessFileChanged(wxFileDirPickerEvent& event);
        void OnFileEndFileChanged(wxFileDirPickerEvent& event);
        void OnFileSynodFileChanged(wxFileDirPickerEvent& event);
        void OnTextPswdText(wxCommandEvent& event);
        void OnButtonStartClick(wxCommandEvent& event);
        void OnButtonHelpClick(wxCommandEvent& event);
        void OnFileSynodEncFileChanged(wxFileDirPickerEvent& event);
        void OnFilePswdFileChanged(wxFileDirPickerEvent& event);

        ///IDs
        static const long ID_TXT_TITLE;
        static const long ID_FileProcess;
        static const long ID_FILEEND;
        static const long ID_FILESYNODEC;
        static const long ID_FILEPSWD;
        static const long ID_TEXTPSWD;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_SYNODTXT;
        static const long ID_STATICTEXT4;
        static const long ID_BUTTON1;
        static const long ID_BUTTON3;
        static const long ID_RADIOPSW;
        static const long ID_RADIOWAY;
        static const long ID_RADIOMODE;
        static const long ID_RADIOP;
        static const long ID_SPINBLOCK;
        static const long ID_STATICTEXT3;
        static const long ID_FILESYNODENC;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;

        ///dichiarazioni
        wxStaticText* Title;
        wxRadioBox* BoxOp;
        wxPanel* Panel1;
        wxRadioBox* BoxPsw;
        wxStaticText* SynodText;
        wxStatusBar* StatusBar1;
        wxFilePickerCtrl* FileSynodEnc;
        wxSpinButton* Block;
        wxFilePickerCtrl* FileSynodDec;
        wxStaticText* StaticText1;
        wxRadioBox* BoxMode;
        wxButton* ButtonHelp;
        wxFilePickerCtrl* FilePswd;
        wxFileDialog* FileDialog1;
        wxTextCtrl* TextPswd;
        wxFilePickerCtrl* FileProcess;
        wxStaticText* StaticText4;
        wxRadioBox* BoxWay;
        wxStaticText* StaticText2;
        wxButton* ButtonStart;
        wxStaticText* textBlock;
        wxFilePickerCtrl* FileEnd;
        ///Control function
        void ctrPsw();
        void ctrStart();
        void ctrSynod();
        void launchErr(std::string errMsg);
        //Bool per le radio box
        bool wayMinus, pswByFile, advanced, isEnc;
        //bool per la validità dei parametri inseriti
        bool flagStart, flagPsw, flagFile, flagEndFile, flagSynFileDec,
                                                    flagSynFileEnc, flagFirstSynDec, flagFirstPsw;
        unsigned int blockValue, contFile;
        //string per i parametri
        std::string psw, file, endFile, synFile, helpMsg;

        DECLARE_EVENT_TABLE()
};

#endif // CRITTOXGUIMAIN_H
