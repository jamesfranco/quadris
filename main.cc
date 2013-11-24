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
  cout << "Next: " << endl << endl;
}

void clearLines(){
  bool lineCleared = true;
  for (int i = 0; i < 15; i++){
  	for (int j =  0; j < 10; j++){
      if (board[j][i] == " "){
        
      }
    } 
  }
}

int main (){
  set();
  string input;
  TBlock *block1 = new TBlock();
  while (!leaveGame){
    for (int i=0;i<4;i++){
      cout << "blocks x:" << block1->position[i].x << " y:" << block1->position[i].y << endl;
    }
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