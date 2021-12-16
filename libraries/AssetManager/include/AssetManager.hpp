#pragma once

#include <map>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

enum class AssetID {
    MAIN_FONT = 0, BACKGROUND, GUARDIAN, TYAN, STONE, BULLET,  PAUSE, LOST, MENU
};

class AssetManager {
public:
    AssetManager();

    ~AssetManager();

    void addTexture(AssetID id, const std::string &fileName, bool wantRepeating = false);

    void addFont(AssetID id, const std::string &fileName);

    const sf::Texture &getTexture(AssetID id) const;

    const sf::Font &getFont(AssetID id) const;

private:
    std::map<AssetID, std::unique_ptr<sf::Texture>> textures;
    std::map<AssetID, std::unique_ptr<sf::Font>> fonts;
};
