#include <string>
#include <iostream>
#include <string>
using namespace std;

bool leaveGame = false;

string board [10][15];
void set(){
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 15; j++){
      board[i][j] = " ";
    }
  }
  // board[5][0] = "L";
}

#include "block.cc"

int score = 0;
int hiScore = score;
int level = 0;

void textdraw (){
  cout << "Level: " << level << endl;
  cout << "Score: " << score << endl;
  cout << "HiScore: " << hiScore << endl;
  cout << "----------" << endl;
    for (int i = 14; i >= 0; i--){
      for (int j = 0; j < 10; j++){
        cout << board[j][i];
      }
      cout << endl;
    }
  cout << "----------" << endl;
  cout << "Next: " << endl;
}

int main (){
  set();
  string input;
  IBlock *block1 = new IBlock();
  while (!leaveGame){
    textdraw();
    if (cin >> input){
      if (input == "left"){
      	block1->left();
      } else if (input == "right"){
        block1->right();
      } else if (input == "down"){
        block1->down();
      } else if (input == "clockwise"){
        block1->clockwise();
      } else if (input == "counterclockwise"){
        block1->counterclockwise();
      } else if (input == "drop"){
        block1->drop();
      } else if (input == "levelup") {
        if (level <= 3) { 
          level++;
        }
      } else if (input == "leveldown"){
        if (level >= 0) {
          level--;
        }
      } else if (input == "restart"){
        leaveGame = true;
      }
    }
  }
  return 0;
}