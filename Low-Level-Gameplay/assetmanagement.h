#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <iostream>

std::shared_ptr<sf::Texture> LoadResource(std::string file);
