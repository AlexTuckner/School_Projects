import peasy.*;
import peasy.org.apache.commons.math.*;
import peasy.org.apache.commons.math.geometry.*;
import processing.sound.*;
SoundFile file, file2;
PImage food1_image, food2_image, food3_image, food4_image;
PImage ground_image;
PImage[] zombieWalk = new PImage[8];
PImage[] personWalk = new PImage[5];
PImage tree_image;
PImage house1_image, house2_image, house3_image;


// My Cloth
PeasyCam camera;
float windowLenX = 1280;
float windowLenY = 720;
float borderLenX = 32;
float borderLenY = 18;
float gameBorderLeft = borderLenX;
float gameBorderRight = windowLenX-borderLenX;
float gameBorderTop = borderLenY;
float gameBorderBottom = windowLenY-borderLenY;
float gameBorderLength = windowLenX-2*borderLenX;
float gameBorderWidth = windowLenY-2*borderLenY;
Player p;
ArrayList<Obstacle> obstacles = new ArrayList<Obstacle>();
ArrayList<Zombie> zombies = new ArrayList<Zombie>();

FloatList ZombieX = new FloatList();
FloatList ZombieY = new FloatList();

PFont font;
int score = 0;
float oldpos_x = 0;
float oldpos_y = 0;
float speed = 25;
int time = 0;
int hunger = 105;
int food = 0;
int zombieNum = 5;
boolean gameOver = false;
int obstacleNum = 6;
int playerRadius = 10;
int zombieSpeed = 3;

float imagex, imagey, imagelen, imagewid;
boolean paused = true;

void setup(){
  size(1280, 720, P3D);
  surface.setTitle("Zombie Survival");
  p = new Player(random(gameBorderLength) + borderLenX, random(gameBorderWidth) + borderLenY, playerRadius);
  generateObstacles();
  font = createFont("Arial BOLD",16,true);
  food1_image = loadImage("Cookie.png");
  food2_image = loadImage("Apple.png");
  food3_image = loadImage("Carrot.png");
  food4_image = loadImage("Meat.png");
  ground_image = loadImage("Ground Texture.jpg");
  tree_image = loadImage("Tree1.png");
  house1_image = loadImage("House1.jpg");
  house2_image = loadImage("House2.jpg");
  house3_image = loadImage("House3.jpg");
  for(int i = 0; i < zombieNum; i++){
    generateZombie();
  }
  
  zombieWalk[0] = loadImage("ZombieWalk0.png");
  zombieWalk[1] = loadImage("ZombieWalk1.png");
  zombieWalk[2] = loadImage("ZombieWalk2.png");
  zombieWalk[3] = loadImage("ZombieWalk3.png");
  zombieWalk[4] = loadImage("ZombieWalk4.png");
  zombieWalk[5] = loadImage("ZombieWalk5.png");
  zombieWalk[6] = loadImage("ZombieWalk6.png");
  zombieWalk[7] = loadImage("ZombieWalk7.png");
  
  personWalk[0] = loadImage("PersonWalk0.png");
  personWalk[1] = loadImage("PersonWalk1.png");
  personWalk[2] = loadImage("PersonWalk2.png");
  personWalk[3] = loadImage("PersonWalk3.png");
  personWalk[4] = loadImage("PersonWalk4.png");
  
  file = new SoundFile(this, "owen_wilson_wow.mp3");
  file2 = new SoundFile(this, "EatingChips.wav");
}

void draw(){
  background(100, 100, 100);
  //drawArena();
  image(ground_image, gameBorderLeft, gameBorderTop, ground_image.width/1.03, ground_image.height/1.33);
  if (!gameOver) {
    update(.15);
    displayScore();
    displayHunger();
  } else{
    displayEndMessage();
  }
}

void update(float dt){
  computePhysics(dt);
  checkOutOfBounds();
  if (food == 0) {
    spawnFood();
    food += 1;
    generateZombie();
    //zombieNum++;
  }
  checkObstacleCollision();

  applyHunger();
  drawPlayer();
  drawObstacles();
  drawZombies();
}

