#include "Enemy.h"

namespace Entities
{
    Enemy::Enemy() = default;
    Enemy::~Enemy() = default;

    Enemy::Enemy(Size size)
    {
        switch (size) {
        case Size::small:
            this->health = 5;
            this->damage = 2;
            this->miss_chance = 20; 
            break;
        case Size::medium:
            this->health = 15;
            this->damage = 3;
            this->miss_chance = 25; 
            break;
        case Size::big:
            this->health = 25;
            this->damage = 5;
            this->miss_chance = 30; 
            break;
        }

        this->size = size; 
    }

    Enemy::Enemy(int health, int damage, int miss_chance, Size size) : Character(health, damage, miss_chance),
                                                                       size(size)
    {
    }

    Enemy::Size Enemy::GetSize() const
    {
        return size;
    }

    std::string Enemy::GetSizeName() const
    {
        switch (size) {
        case Size::small:
            return "Small";
        case Size::medium:
            return "Medium";
        case Size::big:
            return "Big";
        }

        return "";
    }
}
