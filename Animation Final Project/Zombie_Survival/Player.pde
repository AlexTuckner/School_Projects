
class Player{
  Position pos;
  float radius;
  float velY, velX;
  float align;
  
  Player(float x, float y, float r){
    pos = new Position(x,y);
    radius = r;
    align = 0;
  }
  
  Player(float x, float y, float z, float r){
    pos = new Position(x,y,z);
    radius = r;
    align = 0;
  }
  
}
