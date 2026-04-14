#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

std::shared_ptr<sf::Texture> LoadResource(std::string file);
