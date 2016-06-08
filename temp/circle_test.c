/*******************************************************************************
* Author(s): Reese De Wind
* Version: 0.0
* Created: Fri Jun  3 17:02:45 2016
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
  int num_iters = atoi(argv[1]);
  double increase_angle = atof(argv[2]);
  
  double radiusX = 100;
  double increments = -100.0 / (num_iters - 1.0);

  for(int i = 0; i < num_iters; i++){
    double radiusY = increments * i;
    double tempRad = sqrt(  pow(100, 2) - pow((radiusY),2)  ) + (tan(increase_angle) * radiusY * -1);
    radiusX *= increase_angle + 1;
    printf("actual radius %f: %f\n",increments * i, tempRad);
  }
  return 0;
}

