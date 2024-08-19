#include "Item.h"
#include "Character.h" // Include Character.h to use Character class

Item::Item(const std::string& name, const std::string& desc, const int dam, const int def, int val) : name(name), description(desc), damage(dam), defense(def), value(val) {}

void Item::Interact(Character* character, Item* item) {
	character->TakeDamage(item->GetDamage());
	if (item->GetDamage() > 0) {
		std::cout << character->GetName() << " took " << item->GetDamage() << " damage from " << item->GetName() << std::endl;
	}
	else if (item->GetDamage() < 0) {
		std::cout << character->GetName() << " healed " << item->GetDamage() << " damage from " << item->GetName() << std::endl;
	}
	else {
		std::cout << "This item does nothing to them!" << std::endl;
	}
}

std::string Item::GetName() const {
    return name;
}

std::string Item::GetDescription() const {
    return description;
}

int Item::GetDamage() const {
	return damage;
}

int Item::GetDefense() const {
	return defense;
}

int Item::GetValue() const {
	return value;
}

bool Item::operator == (Item other) {
	return name == other.GetName();
}