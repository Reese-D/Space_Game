/*******************************************************************************
* Author(s): Reese De Wind
* Version: 0.0
* Created: Wed Jun  1 13:21:41 2016
*******************************************************************************/
#include <time.h>
#include <stdlib.h>

double SmoothedNoise_1(double x){
  return rand(x)/2  +  Noise(x-1)/4  +  Noise(x+1)/4;
}


	       function InterpolatedNoise_1(float x)

	       integer_X    = int(x)
  fractional_X = x - integer_X

  v1 = SmoothedNoise1(integer_X)
  v2 = SmoothedNoise1(integer_X + 1)

  return Interpolate(v1 , v2 , fractional_X)

  end function


     function PerlinNoise_1D(float x)

     total = 0
  p = persistence
  n = Number_Of_Octaves - 1

  loop i from 0 to n

  frequency = 2i
  amplitude = pi

  total = total + InterpolatedNoisei(x * frequency) * amplitude

  end of i loop

  return total

  end function
    
int main(int argc, char **argv){
  
  return 0;
}
