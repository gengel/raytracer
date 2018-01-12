#include "TraceObject.H"

TraceObject::TraceObject(GLfloat a_color[3], 
			 GLfloat d_color[3], 
			 GLfloat r_color[3],
			 GLfloat s_color[3],
			 GLfloat amb_k, GLfloat diff_k, 
			 GLfloat ref_k, GLfloat spec_k, 
			 GLfloat ref_i, bool light)
{
  copy3(a_color, ambient_color);
  copy3(d_color, diffuse_color);
  copy3(r_color, refract_color);
  copy3(s_color, specular_color);
  
  ambient_k = amb_k;
  diffuse_k = diff_k;
  specular_k = spec_k;
  refract_k = ref_k;

  refract_index = ref_i;

  source = light;
 
}








