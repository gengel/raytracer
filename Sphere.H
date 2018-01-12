#ifndef AR3_UTILS
#include "ar3.h"
#endif

#ifndef TRACE
#include "TraceObject.H"
#endif

class Sphere : public TraceObject

{

public:

  Sphere(GLfloat a_color[3], GLfloat d_color[3], 
	 GLfloat r_color[3], GLfloat s_color[3], 
	 GLfloat amb_k, GLfloat diff_k, 
	 GLfloat ref_k, GLfloat spec_k, 
	 GLfloat ref_i, 
	 GLfloat cen[3], GLfloat rad);

  Sphere() { } ;
 
   // returns "t" of intercept ray,
  // if ray does not intercept, value will be negative
  GLfloat intersect(GLfloat start[3], 
			    GLfloat slope[3]);

  void getNormal(GLfloat point[3], 
			 GLfloat dest[3]);


  // color retrieval
  void getAmbientColor(GLfloat dest[3]);
  void getSpecularColor(GLfloat dest[3]);
  void getDiffuseColor(GLfloat dest[3]);
  void getRefractColor(GLfloat dest[3]);
  
  // inherits constant retrieval...can leave out...

  // inherits refract retrieval
 
  // inherits default isLightSource()


private:
  GLfloat center[3];
  GLfloat radius;

};
	
    
