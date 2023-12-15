#pragma once
#include <string>

#include "Character.h"

namespace Entities
{
    class Enemy : public Character
    {
    public:
        enum class Size
        {
            small,
            medium,
            big
        };
        
        Enemy();
        ~Enemy();
        Enemy(Size size);
        Enemy(int health, int damage, int miss_chance, Size size);

        Size GetSize() const;
        std::string GetSizeName() const;
        
    private:
        Size size {Size::small};
    };
}
