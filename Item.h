#pragma once // Include guard to prevent multiple inclusion of header

#include <iostream>
#include <string>

class Character; // Forward declaration of Character class to avoid circular dependency

class Item {
public:
    std::string name;
    std::string description;
    int damage;
    int defense;
    int value;
    Item(const std::string& name, const std::string& desc, const int damage, const int defence, int value);
    void Interact(Character* character, Item* item);
    std::string GetName() const;
    std::string GetDescription() const;
    int GetDamage() const;
    int GetDefense() const;
    int GetValue() const;
    bool operator == (Item other);
};

