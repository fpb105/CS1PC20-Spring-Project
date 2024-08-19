#include "Room.h"

Room::Room() {
	name = "Default Room";
	description = "This is a default room.";
}

Room::Room(const std::string& name, const std::string& desc) {
	this->name = name;
	this->description = desc;
}

void Room::AddExit(const std::string& direction, Room* destination) {
	exits[direction] = destination;
}

std::string Room::GetDescription() const {
	return description;
}

std::string Room::GetName() const {
	return name;
}

Room* Room::GetExit(const std::string& direction) {
	if (exits.find(direction) != exits.end()) {
		return exits.at(direction);
	}
	return nullptr;
}

std::map<std::string, Room*> Room::GetExits() {
	return exits;
}

