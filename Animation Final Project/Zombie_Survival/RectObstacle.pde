

  class RectObstacle extends Obstacle {
    float len;
    float wid;
    float center_x;
    float center_y;
    int image = 0;
    
    RectObstacle(float x, float y, float l, float w, int i){
      super(x,y);
      len = l;
      wid = w;
      center_x = pos.x + len/2;
      center_y = pos.y + wid/2;
      image = i;
      
    }
    
  }
