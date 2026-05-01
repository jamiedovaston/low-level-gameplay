#include "game.h"

ScoreManager::ScoreManager(Player* player)
{
	this->player = player;

	NewRound();

	if (!font.openFromFile("../font.ttf"))
		std::cout << "Failed to load font\n";

    backgroundSprite = std::make_unique<sf::Sprite>(*LoadResource("../Images/gradient.png"));
	backgroundSprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(10, 10)));
	backgroundSprite->setScale(sf::Vector2f(63.0f, 96.0f));

	livesDisplay.resize(3);
	for (int i = 0; i < livesDisplay.size(); i++) {
		livesDisplay[i] = std::make_unique<sf::Sprite>(*LoadResource("../Images/jack.png"));
		livesDisplay[i]->setPosition(sf::Vector2f(25.0f + 45.0f * i, 845.0f));
	}

	scoreText = std::make_unique<sf::Text>(font);
	powerUpCountdownText = std::make_unique<sf::Text>(font);
	highScoreText = std::make_unique<sf::Text>(font);

	scoreText->setCharacterSize(55);
	scoreText->setFillColor(sf::Color::White);
	scoreText->setStyle(sf::Text::Bold);
	scoreText->setPosition(sf::Vector2f(10.0f, 5.0f));

	highScoreText->setCharacterSize(20);
	highScoreText->setFillColor(sf::Color::White);
	highScoreText->setStyle(sf::Text::Bold | sf::Text::Italic);
	highScoreText->setPosition(sf::Vector2f(10.0f, 65.0f));
	highScoreText->setString("Highscore: ");

	powerUpCountdownText->setCharacterSize(28);
	powerUpCountdownText->setFillColor(sf::Color::White);
	powerUpCountdownText->setStyle(sf::Text::Bold);
	powerUpCountdownText->setPosition(sf::Vector2f(180.0f, 845.0f));
}

ScoreManager::~ScoreManager()
{

}

void ScoreManager::Update(float deltaTime)
{
	if (currentRound != nullptr) {
		currentRound->Update(deltaTime);
	}

	if (player->freeze.size() > 0)
	{
		currentRound->isPowerUp = false;
		currentRound->pwrUpTimer = 0.0f;
	}

	scoreText->setString(std::string("Score: ") + std::to_string(score));

	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << currentRound->pwrUpTimer;
	powerUpCountdownText->setString("Power Up Remaining: " + ss.str());

	gradientRuntime += deltaTime;
	if (gradientRuntime >= 9.9f) { gradientRuntime = 0.0f; }

	backgroundSprite->setTextureRect(sf::IntRect(sf::Vector2i(10.0f * gradientRuntime, 0.0f), sf::Vector2i(10, 10)));
}

void ScoreManager::Render(sf::RenderWindow* window) const
{
	if(currentRound->isPowerUp) { 
		window->draw(*backgroundSprite); 
		window->draw(*powerUpCountdownText);
	}

	for (int i = 0; i < lives; i++) {
		window->draw(*livesDisplay[i]);
	}
	
	window->draw(*scoreText);
	window->draw(*highScoreText);
}

ScoreManager::Round* ScoreManager::NewRound()
{
	currentRound = std::make_unique<Round>();
	return currentRound.get();
}

bool ScoreManager::Death()
{
	lives--;
	return lives == 0;
}

void ScoreManager::Reset()
{
	score = 0;
	lives = 3;
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

void ScoreManager::SetHighscoreText(int score)
{
	highScoreText->setString("Highscore: " + std::to_string(score));
}
