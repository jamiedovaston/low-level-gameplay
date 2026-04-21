#include "assetmanagement.h"

static std::map<std::string, std::shared_ptr<sf::Texture>> assets;
std::shared_ptr<sf::Texture> LoadResource(std::string file) {

	auto it = assets.find(file);

	if (it == assets.end()) {
		std::cout << "# New resource loaded!" << std::endl;
		assets[file] = std::make_shared<sf::Texture>(file);
		return assets[file];
	}

	return it->second;
}