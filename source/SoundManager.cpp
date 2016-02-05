/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "SoundManager.h"
#include "IPosition.h"
#include "WorldManager.h"

SoundManager::SoundManager()
{
	// Load sounds
	m_pExplosion = new sf::SoundBuffer();
	if (!m_pExplosion->loadFromFile("assets/explosion.ogg"))
	{
		throw std::runtime_error("Unable to load assets/explosion.ogg");
	}

	m_pScore = new sf::SoundBuffer();
	if (!m_pScore->loadFromFile("assets/score.ogg"))
	{
		throw std::runtime_error("Unable to load assets/score.ogg");
	}

	m_pClick = new sf::SoundBuffer();
	if (!m_pClick->loadFromFile("assets/click.ogg"))
	{
		throw std::runtime_error("Unable to load assets/click.ogg");
	}
}

void SoundManager::PlaySoundExplosion()
{
	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*m_pExplosion);
	sound->setVolume(90.f);
	int randPitch = rand() % 30;
	sound->setPitch(0.7f + randPitch / 100.f);
	sound->play();
	m_pSounds.push_back(sound);
}

void SoundManager::PlaySoundScore()
{
	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*m_pScore);
	sound->setPitch(0.9f);
	sound->setVolume(90.f);
	sound->play();
	m_pSounds.push_back(sound);
}

void SoundManager::PlaySoundClick()
{
	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*m_pClick);
	sound->play();
	m_pSounds.push_back(sound);
}

void SoundManager::Update()
{
	// Clear sounds that finished playing
	int i = 0;
	for (auto itr = m_pSounds.begin(); itr != m_pSounds.end(); itr++)
	{
		if ((*itr)->getStatus() == sf::Sound::Status::Stopped)
		{
			m_pCleanup.push_back(i);
		}

		i++;
	}

	for (auto itr = m_pCleanup.rbegin(); itr != m_pCleanup.rend(); itr++)
	{
		delete m_pSounds[*itr];
		m_pSounds.erase(m_pSounds.begin() + *itr);
	}

	m_pCleanup.clear();
}

void SoundManager::Clear()
{
	// Delete leftover sounds
	for (auto itr = m_pSounds.begin(); itr != m_pSounds.end(); itr++)
	{
		delete *itr;
	}
	m_pSounds.clear();

	// Delete soundbuffers
	delete m_pExplosion;
	m_pExplosion = nullptr;

	delete m_pScore;
	m_pScore = nullptr;

	delete m_pClick;
	m_pClick = nullptr;
}