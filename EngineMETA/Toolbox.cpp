#include "Toolbox.h"

float norm(float n){
  if (n > 0) return 1.0f;
  if (n < 1) return -1.0f;
  if (n == 0) return 0.0f;
}

bool collidePointRect(int x1, int y1 ,int x2 ,int y2, int w, int h){
  if((x1>=x2)&&(x1<x2+w))
  if((y1>=y2)&&(y1<y2+h))
  return true;
  return false;
}

bool collideRectRect(int x1, int y1, int w1, int h1 ,int x2 ,int y2, int w2, int h2){
  return !( x2     >=  x1+w1  || 
            x2+w2  <=  x1     || 
            y2     >=  y1+h1  ||
            y2+h2  <=  y1     );
}
