#include "AssetManager.hpp"

AssetManager::AssetManager() {}

AssetManager::~AssetManager() {}

void AssetManager::addTexture(AssetID id, const std::string &fileName, bool wantRepeating) {
    auto texture = std::make_unique<sf::Texture>();

    std::string filePath = "../assets/textures/" + fileName;
    if (texture->loadFromFile(filePath)) {
        texture->setRepeated(wantRepeating);
        textures[id] = std::move(texture);
    }
}

void AssetManager::addFont(AssetID id, const std::string &fileName) {
    auto font = std::make_unique<sf::Font>();

    std::string filePath = "../assets/fonts/" + fileName;
    if (font->loadFromFile(filePath)) {
        fonts[id] = std::move(font);
    }
}


const sf::Texture &AssetManager::getTexture(AssetID id) const {
    return *(textures.at(id).get());
}

const sf::Font &AssetManager::getFont(AssetID id) const {
    return *(fonts.at(id).get());
}
