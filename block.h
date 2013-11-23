#ifndef __BLOCK_H__
#define __BLOCK_H__

struct Posn{
	int x;
	int y;
}


//corners[0] top left
//corners[1] bottom left
//corners[2] bottom right
class Block {
  Posn bottomright;
  Posn bottomleft;
  Posn * position[4];
  
  void clockwise(){
  	int temp = 0;
  	for (int i=0; i++; i < 4){
  	  position[i].x-=bottomright.x;
  	  position[i].y-=bottomright.y;
  	  temp=position[i].x;
  	  position[i].x = position[i].y;
  	  position[i].y = -temp;
    }
  }

 public:
  Block();
  ~Block();
  boolean collision();
  void 
  void drop();
  void down();
  void left();
  void right();
  void clockwise();
  void counterclockwise();
};

class IBlock : public Block {
  IBlock(){
  	bottomleft={0,11};
  	bottomright={3,11};
    this->position[0]={0,11;
    this->position[1]={1,11};
    this->position[2]={2,11};
    this->position[3]=[3,11];
  }
};

class JBlock : public Block {

};

class LBlock : public Block {

};

class OBlock : public Block {

};

class Sblock : public Block {

};

class ZBlock : public Block {

};

class Tblock : public Block {

};

#endif