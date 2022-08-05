#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;


class TextureManager
{
	static unordered_map<string, sf::Texture> textures;
	static void LoadFilter(const string& filter);
public:
	static sf::Texture& GetTexture(const string& filter);
	static void Clear();

};

