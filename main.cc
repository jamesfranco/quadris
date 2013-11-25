#include <string>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool leaveGame;
string board [10][15];
fstream level0("sequence.txt");
string nextBlock;
int score;
int hiScore = 0;
int level = 0;

#include "block.cc"

Block *activeBlock;

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
  int numCleared = 0;
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
      numCleared++;
      for (int i=0;i<10; i++){
        board[i][14] = " ";
      }
      y--;
    }
  }
  score += (level+numCleared)*(level+numCleared);
  if (score > hiScore){
    hiScore=score;
  }
}

//sets the next block to be placed
void newBlock() {
  if (level == 0){
    if (level0 >> nextBlock) {
      if (nextBlock == "I"){
        activeBlock = new IBlock(level);  
      } else if (nextBlock == "J"){
        activeBlock = new JBlock(level);
      } else if (nextBlock == "L"){
        activeBlock = new LBlock(level);
      } else if (nextBlock == "O"){
        activeBlock = new OBlock(level);
      } else if (nextBlock == "S"){
        activeBlock = new SBlock(level);
      } else if (nextBlock == "Z"){
        activeBlock = new ZBlock(level);
      }  else if (nextBlock == "T"){
        activeBlock = new TBlock(level);
      } 
    } else if (level0.fail()){
      level0.clear();
      level0.close();
      level0.open("sequence.txt");
      }
  } else {
    activeBlock = new TBlock(level);
  }
}

//function to start new games
void startGame(){
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 15; j++){
      board[i][j] = " ";
    }
  }
  score = 0;
  leaveGame = false;
  newBlock();
}

int main (){
  string input;
  startGame();
  textdraw();
  while (cin >> input){
    if (input == "left" || input == "l"){
    	activeBlock->left();
    } else if (input == "right" || input == "r"){
      activeBlock->right();
    } else if (input == "down"|| input == "d"){
      activeBlock->down();
    } else if (input == "clockwise" || input == "c"){
      activeBlock->clockwise();
    } else if (input == "counterclockwise" || input == "cc"){
      activeBlock->counterclockwise();
    } else if (input == "drop" || input == "dr"){
      activeBlock->drop();
      clearLines();
      newBlock();
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
    if (leaveGame == true){
      startGame();
    }
    textdraw();
  }
  return 0;
}