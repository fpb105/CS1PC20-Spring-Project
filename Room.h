#pragma once // Include guard to prevent multiple inclusion of header

#include "Inventory.h"
#include "npc.h"
#include <iostream>
#include <string>
#include <map>

class Room {
public:
	std::string name;
	std::string description;
	std::map<std::string, Room*> exits;
	Inventory inventory;
	std::vector<npc*> LocalNpcs;
	Room();
	Room(const std::string& name, const std::string& desc);
	void AddExit(const std::string& direction, Room* destination);
	std::string GetDescription() const;
	std::string GetName() const;
	Room* GetExit(const std::string& direction);
	std::map<std::string, Room*> GetExits();
	//void LoadNpcs(std::string filename);
};
