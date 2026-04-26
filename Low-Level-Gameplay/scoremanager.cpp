#include "game.h"

ScoreManager::ScoreManager()
{
	NewRound();
}

ScoreManager::~ScoreManager()
{

}

void ScoreManager::Update(float deltaTime)
{
	if (currentRound != nullptr) {
		currentRound.get()->Update(deltaTime);
	}
}

ScoreManager::Round* ScoreManager::NewRound()
{
	currentRound = std::make_unique<Round>();
	return currentRound.get();
}

void ScoreManager::AddScore(bool isFused)
{
	Round* r = currentRound.get();
	if (isFused) {
		r->fusedCount++;
		score += 200 + (100 * r->fusedCount);
	}
	else {
		score += 200;
		r->fusedCount = 0;
	}
}

void ScoreManager::AddScore(int amount)
{
	score += amount;
}
