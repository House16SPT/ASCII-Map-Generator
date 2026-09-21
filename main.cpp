#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <random>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[36m"      /* Blue */
#define GREY    "\033[90m"


using namespace std;

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

void fillMatrix(vector<vector<int>>& matrix){

    int lastC = matrix[0].size()-1; // 39 
    int lastR = matrix.size()-1; // 19
    random_device rd;
    mt19937 gen(rd());



    for (int row = 0; row < matrix.size(); row++){
        for (int coll = 0; coll < matrix[row].size();coll++){
            if (row == 0 && coll == 0){
                matrix[row][coll] = 201; //╔
            }
            else if (row == 0 && coll == lastC){
                matrix[row][coll] = 187; //╗
            }
            else if (row == lastR && coll == lastC){
                matrix[row][coll] = 188; // ╝
            }
            else if (row == lastR && coll == 0){
                matrix[row][coll] = 200; // ╚
            }
            else if (row == 0 || row == lastR){
                matrix[row][coll] = 205; // ═
            }
            else if (coll == 0 || coll == lastC){
                matrix[row][coll] = 186; // ║
            }
            else{
                matrix[row][coll] = terrainGen(matrix[row][coll-1],row,coll,gen); // will be empty space for now
            }
        }
    }
    //cout << "Finished Filling!" << endl;

}

void printMatrix(vector<vector<int>>& matrix){
    for (int row = 0; row < matrix.size(); row++){
        for (int coll = 0; coll < matrix[row].size();coll++){
            int p = matrix[row][coll];
            if (p == 247){
                cout << BLUE << char(p) << RESET; //blue
            }
            else if (p == 242){
                cout << YELLOW << char(p) << RESET; // light yellow
            }
            else if (p == 240){
                cout << GREEN << char(p) << RESET; // light green
            }
            else if (p ==143){
                cout << GREY << char(p) << RESET; // Grey
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