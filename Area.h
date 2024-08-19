#pragma once // Include guard to prevent multiple inclusion of header

#include <map>
#include <vector>
#include <string>
#include "Enemy.h"

class Room; // Forward declaration of Room class instead of include to avoid circular dependency

class Area {
public:
	std::map<std::string, Room*> rooms;
	std::vector<Enemy*> GloablEnemys;
	void AddRoom(const std::string& name, Room* room);
	Room* GetRoom(const std::string& name);
	void ConnectRooms(const std::string& room1Name, const std::string&room2Name, const std::string& direction);
	void LoadArea(const std::string& filename);
	void LoadEnemys(const std::string& filename);
};
