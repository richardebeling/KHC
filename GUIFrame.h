///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/stc/stc.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/slider.h>
#include <wx/timer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameTEMPLATE
///////////////////////////////////////////////////////////////////////////////
class GUIFrameTEMPLATE : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			idMenuOpen = 1000,
			idMenuReload,
			idMenuSave,
			idMenuSaveAs,
			idMenuClose,
			idMenuQuit,
			idMenuResetAfterStp,
			idMenuAllowSignedRegister,
			idMenuAdaptLineNumbers,
			idMenuReleaseMode,
			idMenuAbout,
			idMenuHelp
		};
		
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* optionMenu;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxStyledTextCtrl* styledTextCode;
		wxGrid* gridRegister;
		wxButton* buttonClearRegister;
		wxStaticText* staticRegisterCount;
		wxSpinCtrl* spinRegisterCount;
		wxButton* buttonRun;
		wxButton* buttonStop;
		wxButton* buttonStep;
		wxButton* buttonReset;
		wxSlider* sliderExecutionSpeed;
		wxStaticText* staticSpeed;
		wxTimer timerRun;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReload( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnResetAfterStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAllowSignedRegister( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAdaptLineNumbers( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReleaseMode( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSTCChange( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnClearRegister( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRegisterCount( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnRegisterCount( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRun( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStep( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExecutionSpeedChanged( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnTimerRun( wxTimerEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrameTEMPLATE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Know How Computer Emulator - New Program"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUIFrameTEMPLATE();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class HelpFrameTEMPLATE
///////////////////////////////////////////////////////////////////////////////
class HelpFrameTEMPLATE : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText4;
	
	public:
		
		HelpFrameTEMPLATE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Know How Computer - Help"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 764,306 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_TOOL_WINDOW|wxTAB_TRAVERSAL );
		
		~HelpFrameTEMPLATE();
	
};

#endif //__GUIFRAME_H__
