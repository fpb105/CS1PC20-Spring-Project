#include "CommandInterpreter.h"

// extra includes to make sure we can access forward declared classes
#include "Player.h"
#include "Item.h"
#include "Room.h"
#include "Enemy.h"

CommandInterpreter::CommandInterpreter(Player* player) : player_(player) {}

bool CommandInterpreter::commandSpliter(std::string command) {
	std::vector<std::string> commandVector;
	std::string word;
	std::stringstream stream(command);
	while (stream >> word) {
		commandVector.push_back(word);
	}
	commandExecutor(commandVector);
	return true;
}

void CommandInterpreter::commandExecutor(std::vector<std::string> command) {
	for (int i = 0; i < command.size(); i++) {
		if (command[i] == "move") {
			for (const auto& exit : player_->GetLocation()->GetExits()) {
				if (command[i + 1] == exit.first) {
					player_->SetLocation(exit.second);
					break;
				}
			}
		} else if (command [i] == "look") {
			std::cout << player_->GetLocation()->GetDescription() << std::endl;
			std::cout << "You see: " << player_->GetLocation()->inventory.GetItemNames() << "in this area" << std::endl;
			for (npc* npcsInRoom : player_->GetLocation()->LocalNpcs) {
				std::cout << "You see: " << npcsInRoom->GetName() << " in this area!" << std::endl;
			}
		}
		else if (command[i] == "inventory") {
			std::cout << "You have: " << player_->inventory.GetItemNames() << std::endl;
		}
		else if (command[i] == "drop") {
			Item* itemToBeMoved = player_->inventory.GetItem(command[i + 1]);
			player_->GetLocation()->inventory.AddItem(itemToBeMoved);
			player_->inventory.RemoveItem(itemToBeMoved);
			std::cout << "You dropped: " << itemToBeMoved->GetName() << std::endl;
		}
		else if (command[i] == "pickup") {
			Item* itemToBeMoved = player_->inventory.GetItem(command[i + 1]);
			player_->inventory.AddItem(itemToBeMoved);
			player_->GetLocation()->inventory.RemoveItem(itemToBeMoved);
			std::cout << "You picked up: " << itemToBeMoved->GetName() << std::endl;
		}
		else if (command[i] == "use" or command[i] == "attack" or command [i] == "heal") {
			if (player_->inventory.HasItem(command[i + 1])) {
				Item* item = player_->inventory.GetItem(command[i + 1]);
				// go through all npcs in room and check if they are the target
				npc* Traget = nullptr;
				for (npc* npcsInRoom : player_->GetLocation()->LocalNpcs) {
					if (npcsInRoom->GetName() == command[i + 2]) {
						Traget = npcsInRoom;
						break;
					}
				}
				if (Traget == nullptr) {
					std::cout << "No such target" << std::endl;
					return;
				}
				std::string TargetName = Traget->GetName();

				item -> Interact(Traget, item);
				std::cout << "You used: " << item->GetName() << "on" << TargetName << std::endl;

				std::cout << TargetName << "has" << Traget->GetHealth() << "health left" << std::endl;
			}
		}
		else if (command[i] == "inspect") {
			if (player_->inventory.HasItem(command[i + 1])) {
				Item* item = player_->inventory.GetItem(command[i + 1]);
				std::cout << item->GetDescription() << std::endl;
			}
		}
		else if (command[i] == "help") {
			std::cout << "Commands: move, look, inventory, drop, pickup, use, attack, heal, inspect, help, quit" << std::endl;
		}
		else if (command[i] == "quit") {
			exit(0);
		}
	}
}