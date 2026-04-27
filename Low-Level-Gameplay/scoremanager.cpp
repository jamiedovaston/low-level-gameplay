#include "game.h"

ScoreManager::ScoreManager()
{
	NewRound();

	if (!font.openFromFile("../font.ttf"))
		std::cout << "Failed to load font\n";

    backgroundSprite = std::make_unique<sf::Sprite>(*LoadResource("../Images/gradient.png"));
	backgroundSprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(10, 10)));
	backgroundSprite->setScale(sf::Vector2f(63.0f, 96.0f));

	scoreText = std::make_unique<sf::Text>(font);
	powerUpCountdownText = std::make_unique<sf::Text>(font);

	scoreText->setFont(font);
	powerUpCountdownText->setFont(font);

	scoreText->setCharacterSize(60);
	scoreText->setFillColor(sf::Color::White);
	scoreText->setStyle(sf::Text::Bold | sf::Text::Italic);
	scoreText->setPosition(sf::Vector2f(10.0f, 10.0f));

	powerUpCountdownText->setCharacterSize(35);
	powerUpCountdownText->setFillColor(sf::Color::White);
	powerUpCountdownText->setStyle(sf::Text::Bold);
	powerUpCountdownText->setPosition(sf::Vector2f(10.0f, 845.0f));
}

ScoreManager::~ScoreManager()
{

}

void ScoreManager::Update(float deltaTime)
{
	if (currentRound != nullptr) {
		currentRound->Update(deltaTime);
	}

	scoreText->setString(std::string("Score: ") + std::to_string(score));

	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << currentRound->pwrUpTimer;
	powerUpCountdownText->setString("Power Up Remaining: " + ss.str());

	gradientRuntime += deltaTime;
	if (gradientRuntime >= 9.9f) { gradientRuntime = 0.0f; }

	backgroundSprite->setTextureRect(sf::IntRect(sf::Vector2i(10.0f * gradientRuntime, 0.0f), sf::Vector2i(10, 10)));
}

void ScoreManager::Render(sf::RenderWindow* window) 
{
	if(currentRound->isPowerUp) { 
		window->draw(*backgroundSprite); 
		window->draw(*powerUpCountdownText);
	}
	
	window->draw(*scoreText);
}

ScoreManager::Round* ScoreManager::NewRound()
{
	currentRound = std::make_unique<Round>();
	return currentRound.get();
}

void ScoreManager::AddScore(bool isFused)
{
	if (isFused) {
		currentRound->fusedCount++;
		score += 200 + (100 * currentRound->fusedCount);
	}
	else {
		score += 200;
		currentRound->fusedCount = 0;
	}
}

void ScoreManager::AddScore(int amount)
{
	score += amount;
}
