#include "Wall.H"

Wall::Wall(GLfloat a_color[3],
	   GLfloat d_color[3], 
	   GLfloat r_color[3], 
	   GLfloat s_color[3], 

	   GLfloat amb_k, 
	   GLfloat diff_k, 
	   GLfloat ref_k, 
	   GLfloat spec_k, 
	   
	   GLfloat ref_i, 
	   
	   GLfloat depth,
	   bool front
	   ) 
 
 : TraceObject(a_color, d_color, r_color, s_color,
		amb_k, diff_k, ref_k, spec_k,
		ref_i, false)
{
  myDepth = depth;
  myFront = front;
		    
}



GLfloat Wall::intersect(GLfloat start[3], GLfloat slope[3])
{

  return (myDepth - start[2])/(slope[2]);

}


void Wall::getNormal(GLfloat point[3], GLfloat dest[3])
{

  if(myFront)
    {
      GLfloat n[3] = {0.0, 0.0, -1.0};
      unit3(n,dest);

    }
  else
    {
      GLfloat n[3] = {0.0, 0.0, 1.0};
      unit3(n,dest);
    }

      
}
