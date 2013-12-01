#include <string>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool leaveGame;
string board [10][15];
fstream level0("sequence.txt");
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
  string currentBlock;
  if (level == 0){
    if (level0 >> currentBlock) {
      if (currentBlock == "I"){
        activeBlock = new IBlock(level);
      } else if (currentBlock == "J"){
        activeBlock = new JBlock(level);
      } else if (currentBlock == "L"){
        activeBlock = new LBlock(level);
      } else if (currentBlock == "O"){
        activeBlock = new OBlock(level);
      } else if (currentBlock == "S"){
        activeBlock = new SBlock(level);
      } else if (currentBlock == "Z"){
        activeBlock = new ZBlock(level);
      }  else if (currentBlock == "T"){
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
  string command;
  string repetitions;
  int repetitionNumber;
  string commandArray[9];
  commandArray[0] = "left";
  commandArray[1] = "right";
  commandArray[2] = "down";
  commandArray[3] = "drop";
  commandArray[4] = "clockwise";
  commandArray[5] = "counterclockwise";
  commandArray[6] = "levelup";
  commandArray[7] = "leveldown";
  commandArray[8] = "restart";

  startGame();
  textdraw();
  while (cin >> input){
    repetitionNumber = 1;
    repetitions = "";
    command = "";

    if (isdigit(input[0])) {
      for (int i=0; i < input.length(); i++){
        if (isdigit(input[i])) {
          repetitions += input[i];
        } else {
          input = input.substr(i);
          break;
        }
      }
      repetitionNumber = stoi(repetitions);
    }

    for (int i = 0; i < 9; i++) {
      if (commandArray[i].find(input) == 0) {
        if (command == "") {
          command = commandArray[i];
        } else {
          command = "";
          break;
        }
      }
    }

    if (command == commandArray[0]) {
      for (int i=0; i < repetitionNumber; i++){
        activeBlock->left();
      }
    } else if (command == commandArray[1]) {
      for (int i=0; i < repetitionNumber; i++){
        activeBlock->right();
      }
    } else if (command == commandArray[2]) {
      for (int i=0; i < repetitionNumber; i++){
        activeBlock->down();
      }
    } else if (command == commandArray[3]) {
      for (int i=0; i < repetitionNumber; i++){
        activeBlock->drop();
        clearLines();
        newBlock();
      }
    } else if (command == commandArray[4]) {
      for (int i=0; i < repetitionNumber; i++){
        activeBlock->clockwise();
      }
    } else if (command == commandArray[5]) {
      for (int i=0; i < repetitionNumber; i++){
        activeBlock->counterclockwise();
      }
    } else if (command == commandArray[6]) {
      for (int i=0; i < repetitionNumber; i++){
        if (level < 3) {
          level++;
        }
      }
    } else if (command == commandArray[7]) {
      for (int i=0; i < repetitionNumber; i++){
        if (level > 0) {
          level--;
        }
      }
    } else if (command == commandArray[8]) {
      leaveGame = true;
    }

    if (leaveGame == true){
      startGame();
    }
    textdraw();
  }
  return 0;
}
