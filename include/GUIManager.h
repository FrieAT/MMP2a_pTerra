/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IDrawing.h"
#include "IGUI.h"

class IGUI;

class GUIManager
{
public:
	static GUIManager& GetInstance()
	{
		static GUIManager g_Instance;
		return g_Instance;
	}

	void AddGUI(IGUI* pGUI);
	void RemoveGUI(IGUI* pGUI);
	void Update(sf::Time DeltaTime);
	void Clear();
private:
	GUIManager();
	GUIManager(const GUIManager&) = delete;
	void operator= (const GUIManager&) = delete;
	std::vector<IGUI*> m_GUIs;
	void RemoveAllGUI();
};

