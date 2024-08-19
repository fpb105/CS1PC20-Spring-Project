#include "Player.h"
#include "Item.h" // Include Item.h to use Item class

Player::Player(const std::string& name, int health, std::string filename) {
	this->inventory.loadItems(filename);
	this->location = nullptr;
    this->name = name;
    this->health = health;
	this->MaxHealth = health;
}

void Player::TakeDamage(int damage) {
	// get totl amour value of whats in inventory
	int totalArmour = 0;
	for (Item* item : this->inventory.items) {
		int amourValue = item->GetDefense();
		if (amourValue > 0) {
			totalArmour += amourValue;
		}
	}
	damage = damage - (totalArmour / 6);
	if (damage < 0) {
		damage = 0;
	}
	this->health -= damage;
	if (this->health > this->MaxHealth) {
		this->health = this->MaxHealth;
	}
	std::cout << "You are on " << this->health << " health" << std::endl;
    if (this->health <= 0) {
		std::cout << "You died!" << std::endl;
		exit(0);
	}
}