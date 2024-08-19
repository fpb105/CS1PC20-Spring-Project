#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <chrono>

/* Classes */
#include "Area.h"
#include "enemy.h"
#include "Player.h"
#include "CommandInterpreter.h"
#include "Item.h"

int main() {

	std::cout << "Welcome to the game!" << std::endl;
	std::cout << "Commands are move, look, inventory, drop, pickup, use, attack, heal, quit" << std::endl;
	std::cout << "Or type what ever you want and let the AI figure it out! :)" << std::endl;
	std::cout << "Type 'help' for a list of commands" << std::endl;
	std::cout << "Enjoy :)" << std::endl;

	GptApi gpt = GptApi();

	// Create an instance of the Area class
	Area gameWorld;
	// Load the game map from a text file
	gameWorld.LoadArea("map.txt");
	// Create a Player
	Player  player("Alice", 100, "playerInventory.txt");
	// Set the player's starting room (you can modify this room name)
	Room* currentRoom = gameWorld.GetRoom("startRoom");
	player.SetLocation(currentRoom);
	CommandInterpreter brain = CommandInterpreter(&player);
	while (true) {
		// move enemys and check if they moved where player is
		for (Enemy* enemy : gameWorld.GloablEnemys) {
			enemy->GetRandomRoom();
		}

		//print player health
		std::cout << "Health: " << player.GetHealth() << std::endl;

		std::string command = "";
		std::cout << "> ";
		std::getline(std::cin, command);
		if (command == "quit") {
			break;
		}
		//AI will not return good results
		std::string query = "This will be a prompt: " + command;
		std::string result = gpt.POSTQuery(query);
		// This is what the ai responded with
		// Response in json format, but interpreter wont care and only read whats important
		std::cout << result << std::endl;

		// With proper AI it would be brain.commandSpliter(result);
		brain.commandSpliter(command);

		// check here so player can see if enemys present or not
		// enemys should go after player
		for (Enemy* enemy : gameWorld.GloablEnemys) {
			enemy->PlayerPresent(&player);
		}
	}
	return 0;
}