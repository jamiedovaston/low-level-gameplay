#include "pickup.h"

Bomb::Bomb(Player* player, sf::Vector2u screen) : Pickup(player, screen)
{
	spriteSize = sf::Vector2i(48, 48);
	sprite = std::make_unique<sf::Sprite>(*LoadResource("Images/bomb-sprite-sheet.png"));
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
	spriteRect = sf::FloatRect(sf::Vector2f(4.0f, 20.0f), sf::Vector2f(40.0f / 2.0f, 28.0f / 2.0f));
}

Bomb::~Bomb()
{

}

void Bomb::OnPickup()
{
	std::string s = (bstate == BState::FUSED) ? " FUSED!" : "!";
	std::cout << "Picked up" << s << std::endl;
}

void Bomb::Animations(float deltaTime)
{
	if (bstate == BState::NONE) {
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
		return;
	}

	elapsedTime += deltaTime;

	if (elapsedTime > .1f) {
		elapsedTime = 0.0f;
		frame++;
		if (frame > 1) { frame = 0; }
	}

	sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, spriteSize.y), spriteSize));
}