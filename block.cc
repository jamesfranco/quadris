#ifndef __BLOCK_H__
#define __BLOCK_H__

struct Posn{
	int x;
	int y;
};

class Block {
 public:
  string blockType;
  Posn bottomright;
  Posn bottomleft;
  Posn position[4];
  Posn nextposition[4];

  void clockwise(){
  	int temp = 0;
  	for (int i=0; i < 4; i++){
  	  temp = position[i].x;
  	  nextposition[i].x = bottomleft.x + position[i].y - bottomright.y;
  	  nextposition[i].y = bottomleft.y - temp + bottomright.x;
    }
  }
  void updateCorners() {
    bottomleft={9,11};
    bottomright={0,11};
    for (int i=0; i < 4; i++){
      if (position[i].y < bottomleft.y) {
        bottomleft.y = position[i].y;
        bottomright.y = position[i].y;
      }
      if (position[i].x > bottomright.x) {
        bottomright.x = position[i].x;
      }
      if (position[i].x < bottomleft.x) {
        bottomleft.x = position[i].x;
      }
    }
  }
  void placeBlock() {
    for (int i=0; i < 4; i++){
      position[i] = nextposition[i];
      board[position[i].x][position[i].y] = blockType;
      cout << position[i].x << position[i].y << endl;
    }
  }

  bool collision() {
    for (int i=0; i < 4; i++){
      if (nextposition[i].x < 0 || nextposition[i].x > 14 || nextposition[i].y < 0) {
        return true;
      }
      if (board[nextposition[i].x][nextposition[i].y] != " ") {
        return true;
      }
    }
    return false;
  }

  void endMove() {
    if (!collision()) {
      placeBlock();
    }else {
      // lose();
    }
  }

  //Block();
  //~Block();
  void drop();
  void down();
  void left();
  void right();
  void counterclockwise();
};

class IBlock : public Block {
 public:
  IBlock(){
    this->blockType="I";        
    this->nextposition[0]={0,11};
    this->nextposition[1]={1,11};
    this->nextposition[2]={2,11};
    this->nextposition[3]={3,11};
    endMove();
  }
};

class JBlock : public Block {
 public:
  JBlock(){
    this->blockType="J";
    this->nextposition[0]={0,11};
    this->nextposition[1]={0,10};
    this->nextposition[2]={1,10};
    this->nextposition[3]={2,10};
    endMove();
  }
};

class LBlock : public Block {
 public:
  LBlock(){
    this->blockType="L"; 
    this->nextposition[0]={2,11};
    this->nextposition[1]={0,10};
    this->nextposition[2]={1,10};
    this->nextposition[3]={2,10};
    endMove();
  }
};

class OBlock : public Block {
 public:
  OBlock(){
    this->blockType="O"; 
    this->nextposition[0]={0,11};
    this->nextposition[1]={0,10};
    this->nextposition[2]={1,11};
    this->nextposition[3]={1,10};
    endMove();
  }
};

class SBlock : public Block {
 public:
  SBlock(){
    this->blockType="S"; 
    this->nextposition[0]={0,10};
    this->nextposition[1]={1,10};
    this->nextposition[2]={1,11};
    this->nextposition[3]={2,10};
    endMove();
  }
};

class ZBlock : public Block {
 public:
  ZBlock(){
    this->blockType="Z"; 
    this->nextposition[0]={0,11};
    this->nextposition[1]={1,11};
    this->nextposition[2]={1,10};
    this->nextposition[3]={2,10};
    endMove();
  }
};

class TBlock : public Block {
 public:
  TBlock(){
    this->blockType="T"; 
    this->nextposition[0]={0,11};
    this->nextposition[1]={1,11};
    this->nextposition[2]={2,11};
    this->nextposition[3]={1,10};
    endMove();
  }
};

#endif