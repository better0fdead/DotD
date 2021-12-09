#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class AssetManager{
public:
    AssetManager();
    ~AssetManager();

    void addTexture(int id, const std::string& filePath, bool wantRepeating = false);
    void addFont(int id, const std::string& filePath);

    const sf::Texture &getTexture(int id) const;
    const sf::Font &getFont(int id) const;



private:
std::map<int, std::unique_ptr<sf::Texture>> textures;
std::map<int, std::unique_ptr<sf::Font>> fonts;

};