boolean checkforOverlap(Zombie z) {
    //Zombie doesn't spawn too close to Player
    if (dist(z.pos.x, z.pos.y, p.pos.x, p.pos.y) < (p.radius + 150)){
     return true; 
    }
    
    for (int i = 0; i < obstacles.size(); i++){
      //Zombie and Circle overlap
      if(obstacles.get(i) instanceof CircleObstacle){
       CircleObstacle c = (CircleObstacle) obstacles.get(i);
       if (dist(z.pos.x, z.pos.y, c.pos.x, c.pos.y) < (c.radius + 10)){
         return true;
       }         
      }//End of Zombie vs Circle
      else{ //Circle vs Rectangle
        RectObstacle r = (RectObstacle) obstacles.get(i);
        if (abs((z.pos.x) - r.center_x) < r.len/2 + 10 &&
            abs((z.pos.y) - r.center_y) < r.wid/2 + 10){
              return true;
            }
      }//else end
    }//for loop
  
  return false;
}

boolean checkforOverlap(Obstacle obstacle){
  //If current obstacle is a circle
  
  if(obstacle instanceof CircleObstacle){
    CircleObstacle o = (CircleObstacle) obstacle;
    if (dist(o.pos.x, o.pos.y, p.pos.x, p.pos.y) < (p.radius + o.radius)){
     return true; 
    }
    
    for (int i = 0; i < obstacles.size(); i++){
      //Circle and Circle overlap
      if(obstacles.get(i) instanceof CircleObstacle){
       CircleObstacle c = (CircleObstacle) obstacles.get(i);
       if (dist(o.pos.x, o.pos.y, c.pos.x, c.pos.y) < (c.radius + o.radius)){
         return true;
       }         
      }//End of Circle vs Circle
    }//for loop end
  }
  //If current obstacle is a rectangle
  else{
    RectObstacle o = (RectObstacle) obstacle;
    if (abs((p.pos.x) - o.center_x) < o.len/2 + p.radius &&
        abs((p.pos.y) - o.center_y) < o.wid/2 + p.radius){
          return true;
        }
    
    for (int i = 0; i < obstacles.size(); i++){
      //Rectangle vs Rectangle
      if (obstacles.get(i) instanceof RectObstacle){
       RectObstacle r = (RectObstacle) obstacles.get(i);
       if (dist(o.center_x, o.center_y, r.center_x, r.center_y) < o.len/2 + r.len/2 ||
           dist(o.center_x, o.center_y, r.center_x, r.center_y) < o.wid/2 + r.wid/2){
            return true;
           }
      }
      else{ //Circle vs Rectangle
        CircleObstacle c = (CircleObstacle) obstacles.get(i);
        if (abs((c.pos.x) - o.center_x) < o.len/2 + c.radius &&
            abs((c.pos.y) - o.center_y) < o.wid/2 + c.radius){
              return true;
            }
      }//else end
    }//for loop
  } 
  return false;
}

void generateObstacles() {
  float tempRadius;
  float tempXLoc;
  float tempYLoc;
  for(int i = 0; i < 3; i++){
    tempRadius = random(50) + 50;
    tempXLoc = random(gameBorderLength) + borderLenX;
    tempYLoc = random(gameBorderWidth) + borderLenY;
    if (tempXLoc - tempRadius < 32 || tempXLoc + tempRadius > 1216 
        || tempYLoc - tempRadius < 18 ||tempYLoc + tempRadius > 684) {
          i = i - 1;
        }
    else{
      println("x: " + tempXLoc + " y: " + tempYLoc + " radius: " + tempRadius);
      CircleObstacle o = new CircleObstacle(tempXLoc, tempYLoc, tempRadius);
      if (checkforOverlap(o) == false){
        obstacles.add(o);
      }
      else{
        i = i - 1;
        print("Obstacle Overlap. Generating new Obstacle\n");
      }
    }
  }
  
  float tempLen;
  float tempWid;
  int whichImage;
  for(int i = 0; i < 3; i++){
    whichImage = (int) random(3) + 1;
    if (whichImage == 1){
    tempLen = 180;
    tempWid = 180;
    } else if (whichImage == 2) {
    tempLen = 220;
    tempWid = 145;
    } else {
    tempLen = 250;
    tempWid = 196;
    }
    tempXLoc = random(gameBorderLength) + borderLenX;
    tempYLoc = random(gameBorderWidth) + borderLenY;
    if (tempXLoc + tempLen > 1216 ||tempYLoc + tempWid > 684) {
      i = i - 1;
    }
    else{
      println("x: " + tempXLoc + " y: " + tempYLoc + " len: " + tempLen + " wid: " + tempWid);
      RectObstacle o = new RectObstacle(tempXLoc, tempYLoc, tempLen, tempWid, whichImage);
      if (checkforOverlap(o) == false){
              obstacles.add(o);
      }
      else{
        i = i - 1;
        print("Obstacle Overlap. Generating new Obstacle\n");
      }
    }
  }
}

