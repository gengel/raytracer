#include "TraceObject.H"

class SimpleQuad : public TraceObject
{

public:
  SimpleQuad(GLfloat a_color[3], GLfloat d_color[3], 
	     GLfloat r_color[3], GLfloat s_color[3], 
	     GLfloat amb_k, GLfloat diff_k, 
	     GLfloat ref_k, GLfloat spec_k, 
	     GLfloat ref_i, bool light,
	     GLfloat down_left_front_vertex[3],
	     GLfloat height, GLfloat width, GLfloat depth)
    : TraceObject(a_color, d_color, r_color, s_color,
		  amb_k, diff_k, ref_k, spec_k,
		  ref_i, false)
  {

    copy3(down_left_front_vertex,vertex);
    myHeight = height;
    myWidth = width;
    myDepth = depth;
  }


  virtual GLfloat intersect(GLfloat start[3], GLfloat slope[3]);
  virtual void getNormal(GLfloat point[3], GLfloat dest[3]);

  // color retrieval
  virtual inline void getAmbientColor(GLfloat dest[3]) { copy3(ambient_color,dest);  }
  virtual inline void getSpecularColor(GLfloat dest[3]) { copy3(specular_color,dest); }
  virtual inline void getDiffuseColor(GLfloat dest[3]) { copy3(diffuse_color,dest); }
  virtual inline void getRefractColor(GLfloat dest[3]) { copy3(refract_color,dest); }

private:
  GLfloat myHeight;
  GLfloat myWidth;
  GLfloat myDepth;
  GLfloat vertex[3];
		  
	     
);
