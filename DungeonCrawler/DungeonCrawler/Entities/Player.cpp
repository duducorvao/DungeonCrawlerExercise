#include "Player.h"

namespace Entities
{
    Player::Player(const std::string& name)
    {
        this->health = 50;
        this->damage = 10;
        this->miss_chance = 10;
        this->name = name;
    }

    Player::Player(int health, int damage, int miss_chance, std::string name):
        Character(health, damage, miss_chance), name(std::move(name))
    {
        this->health = 100;
        this->damage = 10;
        this->miss_chance = 10;
    }

    std::string Player::GetName() const
    {
        return this->name;
    }
    
}