void checkOutOfBounds(){
  if(p.pos.x - p.radius < gameBorderLeft){
    p.pos.x = gameBorderLeft + p.radius;
  }
  
  if(p.pos.y - p.radius < gameBorderTop){
    p.pos.y = gameBorderTop + p.radius;
  }
  
  if(p.pos.x + p.radius > gameBorderRight){
    p.pos.x = gameBorderRight - p.radius;
  }
  if(p.pos.y + p.radius > gameBorderBottom){
    p.pos.y = gameBorderBottom - p.radius;
  }
}

void checkObstacleCollision() { 
  //Check obstacle collision with player
 for (int i = 0; i < obstacles.size(); i++){
   //Player gets food
   if (i == obstacles.size() -1){
     RectObstacle x = (RectObstacle) obstacles.get(i);
     if (abs(p.pos.x - x.center_x) < x.len/2 &&
         abs(p.pos.y - x.center_y) < x.wid/2){
         //Food is eaten
         obstacles.remove(i);
         hunger += 10;
         if (hunger > 100) {
          hunger = 100; 
         }
         speed += 2.5;
         if (speed > 25) {
           speed = 25;
         }
         food = 0;
         i += 1;
         score += 1;
         if (score%10 == 0){
           file.play();
         } else {
           file2.play();
         }
       }
   }
   
   
   else if(obstacles.get(i) instanceof CircleObstacle){
     CircleObstacle x = (CircleObstacle) obstacles.get(i);
     if (dist(p.pos.x, p.pos.y, obstacles.get(i).pos.x, obstacles.get(i).pos.y) < 
         x.radius + playerRadius){
         p.pos.x = oldpos_x;
         p.pos.y = oldpos_y;
       }
       //Zombie vs Circle Collision
     for (int a = 0; a < zombies.size(); a++){
       Zombie z = zombies.get(a);
       if (dist(z.pos.x, z.pos.y, x.pos.x, x.pos.y) < x.radius + 10){
             z.pos.x = ZombieX.get(a);
             z.pos.y = ZombieY.get(a);
       }
     }
   }
   else if(obstacles.get(i) instanceof RectObstacle){
     RectObstacle x = (RectObstacle) obstacles.get(i);
     if (abs(p.pos.x - x.center_x) < x.len/2 + playerRadius &&
         abs(p.pos.y - x.center_y) < x.wid/2 + playerRadius) {
         p.pos.x = oldpos_x;
         p.pos.y = oldpos_y;         
     }
          //Zombie v Rectangle Collision
     for (int a = 0; a < zombies.size(); a++){
       Zombie z = zombies.get(a);
       if (abs(z.pos.x - x.center_x) < x.len/2 + 10 &&
           abs(z.pos.y - x.center_y) < x.wid/2 + 10){
             z.pos.x = ZombieX.get(a);
             z.pos.y = ZombieY.get(a);
       }
     }
   }


 } //for loop
}

