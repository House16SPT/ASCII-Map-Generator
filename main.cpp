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

                int index = (coll * matrix.size() + row) * 4;

                float val = 0;

                float freq = 1;
                float amp = 3; // amplitude of 

                for (int i = 0; i < 12; i++){
                    val += Noise::perlin(row *freq / 10 + seedx, coll * freq / 10 + seedy) * amp;

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