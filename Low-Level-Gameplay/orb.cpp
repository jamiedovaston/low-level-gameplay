#include "enemy.h"

Orb::Orb(Player* player, sf::Vector2u screen) : Enemy(player, screen)
{
	spriteSize = sf::Vector2i(42, 39);
	sprite = std::make_unique<sf::Sprite>(*LoadResource("../Images/orb-sprite-sheet.png"));
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
	spriteRect = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(42.0f / 2.0f, 39.0f / 2.0f));

	maxVerticalSpeed = 5.0f;

	direction.x = 1.0f;
}

Orb::~Orb()
{

}

void Orb::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (player->freeze.size() > 0 || flags == Enemy_Flags::POWERUP) return;

	Animations(deltaTime);

	projectedDirection += std::clamp(player->position.y - position.y, -.01f, .01f);
	projectedDirection = std::clamp(projectedDirection, -maxVerticalSpeed, maxVerticalSpeed);
	direction.y = std::clamp(projectedDirection, -1.0f, 1.0f);

	projectedVelocity = direction.normalized() * 0.5f;

	velocity += projectedVelocity;

	velocity *= drag;

	position += velocity * deltaTime;

	sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void Orb::Animations(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime > .1f) {
		elapsedTime = 0.0f;
		frame++;
		if (frame > 6) { frame = 0; }
	}

	sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, 0), spriteSize));
}
