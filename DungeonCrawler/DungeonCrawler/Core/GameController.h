#pragma once
#include <vector>
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"

// namespace Entities
// {
//     class Player;
//     class Enemy;
// }

namespace Core
{
    class GameController
    {
    public:
        void StartGame();

    private:
        Entities::Player * player = nullptr;
        std::vector<Entities::Enemy> enemies;
        
        int small_enemies_alive {0};
        int small_enemies_total {0};
        int medium_enemies_alive {0};
        int medium_enemies_total {0};
        int big_enemies_alive {0};
        int big_enemies_total {0};
        
        void SetupPlayer();
        void SetupEnemies();
        void IterateBattles();
        bool Battle(Entities::Player* player_ref, Entities::Enemy* enemy_ref);
        void UpdateEnemiesAlive(Entities::Enemy* enemy);
        void GameOver(bool is_win) const;

        void SetSmallEnemiesTotal(int amount);
        void SetMediumEnemiesTotal(int amount);
        void SetBigEnemiesTotal(int amount);
        int GetEnemiesTotalAmount() const;
        int GetEnemiesAliveAmount() const;
    };
}
