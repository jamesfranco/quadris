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
  string blockType;
  Posn bottomright;
  Posn bottomleft;
  Posn position[4];
  Posn nextposition[4];


  void updateCorners() {
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
      board[position[i].x][position[i].y] = " ";
    }
    for (int i=0; i < 4; i++){
      position[i] = nextposition[i];
      board[position[i].x][position[i].y] = blockType;
      updateCorners();
    }
  }

  void resetBlock(){
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
      placeBlock();
    } else {
      leaveGame = true;
    }
  }

  //Block();
  //~Block();
  void drop() {
    while (!collision()) {
      for (int i=0; i < 4; i++){
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

    cout << "DOWN COLLISION: (1 is true, 0 false): " << collision() << endl;
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

    cout << "LEFT COLLISION: (1 is true, 0 false): " << collision() << endl;
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
    cout << "RIGHT COLLISION: (1 is true, 0 false): " << collision() << endl;
    if (!collision()) {
      placeBlock();
    } else {
      resetBlock();
    }
  }

  void clockwise(){
    int temp;
    for (int i=0; i < 4; i++){
      temp = position[i].x;
      nextposition[i].x = bottomleft.x + position[i].y - bottomright.y;
      nextposition[i].y = bottomleft.y - temp + bottomright.x;
    }
    cout << "CLOCKWISE COLLISION: (1 is true, 0 false): " << collision() << endl;
    if (!collision()) {
      placeBlock();
    } else {
      resetBlock();
    }
  }

  void counterclockwise() {
    int temp;
    for (int i=0; i < 4; i++){
      temp = position[i].x;
      nextposition[i].x = bottomleft.x + position[i].y - bottomright.y;
      nextposition[i].y = bottomleft.y - temp + bottomright.x;
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
  IBlock(){
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
  JBlock(){
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
  LBlock(){
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
  OBlock(){
    this->blockType="O";
    this->nextposition[0]={0,11};
    this->nextposition[1]={0,10};
    this->nextposition[2]={1,11};
    this->nextposition[3]={1,10};
    spawn();
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
    spawn();
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
    spawn();
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
    spawn();      
  }
};

#endif