#include <string>
#include <iostream>
#include <string>
#include "block.cc"
using namespace std;


string board [10][15];
void set(){
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 15; j++){
      board[i][j] = " ";
    }
  }
  // board[5][0] = "L";
}

int score = 0;
int hiScore = score;
int level = 0;

void textdraw (){
  cout << "Level: " << level << endl;
  cout << "Score: " << score << endl;
  cout << "HiScore: " << hiScore << endl;
  cout << "----------" << endl;
    for (int i = 14; i >= 0; i--){
      for (int j = 9; j >= 0; j--){
        cout << board[j][i];
      }
      cout << endl;
    }
  cout << "----------" << endl;
  cout << "Next: " << endl;
}

int main (){
  set();
  IBlock block1 = Iblock();
  textdraw();
  return 0;
}
