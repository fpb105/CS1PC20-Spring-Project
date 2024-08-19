#pragma once // Include guard to prevent multiple inclusion of header

#include <vector>
#include <fstream>
#include <iostream>
#include "sstream"

class Item; // Forward declaration of Item class to avoid circular dependency

class Inventory {
public:
	std::vector<Item*> items;
	std::string GetItemNames();
	void AddItem(Item* item);
	void RemoveItem(Item* item);
	std::vector<Item*> GetItems() const;
	Item* GetItem(const std::string& name) const;
	bool HasItem(const std::string& name) const;
	bool IsEmpty() const;
	void loadItems(const std::string& filename);
};
