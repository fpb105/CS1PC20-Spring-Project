#pragma once // Include guard to prevent multiple inclusion of header

#include <iostream>
#include <string>
#include <vector>
#include "Inventory.h"

class Room;

class Character {
public:
	std::string name;
	int health;
	Room* location;
	Inventory inventory;
	Character(const std::string& name, int health);
	Character() {};
	std::string GetName() const;
	int GetHealth() const;
	void TakeDamage(int damage);
	void SetLocation(Room* newLocation);
	Room* GetLocation();
}; 
