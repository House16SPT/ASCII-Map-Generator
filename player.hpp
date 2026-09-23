#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdlib>


class Player{

    private:
        int health;
        int damage;


    public:
        

        Player(){
            health = 100;
            damage = 10;
        };

        const int getHealth(){
            return health;
        }

        const int getDamage(){
            return damage;
        }
};

#endif