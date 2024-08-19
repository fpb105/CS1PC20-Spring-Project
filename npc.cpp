#include "npc.h"
#include "Item.h" // Include Item.h to access the Item class
#include "Room.h" // Include Room.h to access the Room class

npc::npc(const std::string& name, int health) {
	this -> name = name;
	this -> health = health;
}

void npc::GetRandomRoom() {
    // Get exits as a map
    std::map<std::string, Room*> exitsMap = GetLocation()->GetExits();

    // Convert the map values (Room*) to a vector
    std::vector<Room*> connectedRooms;
    for (auto const& entry : exitsMap) {
        connectedRooms.push_back(entry.second);
    }

    // Choose a random room from the vector
    int randomIndex = rand() % connectedRooms.size();
    SetLocation(connectedRooms[randomIndex]);
}

void npc::takeDamage(int damage) {
	health -= damage;
    if (health <= 0) {
		std::cout << name << " has died." << std::endl;
		delete this;
	}
}

npc::~npc() {
    //transfer npcs Inventory to the room
    for (Item* item : this->inventory.GetItems()) {
        if (this->GetLocation()) {
            this->GetLocation()->inventory.AddItem(item);
        }
    }
}


void npc::PlayerPresent(Character* player) {
    // Ensure enemy and player have locations set
    if (location && player->GetLocation()) {
        std::cout << "Enemy " << name << " is with you!" << std::endl;
        // Check if enemy and player are in the same location
        if (location == player->GetLocation()) {
            // Find the item with the highest damage in the enemy's inventory
            Item* bestItem = nullptr;
            for (Item* item : inventory.GetItems()) {
                if (!bestItem || item->GetDamage() > bestItem->GetDamage()) {
                    bestItem = item;
                }
            }

            // If an item with damage is found, attack the player using the best item
            if (bestItem) {
                bestItem->Interact(player, bestItem);
            }
        }
    }
}