/***************************************************************
 * Name:      KHCApp.h
 * Purpose:   Defines Application Class
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

#ifndef KHCAPP_H
#define KHCAPP_H

#include <wx/app.h>

#include <wx/regex.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/cmdline.h>

class KHCApp : public wxApp
{
    public:
		virtual void OnInitCmdLine(wxCmdLineParser& parser);
		virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
        virtual bool OnInit();

        wxString m_file;
        static const int build = 6;
};

static const wxCmdLineEntryDesc g_cmdLineDesc[] =
{
	{ wxCMD_LINE_PARAM, NULL, NULL, "input file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL | wxCMD_LINE_PARAM_MULTIPLE},
	{ wxCMD_LINE_NONE }
};

#endif // KHCAPP_H
