#include "pickup.h"

PowerUpCoin::PowerUpCoin(Player* player, sf::Vector2u screen) : Pickup(player, screen)
{
	spriteSize = sf::Vector2i(36, 36);
	sprite = std::make_unique<sf::Sprite>(*LoadResource("Images/coins.png"));
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
	spriteRect = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(36.0f / 2.0f, 36.0f / 2.0f));

	direction = sf::Vector2f(1.0f, -1.0f);
}

PowerUpCoin::~PowerUpCoin()
{

}

void PowerUpCoin::Update(float deltaTime)
{
	if (player->freeze.size() != 0) return;

	Pickup::Update(deltaTime);

	sf::Vector2f maxVel(maxHorizontalSpeed, maxVerticalSpeed);

	projectedVelocity = (direction != sf::Vector2f(0.0f, 0.0f) ? direction.normalized() : sf::Vector2f(0.0f, 0.0f)) * 1.2f;

	if (velocity.length() < maxVel.length())
		velocity += projectedVelocity;

	velocity *= drag;

	position += velocity * deltaTime;

	sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void PowerUpCoin::OnPickup()
{
	
}

void PowerUpCoin::Animations(float deltaTime)
{
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x, 0), spriteSize));
}
