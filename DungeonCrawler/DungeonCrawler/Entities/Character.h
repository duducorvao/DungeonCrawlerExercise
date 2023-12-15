#pragma once
namespace Entities
{
    class Character
    {
    public:
        Character();
        ~Character();
        Character(int health, int damage, int miss_chance);
        void TakeDamage(int amount);
        int DoDamage() const;
        bool IsDead() const;
        int GetHealth() const;

    protected:
        int health {0};
        int damage {0};
        int miss_chance = {0};
        bool is_dead {false};
    };
}
