#include "enemy.h"

Club::Club(Player* player, sf::Vector2u screen) : Enemy(player, screen)
{
	spriteSize = sf::Vector2i(45, 48);
	sprite = std::make_unique<sf::Sprite>(*LoadResource("Images/club-sprite-sheet.png"));
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
	spriteRect = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(45.0f / 2.0f, 48.0f / 2.0f));
}

Club::~Club()
{

}

void Club::Update(float deltaTime) 
{
	Enemy::Update(deltaTime);

	if (player->freeze.size() > 0 || flags == Enemy_Flags::POWERUP) return;

	Animations(deltaTime);

	direction = player->position - position;

	sf::Vector2f _direction = player->position - position;

	_direction.y = std::clamp(_direction.y, -1.0f, 1.0f);
	_direction.x = std::clamp(_direction.x, -1.0f, 1.0f);

	projectedDirection += _direction;
	projectedDirection.x = std::clamp(projectedDirection.x, -maxHorizontalSpeed, maxHorizontalSpeed);
	projectedDirection.y = std::clamp(projectedDirection.y, -maxVerticalSpeed, maxVerticalSpeed);

	direction.y = std::clamp(projectedDirection.y, -1.0f, 1.0f);
	direction.x = std::clamp(projectedDirection.x, -1.0f, 1.0f);

	sf::Vector2f maxVel(maxHorizontalSpeed, maxVerticalSpeed);

	projectedVelocity = (direction != sf::Vector2f(0.0f, 0.0f) ? direction.normalized() : sf::Vector2f(0.0f, 0.0f)) * 0.5f;

	if (velocity.length() < maxVel.length())
		velocity += projectedVelocity;

	velocity *= drag;

	position += velocity * deltaTime;

	sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void Club::Animations(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime > .15f) {
		elapsedTime = 0.0f;
		frame++;
		if (frame > 3) { frame = 0; }
	}

	if (direction.x > 0.0f) { // LEFT
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, spriteSize.y), spriteSize));
	}
	else { // RIGHT
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, 0), spriteSize));
	}

}
