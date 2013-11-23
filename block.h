#ifndef __BLOCK_H__
#define __BLOCK_H__

class Block {

 public:
  Block();
  ~Block();
  void drop();
  void left();
  void right();
  void clockwise();
  void counterclockwise();
};

class IBlock : public Block {

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
