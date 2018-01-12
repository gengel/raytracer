#include "Floor.H"

Floor::Floor(GLfloat a_color[3], GLfloat d_color[3], 
	     GLfloat r_color[3], GLfloat s_color[3], 
	     GLfloat amb_k, GLfloat diff_k, 
	     GLfloat ref_k, GLfloat spec_k, 
	     GLfloat ref_i, 
	     GLfloat height)

  : TraceObject(a_color, d_color, r_color, s_color, 
		amb_k, diff_k, ref_k, spec_k, 
		ref_i, false)
{
  myHeight = height;
}



GLfloat Floor::intersect(GLfloat start[3], GLfloat slope[3])
{

  return (myHeight - start[1])/(slope[1]);

}




void Floor::getNormal(GLfloat point[3], GLfloat dest[3])
{

  GLfloat n[3] = { 0.0, 1.0, 0.0 };
  copy3(n,dest);

}

