#include "entity.h"

Enemy::Enemy(sf::Vector2u screen) : Entity(screen)
{
	texture = new sf::Texture("../Images/skeleton.png");
	sprite = new sf::Sprite(*texture);
	spriteRect = sf::FloatRect(sf::Vector2f(0.0f / 2.0f, 0.0f), sf::Vector2f(34.0f / 2.0f, 43.0f / 2.0f));

	// SPAWN AT POSITION
	position = sf::Vector2f(400.0f, 200.0f);
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime){

	float projectedVelocityY = gravity;
	projectedVelocity.y += projectedVelocityY;
	velocity.y = std::clamp(projectedVelocity.y, -maxVerticalSpeed, maxVerticalSpeed);

	groundedBuffer -= deltaTime;
	isGrounded = groundedBuffer > 0.0f;

	if (isGroundedChanged != isGrounded) {
		isGroundedChanged = isGrounded;
		if (isGrounded) {
			aiDirection = -aiDirection;
		}
	}

	if (isGrounded) {
		float projectedVelocityX = aiDirection.x * 0.5f;
		if (velocity.x + projectedVelocityX < maxHorizontalSpeed && velocity.x + projectedVelocityX > -maxHorizontalSpeed)
			velocity.x += projectedVelocityX;
	}

	// DRAG
	velocity.x *= drag;

	// INVERT VELOCITY Y (defaults to downwards being positive) AND ADDS TO POSITION
	position += sf::Vector2f(velocity.x, -velocity.y) * deltaTime;

	sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void Enemy::Render(sf::RenderWindow* window)
{
	if (sprite != nullptr) { window->draw(*sprite); }
}
