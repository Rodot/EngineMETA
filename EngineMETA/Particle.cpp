#include "Particle.h"

Particle::Particle(float X, float Y, float VX, float VY, float W, float H, boolean collide){
  init();
  x = X;
  y = Y;
  vx = VX;
  vy = VY;
  width = W;
  height = H;
  density = 2;
  bounce = 0.4;
  collideMap = collide;
  collideObjects = false;
  life = 50;
  color = DARKGRAY;
}

void Particle::update(){
  Object::update();
  life --;
}

void Particle::die(){
  //do nothing
}

