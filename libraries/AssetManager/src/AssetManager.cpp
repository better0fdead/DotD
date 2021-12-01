#include "AssetManager.hpp"


AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

void AssetManager::addTexture(int id, const std::string &filePath, bool wantRepeating) {
    auto texture = std::make_unique<sf::Texture>();

    if(texture->loadFromFile(filePath)){
        texture->setRepeated(wantRepeating);
        textures[id] = std::move(texture);
    }
}

void AssetManager::addFont(int id, const std::string &filePath){
    auto font = std::make_unique<sf::Font>();

    if(font->loadFromFile(filePath)){
        fonts[id] = std::move(font);
    }
}


const sf::Texture &AssetManager::getTexture(int id) const {
    return *(textures.at(id).get());
}

const sf::Font &AssetManager::getFont(int id) const {
    return *(fonts.at(id).get());
}
