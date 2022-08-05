#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadFilter(const string& filter) {
	string folder = "images/";
	folder += filter + ".png";
	textures[filter].loadFromFile(folder);
}

sf::Texture& TextureManager::GetTexture(const string& filter) {
	// When no TextureManager is found
	if (textures.find(filter) == textures.end()) {
        LoadFilter(filter);
	}
	return textures[filter];
}

void TextureManager::Clear() {
	textures.clear();
}