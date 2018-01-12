#define AR3_UTILS
#include <iostream>
#include <GLUT/glut.h>
#include <math.h>

using namespace std;

// prints ar3
void print3(GLfloat ar[3]);

// copies source to dest
void copy3(GLfloat source[3], GLfloat dest[3]);

// adds one and two, puts in sum 
void add3(GLfloat one[3], GLfloat two[3], GLfloat sum[3]);
void sub3(GLfloat one[3], GLfloat two[3], GLfloat sum[3]);


// scales ar by num, stores in product
void scale3(GLfloat ar[3], GLfloat num, GLfloat product[3]);

GLfloat dot3(GLfloat u[3], GLfloat v[3]);

GLfloat length3(GLfloat u[3]);

void unit3(GLfloat u[3], GLfloat dest[3]);

void mult3(GLfloat u[3], GLfloat v[3], GLfloat dest[3]);
