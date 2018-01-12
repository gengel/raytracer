#include "Sphere.H"

#include <iostream>
using namespace std;

GLfloat RED[3] = {1.0, 0.1, 0.1};
GLfloat BLUE[3] = {0.0, 0.0, 1.0};
GLfloat GREEN[3] = {0.0, 1.0, 0.0};
GLfloat BLACK[3] = {0.0, 0.0, 0.0};
GLfloat WHITE[3] = {1.0, 1.0, 1.0};
GLfloat CYAN[3] = {0.0, 1.0, 1.0};
GLfloat CENTER[3] = {100, 550, 150};


GLfloat START[3] = {-100,250,250};
GLfloat SLOPE[3] = {100,-250,-250};


int main(char** argv, int argc) {

  unit3(SLOPE, SLOPE);
  Sphere* test = new Sphere(RED, RED, RED, RED,
			    0.3, 0.3, 0.3, 0.3,
			    0.5, 
			    CENTER, 400);

  GLfloat val = 7.0;
  val = test->intersect(START, SLOPE);
  cerr << "Best Intersection: " << val  << endl;

  return 0;
}


			  
