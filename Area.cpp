#include <iostream>
#include <fstream>
#include <sstream>
#include "Area.h" // Include Area.h to get the Area class definition
#include "Room.h" // Include the Room header file

void Area::AddRoom(const std::string& name, Room* room) {
    if (rooms.find(name) != rooms.end()) {
        return; // Do not add the room if it already exists
    }

    rooms[name] = room;
}

Room* Area::GetRoom(const std::string& name) {
	for (auto& pair : rooms) {
		if (pair.first == name) {
			return pair.second; // Returning the room pointer instead of nullptr
		}
	}
	return nullptr;
}

void Area::ConnectRooms(const std::string& room1Name, const std::string& room2Name, const std::string& direction) {
    Room* room1 = GetRoom(room1Name);
    Room* room2 = GetRoom(room2Name);

    if (room1 && room2) {
        room1->AddExit(direction, room2);
    }
}

void Area::LoadArea(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
    std::string line;
    std::string part;
    while (std::getline(file, line)) {
        if (line == "rooms") {
			part = "rooms";
		}
        else if (line == "connections") {
			part = "connections";
		}
        else if (part == "rooms") {
			std::string name;
			std::string description;
            std::string inventoryFile;
			std::istringstream ss(line);
			std::getline(ss, name, ',');
			std::getline(ss, description, ',');
            std::getline(ss, inventoryFile);
			Room* room = new Room(name, description);
			AddRoom(name, room);
            // load the inventory for the room
            room->inventory.loadItems(inventoryFile + ".txt");
		}
        else if (part == "connections") {
			std::string room1Name;
			std::string room2Name;
			std::string direction;
			std::istringstream ss(line);
			std::getline(ss, room1Name, ',');
			std::getline(ss, room2Name, ',');
			std::getline(ss, direction);
			ConnectRooms(room1Name, room2Name, direction);
		}
	}
	file.close();
	LoadEnemys("npcs.txt");
}

void Area::LoadEnemys(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
		std::string name;
		int health;
		std::string roomName;
		std::string inventoryFile;

		std::istringstream ss(line);
		std::getline(ss, name, ',');
		std::getline(ss, roomName, ',');
		std::getline(ss, inventoryFile, ',');
		ss >> health;

		Room* room = GetRoom(roomName);
		if (room) {
			Enemy* NewEnemy = new Enemy(name, health);
			NewEnemy->location = room;
			room->LocalNpcs.push_back(NewEnemy);
			GloablEnemys.push_back(NewEnemy);
			NewEnemy->inventory.loadItems(inventoryFile + ".txt");
		}
	}

    file.close();
}

