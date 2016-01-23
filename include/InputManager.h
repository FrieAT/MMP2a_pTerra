/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IInputObserver.h"

class InputManager
{
public:
	static InputManager& GetInstance()
	{
		static InputManager g_Instance;
		return g_Instance;
	}
	void Update(sf::RenderWindow* pWindow, tgui::Gui* pGui);
	void RegisterEventObserver(IInputObserver* pObserver);
	void UnregisterEventObserver(IInputObserver* pObserver);
	void Clear();
private:
	InputManager() { }
	InputManager(const InputManager&) = delete;
	void operator= (const InputManager&) = delete;
	std::vector<IInputObserver*> m_Observers;
	void UpdateEventObserver(std::string strEvent);
};
