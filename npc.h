#pragma once // Include guard to prevent multiple inclusion of header


#include "Character.h"
#include "Player.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

class npc : public Character {
public:
	npc(const std::string& name, int health);
	~npc();
	void takeDamage(int damage);
	void GetRandomRoom();
	void PlayerPresent(Character* player);
};
