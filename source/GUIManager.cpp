/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "GUIManager.h"

GUIManager::GUIManager()
{
	
}

void GUIManager::AddGUI(IGUI* pGUI)
{
	if (pGUI == nullptr)
	{
		throw std::runtime_error("Given GUI-object has a null-pointer-reference.");
	}
	
	m_GUIs.push_back(pGUI);
}

void GUIManager::RemoveGUI(IGUI* pGUI)
{
	for (auto itr = m_GUIs.begin(); itr != m_GUIs.end(); ++itr)
	{
		if (*itr == pGUI)
		{
			m_GUIs.erase(itr);
			delete pGUI;
		}
	}
}

void GUIManager::Update(sf::Time DeltaTime)
{
	// Not needed for GUI (Eventbus driven), probable usage for time based events (Notifications / Popups)
}

void GUIManager::Clear()
{
	RemoveAllGUI();
}

void GUIManager::RemoveAllGUI()
{
	for (auto itr = m_GUIs.begin(); itr != m_GUIs.end(); ++itr)
	{
		delete *itr;
	}
	m_GUIs.clear();
}