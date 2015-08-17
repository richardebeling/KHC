/***************************************************************
 * Name:      KHCThread.cpp
 * Purpose:   Code for Release Mode thread.
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

#include "KHCThread.h"
 
wxDEFINE_EVENT(wxEVT_COMMAND_KHCTHREAD_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_KHCTHREAD_ERROR, wxThreadEvent);

KHCThread::KHCThread(KHCFrame *mainWindow, wxString code, std::vector<int> reg)
	: wxThread(wxTHREAD_DETACHED), m_mainWindow(mainWindow), m_code(code), m_registers(reg), m_line(0)
{
}

KHCThread::~KHCThread()
{
	wxCriticalSectionLocker enter(m_mainWindow->m_pThreadCS);
	m_mainWindow->m_pThread = NULL;
}

wxThread::ExitCode KHCThread::Entry()
{
	wxStringTokenizer tokenizer (m_code, wxT("\n"), wxTOKEN_RET_EMPTY_ALL); //this mode will also make \n\n appear as a token
	while (tokenizer.HasMoreTokens() && !TestDestroy())
	{
		wxString token = tokenizer.GetNextToken();
		m_commands.push_back(CommandFromCode(token));
	}
	
	int ret = 1; // 1 - continue executing; 0 - finished; -1 - error
	
	while (!TestDestroy() && (ret == 1))
	{
		ret = execute(m_commands.at(m_line));
	}
	
	ThreadResult *pRes = new ThreadResult;
	pRes->line = m_line;
	pRes->registers = m_registers;
	
	if (ret == -1)
	{
		wxThreadEvent *pEvent = new wxThreadEvent(wxEVT_COMMAND_KHCTHREAD_ERROR);
		pEvent->SetPayload(pRes);
		wxQueueEvent(m_mainWindow, pEvent);
		return (wxThread::ExitCode)0;
	}
	else
	{
		wxThreadEvent *pEvent = new wxThreadEvent(wxEVT_COMMAND_KHCTHREAD_COMPLETED);
		pEvent->SetPayload(pRes);
		wxQueueEvent(m_mainWindow, pEvent);
		return (wxThread::ExitCode)0;
	}
}

Command KHCThread::CommandFromCode(wxString line)
{
	Command cmd;
	wxRegEx reParam ("^\\s*(jmp|isz|dec|inc)\\s*(\\d+)", wxRE_ADVANCED | wxRE_ICASE);
	wxRegEx reStp ("^\\s*stp", wxRE_ADVANCED | wxRE_ICASE);
	wxRegEx reComment ("^//", wxRE_ADVANCED | wxRE_ICASE);
	wxRegEx reEmpty ("^\\s*$", wxRE_ADVANCED | wxRE_ICASE);
	
	if (reComment.Matches(line))
	{
		cmd.command = cmd.KHC_COMMENT;
	}
	else if (reStp.Matches(line) | reEmpty.Matches(line))
	{
		cmd.command = cmd.KHC_CMD_STP;
	}
	else if (reParam.Matches(line))
	{
		wxString instruction = reParam.GetMatch(line, 1);
		wxString parameter = reParam.GetMatch(line, 2);
		
		if (!instruction.CmpNoCase(wxT("jmp")))
		{
			cmd.command = cmd.KHC_CMD_JMP;
		}
		else if (!instruction.CmpNoCase(wxT("inc")))
		{
			cmd.command = cmd.KHC_CMD_INC;
		}
		else if (!instruction.CmpNoCase(wxT("dec")))
		{
			cmd.command = cmd.KHC_CMD_DEC;
		}
		else if (!instruction.CmpNoCase(wxT("isz")))
		{
			cmd.command = cmd.KHC_CMD_ISZ;
		}
		
		cmd.param = wxAtoi(parameter);
	}
	else
	{
		cmd.command = cmd.KHC_UNKNOWN;
	}
	
	return cmd;
}

int KHCThread::execute(Command cmd)
{
	switch(m_commands.at(m_line).command)
	{
		case Command::KHC_CMD_INC:
			if (m_registers.size() < cmd.param)
				return -1;
			
			m_registers.at(cmd.param - 1) += 1;
			m_line += 1;
			break;
		
		case Command::KHC_CMD_DEC:
			if (m_registers.size() < cmd.param)
				return -1;
			
			m_registers.at(cmd.param - 1) -= 1;
			if ((m_registers.at(cmd.param - 1) < 0) && !m_mainWindow->m_allowSignedRegister)
			{
				m_registers.at(cmd.param - 1) = 0;
			}

			
			m_line += 1;
			break;
		
		case Command::KHC_CMD_ISZ:
			if (m_registers.size() < cmd.param)
				return -1;
			
			m_line += (m_registers.at(cmd.param - 1) == 0) ? 2 : 1;
			break;
		
		case Command::KHC_CMD_JMP:
			if (m_commands.size() < (cmd.param - 2) && (!cmd.param - 1 == 0)) //one for size being one bigger than highest line number, one for line number being one lower internally
				return -1;
			
			m_line = cmd.param - 1;
			break;
			
		case Command::KHC_CMD_STP:
			return 0;
			break;
		
		case Command::KHC_UNKNOWN:
			return -1;
			break;
		
		case Command::KHC_COMMENT:
			m_line += 1;
	}
	return 1;
}