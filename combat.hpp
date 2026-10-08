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

        combatStart();
    }

    void combatGUI(){
        

    }

    combatStart(){
        bool combat = true;

        while (combat){
            std::string frame = "";
            frame += "\n\n\n\n";
            frame +="Player VS " +  mNAME + "\n";
            frame += "\n\n\n\n\n\n\n\n\n";
            frame += "a = Attack, i = Use Item\n";
            frame += "Your choice: ";
            std:: cout << frame;


            std::cin >> choice; 
        }
        return true;
    }



};
#endif