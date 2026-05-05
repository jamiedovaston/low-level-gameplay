#include "enemy.h"

Skeleton::Skeleton(Player* player, sf::Vector2u screen, bool isRight) : Enemy(player, screen)
{
	spriteSize = sf::Vector2i(39, 45);
	sprite = std::make_unique<sf::Sprite>(*LoadResource("Images/skeleton-sprite-sheet.png"));
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), spriteSize));
	spriteRect = sf::FloatRect(sf::Vector2f(3.0f, 2.0f), sf::Vector2f(34.0f / 2.0f, 43.0f / 2.0f));

	direction = sf::Vector2f((isRight ? 1.0f : -1.0f), 0.0f);
}

Skeleton::~Skeleton()
{

}

void Skeleton::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (player->freeze.size() > 0 || flags == Enemy_Flags::POWERUP) return;

	float projectedVelocityY = gravity;
	projectedVelocity.y += projectedVelocityY;
	velocity.y = std::clamp(projectedVelocity.y, -maxVerticalSpeed, maxVerticalSpeed);

	groundedBuffer -= deltaTime;
	isGrounded = groundedBuffer > 0.0f;

	// RESET DIRECTION CHANGE COUNT WHEN LANDED FROM FALL
	if (isGroundedChanged != isGrounded) {
		isGroundedChanged = isGrounded;
		if (isGrounded) {
			directionChangeCount = 3;
		}
	}

	if (isGrounded) {
		float projectedVelocityX = direction.x * 0.5f;
		if (velocity.x + projectedVelocityX < maxHorizontalSpeed && velocity.x + projectedVelocityX > -maxHorizontalSpeed)
			velocity.x += projectedVelocityX;
	}

	// DRAG
	velocity.x *= drag;

	// INVERT VELOCITY Y (defaults to downwards being positive) AND ADDS TO POSITION
	position += sf::Vector2f(velocity.x, -velocity.y) * deltaTime;

	Animations(deltaTime);

	sprite->setPosition(sf::Vector2f(position.x - spriteRect.position.x - spriteRect.size.x, position.y - spriteRect.position.y - spriteRect.size.y));
}

void Skeleton::ChangeDirection(sf::Vector2f direction)
{
	if (this->direction == direction) return;
	
	if (directionChangeCount > 0) {
		this->direction = direction;
		directionChangeCount--;
		elapsedTime = 0.0f;
		frame = 0;
	}
}

void Skeleton::Animations(float deltaTime)
{
	elapsedTime += deltaTime;

	if (direction.x > 0.0f) // RIGHT
	{
		if (elapsedTime > .075f) {
			elapsedTime = 0.0f;
			frame++;
			if (frame > 3) { frame = 0; }
		}
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, spriteSize.y), spriteSize));
	}
	else if (direction.x < 0.0f) // LEFT
	{
		if (elapsedTime > .075f) {
			elapsedTime = 0.0f;
			frame++;
			if (frame > 3) { frame = 0; }
		}
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(spriteSize.x * frame, spriteSize.y * 2), spriteSize));
	}
	
	if(!isGrounded)// STRAIGHT
	{
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, spriteSize.y * 3), spriteSize));
	}
}
