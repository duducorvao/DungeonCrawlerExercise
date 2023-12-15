#pragma once
#include <string>
#include "Character.h"

namespace Entities
{
    class Player : public Character
    {
    public:
        explicit Player(const std::string& name);
        Player(int health, int damage, int miss_chance, std::string name);
        std::string GetName() const;

    private:
        std::string name;
    };
}
