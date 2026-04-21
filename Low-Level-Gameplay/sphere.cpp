#include "enemy.h"

Sphere::Sphere(Player* player, sf::Vector2u screen) : Enemy(player, screen)
{
	spriteSize = sf::Vector2i(42, 42);
	sprite = new sf::Sprite(*LoadResource("../Images/ball-sprite-sheet.png"));
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
	spriteRect = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(42.0f / 2.0f, 42.0f / 2.0f));

	direction.y = 1.0f;
}

Sphere::~Sphere()
{

}

void Sphere::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (player->isDead) return;

	Animations(deltaTime);

	direction.x = std::clamp(player->position.x - position.x, -1.0f, 1.0f);

	sf::Vector2f maxVel(maxHorizontalSpeed, maxVerticalSpeed);

	projectedVelocity = direction.normalized() * 0.5f;

	if (velocity.length() < maxVel.length())
		velocity += projectedVelocity;

	velocity *= drag;

	position += velocity * deltaTime;

	sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void Sphere::Animations(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime > .1f) {
		elapsedTime = 0.0f;
		frame++;
		if (frame > 8) { frame = 0; }
	}

	sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, 0), spriteSize));
}
