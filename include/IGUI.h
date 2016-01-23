/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IDrawing.h"
#include "GUIManager.h"

class IGUI
{
public:
	IGUI(tgui::Gui& gui) :
		m_gui(gui)
	{
	}
	virtual ~IGUI() { }
protected:
	tgui::Gui& m_gui;
};