#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdlib>


class Player{

    private:
        int health;
        float damage;
        int level;
        int xp;

    public:
        int x;    
        int y;

        Player(int width, int height){
            x = width/2;
            y = height/2;

            health = 100;
            damage = 1.0;
            level = 1;
            xp = 0;
        };

        const int getHealth(){
            return health;
        }

        const float getDamage(){
            return damage;
        }

        const int getLevel(){
            return level;
        }

        const int getXP(){
            return xp;
        }

        void setXP(int nxp){
            xp += nxp;
        }

        void lvlUp(){
            health += 5;
            damage += 0.1;
            level += 1;
            xp = 0;
        }

        int rollDamage(){
            srand(time(NULL));
            return rand() % 5 + 1 * damage;
        }
};

#endif