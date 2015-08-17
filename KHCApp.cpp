/***************************************************************
 * Name:      KHCApp.cpp
 * Purpose:   Code for Application Class
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

#include "KHCApp.h"
#include "KHCMain.h"

IMPLEMENT_APP(KHCApp);

bool KHCApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	
    KHCFrame* frame = new KHCFrame(0L, m_file);
    frame->SetIcon(wxICON(myIcon));
    frame->Show();
    
    return true;
}

void KHCApp::OnInitCmdLine(wxCmdLineParser& parser)
{
	parser.SetDesc (g_cmdLineDesc);
	parser.SetSwitchChars (wxT(""));
}

bool KHCApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	if (parser.GetParamCount() > 0)
		m_file = parser.GetParam(0);
	else
		m_file = wxT("");
	
    return true;
}