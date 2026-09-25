#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <cstdlib>
#include <string>
#include <random>


class Monster{

    private:
        std::string name;
        int health;
        int damage;


        std::string names[10] = {"Goblin", "Hobgoblin", "Ork", "Demon", "Bandit",
             "Highwayman", "Zombie", "Rat", "Vampire Thrall", "Vampire"};

    public:
        
        int x;
        int y;
        int type;
        Monster(){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution posSeedX(1, 1198);
            std::uniform_int_distribution posSeedY(1, 278);           
            
            health = rand() % 100 + 5;
            damage = rand() % 5 + 1;
            name = nameGen();
            x = posSeedX(gen);
            y = posSeedY(gen);
            type = 11;
        };

        const int getHealth(){
            return health;
        }

        const float getDamage(){
            return damage;
        }

        std::string nameGen(){
            srand(time(NULL));
            int r = rand() % 9;

            return names[r];
        }

        int rollDamage(){
            srand(time(NULL));
            return rand() % damage;
        }
};

#endif