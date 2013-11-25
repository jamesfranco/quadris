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
  bool lineCleared;
  for (int y = 0; y < 15; y++){
    lineCleared = true;
  	for (int x =  0; x < 10 && lineCleared == true; x++){
      if (board[x][y] == " "){
        lineCleared = false;
      }
    }
    if (lineCleared == true){
      for (int i = y; i < 14; i++){  //start at 14 so you dont access row 15
        for (int j = 0; j < 10; j++){
          board[j][i]=board[j][i+1];
        }
      }
      score+=100;
      for (int i=0;i<10; i++){
        board[i][14] = " ";
      }
      y--;
    }
  }
}

Block newBlock() {

  return SBlock();
}

int main (){
  set();
  string input;
  Block *block1 = new TBlock();
  while (!leaveGame){
    textdraw();
    if (cin >> input){
      if (input == "left" || input == "l"){
      	block1->left();
      } else if (input == "right" || input == "r"){
        block1->right();
      } else if (input == "down"|| input == "d"){
        block1->down();
      } else if (input == "clockwise" || input == "c"){
        block1->clockwise();
      } else if (input == "counterclockwise" || input == "cc"){
        block1->counterclockwise();
      } else if (input == "drop" || input == "dr"){
        block1->drop();
        //delete [] block1;
        clearLines();
        block1 = new TBlock();
      } else if (input == "levelup") {
        if (level < 3) { 
          level++;
        }
      } else if (input == "leveldown"){
        if (level > 0) {
          level--;
        }
      } else if (input == "restart"){
        leaveGame = true;
      }
    }
  }
  return 0;
}