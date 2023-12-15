#include "Character.h"
#include <algorithm>

namespace Entities
{
    Character::Character() = default;
    Character::~Character() = default;

    Character::Character(int health, int damage, int miss_chance): health(health), damage(damage),
                                                                   miss_chance(miss_chance), is_dead(false)
    {
    }

    void Character::TakeDamage(int amount)
    {
        this->health = std::max(0, this->health - amount);
        this->is_dead = this->health == 0;
    }

    int Character::DoDamage() const
    {
        const int proc { std::rand() % 100};
        return proc <= miss_chance ? 0 : this->damage;
    }
    
    bool Character::IsDead() const
    {
        return this->is_dead;
    }

    int Character::GetHealth() const
    {
        return health;
    }
}
