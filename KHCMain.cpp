/***************************************************************
 * Name:      KHCMain.cpp
 * Purpose:   Code for Know How Computer Frame
 * Author:    Richard Ebeling
 * Created:   2014-09-21
 * Copyright: Richard Ebeling
 * License:   GNU GPLv3
 **************************************************************/

/*
	This file is part of the Know How Computer Emulator.

    THe Know How Computer Emulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Know How Computer Emulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this file.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "KHCMain.h"

KHCDropTarget::KHCDropTarget(KHCFrame *frame)
{
	m_pMainWindow = frame;
}

bool KHCDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
	if (filenames.GetCount() != 1)
	{
		wxMessageBox(wxT("Sorry, but you can only have one file open at the same time."), wxT("Too many files"));
		return false;
	}
	wxString file = filenames.Item(0);
	wxStringTokenizer tokenizer (file, ".");
	wxString fileEnding = wxT("");
	while (tokenizer.HasMoreTokens())
	{
		fileEnding = tokenizer.GetNextToken();
	}
	if (fileEnding.CmpNoCase("khc") && fileEnding.CmpNoCase("txt"))
	{
		 if (wxMessageBox(wxT("According to its name suffix, the file does not look like a KHC program. Are you sure you want to open it?"),
							wxT("Please confirm..."), wxYES | wxNO | wxCANCEL | wxICON_WARNING | wxCENTER) != wxYES)
		 {
		 	return false;
		 }
	}
	if (m_pMainWindow->m_wasChanged)
	{
		if (wxMessageBox(wxT("Any unsaved progress will be lost. Are you sure you want to proceed?"),
			wxT("Please confirm"), wxYES | wxNO | wxCANCEL | wxICON_WARNING) != wxYES)
		{
			return false;
		}
	}
	m_pMainWindow->m_filePath = file;
	m_pMainWindow->m_wasChanged = false;
	m_pMainWindow->reloadFile();
	return true;
}

KHCFrame::KHCFrame(wxFrame *frame, wxString file)
	: GUIFrameTEMPLATE(frame)
{
	//Initialize members:
	m_line = 0;
	m_allowSignedRegister = false;
	m_resetAfterStp = false;
	m_adaptLineNumbers = false;
	m_wasChanged = false;
	m_releaseMode = false;
	m_filePath = wxT("");
	m_pThread = NULL;
	m_pHelpWindow = NULL;
	
	statusBar->SetStatusText(wxT("Know How Computer Emulator started."));
	
	styledTextCode->Connect(wxEVT_MOUSE_CAPTURE_LOST, wxMouseCaptureLostEventHandler(KHCFrame::OnMouseCaptureLost), NULL, this );
	styledTextCode->Connect(wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler(KHCFrame::OnMarginClick), NULL, this);
	this->Connect(wxEVT_COMMAND_KHCTHREAD_COMPLETED, wxThreadEventHandler(KHCFrame::OnThreadCompletion));
	this->Connect(wxEVT_COMMAND_KHCTHREAD_ERROR, wxThreadEventHandler(KHCFrame::OnThreadError));
	
	KHCDropTarget *dropTarget = new KHCDropTarget(this);
	this->SetDropTarget(dropTarget);
	
	styledTextCode->SetEOLMode(wxSTC_EOL_LF);
	styledTextCode->SetIndent(0);
	
	styledTextCode->SetMarginSensitive(0, true);
	styledTextCode->SetMarginSensitive(1, true);
	
	styledTextCode->AlwaysShowScrollbars(false, false);
	
    styledTextCode->SetMarginWidth(1, 30);
	styledTextCode->MarkerDefine(0, wxSTC_MARK_ARROW);
	styledTextCode->MarkerSetBackground(0, 0x0000FF);
	styledTextCode->MarkerSetForeground(0, 0x0000FF);
	
	wxFont font (wxFontInfo(10).FaceName("Consolas"));
	
	styledTextCode->StyleClearAll();
	styledTextCode->SetLexer(wxSTC_LEX_CPPNOCASE);
		
	for (int i = 0; i < 64; i++)
	{
		styledTextCode->StyleSetFont (i, font);
		styledTextCode->StyleSetCharacterSet(i, wxSTC_CHARSET_8859_15);
	}
	
	styledTextCode->StyleSetForeground (wxSTC_C_WORD, wxColour(0,0,255));
	styledTextCode->StyleSetForeground (wxSTC_C_WORD2, wxColour(255,0,0));
	styledTextCode->StyleSetForeground (wxSTC_C_COMMENTLINE, wxColour(0,100,0));
	styledTextCode->StyleSetForeground (wxSTC_C_NUMBER, wxColour(0,0,255));
	styledTextCode->StyleSetBold (wxSTC_C_WORD, true);
	styledTextCode->StyleSetBold (wxSTC_C_WORD2, true);
	styledTextCode->SetKeyWords (0, wxT("dec inc isz jmp"));
	styledTextCode->SetKeyWords (1, wxT("stp"));
	
	if (file.Len() > 0)
	{
		m_filePath = file;
		reloadFile();
	}
	else
	{
		closeFile();
	}
	
	gridRegister->SetDefaultEditor(new wxGridCellNumberEditor());
	gridRegister->SetColFormatNumber(0);
	
	clearRegister();
}

KHCFrame::~KHCFrame()
{
	//cleanup is done in OnClose()
}

void KHCFrame::OnClose(wxCloseEvent &event)
{
	if (m_wasChanged)
	{
		if (wxMessageBox(wxT("Any unsaved progress will be lost. Are you sure you want to exit?"),
			wxT("Please confirm"), wxYES | wxNO | wxICON_WARNING) != wxYES)
		{
			return;
		}
	}
	styledTextCode->Disconnect(wxEVT_MOUSE_CAPTURE_LOST,  wxMouseCaptureLostEventHandler(KHCFrame::OnMouseCaptureLost), NULL, this);
	this->Disconnect(wxEVT_COMMAND_KHCTHREAD_COMPLETED, wxThreadEventHandler(KHCFrame::OnThreadCompletion));
	this->Disconnect(wxEVT_COMMAND_KHCTHREAD_ERROR, wxThreadEventHandler(KHCFrame::OnThreadError));
	
	//End thread, if still running...
	{
		wxCriticalSectionLocker enter(m_pThreadCS);
		if (m_pThread)
		{
			if (m_pThread->Delete() != wxTHREAD_NO_ERROR)
			{
				wxLogError("Well, I could not delete my own thread. Looks like you're going to die now...");
			}
		}
	} //end critical section
	
	while (1)
	{
		{
			wxCriticalSectionLocker enter(m_pThreadCS);
			if (!m_pThread) break;
		}
		
		wxThread::This()->Sleep(1);
	}
		
    Destroy();
}


//CALLBACK MENUBAR ---------------------------------------------------------------------------------
void KHCFrame::OnQuit(wxCommandEvent &event)
{
	wxQueueEvent(this, new wxCloseEvent(wxEVT_CLOSE_WINDOW));
}

void KHCFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox(wxString::Format(
			wxT("Know How Computer Emulator\nBuild %d\n\nCopyright \u00A9 2014 Richard Ebeling"), KHCApp::build),
			wxT("Know How Computer Emulator - About"));
}

void KHCFrame::OnHelp(wxCommandEvent &event)
{
	if (m_pHelpWindow)
	{
		m_pHelpWindow->Raise();
	}
	else
	{
		m_pHelpWindow = new KHCHelp(this);
		m_pHelpWindow->Show();
	}
}

void KHCFrame::OnResetAfterStop(wxCommandEvent &event)
{
	m_resetAfterStp = event.IsChecked();
}

void KHCFrame::OnAllowSignedRegister(wxCommandEvent &event)
{
	m_allowSignedRegister = event.IsChecked();
}

void KHCFrame::OnAdaptLineNumbers(wxCommandEvent &event)
{
	m_adaptLineNumbers = event.IsChecked();
}

void KHCFrame::OnReleaseMode(wxCommandEvent &event)
{
	if (buttonStop->IsEnabled())
	{
		wxMessageBox(wxT("You can't enable this while running your program."), wxT("Error"), wxICON_ERROR | wxOK | wxCENTER);
		mbar->Check(idMenuReleaseMode, false);
	}
	else
	{
		m_releaseMode = event.IsChecked();
	}
}

void KHCFrame::OnOpen(wxCommandEvent& event)
{
	openFile();
}

void KHCFrame::OnReload(wxCommandEvent& event)
{
	reloadFile();
}

void KHCFrame::OnSave(wxCommandEvent& event)
{
	saveFile();
}

void KHCFrame::OnClose(wxCommandEvent& event)
{
	closeFile();
}

void KHCFrame::OnSaveAs(wxCommandEvent& event)
{
	saveFileAs();
}


//CALLBACK OTHER GUI INTERACTION -------------------------------------------------------------------
void KHCFrame::OnMarginClick(wxStyledTextEvent &event)
{
	int m_line = styledTextCode->LineFromPosition(event.GetPosition());
	jmp(m_line);
	redrawMarker();
}

void KHCFrame::OnSTCChange(wxKeyEvent &event)
{
	wxChar kc = event.GetUnicodeKey();
	
	if (!m_wasChanged && !((kc==WXK_SHIFT)			| (kc==WXK_CONTROL)			| (kc==WXK_ALT)				| (kc==WXK_INSERT)
						 | (kc==WXK_DOWN)			| (kc==WXK_UP)				| (kc==WXK_LEFT)			| (kc==WXK_RIGHT)
						 | (kc==WXK_END)			| (kc==WXK_ESCAPE)			| (kc==WXK_EXECUTE) 		| (kc==WXK_HOME)
						 | (kc==WXK_LBUTTON)		| (kc==WXK_MBUTTON)			| (kc==WXK_MENU)			| (kc==WXK_NONE)
						 | (kc==WXK_NUMPAD_DOWN) 	| (kc==WXK_NUMPAD_HOME)		| (kc==WXK_NUMPAD_INSERT)
						 | (kc==WXK_NUMPAD_LEFT) 	| (kc==WXK_NUMPAD_PAGEDOWN) | (kc==WXK_NUMPAD_PAGEUP)
						 | (kc==WXK_NUMPAD_RIGHT)	| (kc==WXK_NUMPAD_UP)		| (kc==WXK_PAGEDOWN)
						 | (kc==WXK_PAGEUP)			| (kc==WXK_PAUSE)			| (kc==WXK_PRINT)
						 | (kc==WXK_RBUTTON)		| (kc==WXK_SCROLL)			| (kc==WXK_SELECT)
						 | (kc==WXK_SNAPSHOT)		| (kc==WXK_START)
						 | (kc==WXK_WINDOWS_LEFT)	| (kc==WXK_WINDOWS_RIGHT)	| (kc==WXK_WINDOWS_MENU)))
	{
		m_wasChanged = true;
		this->SetTitle(this->GetTitle() + wxT("*"));
		mbar->Enable(idMenuSave, true);
		if (m_filePath.Len() != 0) mbar->Enable(idMenuReload, true);
	}
	
	if (!m_adaptLineNumbers)
	{
		event.Skip();
		return;
	}
	
	long from;
	long to;
	styledTextCode->GetSelection(&from, &to);
	
	if (from != to)
	{
		statusBar->SetStatusText(wxT("!!! WARNING !!!: The option \"Adapt line numbers\" does NOT work when replacing selected text."));
		event.Skip();
		return;
	}
	
	int m_line = styledTextCode->GetCurrentLine();
	int pos = styledTextCode->GetCurrentPos();	

	if (kc == WXK_RETURN) //increase all references to line numbers higher than current line
	{
		int posInLine = pos - styledTextCode->PositionFromLine(m_line);
		bool goRight = false;
		
		wxRegEx reJmp ("^(\\s*jmp\\s*)(\\d+)", wxRE_ADVANCED | wxRE_ICASE);
		int lineCount = styledTextCode->GetLineCount();
		wxString sLine;
		
		for (int l = 0; l < lineCount; l++)
		{
			sLine = styledTextCode->GetLine(l);
			if (reJmp.Matches(sLine))
			{
				wxString oldNumber = reJmp.GetMatch(sLine, 2);
				int oldNumberInt = wxAtoi(oldNumber);
				if (((styledTextCode->GetCharAt(pos - 1) == '\n') && (oldNumberInt > m_line)) |
					 (oldNumberInt > (m_line + 1)))
				{
					wxString newNumber = wxString::Format(wxT("%i"), oldNumberInt + 1);
					int posStart = styledTextCode->PositionFromLine(l) + reJmp.GetMatch(sLine, 1).Len();
					int posEnd = posStart + reJmp.GetMatch(sLine, 2).Len();
					if ((l == m_line) && (posStart < pos) && (pos <= posEnd) && (newNumber.Len() > oldNumber.Len()))
					{
						goRight = true;
					}
					
					styledTextCode->Replace(posStart, posEnd, newNumber);
				}
			}
		}
		pos = styledTextCode->PositionFromLine(m_line) + posInLine;
		if (goRight)
		{
			styledTextCode->GotoPos(styledTextCode->WordEndPosition(pos, false));
		}
		else
		{
			styledTextCode->GotoPos(pos);
		}
	}
	else if (kc == WXK_BACK) //decrease all references to line numbers higher than current line
	{
		if (styledTextCode->GetCharAt(pos - 1) == '\n')
		{
			wxRegEx reJmp ("^(\\s*jmp\\s*)(\\d+)", wxRE_ADVANCED | wxRE_ICASE);
			int lineCount = styledTextCode->GetLineCount();
			wxString sLine;
			
			for (int l = 0; l < lineCount; l++)
			{
				sLine = styledTextCode->GetLine(l);
				if (reJmp.Matches(sLine))
				{
					int oldNumber = wxAtoi(reJmp.GetMatch(sLine, 2));
					if (oldNumber > m_line)
					{
						wxString newNumber = wxString::Format(wxT("%i"), oldNumber - 1);
						int posStart = styledTextCode->PositionFromLine(l) + reJmp.GetMatch(sLine, 1).Len();
						int posEnd = posStart + reJmp.GetMatch(sLine, 2).Len();
						styledTextCode->Replace(posStart, posEnd, newNumber);
					}
				}
				styledTextCode->GotoLine(m_line);
			}
		}
	}
	else if (kc == WXK_DELETE) //decrease all references to line numbers higher than current line
	{
		if ((styledTextCode->GetCharAt(pos + 1) == '\n') | (styledTextCode->GetCharAt(pos + 1) == '\r'))
		{
			wxRegEx reJmp ("^(\\s*jmp\\s*)(\\d+)", wxRE_ADVANCED | wxRE_ICASE);
			int lineCount = styledTextCode->GetLineCount();
			wxString sLine;
			
			for (int l = 0; l < lineCount; l++)
			{
				sLine = styledTextCode->GetLine(l);
				if (reJmp.Matches(sLine))
				{
					int oldNumber = wxAtoi(reJmp.GetMatch(sLine, 2));
					if (oldNumber > m_line)
					{
						wxString newNumber = wxString::Format(wxT("%i"), oldNumber - 1);
						int posStart = styledTextCode->PositionFromLine(l) + reJmp.GetMatch(sLine, 1).Len();
						int posEnd = posStart + reJmp.GetMatch(sLine, 2).Len();
						styledTextCode->Replace(posStart, posEnd, newNumber);
					}
				}
				styledTextCode->GotoLine(m_line);
			}
		}
	}
	event.Skip();
}

void KHCFrame::OnStep(wxCommandEvent &event)
{
	statusBar->SetStatusText(wxString::Format(wxT("Executed line %d"), m_line + 1));
	execute();
}

void KHCFrame::OnReset(wxCommandEvent &event)
{
	reset();
	statusBar->SetStatusText(wxT("Program reset."));
}

void KHCFrame::OnClearRegister(wxCommandEvent &event)
{
	clearRegister();
}

void KHCFrame::OnRegisterCount(wxSpinEvent& event)
{
	int current = gridRegister->GetNumberRows();
	int wanted = spinRegisterCount->GetValue();
	int diff = wanted - current;
	if (diff > 0)
	{
		gridRegister->InsertRows(current, diff, false);
		for (int r = current; r < wanted; r++)
		{
			gridRegister->SetCellValue("0", r, 0);
			gridRegister->SetCellEditor(r, 0, new wxGridCellNumberEditor());
		}
		
	}
	else if (diff < 0)
	{
		gridRegister->DeleteRows(wanted, current-wanted, false);
	}
}

void KHCFrame::OnExecutionSpeedChanged(wxScrollEvent& event)
{
	staticSpeed->SetLabel(wxString::Format("Interval: %dms", event.GetPosition() * 10));
	
	if (timerRun.IsRunning())
	{
		stopExecuting(); //will re-read the value the user set.
		startExecuting();
	}
}

void KHCFrame::OnRun(wxCommandEvent& event)
{
	startExecuting();
}

void KHCFrame::OnStop(wxCommandEvent& event)
{
	stopExecuting();
}

void KHCFrame::OnTimerRun(wxTimerEvent& event)
{
	execute();
}

//CALLBACK THREAD

void KHCFrame::OnThreadCompletion(wxThreadEvent& event)
{	
	ThreadResult *res = event.GetPayload<ThreadResult*>();
	for (unsigned int i = 0; i < res->registers.size(); i++)
	{
		gridRegister->SetCellValue(wxString::Format(wxT("%i"), res->registers.at(i)), i, 0);
	}
	jmp(res->line);
	delete res;
	
	
	statusBar->SetStatusText(wxT("Finished execution, you should now see the results."));
	mbar->Enable();
	styledTextCode->Enable();
	buttonRun->Enable();
	buttonClearRegister->Enable();
	buttonReset->Enable();
	buttonStep->Enable();
	gridRegister->Enable();
	buttonStop->Disable();
	redrawMarker();
	styledTextCode->GotoLine(m_line);
}

void KHCFrame::OnThreadError(wxThreadEvent& event)
{
	ThreadResult *res = event.GetPayload<ThreadResult*>();
	jmp(res->line);
	delete res;
	
	redrawMarker();
	styledTextCode->GotoLine(m_line);

	wxMessageBox(wxT("An error occured on the currently marked line. You should check you program for mistakes."),
				 wxT("Error while executing..."), wxOK | wxCENTER | wxICON_ERROR);
	
	statusBar->SetStatusText(wxString::Format(wxT("An error occurred in line %d"), m_line + 1));
				 
	mbar->Enable();
	styledTextCode->Enable();
	buttonRun->Enable();
	buttonClearRegister->Enable();
	buttonReset->Enable();
	buttonStep->Enable();
	gridRegister->Enable();
	buttonStop->Disable();
}


//VNR-FUNCTIONS ------------------------------------------------------------------------------------
void KHCFrame::jmp(int line)
{
	m_line = line;
}

void KHCFrame::isz(int reg)
{
	wxString value = gridRegister->GetCellValue(wxGridCellCoords(reg, 0));
	int number = wxAtoi (value);
	if (number == 0)
	{
		jmp(m_line + 2);
	}
	else
	{
		jmp(m_line + 1);
	}
}

void KHCFrame::dec(int reg)
{
	wxString currentValue = gridRegister->GetCellValue(wxGridCellCoords(reg, 0));
	int newNumber = wxAtoi (currentValue) - 1;
	if (newNumber < 0 && (!m_allowSignedRegister))
	{
		newNumber = 0;
	}
	
	wxString newValue = wxString::Format(wxT("%i"), newNumber);
	
	gridRegister->SetCellValue(wxGridCellCoords(reg, 0), newValue);
}

void KHCFrame::inc(int reg)
{
	wxString currentValue = gridRegister->GetCellValue(wxGridCellCoords(reg, 0));
	int newNumber = wxAtoi (currentValue) + 1;
	wxString newValue = wxString::Format(wxT("%i"), newNumber);
	
	gridRegister->SetCellValue(wxGridCellCoords(reg, 0), newValue);
}

void KHCFrame::stp(void)
{
	stopExecuting();
	if (m_resetAfterStp)
	{
		reset();
	}
}


//OTHER FUNCTIONS ----------------------------------------------------------------------------------
void KHCFrame::execute(void)
{
	wxRegEx reParam ("^\\s*(jmp|isz|dec|inc)\\s*(\\d+)", wxRE_ADVANCED | wxRE_ICASE);
	wxRegEx reStp ("^\\s*stp", wxRE_ADVANCED | wxRE_ICASE);
	wxRegEx reComment ("^//", wxRE_ADVANCED | wxRE_ICASE);
	wxRegEx reEmpty ("^\\s*$", wxRE_ADVANCED | wxRE_ICASE);
	
	while (reComment.Matches(styledTextCode->GetLine(m_line)))
	{
		m_line += 1;
	}
	
	wxString sLine = styledTextCode->GetLine(m_line);
	
	if (reStp.Matches(sLine) | reEmpty.Matches(sLine))
	{
		styledTextCode->GotoLine(m_line); //Make sure the line we stopped in is visible.
		stp();
		statusBar->SetStatusText(wxString::Format(wxT("Stopped in line %d."), m_line + 1), 0);
	}
	
	else if (reParam.Matches(sLine))
	{
		wxString cmd = reParam.GetMatch(sLine, 1);
		wxString param = reParam.GetMatch(sLine, 2);
		int iParam = wxAtoi(param);
		
		if (!cmd.CmpNoCase(wxT("jmp")))
		{
			if (styledTextCode->GetLineCount() < iParam)
			{
				stp();
				wxMessageBox(wxString::Format(wxT("Error: Tried to jump to line %d in line %d."), iParam, m_line + 1),
								"Error", wxOK | wxCENTER | wxICON_ERROR);
				return;
			}
			jmp(iParam - 1); //internally, line counts start at 0
		}
		
		else if ((!cmd.CmpNoCase(wxT("isz"))) | (!cmd.CmpNoCase(wxT("dec"))) | (!cmd.CmpNoCase(wxT("inc"))))
		{
			if (gridRegister->GetRows() < iParam)
			{
				stp();
				wxMessageBox(wxString::Format(wxT("Error: Tried to access register %d in line %d."), iParam, m_line + 1),
								"Error", wxOK | wxCENTER | wxICON_ERROR);
				return;
			}
			
			if (!cmd.CmpNoCase(wxT("isz")))
			{
				isz(iParam - 1); //internally, 1st field in grid is 0|0
			}
			
			else if (!cmd.CmpNoCase("dec"))
			{
				dec(iParam - 1); //internally, 1st field in grid is 0|0
				m_line += 1;
			}
			
			else if (!cmd.CmpNoCase("inc"))
			{
				inc(iParam - 1); //internally, 1st field in grid is 0|0
				m_line += 1;
			}
		}
		
		//go forward to next line that does not start with "//"
		while (reComment.Matches(styledTextCode->GetLine(m_line)))
		{
			m_line += 1;
		}
	}
	
	else
	{
		stopExecuting();
		wxString lineNumber;
		lineNumber << m_line + 1;
		wxMessageBox(wxT("Could not identify command in line ") + lineNumber + wxT (". Aborting."),
					wxT("Error"), wxOK | wxCENTRE | wxICON_ERROR, this);
	}
	
	redrawMarker();
}

void KHCFrame::reset(void)
{
	jmp(0);
	styledTextCode->GotoLine(0);
	redrawMarker();
}

void KHCFrame::redrawMarker(void)
{
	styledTextCode->MarkerDeleteAll(0);
	styledTextCode->MarkerAdd(m_line, 0);
}

void KHCFrame::clearRegister (void)
{
	int rows = gridRegister->GetRows();
	for (int r = 0; r < rows; r++)
	{
		gridRegister->SetCellValue("0", r, 0);
	}
}

void KHCFrame::startExecuting(void)
{
	if (m_releaseMode)
	{
		std::vector<int> reg;
		for (int i = 0; i < gridRegister->GetRows(); i++)
		{
			reg.push_back(wxAtoi(gridRegister->GetCellValue(i, 0)));
		}
		
		m_pThread = new KHCThread(this, styledTextCode->GetText(), reg);
		
		if ( m_pThread->Run() != wxTHREAD_NO_ERROR )
		{
			wxLogError("Could not create the thread!");
			delete m_pThread;
			m_pThread = NULL;
			return;
		}
		
		mbar->Disable();
		styledTextCode->Disable();
		buttonRun->Disable();
		buttonClearRegister->Disable();
		buttonReset->Disable();
		buttonStep->Disable();
		gridRegister->Disable();
		buttonStop->Enable();
	}
	
	else
	{
		timerRun.Start(sliderExecutionSpeed->GetValue() * 10);
		buttonRun->Enable(false);
		buttonStop->Enable(true);
	}
	
	statusBar->SetStatusText(wxT("Running..."));
}

void KHCFrame::stopExecuting(void)
{
	if (m_releaseMode)
	{
		{
			wxCriticalSectionLocker enter(m_pThreadCS);
			if (m_pThread)
			{
				if (m_pThread->Delete() != wxTHREAD_NO_ERROR)
				{
					wxLogError("Well, I could now delete my own thread. Looks like you're going to die now...");
				}
			}
		} //end critical section
		while (1)
		{
			{
				wxCriticalSectionLocker enter(m_pThreadCS);
				if (!m_pThread) break;
			}
			
			wxThread::This()->Sleep(1);
		}
		
	}
	else
	{
		timerRun.Stop();
		buttonRun->Enable(true);
		buttonStop->Enable(false);
	}
	
	statusBar->SetStatusText(wxString::Format(wxT("Interrupted in line %d."), m_line + 1));
}

void KHCFrame::openFile(void)
{
	wxFileDialog openFileDialog(this, wxT("Open a KHC program"), "", "",
								wxT("Know How Computer file (*.khc)|*.khc|")
								wxT("Text document (*.txt)|*.txt|")
								wxT("Any file type (*.*)|*.*"),
								wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	
	m_filePath = openFileDialog.GetPath();
	reloadFile();
}

void KHCFrame::reloadFile(void)
{
	if (m_wasChanged)
	{
		if (wxMessageBox(wxT("Any unsaved progress will be lost. Are you sure you want to proceed?"),
			wxT("Please confirm"), wxYES | wxNO | wxCANCEL | wxICON_WARNING) != wxYES)
		{
			return;
		} 
	}
	
	wxFileInputStream inStream (m_filePath);
	
	if (!inStream.IsOk())
	{
		wxLogError("Could not load file '%s'.", m_filePath);
		return;
	}
	
	size_t size = inStream.GetLength();
	char * buffer = new char[size + 1];
	if (inStream.ReadAll(buffer, size))
	{
		statusBar->SetStatusText(wxT("Successfully loaded ") + m_filePath);
	}
	
	buffer[inStream.LastRead()] = '\0';
	
	styledTextCode->SetText(wxString(buffer));
	delete[] buffer;
	
	this->SetTitle(wxT("Know How Computer Emulator - ") + m_filePath);
	mbar->Enable(idMenuSave, false);
	mbar->Enable(idMenuReload, false);
	m_wasChanged = false;
	reset();
}

void KHCFrame::saveFile(void)
{	
	if (m_filePath.Len() == 0)
	{
		saveFileAs();
		return;
	}
	
	wxFileOutputStream outStream (m_filePath);
	
	if (!outStream.IsOk())
	{
		wxLogError("Could not save current contents in file '%s'.", m_filePath);
		return;
	}
	wxString text = styledTextCode->GetText();
	
	outStream.Write(text.mb_str(), text.Len());
	
	m_wasChanged = false;
	mbar->Enable(idMenuSave, false);
	mbar->Enable(idMenuReload, false);
	this->SetTitle(wxT("Know How Computer Emulator - ") + m_filePath);
}

void KHCFrame::saveFileAs(void)
{
	 wxFileDialog saveFileDialog(this, wxT("Save current program"), "", wxT("*.khc"),
								wxT("Know How Computer file (*.khc)|*.khc|")
								wxT("Text document (*.txt)|*.txt|")
								wxT("Any file type (*.*)|*.*"),
								wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	
	 if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	
	m_filePath = saveFileDialog.GetPath();
	if (m_filePath.Len() != 0) //make sure we don't get an infinite loop.
	{
		saveFile();
	}
	else
	{
		wxLogError("Something went wrong, you may try selection another location to save the file.");
	}
}

void KHCFrame::closeFile (void)
{
	if (m_wasChanged)
	{
		if (wxMessageBox(wxT("Any unsaved progress will be lost. Are you sure you want to proceed?"),
			wxT("Please confirm"), wxYES | wxNO | wxCANCEL | wxICON_WARNING) != wxYES)
		{
			return;
		} 
	}
	styledTextCode->SetText(wxString('\n', 19));
	this->SetTitle(wxT("Know How Computer Emulator - New Program"));
	mbar->Enable(idMenuSave, false);
	mbar->Enable(idMenuReload, false);
	m_filePath = wxT("");
	m_wasChanged = false;
	reset();
}