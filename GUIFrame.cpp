///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrameTEMPLATE::GUIFrameTEMPLATE( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileOpen;
	menuFileOpen = new wxMenuItem( fileMenu, idMenuOpen, wxString( wxT("&Open...") ) + wxT('\t') + wxT("CTRL+O"), wxT("Open a file"), wxITEM_NORMAL );
	fileMenu->Append( menuFileOpen );
	
	wxMenuItem* menuFileReload;
	menuFileReload = new wxMenuItem( fileMenu, idMenuReload, wxString( wxT("&Reload current") ) + wxT('\t') + wxT("CTRL+R"), wxT("Reload the current file (in case it has been modified)"), wxITEM_NORMAL );
	fileMenu->Append( menuFileReload );
	menuFileReload->Enable( false );
	
	wxMenuItem* menuFileSave;
	menuFileSave = new wxMenuItem( fileMenu, idMenuSave, wxString( wxT("&Save") ) + wxT('\t') + wxT("CTRL+S"), wxT("Save the current program"), wxITEM_NORMAL );
	fileMenu->Append( menuFileSave );
	menuFileSave->Enable( false );
	
	wxMenuItem* menuFileSaveAs;
	menuFileSaveAs = new wxMenuItem( fileMenu, idMenuSaveAs, wxString( wxT("Save &As...") ) , wxT("Save the current program"), wxITEM_NORMAL );
	fileMenu->Append( menuFileSaveAs );
	
	wxMenuItem* menuFileClose;
	menuFileClose = new wxMenuItem( fileMenu, idMenuClose, wxString( wxT("&Close") ) + wxT('\t') + wxT("CTRL+W"), wxT("Close the current file."), wxITEM_NORMAL );
	fileMenu->Append( menuFileClose );
	
	fileMenu->AppendSeparator();
	
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	mbar->Append( fileMenu, wxT("&File") ); 
	
	optionMenu = new wxMenu();
	wxMenuItem* menuOptionResetAfterStp;
	menuOptionResetAfterStp = new wxMenuItem( optionMenu, idMenuResetAfterStp, wxString( wxT("&Reset after stp") ) , wxT("If checked, the program will automatically jump back to 1 when \"stp\" is reached."), wxITEM_CHECK );
	optionMenu->Append( menuOptionResetAfterStp );
	
	wxMenuItem* menuOptionAllowSignedRegister;
	menuOptionAllowSignedRegister = new wxMenuItem( optionMenu, idMenuAllowSignedRegister, wxString( wxT("Allow &signed register value") ) , wxT("If checked, the program will allow the register's values to go below 0"), wxITEM_CHECK );
	optionMenu->Append( menuOptionAllowSignedRegister );
	
	wxMenuItem* menuOptionAdaptLineNumbers;
	menuOptionAdaptLineNumbers = new wxMenuItem( optionMenu, idMenuAdaptLineNumbers, wxString( wxT("Adapt &line numbers") ) , wxT("If checked, the program will try to keep \"jmp\" commands pointing to the same line even if you add or delete lines."), wxITEM_CHECK );
	optionMenu->Append( menuOptionAdaptLineNumbers );
	
	wxMenuItem* menuOptionReleaseMode;
	menuOptionReleaseMode = new wxMenuItem( optionMenu, idMenuReleaseMode, wxString( wxT("R&elease mode") ) , wxT("If checked, the program will not update the GUI after every step but run the program internally and display the result when done. This will result in an extremely faster calculation."), wxITEM_CHECK );
	optionMenu->Append( menuOptionReleaseMode );
	
	mbar->Append( optionMenu, wxT("&Options") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About...") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	wxMenuItem* menuHelpHelp;
	menuHelpHelp = new wxMenuItem( helpMenu, idMenuHelp, wxString( wxT("&Help...") ) + wxT('\t') + wxT("F2"), wxT("Display a windows with all available commands and what they do including additional information about this program."), wxITEM_NORMAL );
	helpMenu->Append( menuHelpHelp );
	
	mbar->Append( helpMenu, wxT("&Help") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* MainWindowsSizer;
	MainWindowsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	styledTextCode = new wxStyledTextCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
	styledTextCode->SetUseTabs( true );
	styledTextCode->SetTabWidth( 4 );
	styledTextCode->SetIndent( 4 );
	styledTextCode->SetTabIndents( true );
	styledTextCode->SetBackSpaceUnIndents( true );
	styledTextCode->SetViewEOL( false );
	styledTextCode->SetViewWhiteSpace( false );
	styledTextCode->SetMarginWidth( 2, 0 );
	styledTextCode->SetIndentationGuides( true );
	styledTextCode->SetMarginWidth( 1, 0 );
	styledTextCode->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	styledTextCode->SetMarginWidth( 0, styledTextCode->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	styledTextCode->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	styledTextCode->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	styledTextCode->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	styledTextCode->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	styledTextCode->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	styledTextCode->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	styledTextCode->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	styledTextCode->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	styledTextCode->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	styledTextCode->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	styledTextCode->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	styledTextCode->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	styledTextCode->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	styledTextCode->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	styledTextCode->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	styledTextCode->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	styledTextCode->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	MainWindowsSizer->Add( styledTextCode, 1, wxEXPAND|wxRIGHT, 5 );
	
	wxStaticBoxSizer* sbRegister;
	sbRegister = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Register") ), wxVERTICAL );
	
	gridRegister = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxSize( 127,-1 ), wxALWAYS_SHOW_SB );
	
	// Grid
	gridRegister->CreateGrid( 30, 1 );
	gridRegister->EnableEditing( true );
	gridRegister->EnableGridLines( true );
	gridRegister->EnableDragGridSize( false );
	gridRegister->SetMargins( 0, 0 );
	
	// Columns
	gridRegister->EnableDragColMove( false );
	gridRegister->EnableDragColSize( true );
	gridRegister->SetColLabelSize( 30 );
	gridRegister->SetColLabelValue( 0, wxT("Register") );
	gridRegister->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	gridRegister->EnableDragRowSize( true );
	gridRegister->SetRowLabelSize( 30 );
	gridRegister->SetRowLabelAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	gridRegister->SetDefaultCellAlignment( wxALIGN_RIGHT, wxALIGN_CENTRE );
	sbRegister->Add( gridRegister, 1, wxALL|wxEXPAND, 5 );
	
	buttonClearRegister = new wxButton( this, wxID_ANY, wxT("Clear all registers"), wxDefaultPosition, wxDefaultSize, 0 );
	sbRegister->Add( buttonClearRegister, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* Sizer5;
	Sizer5 = new wxBoxSizer( wxVERTICAL );
	
	staticRegisterCount = new wxStaticText( this, wxID_ANY, wxT("Set register count:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticRegisterCount->Wrap( -1 );
	Sizer5->Add( staticRegisterCount, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	spinRegisterCount = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxSP_ARROW_KEYS, 0, 999, 30 );
	Sizer5->Add( spinRegisterCount, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxEXPAND, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	
	gSizer1->Add( bSizer4, 1, wxEXPAND, 5 );
	
	
	Sizer5->Add( gSizer1, 1, wxEXPAND, 5 );
	
	
	sbRegister->Add( Sizer5, 0, wxEXPAND, 5 );
	
	
	MainWindowsSizer->Add( sbRegister, 0, wxALL|wxBOTTOM|wxEXPAND|wxRIGHT, 5 );
	
	wxBoxSizer* Controls;
	Controls = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbControl;
	sbControl = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Program Control") ), wxVERTICAL );
	
	buttonRun = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	sbControl->Add( buttonRun, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	buttonStop = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonStop->Enable( false );
	
	sbControl->Add( buttonStop, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	buttonStep = new wxButton( this, wxID_ANY, wxT("Step"), wxDefaultPosition, wxDefaultSize, 0 );
	sbControl->Add( buttonStep, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	buttonReset = new wxButton( this, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	sbControl->Add( buttonReset, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxTOP, 5 );
	
	wxStaticBoxSizer* staticBoxExecutionSpeed;
	staticBoxExecutionSpeed = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Execution Speed") ), wxVERTICAL );
	
	sliderExecutionSpeed = new wxSlider( this, wxID_ANY, 20, 0, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	staticBoxExecutionSpeed->Add( sliderExecutionSpeed, 0, 0, 5 );
	
	staticSpeed = new wxStaticText( this, wxID_ANY, wxT("Interval: 200ms"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	staticSpeed->Wrap( -1 );
	staticBoxExecutionSpeed->Add( staticSpeed, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbControl->Add( staticBoxExecutionSpeed, 0, wxALL|wxEXPAND, 5 );
	
	
	Controls->Add( sbControl, 0, wxALL|wxEXPAND, 5 );
	
	
	MainWindowsSizer->Add( Controls, 0, wxEXPAND|wxRIGHT, 5 );
	
	
	this->SetSizer( MainWindowsSizer );
	this->Layout();
	timerRun.SetOwner( this, wxID_ANY );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameTEMPLATE::OnClose ) );
	this->Connect( menuFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnOpen ) );
	this->Connect( menuFileReload->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnReload ) );
	this->Connect( menuFileSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnSave ) );
	this->Connect( menuFileSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnSaveAs ) );
	this->Connect( menuFileClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnClose ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnQuit ) );
	this->Connect( menuOptionResetAfterStp->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnResetAfterStop ) );
	this->Connect( menuOptionAllowSignedRegister->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnAllowSignedRegister ) );
	this->Connect( menuOptionAdaptLineNumbers->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnAdaptLineNumbers ) );
	this->Connect( menuOptionReleaseMode->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnReleaseMode ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnAbout ) );
	this->Connect( menuHelpHelp->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnHelp ) );
	styledTextCode->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( GUIFrameTEMPLATE::OnSTCChange ), NULL, this );
	buttonClearRegister->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnClearRegister ), NULL, this );
	spinRegisterCount->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( GUIFrameTEMPLATE::OnRegisterCount ), NULL, this );
	spinRegisterCount->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameTEMPLATE::OnRegisterCount ), NULL, this );
	buttonRun->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnRun ), NULL, this );
	buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnStop ), NULL, this );
	buttonStep->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnStep ), NULL, this );
	buttonReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnReset ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( GUIFrameTEMPLATE::OnTimerRun ) );
}

