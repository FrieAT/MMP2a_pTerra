/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

class TextureFactory
{
public:
    static TextureFactory& GetInstance()
    {
        static TextureFactory g_Instance;
        return g_Instance;
    }
    sf::Texture* GetTexture(std::string resource_path);
    sf::Font* GetFont(std::string resource_path);
    void Clear();
private:
    TextureFactory() { }
    TextureFactory(const TextureFactory&) = delete;
    void operator= (const TextureFactory&) = delete;
    std::map<std::string, sf::Texture*> m_TextureRes;
    std::map<std::string, sf::Font*> m_FontRes;
};