
class Zombie{
  Position pos;
  float velY, velX;
  float align;
  Zombie(float x, float y){
    pos = new Position(x,y);
    align = 0;
  }
  
  Zombie(float x, float y, float z){
    pos = new Position(x,y,z);
    align = 0;
  }
  
}