void drawObstacles(){
 fill(255, 0, 0);
 // Fill this in 
 for(int i = 0; i < obstacles.size(); i++){
   if(obstacles.get(i) instanceof CircleObstacle){
     CircleObstacle c = (CircleObstacle) obstacles.get(i);
     //ellipse(c.pos.x, c.pos.y, 2*c.radius, 2*c.radius); // Outline
     float div = 380;
     float k = c.radius/3;
     image(tree_image, c.pos.x - c.radius - k + 6, c.pos.y - c.radius - k, tree_image.width*c.radius/div, tree_image.height*c.radius/div);
   }
   
   else if(obstacles.get(i) instanceof RectObstacle){
     RectObstacle r = (RectObstacle) obstacles.get(i);
     //rect(r.pos.x, r.pos.y, r.len, r.wid); //Outline
     if (r.image == 1){ // House 1
       float div = 4.65;
       image(house1_image, r.pos.x, r.pos.y, house1_image.width/div, house1_image.height/div);
     } else if (r.image == 2) { // House 2
       float div = 6.986;
       image(house2_image, r.pos.x, r.pos.y, house2_image.width/div, house2_image.height/div);
       
     } else if (r.image == 3) { // House 3
       float div = 1.772;
       image(house3_image, r.pos.x, r.pos.y, house3_image.width/div, house3_image.height/div);
       
     } else if (r.image == 5) { // Food 1 Cookie
      float div = 40;
      float adjust = 2;
      image(food1_image, imagex - adjust, imagey - adjust, food1_image.width/div, food1_image.height/div);
     } else if (r.image == 6) { // Food 2 Apple
      float div = 52;
      image(food2_image, imagex, imagey, food2_image.width/div, food2_image.height/div);
     } else if (r.image == 7) { // Food 3 Carrot
      float div = 60;
      float adjustX = 2;
      image(food3_image, imagex - adjustX, imagey, food3_image.width/div, food3_image.height/div);
     } else if (r.image == 8) { // Food 4 Meat
      float div = 120;
      float adjustX = 2;
      image(food4_image, imagex - adjustX, imagey, food4_image.width/div, food4_image.height/div);
     }
     //println("size:" + obstacles.size() + ", i= " + i) ;
   }
   //println(i);
 }
 
}

void applyHunger() {
  int elapsed = millis();
  if (elapsed - time > 2500) {
   time = elapsed;
   if (hunger != 0){
     hunger -= 5;
   }
   if (speed != 0){
     speed -= 1.25;
   }
  }
}

void spawnFood() {
  float side = 30;
  RectObstacle f = new RectObstacle(random(gameBorderLength) + borderLenX,
   random(gameBorderWidth) + borderLenY, side, side, (int) random(4) + 5);
   if (f.pos.x + side > 1216 ||f.pos.y + side > 684) {
      spawnFood();
   }
   else if (checkforOverlap(f) == false){
     obstacles.add(f);
     imagex = f.pos.x;
     imagey = f.pos.y;
   }
   else {
     spawnFood();
   }
} 

void reset(){
    obstacles.clear();
    zombies.clear();
    ZombieX.clear();
    ZombieY.clear();
    score = 0;
    oldpos_x = 0;
    oldpos_y = 0;
    speed = 25;
    time = 0;
    hunger = 105;
    food = 0;
    zombieNum = 5;
    gameOver = false;
    obstacleNum = 6;
    playerRadius = 10;
    paused = false;
    setup();
}

void keyPressed(){

  if(keyCode == LEFT || key == 'a'){
    p.velX = -speed;
  }
  if(keyCode == RIGHT || key == 'd'){
    p.velX = speed;
  }
  if (keyCode == UP || key == 'w'){
    p.velY = -speed;
  }
  if (keyCode == DOWN || key == 's'){
    p.velY = speed;
  }
  if (keyCode == ' '){
    if (paused == true){
      paused = false;
      noLoop();
      draw();

    }
    else {
      paused = true;
      loop();

    }
  }
  if (keyCode == 'p' || keyCode == 'P') { 
    reset();
  }
}

void keyReleased(){
  if (keyCode == LEFT || keyCode == RIGHT || key == 'a' || key == 'd')
    p.velX = 0;
  if (keyCode == UP || keyCode == DOWN || key == 'w' || key == 's')
    p.velY = 0;
}

void computePhysics(float dt) {
  oldpos_x = p.pos.x;
  oldpos_y = p.pos.y;
  p.pos.x += p.velX * dt;
  p.pos.y += p.velY * dt;
  
  for(int i = 0; i < zombies.size(); i++){
    Zombie z = zombies.get(i);
    
    ZombieX.set(i, z.pos.x);
    ZombieY.set(i, z.pos.y);
    
    z.pos.x += z.velX * dt;
    z.pos.y += z.velY * dt;
  }
}

void drawPlayer() {  
  pushMatrix();
  //fill(0, 0, 255);
  //ellipse(p.pos.x, p.pos.y, 2*p.radius, 2*p.radius);
  alignPlayer();
  translate(p.pos.x, p.pos.y);
  rotate(p.align);
  translate(-p.pos.x, -p.pos.y);
  if(p.velX != 0 || p.velY != 0){
    image( personWalk[(int)(frameCount/5)%5], p.pos.x - 12.8, p.pos.y - 12.8, personWalk[(int)(frameCount/5)%5].width/6.25, personWalk[(int)(frameCount/5)%5].height/6.25);
  } else {
    image(personWalk[3], p.pos.x - 12.8, p.pos.y - 12.8, personWalk[3].width/6.25, personWalk[3].height/6.25);
  }
  popMatrix();
}

