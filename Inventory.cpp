#include "Inventory.h"
#include "Item.h" // Include Item.h to use Item class

//make functions for Inventory class
void Inventory::AddItem(Item* item) {
	items.push_back(item);
}

void Inventory::RemoveItem(Item* item) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i] == item) {
			items.erase(items.begin() + i);
			break;
		}
	}
}

std::vector<Item*> Inventory::GetItems() const {
	return items;
}

Item* Inventory::GetItem(const std::string& name) const {
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->GetName() == name) {
			return items[i];
		}
	}
	return nullptr;
}

bool Inventory::HasItem(const std::string& name) const {
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->GetName() == name) {
			return true;
		}
	}
	return false;
}

bool Inventory::IsEmpty() const {
	return items.empty();
}

std::string Inventory::GetItemNames() {
	std::string itemNames;
	for (int i = 0; i < items.size(); i++) {
		if (items[i] != nullptr) {
			itemNames += items[i]->GetName() + ", ";
		}
	}
	return itemNames;
}

void Inventory::loadItems(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
	
	std::string line;
	std::string name;
	std::string description;
	int damage;
	int defense;
	int value;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::getline(ss, name, ',');
		std::getline(ss, description, ',');
		ss >> damage;
		ss >> defense;
		ss >> value;
		Item* item = new Item(name, description, damage, defense, value);
		AddItem(item);
	}

	file.close();
}