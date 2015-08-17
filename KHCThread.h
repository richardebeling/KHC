/***************************************************************
 * Name:      KHCThread.h
 * Purpose:   Defines Release Mode thread class
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

#ifndef KHCTHREAD_H
#define KHCTHREAD_H

#include "KHCMain.h"
#include <vector>
#include <wx/tokenzr.h>

wxDECLARE_EVENT(wxEVT_COMMAND_KHCTHREAD_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_KHCTHREAD_ERROR, wxThreadEvent);

struct Command
{
	unsigned int command;
	unsigned int param;
	
	enum
		{
			KHC_CMD_INC = 0,
			KHC_CMD_DEC = 1,
			KHC_CMD_ISZ = 2,
			KHC_CMD_JMP = 3,
			KHC_CMD_STP = 4,
			KHC_COMMENT = 5,
			KHC_UNKNOWN = 6,
		};
};

struct ThreadResult
{
	unsigned int line;
	std::vector<int> registers;
};

class KHCFrame;

class KHCThread : public wxThread
{
	public:
		KHCThread(KHCFrame *mainWindow, wxString code, std::vector<int> reg);
		~KHCThread();
	
	protected:
		virtual ExitCode Entry();
		Command CommandFromCode (wxString line);
		int execute(Command cmd);
		
		KHCFrame *m_mainWindow;
		wxString m_code;
		std::vector<Command> m_commands;
		std::vector<int> m_registers;
		
		int m_line;
};
#endif // KHCTHREAD_H