#include "GameController.h"
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace Core
{
    void GameController::StartGame()
    {
        SetupPlayer();
        SetupEnemies();
        IterateBattles();
    }

    void GameController::IterateBattles()
    {
        std::vector<Entities::Enemy>::iterator iter = enemies.begin();

        while (iter < enemies.end())
        {
            if (Battle(player, &*iter))
            {
                //Player won this round. Battle the next enemy.
                UpdateEnemiesAlive(&*iter);
                ++iter;
            }
            else
            {
                GameOver(false);
                return;
            }
        }

        GameOver(true);
    }
    
    /**
     * \brief Simulates a battle between the player and an enemy.
     * \param player_ref Player reference
     * \param enemy_ref Enemy reference
     * \return Returns true if the player won this battle, or false if lost.
     */
    bool GameController::Battle(Entities::Player* player_ref, Entities::Enemy* enemy_ref)
    {
        while (!enemy_ref->IsDead() && !player_ref->IsDead())
        {
            int damage = player_ref->DoDamage();
            enemy_ref->TakeDamage(damage);
            std::cout << "Enemy(" << enemy_ref->GetSizeName() << ") " << "took " << damage << " damage from player. Now has " << enemy_ref->GetHealth() << "HP" << std::endl;

            if(!enemy_ref->IsDead())
            {
                damage = enemy_ref->DoDamage();
                player_ref->TakeDamage(damage);
                std::cout << player_ref->GetName() << " took " << damage << " damage from " << "Enemy(" << enemy_ref->GetSizeName() << "). " << "Now has " << player_ref->GetHealth() << "HP" << std::endl;
            }
            
            std::cout << "-------------------------------------------------" << std::endl;
        }

        // If returns that the enemy is dead, that means the player won this battle
        return enemy_ref->IsDead();
    }

    void GameController::SetupPlayer()
    {
        std::cout << "Enter you character name: ";
        std::string char_name;
        std::getline(std::cin, char_name);
        player = new Entities::Player(char_name);
    }

    void GameController::SetupEnemies()
    {
        int small_enemies;
        std::cout << "Enter the amount of small enemies: ";
        std::cin >> small_enemies;
        this->SetSmallEnemiesTotal(small_enemies);

        int medium_enemies;
        std::cout << "Enter the amount of medium enemies: ";
        std::cin >> medium_enemies;
        this->SetMediumEnemiesTotal(medium_enemies);

        int big_enemies;
        std::cout << "Enter the amount of big enemies: ";
        std::cin >> big_enemies;
        this->SetBigEnemiesTotal(big_enemies);

        system("cls");

        for (int i = 0; i < small_enemies; ++i)
        {
            enemies.emplace_back(Entities::Enemy::Size::small);
        }

        for (int i = 0; i < medium_enemies; ++i)
        {
            enemies.emplace_back(Entities::Enemy::Size::medium);
        }

        for (int i = 0; i < big_enemies; ++i)
        {
            enemies.emplace_back(Entities::Enemy::Size::big);
        }

        const unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
        std::shuffle(enemies.begin(), enemies.end(), std::default_random_engine(seed));
    }

    void GameController::UpdateEnemiesAlive(Entities::Enemy* enemy)
    {
        switch (enemy->GetSize()) {
        case Entities::Enemy::Size::small:
            --small_enemies_alive;
            break;
        case Entities::Enemy::Size::medium:
            --medium_enemies_alive;
            break;
        case Entities::Enemy::Size::big:
            --big_enemies_alive;
            break;
        }
    }

    void GameController::GameOver(bool is_win) const
    {
        std::cout << (is_win ? "You Win!" : "You Lose!") << std::endl;
        std::cout << "Enemies Slain:" << std::endl;
        std::cout << "Big: " << (big_enemies_total - big_enemies_alive) << "/" << big_enemies_total << std::endl;        
        std::cout << "Medium: " << (medium_enemies_total - medium_enemies_alive) << "/" << medium_enemies_total << std::endl;
        std::cout << "Small: " << (small_enemies_total - small_enemies_alive) << "/" << small_enemies_total << std::endl;
    }
    
    void GameController::SetSmallEnemiesTotal(int amount)
    {
        this->small_enemies_total = this->small_enemies_alive = amount;
    }

    void GameController::SetMediumEnemiesTotal(int amount)
    {
        this->medium_enemies_total = this->medium_enemies_alive = amount;
    }

    void GameController::SetBigEnemiesTotal(int amount)
    {
        this->big_enemies_total = this->big_enemies_alive = amount;
    }

    int GameController::GetEnemiesTotalAmount() const
    {
        return this->small_enemies_total + this->medium_enemies_total + this->big_enemies_total;
    }

    int GameController::GetEnemiesAliveAmount() const
    {
        return this->small_enemies_alive + this->medium_enemies_alive + this->big_enemies_alive;
    }
    
}
