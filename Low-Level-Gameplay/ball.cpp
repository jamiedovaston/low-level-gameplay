#include "entity.h"

Ball::Ball(Player* player, sf::Vector2u screen) : Enemy(player, screen)
{
	spriteSize = sf::Vector2i(42, 42);
	texture = new sf::Texture("../Images/ball-sprite-sheet.png");
	sprite = new sf::Sprite(*texture);
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
	spriteRect = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(42.0f / 2.0f, 42.0f / 2.0f));
}

Ball::~Ball()
{

}

void Ball::Update(float deltaTime) 
{
	Enemy::Update(deltaTime);

	if (player->isDead) return;

	Animations(deltaTime);

	direction = player->position - position;

	sf::Vector2f maxVel(maxHorizontalSpeed, maxVerticalSpeed);

	sf::Vector2f projectedVelocity = (direction != sf::Vector2f(0.0f, 0.0f) ? direction.normalized() : sf::Vector2f(0.0f, 0.0f)) * 0.5f;

	if (velocity.length() < maxVel.length())
		velocity += projectedVelocity;

	velocity *= drag;

	position += velocity * deltaTime;

	sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void Ball::Animations(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime > .075f) {
		elapsedTime = 0.0f;
		frame++;
		if (frame > 8) { frame = 0; }
	}

	sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, 0), spriteSize));
}
