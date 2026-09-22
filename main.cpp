#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <random>
#include "perlin.hpp"

#define RESET   "\033[0m"       //Default
#define GREEN   "\033[32m"      //Green
#define YELLOW  "\033[33m"      //Yellow 
#define BLUE    "\033[36m"      //Blue
#define GREY    "\033[90m"      //Grey


using namespace std;

/*
int terrainGen(int last, int row, int coll,mt19937& gen){
    int random;
    if ( row <= 2 || row >= 27){
        return 247;
    }
    else if (row <= 3 || row >= 25){
        discrete_distribution<int> distribution({40,0,10,60}); // sea, ground, mountain, desert
        random = distribution(gen);
        if (random == 0){
            return 247;
        }
        else if (random == 1){
            return 240;
        }
        else if (random == 2){
            return 143;
        }
        else{
            return 242;
        }
    }
    else if (last == 247){
        discrete_distribution<int> distribution({60,20,9,1}); // sea, ground, mountain, desert
        random = distribution(gen);
        if (random == 0){
            return 247;
        }
        else if (random == 1){
            return 240;
        }
        else if (random == 2){
            return 143;
        }
        else{
            return 242;
        }
    }
    else {
        discrete_distribution<int> distribution({5,65,15,15});
        random = distribution(gen);
        if (random == 0){
            return 247;
        }
        else if (random == 1){
            return 240;
        }
        else if (random == 2){
            return 143;
        }
        else{
            return 242;
        }
    }
}
*/

void fillMatrix(vector<vector<int>>& matrix){

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
                int index = (coll * matrix.size() + row) * 4;

                float val = 0;

                float freq = 1;
                float amp = 1;

                for (int i = 0; i < 12; i++){
                    val += Noise::perlin(row *freq / 10, coll * freq / 10) * amp;

                    freq *= 2;
                    amp /= 2;
                }

                val *= 1.2;

                if (val > 1.0f){
                    val = 1.0f;
                }
                else if (val < -1.0f){
                    val = -1.0f;
                }
                int color = (int)(((val + 1.0f) * 0.5f) * 3);
                matrix[row][coll] = color;
            }
        }
    }

}

void printMatrix(vector<vector<int>>& matrix){
    for (int row = 0; row < matrix.size(); row++){
        for (int coll = 0; coll < matrix[row].size();coll++){
            int p = matrix[row][coll];
            if (p == 0){
                cout << BLUE << char(247) << RESET; //blue
            }
            else if (p == 1){
                cout << YELLOW << char(242) << RESET; // light yellow
            }
            else if (p == 2){
                cout << GREEN << char(240) << RESET; // light green
            }
            else if (p ==3){
                cout << GREY << char(143) << RESET; // Grey
            }
            else {
                cout << char(p); // Normal Text Color
            }
        }
        cout << endl;
    }
    //cout << "Finished Printing!" << endl;
}

int main(){

    SetConsoleOutputCP(437);
    int height = 29;
    int width = 120;
    vector<vector<int>> matrix(height,vector<int>(width,0));
    fillMatrix(matrix);
    //cout << matrix.size() << " " << matrix[0].size() ;
    printMatrix(matrix);

    cin.get();

    return 0;

}