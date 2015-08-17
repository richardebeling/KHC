/***************************************************************
 * Name:      KHCMain.h
 * Purpose:   Defines Know How Computer Frame
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

#ifndef KHCMAIN_H
#define KHCMAIN_H


#include "KHCApp.h"
#include "GUIFrame.h"
#include "KHCHelp.h"
#include "KHCThread.h"

#include <vector>

class KHCHelp;
class KHCThread;

class KHCFrame: public GUIFrameTEMPLATE
{
    public:
        KHCFrame(wxFrame *frame, wxString file);
        ~KHCFrame();
        
		void inc (int reg);
        void dec (int reg);
        void jmp (int line);
        void stp (void);
        void isz (int reg);
        void execute (void);
        void startExecuting (void);
        void stopExecuting (void);
        void reset(void);
        void clearRegister(void);
        void saveFile(void);
        void saveFileAs(void);
        void openFile(void);
        void reloadFile(void);
        void closeFile(void);
        void redrawMarker(void);
        
	protected:
		int m_line;
		bool m_allowSignedRegister;
		bool m_resetAfterStp;
		bool m_adaptLineNumbers;
		bool m_wasChanged;
		bool m_releaseMode;
		wxString m_filePath;
		KHCHelp *m_pHelpWindow;
		
		KHCThread *m_pThread;
		wxCriticalSection m_pThreadCS;
		friend class KHCThread;
		friend class KHCHelp;
		friend class KHCDropTarget;
        
    private:
		virtual void OnClose(wxCloseEvent& event);
		virtual void OnOpen(wxCommandEvent& event);
		virtual void OnReload(wxCommandEvent& event);
		virtual void OnSave(wxCommandEvent& event);
		virtual void OnSaveAs(wxCommandEvent& event);
		virtual void OnClose(wxCommandEvent& event);
		virtual void OnQuit(wxCommandEvent& event);
		virtual void OnResetAfterStop(wxCommandEvent& event);
		virtual void OnAllowSignedRegister(wxCommandEvent& event);
		virtual void OnAdaptLineNumbers(wxCommandEvent& event);
		virtual void OnReleaseMode(wxCommandEvent& event);
		virtual void OnAbout(wxCommandEvent& event);
		virtual void OnHelp(wxCommandEvent& event);
		virtual void OnClearRegister(wxCommandEvent& event);
		virtual void OnRegisterCount(wxSpinEvent& event);
		virtual void OnRun(wxCommandEvent& event);
		virtual void OnSTCChange(wxKeyEvent& event);
		virtual void OnStop(wxCommandEvent& event);
		virtual void OnStep(wxCommandEvent& event);
		virtual void OnReset(wxCommandEvent& event);
		virtual void OnExecutionSpeedChanged(wxScrollEvent& event);
		virtual void OnTimerRun(wxTimerEvent& event);
		virtual void OnMarginClick(wxStyledTextEvent& event);
		virtual void OnThreadCompletion(wxThreadEvent& event);
		virtual void OnThreadError(wxThreadEvent& event);
		//Must NOT be Skip()ed! Otherwise, causes runtime error if mouse capture is lost.
		virtual void OnMouseCaptureLost (wxMouseCaptureLostEvent& WXUNUSED(event)) { return; }
};

class KHCDropTarget : public wxFileDropTarget
{
public:
	KHCDropTarget(KHCFrame *frame);
	
	virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);
	KHCFrame *m_pMainWindow;
};

#endif // KHCMAIN_H
