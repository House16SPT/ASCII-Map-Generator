#ifndef COMBAT_HPP
#define COMBAT_HPP

#include <cstdlib>
#include "player.hpp"
#include "monster.hpp"
#include "string"

class Combat {
    private:
        int pHP;
        float pDMG;

        int mDMG;
        int mHP;
        std::string mNAME;

        int choice;
    public:

    Combat(Player player, Monster monster){
        pHP = player.getHealth();
        pDMG = player.getDamage();

        mDMG = monster.getDamage();
        mHP = monster.getHealth();
        mNAME = monster.getName();

        std::cin.
        start();
    }

    void combatGUI(){

        std::cout << "Player VS " << mNAME << "\n";

        std::cin >> choice; //need to clear cin buffer probably in print matrix to clear it every frame but maybe not will research.
    }

    start(){
        bool combat = true;

        while (combat){
            combatGUI();
        }
        return true;
    }



};
#endif