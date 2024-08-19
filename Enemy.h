#pragma once // Include guard to prevent multiple inclusion of header

#include "npc.h"

class Enemy : public npc {
public:
	Enemy(const std::string& name, int health);
};
