#include "Character.h"

Character::Character(const std::string& name, int health) {
    this->name = name;
	this->health = health;
    this->location = nullptr;
}

void Character::TakeDamage(int damage) {
    //different for npcs and players so will be overriden
    // by this i mean npc will die, player will end game, boss will give rewards
}

void Character::SetLocation(Room* newLocation) {
    location = newLocation;
}

Room* Character::GetLocation() {
    return location;
}

std::string Character::GetName() const {
	return name;
}

int Character::GetHealth() const {
	return health;
}