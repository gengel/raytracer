#include "ar3.h"

void print3(GLfloat ar[3])
{
  for(int i = 0; i < 3; i++)
    cout << i << ": " << ar[i] << endl;
}

void copy3(GLfloat source[3], GLfloat dest[3])
{
  for(int i = 0; i < 3; i++)
    dest[i] = source[i];
}


void add3(GLfloat one[3], GLfloat two[3], GLfloat sum[3])
{
  for (int i = 0; i<3; i++)
    sum[i] = one[i] + two[i];
}

void sub3(GLfloat one[3], GLfloat two[3], GLfloat sum[3])
{
  for(int i = 0; i<3; i++)
    sum[i] = one[i] - two[i];
}

void scale3(GLfloat ar[3], GLfloat num, GLfloat product[3])
{
  for (int i = 0; i<3; i++)
    product[i] = ar[i] * num;
}

GLfloat dot3(GLfloat u[3], GLfloat v[3])
{
  GLfloat product = 0;

  for (int i = 0; i<3; i++)
    product += u[i] * v[i];

  return product;
}

GLfloat length3(GLfloat u[3])
{
  GLfloat dot =  dot3(u,u);


  return( sqrt( dot ));
}


void unit3(GLfloat u[3], GLfloat dest[3])
{

  GLfloat l = length3(u);

  for(int i = 0; i<3; i++)
    dest[i] = u[i] / l;


}

void mult3(GLfloat u[3], GLfloat v[3], GLfloat dest[3])
{
  for(int i = 0; i<3; i++)
    dest[i] = u[i] * v[i];
}