void alignPlayer() {
  if (p.velX == 0 && p.velY == 0){
    
  } else if (p.velX > 0 && p.velY == 0) {
    p.align = PI/2;
  } else if (p.velX > 0 && p.velY > 0) {
    p.align = 3 * PI/4;
  } else if (p.velX > 0 && p.velY < 0) {
    p.align = PI/4;
  } else if (p.velX < 0 && p.velY == 0) {
    p.align = 3 * PI/2;
  } else if (p.velX < 0 && p.velY > 0) {
    p.align = 5 * PI / 4;
  } else if (p.velX < 0 && p.velY < 0) {
    p.align = 7 * PI / 4;
  } else if (p.velX == 0 && p.velY > 0) {
    p.align = PI;
  } else if (p.velX == 0 && p.velY < 0) {
    p.align = 0;
  }
}



void displayScore() {
  pushMatrix();
    textFont(font,16);
    fill(255);
    textAlign(CENTER);
    text("Score: " + score, windowLenX/2, 100);
    if (paused == false){
      text("Press Space to Resume", windowLenX/2, 80);
    }
    else{
      text("Press Space to Pause", windowLenX/2, 80);
    }
  popMatrix();
}

void displayHunger() {
  pushMatrix();
    textFont(font,16);
    fill(255);
    textAlign(CENTER);
    text("Hunger: " + hunger + "%", windowLenX/2, 120);
  popMatrix();
}


void generateZombie(){
  float tempXLoc;
  float tempYLoc;
  tempXLoc = random(gameBorderLength) + borderLenX;
  tempYLoc = random(gameBorderWidth) + borderLenY;
  Zombie z = new Zombie(tempXLoc,tempYLoc);
  if (checkforOverlap(z) == false){
    zombies.add(z);
    ZombieX.append(z.pos.x);
    ZombieY.append(z.pos.y);
  }
  else{
    generateZombie();
  }
}

void drawZombies(){
  updateZombies();
  for(int i = 0; i < zombies.size(); i++){
    Zombie z = zombies.get(i);
    pushMatrix();
    //fill(0,200,0);
    alignZombie(z);
    translate(z.pos.x, z.pos.y);
    rotate(z.align);
    translate(-z.pos.x, -z.pos.y);
    image( zombieWalk[(int)(frameCount/5)%8], z.pos.x - 12.8, z.pos.y - 12.8, zombieWalk[(int)(frameCount/5)%8].width/2.5, zombieWalk[(int)(frameCount/5)%8].height/2.5);
    //ellipse(z.pos.x,z.pos.y,10,10);
    popMatrix();
  }
}


void alignZombie(Zombie z) {
  if (z.velX == 0 && z.velY == 0){
    
  } else if (z.velX > 0 && z.velY == 0) {
    z.align = PI/2;
  } else if (z.velX > 0 && z.velY > 0) {
    z.align = 3 * PI/4;
  } else if (z.velX > 0 && z.velY < 0) {
    z.align = PI/4;
  } else if (z.velX < 0 && z.velY == 0) {
    z.align = 3 * PI/2;
  } else if (z.velX < 0 && z.velY > 0) {
    z.align = 5 * PI / 4;
  } else if (z.velX < 0 && z.velY < 0) {
    z.align = 7 * PI / 4;
  } else if (z.velX == 0 && z.velY > 0) {
    z.align = PI;
  } else if (z.velX == 0 && z.velY < 0) {
    z.align = 0;
  }
}

