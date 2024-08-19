#pragma once // Include guard to prevent multiple inclusion of header

#include "Character.h"

class Player : public Character {
private:
	int MaxHealth = 100;
public:
	int coins;
	Player(const std::string& name, int health, std::string filename);
	void TakeDamage(int damage);
};