GUIFrameTEMPLATE::~GUIFrameTEMPLATE()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameTEMPLATE::OnClose ) );
	this->Disconnect( idMenuOpen, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnOpen ) );
	this->Disconnect( idMenuReload, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnReload ) );
	this->Disconnect( idMenuSave, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnSave ) );
	this->Disconnect( idMenuSaveAs, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnSaveAs ) );
	this->Disconnect( idMenuClose, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnClose ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnQuit ) );
	this->Disconnect( idMenuResetAfterStp, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnResetAfterStop ) );
	this->Disconnect( idMenuAllowSignedRegister, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnAllowSignedRegister ) );
	this->Disconnect( idMenuAdaptLineNumbers, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnAdaptLineNumbers ) );
	this->Disconnect( idMenuReleaseMode, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnReleaseMode ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnAbout ) );
	this->Disconnect( idMenuHelp, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameTEMPLATE::OnHelp ) );
	styledTextCode->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( GUIFrameTEMPLATE::OnSTCChange ), NULL, this );
	buttonClearRegister->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnClearRegister ), NULL, this );
	spinRegisterCount->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( GUIFrameTEMPLATE::OnRegisterCount ), NULL, this );
	spinRegisterCount->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameTEMPLATE::OnRegisterCount ), NULL, this );
	buttonRun->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnRun ), NULL, this );
	buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnStop ), NULL, this );
	buttonStep->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnStep ), NULL, this );
	buttonReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameTEMPLATE::OnReset ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	sliderExecutionSpeed->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameTEMPLATE::OnExecutionSpeedChanged ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( GUIFrameTEMPLATE::OnTimerRun ) );
	
}

HelpFrameTEMPLATE::HelpFrameTEMPLATE( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Commands:                                                                                | C-equivalents\ninc [x] - increases the value of register [x] by one                                     | x += 1\ndec [x] - decreases the value of register [x] by one                                     | x -= 1\nisz [x] - skips the next command if the value of register [x] is 0                       | if(x)\njmp [y] - jump to line [y]                                                               | y()\nstp     - stop the program                                                               | return\n//      - starts a command. These lines will simply be ignored when running the program. | //"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetFont( wxFont( 9, 75, 90, 90, false, wxT("Courier New") ) );
	
	bSizer5->Add( m_staticText3, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("If an empty line is found, it will be treated like \"stp\". If an unkown command is found, you will be shown a message box telling you the line.\n\nRelease Mode:\nThis is for everyone who wants to have his or her results calculated in a short time. When activated, you won't see your program working, but the result will be shown a lot faster.\n\nAdapt line numbers:\nThis feature tries to keep jmp commands pointing to the same line when you insert or delete lines. It may be useful if you want to make some extra space to write down a comment. It does not work when replacing selected text."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( m_staticText4, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer5 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

HelpFrameTEMPLATE::~HelpFrameTEMPLATE()
{
}
