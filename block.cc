#ifndef __BLOCK_H__
#define __BLOCK_H__

struct Posn{
	int x;
	int y;
};

class Block {
 public:
  Posn bottomright;
  Posn bottomleft;
  Posn position[4];
  Posn nextposition[4];

  void clockwise(){
  	int temp = 0;
  	for (int i=0; i++; i < 4){
  	  temp = position[i].x;
  	  nextposition[i].x = bottomleft.x + position[i].y - bottomright.y;
  	  nextposition[i].y = bottomleft.y - temp + bottomright.x;
    }
  }
  void updateCorners() {
    bottomleft={9,11};
    bottomright={0,11};
    for (int i=0; i++; i < 4){
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
    for (int i=0; i++; i < 4){
      position[i] = nextposition[i];
    }
  }

  bool collision() {
    for (int i=0; i++; i < 4){
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
    if (collision()) {
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
    this->nextposition[0]={0,11};
    this->nextposition[1]={1,11};
    this->nextposition[2]={2,11};
    this->nextposition[3]={1,10};
    endMove();
  }
};

#endif
