/***************************************************************
 * Name:      KHCHelp.cpp
 * Purpose:   Code for Help Frame
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

#include "KHCHelp.h"
 
KHCHelp::KHCHelp(KHCFrame *parent) : HelpFrameTEMPLATE(parent)
{
	m_parent = parent;
}

KHCHelp::~KHCHelp()
{
	m_parent->m_pHelpWindow = NULL;
}