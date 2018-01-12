#include "Sphere.H"
#include <iostream>

using namespace std;

GLfloat START[3] = { 0, 0, 0};
GLfloat DIRECTION[3] = { 4, 5, 6};
GLfloat NORMAL[3] = { 0, -4, -4 };

void reflect(GLfloat[3], GLfloat[3], GLfloat[3]);

int main(char** argv, int argc) 
{


  reflect(START, DIRECTION, NORMAL);

  return 0;

}


void reflect(GLfloat start[3], GLfloat direction[3], GLfloat N[3])
{

    // specular direction
      GLfloat R[3];
      GLfloat V[3];
      /*
      V[0] = start[0] - point[0];
      V[1] = start[1] - point[1];
      V[2] = start[2] - point[2];
      */

      V[0] = -direction[0];
      V[1] = -direction[1];
      V[2] = -direction[2];

      unit3(V,V);
      unit3(N,N);

      GLfloat Rdot = dot3(N,V) * 2;
      
      cerr << "Dot Prod: " << Rdot << endl;

      scale3(N,Rdot,R);

      sub3(R,V,R);

      cerr << "Answer: " << R[0] << ", " << R[1] << ", " << R[2] << endl;

}
