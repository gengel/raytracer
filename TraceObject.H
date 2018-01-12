#ifndef AR3_UTILS
#include "ar3.h"
#endif

#define TRACE

class TraceObject
{

public:
  TraceObject(GLfloat a_color[3], GLfloat d_color[3], 
	      GLfloat r_color[3], GLfloat s_color[3], 
	      GLfloat amb_k, GLfloat diff_k, 
	      GLfloat ref_k, GLfloat spec_k, 
	      GLfloat ref_i, bool light);

  TraceObject() { } ;

  virtual ~TraceObject() { };

  // spatial functions
  virtual GLfloat intersect(GLfloat start[3], GLfloat slope[3]) = 0;
  virtual void getNormal(GLfloat point[3], GLfloat dest[3]) = 0;

  // color retrieval
  virtual void getAmbientColor(GLfloat dest[3]) = 0;
  virtual void getSpecularColor(GLfloat dest[3]) = 0;
  virtual void getDiffuseColor(GLfloat dest[3]) = 0;
  virtual void getRefractColor(GLfloat dest[3]) = 0;

  // konstant retrieval
  inline GLfloat getAmbientK() { return ambient_k; }
  inline GLfloat getDiffuseK() { return diffuse_k; }
  inline GLfloat getSpecularK() { return specular_k; }
  inline GLfloat getRefractK() { return refract_k; }
  
  // refraction
  inline GLfloat getRefractIndex() { return refract_index; } 

  virtual inline bool isLightSource() { return source; }
  virtual inline void flipLight() { source = !source; }

protected:
  // coefficients for various components of light
  // (should add up to 1, but can exceed if you want)
  GLfloat ambient_k;
  GLfloat diffuse_k;
  GLfloat specular_k;
  GLfloat refract_k;

  // colors for various components
  // (Specular should probably be white)
  GLfloat ambient_color[3];
  GLfloat diffuse_color[3];
  GLfloat specular_color[3];
  GLfloat refract_color[3];

  // refraction index
  GLfloat refract_index;

  // light source?
  bool source;

  

};
	      
