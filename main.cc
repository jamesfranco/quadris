#include <string>
#include <iostream>
#include <fstream>
#include "window.h"
#include <sstream>
#include <cmath>
using namespace std;

bool leaveGame;
string board [10][15];
fstream level0("sequence.txt");
string nextBlock;
Xwindow window;

int score;
int hiScore = 0;
int level = 0;

#include "block.cc"

Block *activeBlock;
PRNG prng;

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
  if (nextBlock == "I"){
    cout << endl << "IIII" << endl;
  } else if (nextBlock == "J"){
    cout << "J" << endl << "JJJ" << endl;
  } else if (nextBlock == "L"){
    cout << "  L" << endl << "LLL" << endl;
  } else if (nextBlock == "O"){
    cout << "OO" << endl << "OO" << endl;
  } else if (nextBlock == "S"){
    cout << " SS" << endl << "SS" << endl;
  } else if (nextBlock == "Z"){
    cout << "ZZ" << endl << " ZZ" << endl;
  } else if (nextBlock == "T"){
    cout << "TTT" << endl << " T" << endl;
  }
}

void graphicsDraw(){
  window.fillRectangle(0,0,500,850,Xwindow::White);
  window.drawString(0, 10, "Level:  " + to_string(level), Xwindow::Black);
  window.drawString(0, 25, "Score:  " + to_string(score), Xwindow::Black);
  window.drawString(0, 40, "HiScore:  " + to_string(hiScore), Xwindow::Black);
  window.drawString(250, 20, "Next:", Xwindow::Black);

  // draw nextBlock
  if (nextBlock == "I"){
    window.fillRectangle(300,50,200,50, Xwindow::Cyan);
  } else if (nextBlock == "J"){
    window.fillRectangle(300,0,50,50, Xwindow::Blue);
    window.fillRectangle(300,50,150,50, Xwindow::Blue);
  } else if (nextBlock == "L"){
    window.fillRectangle(300,50,150,50, Xwindow::Orange);
    window.fillRectangle(400,0,50,50, Xwindow::Orange);
  } else if (nextBlock == "O"){
    window.fillRectangle(300,0,100,100,Xwindow::Yellow);
  } else if (nextBlock == "S"){
    window.fillRectangle(350,0,100,50,Xwindow::Green);
    window.fillRectangle(300,50,100,50,Xwindow::Green);
  } else if (nextBlock == "Z"){
    window.fillRectangle(300,0,100,50,Xwindow::Red);
    window.fillRectangle(350,50,100,50,Xwindow::Red);
  } else if (nextBlock == "T"){
    window.fillRectangle(350,50,50,50,Xwindow::Magenta);
    window.fillRectangle(300,0,150,50,Xwindow::Magenta);
  }
  for (int i = 14; i >= 0; i--){
    for (int j = 0; j < 10; j++){
      if (board[j][i] == "I") {
        window.fillRectangle(j*50, abs(850-((i+1)*50 + 100)) + 100, 50,50,Xwindow::Cyan);
      } else if (board[j][i] == "J") {
        window.fillRectangle(j*50, abs(850-((i+1)*50 + 100)) + 100, 50,50,Xwindow::Blue);
      } else if (board[j][i] == "L") {
        window.fillRectangle(j*50, abs(850-((i+1)*50 + 100)) + 100, 50,50,Xwindow::Orange);
      } else if(board[j][i] == "O") {
        window.fillRectangle(j*50, abs(850-((i+1)*50 + 100)) + 100, 50,50,Xwindow::Yellow);
      } else if(board[j][i] == "S") {
        window.fillRectangle(j*50, abs(850-((i+1)*50 + 100)) + 100, 50,50,Xwindow::Green);
      } else if(board[j][i] == "Z") {
        window.fillRectangle(j*50, abs(850-((i+1)*50 + 100)) + 100, 50,50,Xwindow::Red);
      } else if(board[j][i] == "T") {
        window.fillRectangle(j*50, abs(850-((i+1)*50 + 100)) + 100, 50,50,Xwindow::Magenta);
      }
    }
  }
  window.fillRectangle(300,0,1,100,Xwindow::Red);    //draw next box
  window.fillRectangle(0,100,850,1,Xwindow::Red);    //draw seperating line
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
  if (numCleared > 0){
    score += (level+numCleared)*(level+numCleared);
  }
  if (score > hiScore){
    hiScore=score;
  }
}

//sets the next block to be placed
void newBlock() {
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
  if (level == 0) {
    level0 >> nextBlock;
    if (level0.fail()) {
      level0.close();
      level0.open("sequence.txt");
      level0 >> nextBlock;
    }
  } else if (level == 1) {
    int i = prng(1,12);
    if (i == 1) nextBlock = "S";
    else if (i == 2) nextBlock = "Z";
    else if (i == 3 | i == 4) nextBlock = "I";
    else if (i == 5 || i == 6) nextBlock = "J";
    else if (i == 7 || i == 8) nextBlock = "L";
    else if (i == 9 || i == 10) nextBlock = "O";
    else if (i == 11 || i == 12) nextBlock = "T";
  } else if (level == 2) {
    int i = prng(1,7);
    if (i == 1) nextBlock = "I";
    else if (i == 2) nextBlock = "J";
    else if (i == 3) nextBlock = "L";
    else if (i == 4) nextBlock = "O";
    else if (i == 5) nextBlock = "T";
    else if (i == 6) nextBlock = "S";
    else if (i == 7) nextBlock = "Z";
  } else if (level == 3) {
    int i = prng(1,9);
    if (i == 1) nextBlock = "I";
    else if (i == 2) nextBlock = "J";
    else if (i == 3) nextBlock = "L";
    else if (i == 4) nextBlock = "O";
    else if (i == 5) nextBlock = "T";
    else if (i == 6 || i == 7) nextBlock = "S";
    else if (i == 8 || i == 9) nextBlock = "Z";
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
  level0 >> nextBlock;
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
  graphicsDraw();
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
    graphicsDraw();
  }
  return 0;
}
