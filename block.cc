#ifndef __BLOCK_H__
#define __BLOCK_H__

struct Posn{
	int x;
	int y;  
};

//to compare two posns; ex: if (posn1 == posn2){...}
bool operator==(const Posn& lhs, const Posn& rhs) {
    if (lhs.x == rhs.x && lhs.y == rhs.y) return true;
  else return false;
}

//to compare two posns; ex: if (posn1 != posn2){...}
bool operator!=(const Posn& lhs, const Posn& rhs) {
  if (lhs.x != rhs.x || lhs.y != rhs.y) return true;
  else return false;
}

class Block {
 public:
  int level;
  string blockType;
  Posn topLeft;
  Posn bottomRight;
  Posn bottomLeft;
  Posn position[4];
  Posn nextposition[4];


  void updateCorners() {
    bottomRight = {0,12};
    bottomLeft = {10,12};
    topLeft = {10,0};
    for (int i=0; i < 4; i++) {
      if (position[i].y < bottomLeft.y) {
        bottomLeft.y = position[i].y;
        bottomRight.y = position[i].y;
      }
      if (position[i].y > topLeft.y) {
        topLeft.y = position[i].y;
      } 
      if (position[i].x > bottomRight.x) {
        bottomRight.x = position[i].x;
      }
      if (position[i].x < bottomLeft.x) {
        bottomLeft.x = position[i].x;
        topLeft.x = position[i].x;
      }
    }
  }
  void placeBlock() {
    for (int i=0; i < 4; i++){
      board[position[i].x][position[i].y] = " ";
    }
    for (int i=0; i < 4; i++){
      position[i] = nextposition[i];
      board[position[i].x][position[i].y] = blockType;
    }
    updateCorners();
  }

  void resetBlock() {
    for (int i=0; i < 4; i++){
      nextposition[i]=position[i];
    }
  }

  bool collision() {
    for (int i=0; i < 4; i++){ 
      //checks if nextposition goes out of bounds
      if (nextposition[i].x < 0 || nextposition[i].x > 9 || nextposition[i].y < 0) {
        return true;
      }

      //checks if nextposition is occupied by a block
      if (board[nextposition[i].x][nextposition[i].y] != " " && nextposition[i] != position[0] && nextposition[i] != position[1] && nextposition[i] != position[2] && nextposition[i] != position[3]) {
        return true;
      }
    }
    return false;
  }

  void spawn() {
    if (!collision()) {
      for (int i=0; i < 4; i++){
        position[i] = nextposition[i];
        board[position[i].x][position[i].y] = blockType;
      }
      updateCorners();
    } else {
      leaveGame = true;
    }
  }

  //Block();
  //~Block();
  void drop() {
    while (!collision()) {
      for (int i=0; i < 4; i++) {
        nextposition[i].y -= 1;
      }
    }
    for (int i=0; i < 4; i++){
        nextposition[i].y += 1;
    }
    placeBlock();
  }

  void down() {
    for (int i=0; i < 4; i++){
      nextposition[i].y -= 1;
    }
    if (!collision()) {
      placeBlock();
    } else {
      resetBlock();
    }
  }

  void left() {
    for (int i=0; i < 4; i++){
      nextposition[i].x -= 1;
    }
    if (!collision()) {
      placeBlock();
    } else {
      resetBlock();
    }
  }

  void right() {
    for (int i=0; i < 4; i++){
      nextposition[i].x += 1;
    }
    if (!collision()) {
      placeBlock();
    } else {
      resetBlock();
    }
  }

  void clockwise(){
    for (int i=0; i < 4; i++){
      nextposition[i].x = bottomLeft.x + position[i].y - bottomRight.y;
      nextposition[i].y = bottomLeft.y - position[i].x + bottomRight.x;
    }
    if (!collision()) {
      placeBlock();
    } else {
      resetBlock();
    }
  }

  void counterclockwise() {
    for (int i=0; i < 4; i++){
      nextposition[i].x = -position[i].y + bottomLeft.x + topLeft.y;
      nextposition[i].y =  position[i].x + bottomLeft.y - topLeft.x;
    }
    if (!collision()) {
      placeBlock();
    } else {
      resetBlock();
    }
  }
};



class IBlock : public Block {
 public:
  IBlock(int level){
    this->level = level;
    this->blockType="I";
    this->nextposition[0]={0,11};
    this->nextposition[1]={1,11};
    this->nextposition[2]={2,11};
    this->nextposition[3]={3,11};
    spawn();
  }
};

class JBlock : public Block {
 public:
  JBlock(int level){
    this->level = level;
    this->blockType="J";
    this->nextposition[0]={0,11};
    this->nextposition[1]={0,10};
    this->nextposition[2]={1,10};
    this->nextposition[3]={2,10};
    spawn();
  }
};

class LBlock : public Block {
 public:
  LBlock(int level){
    this->level = level;
    this->blockType="L";
    this->nextposition[0]={2,11};
    this->nextposition[1]={0,10};
    this->nextposition[2]={1,10};
    this->nextposition[3]={2,10};
    spawn();
  }
};

class OBlock : public Block {
 public:
  OBlock(int level){
    this->level = level;
    this->blockType="O";
    this->nextposition[0]={0,11};
    this->nextposition[1]={0,10};
    this->nextposition[2]={1,11};
    this->nextposition[3]={1,10};
    spawn();
  }
  void clockwise(){}
  void counterclockwise(){}
};

class SBlock : public Block {
 public:
  SBlock(int level){
    this->level = level;
    this->blockType="S";
    this->nextposition[0]={0,10};
    this->nextposition[1]={1,10};
    this->nextposition[2]={1,11};
    this->nextposition[3]={2,11};
    spawn();
  }
};

class ZBlock : public Block {
 public:
  ZBlock(int level){
    this->level = level;
    this->blockType="Z";
    this->nextposition[0]={0,11};
    this->nextposition[1]={1,11};
    this->nextposition[2]={1,10};
    this->nextposition[3]={2,10};
    spawn();
  }
};

class TBlock : public Block {
 public:
  TBlock(int level){
    this->level = level;
    this->blockType="T";
    this->nextposition[0]={0,11};
    this->nextposition[1]={1,11};
    this->nextposition[2]={2,11};
    this->nextposition[3]={1,10};
    spawn();      
  }
};

#endif