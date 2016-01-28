/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IDrawing.h"
#include "GameObject.h"
#include "Quadrant.h"

class SoundManager
{
public:
	static SoundManager& GetInstance()
	{
		static SoundManager g_Instance;
		return g_Instance;
	}

	void PlaySoundExplosion();
	void PlaySoundScore();
	void PlaySoundClick();
	void Update();
	void Clear();
private:
	SoundManager();
	SoundManager(const SoundManager&) = delete;
	void operator= (const SoundManager&) = delete;

	std::vector<sf::Sound*> m_pSounds;
	std::vector<int> m_pCleanup;
	sf::SoundBuffer* m_pExplosion;
	sf::SoundBuffer* m_pScore;
	sf::SoundBuffer* m_pClick;
};
