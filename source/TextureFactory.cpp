/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "stdafx.h"

#include "TextureFactory.h"

sf::Texture* TextureFactory::GetTexture(std::string resource_path)
{
    sf::Texture* texture = nullptr;
    if(m_TextureRes.find(resource_path) == m_TextureRes.end())
    {
        texture = new sf::Texture();
        if(!texture->loadFromFile(resource_path))
        {
            throw std::exception();
        }
        m_TextureRes[resource_path] = texture;
    }
    return m_TextureRes[resource_path];
}

sf::Font* TextureFactory::GetFont(std::string resource_path)
{
    sf::Font* font = nullptr;
    if(m_FontRes.find(resource_path) == m_FontRes.end())
    {
        font = new sf::Font();
        if(!font->loadFromFile(resource_path))
        {
            throw std::exception();
        }
        m_FontRes[resource_path] = font;
    }
    return m_FontRes[resource_path];
}

void TextureFactory::Clear()
{
    auto it_texture = m_TextureRes.begin();
    while(it_texture != m_TextureRes.end())
    {
        delete(it_texture->second);
        it_texture++;
    }
    m_TextureRes.clear();
    
    auto it_font = m_FontRes.begin();
    while(it_font != m_FontRes.end())
    {
        delete(it_font->second);
        it_font++;
    }
    m_FontRes.clear();
}