void updateZombies(){
  for(int i = 0; i < zombies.size(); i++){
    Zombie z = zombies.get(i);
    boolean seen = true;
    if (dist(p.pos.x, p.pos.y, z.pos.x, z.pos.y) < p.radius*2){  //player touched by zombie
      gameOver = true;
    }
    for(int j = 0; j < obstacles.size()-1; j++) {
      if(obstacles.get(j) instanceof CircleObstacle){
        CircleObstacle c = (CircleObstacle) obstacles.get(j);
        if(pointToLineDistance(p.pos.x,p.pos.y,z.pos.x,z.pos.y,c.pos.x,c.pos.y) < c.radius){
          seen = false;
        }
      }
      else if(obstacles.get(j) instanceof RectObstacle){
        RectObstacle r = (RectObstacle) obstacles.get(j);
        if (lineRect(p.pos.x,p.pos.y,z.pos.x,z.pos.y,r.pos.x,r.pos.y,r.len,r.wid)){
          seen = false;
        }
      }
    }
    if (seen) {
      z.velX = (int)(p.pos.x - z.pos.x)/abs(p.pos.x - z.pos.x)*zombieSpeed;
      z.velY = (int)(p.pos.y - z.pos.y)/abs(p.pos.y - z.pos.y)*zombieSpeed;
    }
    else {
      if (random(10)<.2) {
        float randomSpeed = random(zombieSpeed);
        z.velX = randomSpeed * (int)random(3)-1;
        z.velY = randomSpeed * (int)random(3)-1;
      }
    }

    z.velX += separation(i).x + alignment(i).x + cohesion(i).x;
    z.velY += separation(i).y + alignment(i).y + cohesion(i).y;
  }
}

void displayEndMessage() {
  pushMatrix();
    textFont(font,16);
    fill(255);
    textAlign(CENTER);
    text("Game OVER! Final score: " + score, windowLenX/2, 120);
    text("Press P to restart or Esc to quit", windowLenX/2, 140);
  popMatrix();
}

//shortest distance between line of A to B to point P
float pointToLineDistance(float Ax, float Ay, float Bx, float By, float Px,float Py)
{
  float vx = Px-Ax,   vy = Py-Ay;  
  float ux = Bx-Ax,   uy = By-Ay;   
  float det = vx*ux + vy*uy; 

  if (det <= 0)
  { 
    return sqrt(vx*vx + vy*vy);
  }
  float len = ux*ux + uy*uy;  
  if (det >= len)
  { 
    return sqrt(sq(Bx-Px) + sq(By-Py));  
  }
  return sqrt(sq(ux*vy-uy*vx) / len); 
}

float pointToPointDistance(float Ax, float Ay, float Bx, float By) {
  return sqrt((Ax-Bx)*(Ax-Bx)+(Ay-By)*(Ay-By));
}

/*
Calculating distance between a line and a rectangle, referenced from http://www.jeffreythompson.org/collision-detection/line-rect.php
*/

// LINE/RECTANGLE
boolean lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {

  // check if the line has hit any of the rectangle's sides
  // uses the Line/Line function below
  boolean left =   lineLine(x1,y1,x2,y2, rx,ry,rx, ry+rh);
  boolean right =  lineLine(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
  boolean top =    lineLine(x1,y1,x2,y2, rx,ry, rx+rw,ry);
  boolean bottom = lineLine(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);

  // if ANY of the above are true, the line
  // has hit the rectangle
  if (left || right || top || bottom) {
    return true;
  }
  return false;
}


// LINE/LINE
boolean lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

  // calculate the direction of the lines
  float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

  // if uA and uB are between 0-1, lines are colliding
  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

    return true;
  }
  return false;
}

PVector separation(int index) {
  PVector result = new PVector(0,0);
  Zombie z = zombies.get(index);
  for(int i = 0; i < zombies.size(); i++){
    if (i != index){
      Zombie z2 = zombies.get(i);
      if (pointToPointDistance(z.pos.x,z.pos.y,z2.pos.x,z2.pos.y) < 2 * playerRadius){
        result.x = result.x + (z.pos.x - z2.pos.x);
        result.y = result.y + (z.pos.y - z2.pos.y);
      }
    }
  }
  return result.mult(.1);
}

PVector alignment(int index) {
  PVector result = new PVector(0,0);
  return result;
}

PVector cohesion(int index) {
  PVector result = new PVector(0,0);
  /*float centerX = 0;
  float centerY = 0;
  int count = 1;
  Zombie z = zombies.get(index);
  for(int i = 0; i < zombies.size(); i++){
    if (i != index){
      Zombie z2 = zombies.get(i);
      if (pointToPointDistance(z.pos.x,z.pos.y,z2.pos.x,z2.pos.y) < 300){
        centerX += z2.pos.x;
        centerY += z2.pos.y;
        count++;
      }
    }
  }
  centerX = centerX / (count-1);
  centerY = centerY / (count-1);
  println (centerX + " " + centerY + " " + count);
  result.x = centerX - z.pos.x;
  result.y = centerY - z.pos.y;*/
  return result.mult(0);
}