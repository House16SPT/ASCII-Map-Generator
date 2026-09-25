#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <random>
#include <ranges>
#include "perlin.hpp"
#include "player.hpp"
#include "monster.hpp"



#define RESET   "\033[0m"       //Default
#define GREEN   "\033[32m"      //Green
#define YELLOW  "\033[33m"      //Yellow 
#define BLUE    "\033[34m"      //Blue
#define LBLUE    "\033[36m"      //Blue
#define RED    "\033[31m"      //Blue
#define GREY    "\033[90m"      //Grey

const int ENEMYCOUNT = 200;
const bool DEBUG = false;


using namespace std;

struct Position {
    int x;
    int y;
    int type;
};

vector<Monster> monsterCreation(int width, int height){
    vector<Monster> MonsterList;

    for (int m = 0; m < ENEMYCOUNT; m++){
        MonsterList.emplace_back(Monster());
    }

    return MonsterList;
}

void fillMatrix(vector<vector<int>>& matrix){

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> seed(0.0f, 100.0f);
    float seedx = seed(gen);
    float seedy = seed(gen); // create a random seed for both x and y to use in perlin call

    for (int row = 0; row < matrix.size(); row++){
        for (int coll = 0; coll < matrix[row].size(); coll++){
            if (row == 0 && coll == 0){
                matrix[row][coll] = 201; //╔
            }
            else if (row == 0 && coll == matrix[0].size()-1){
                matrix[row][coll] = 187; //╗
            }
            else if (row == matrix.size()-1 && coll == matrix[0].size()-1){
                matrix[row][coll] = 188; // ╝
            }
            else if (row == matrix.size()-1  && coll == 0){
                matrix[row][coll] = 200; // ╚
            }
            else if (row == 0 || row == matrix.size()-1 ){
                matrix[row][coll] = 205; // ═
            }
            else if (coll == 0 || coll == matrix[0].size()-1){
                matrix[row][coll] = 186; // ║
            }
            else{
                //see top comment in perlin.hpp for this else block

                //int index = (coll * matrix.size() + row) * 4;

                float val = 0;

                float freq = 1; // how stretched/spiky terrain looks. greater = scrambled lower = smoother/flatter
                float amp = 2; // amplitude of terrain greater = sharper elevation

                for (int i = 0; i < 3; i++){
                    val += Noise::perlin(row *freq / 10 + seedx, coll * freq / 10 + seedy) * amp;

                    freq *= 2.1;
                    amp /= 2;
                }

                val *= 1.1;

                if (val > 1.0f){
                    val = 1.0f;
                }
                else if (val < -1.0f){
                    val = -1.0f;
                }
                int fVal = (int)(((val + 1.0f) * 0.5f) * 5); // the 5 represents changes value to be a range of 0-5 
                //so in this case i can have 5 different ascii characters. for proper visualization a large number
                //would mean smoother or higher detailed growth.

                matrix[row][coll] = fVal; // return our final value.
            }
        }
    }

}


void printMatrix(vector<vector<int>>& matrix, vector<Monster>& MonsterList, int height, int width, Player& player){
    const int rowstart = (height / 2) - 14;
    const int rowend = (height/2) + 14;
    const int collstart = (width/2) - 60;
    const int collend = (width/2) + 60;

    bool drawn = false;

    string frame;
    frame.reserve((rowend - rowstart) * (collend - collstart)); 
    for (int row = (height/2) - 14; row < (height/2)+14; row++){
        for (int coll = (width/2) - 60; coll < (width/2) + 60;coll++){
            drawn = false;
            
            if ((row == player.y) && (coll == player.x)){
                frame += char(233);
                drawn = true;
            }

            for (const auto& position: MonsterList){
                if ((row == position.y) && (coll == position.x)){
                    frame += RED; frame += char(233); frame += RESET;
                    drawn = true;
                    break;
                }
            }

            if (!drawn){
                int p = matrix[row][coll];
                if (p == 0){                //prime switch statement material will come back
                    frame+= BLUE; frame += char(247); frame += RESET; //blue
                }
                else if (p == 1){
                    frame+= LBLUE; frame += char(247); frame += RESET; //blue
                }
                else if (p == 2){
                    frame+= YELLOW; frame += char(242); frame += RESET; // light yellow
                }
                else if (p == 3){
                    frame += GREEN; frame += char(240); frame += RESET; // light green
                }
                else if (p ==4){
                    frame += GREY; frame += '^'; frame += RESET; // Grey
                }
                else if (p == 5){
                    frame += '^'; // white
                }
                else {
                    frame+= char(p); // Normal Text Color
                }
            }
        }
        frame += "\r\n";
    }
    cout << frame;
    cout << "Level: " << player.getLevel() << ", Health: " << player.getHealth()
        << ", Damage Multiplier: " << player.getDamage() << ", XP: " << player.getXP() << "/100, WASD = Movement, Q = Quit";
    cout.flush();
}

bool keycheck(bool keydown){

    for (const auto i : views::iota(0,256)){
        if (GetAsyncKeyState(i) & 0x8000){
            return true;
        }
    }
    return false; cout << "false";
}

void update(vector<vector<int>>& matrix,vector<Monster>& MonsterList, int height, int width, Player& player){
    
    bool keyisdown = false;

    while (1){
        Sleep(10);
        if (!keyisdown){
            if(GetAsyncKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {
                exit(0);
            }

            if(GetAsyncKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {
                if (!(width/2 - 60 == 0)){
                    keyisdown = true;
                    system("cls");
                    width -= 2;
                    player.x -=1;
                    printMatrix(matrix, MonsterList, height,width, player);
                }
            }
            else if (GetAsyncKeyState('D') & 0x8000){
                if (!(width/2 + 60 == 1200)){
                    keyisdown = true;
                    system("cls");
                    width += 2;
                    player.x +=1;
                    printMatrix(matrix,MonsterList, height,width, player);
                }
            }
            else if (GetAsyncKeyState('W') & 0x8000){
                if (!(height/2 - 14 == 0)){
                    keyisdown = true;
                    system("cls");
                    height -= 2;
                    player.y -=1;
                    printMatrix(matrix,MonsterList,height,width, player);

                    //player.setXP(10);
                }
            }
            else if (GetAsyncKeyState('S') & 0x8000){
                if (!(height/2 + 14 == 280)){
                    keyisdown = true;
                    system("cls");
                    height += 2;
                    player.y +=1;
                    printMatrix(matrix,MonsterList,height,width, player);
                }
            }
        }
        if (keyisdown == true){
            keyisdown = keycheck(keyisdown);
        }

        if (player.getXP() >= 100){
            player.lvlUp();
        }
    }
}

int main(){

    SetConsoleOutputCP(437);

    
    int height = 280; // 29 window viewport height
    int width = 1200; // 120 window viewport width
    vector<vector<int>> matrix(height,vector<int>(width,0));
    vector<Monster> MonsterList = monsterCreation(width, height);
    fillMatrix(matrix);
    Player player = Player(width,height);


    if (DEBUG == true){
        for (int m = 0; m < MonsterList.size(); m++){
            cout << "(" << MonsterList[m].x << ")," << "(" << MonsterList[m].y << ")"; 
        }
        cout << "Player = (" << player.x << ")," << "(" << player.y << ")"; 
    }

    else{
        printMatrix(matrix,MonsterList,height,width,player);
    }


    update(matrix,MonsterList,height,width,player);

    return 0;

}

