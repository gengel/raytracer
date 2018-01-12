#include "Sphere.H"


// constructor
Sphere::Sphere(GLfloat a_color[3],
	       GLfloat d_color[3],
	       GLfloat r_color[3],
	       GLfloat s_color[3],
	       GLfloat amb_k, GLfloat diff_k,
	       GLfloat ref_k, GLfloat spec_k,
	       GLfloat ref_i,
	       GLfloat cen[3], GLfloat rad)

  : TraceObject(a_color, d_color, r_color, s_color,
		amb_k, diff_k, ref_k, spec_k,
		ref_i, false)
{
  copy3(cen, center);
  radius = rad;
}


void Sphere::getNormal(GLfloat point[3], GLfloat dest[3])
{
  GLfloat temp[3];

  for(int i = 0; i<3; i++)
    temp[i] = point[i] - center[i];

  // unit vector
  unit3(temp,dest);

}




// returns lowest t value of intersection
// negative indicates no intersection
GLfloat Sphere::intersect(GLfloat start[3],GLfloat slope[3])
{
    // quad formula
    //x = -b (+||-) (sqrt(b*b - 4*a*c) / (2*a) )

    GLfloat a = (slope[0]*slope[0]) + (slope[1]*slope[1]) +
                (slope[2]*slope[2]);
    //cerr << "a: " << a << endl;

    GLfloat b = 2*( (start[0]*slope[0]) - ( center[0]*slope[0] ) +
	            (start[1]*slope[1]) - ( center[1]*slope[1] ) +
		    (start[2]*slope[2]) - ( center[2]*slope[2] )  );

    //cerr << "b: " << b << endl;
    GLfloat c = ( (start[0]*start[0]) + (center[0]*center[0])  +
		  (start[1]*start[1]) + (center[1]*center[1])  +
		  (start[2]*start[2]) + (center[2]*center[2])) +
           (-2 * ( (center[0]*start[0]) + (center[1]*start[1]) +
	          (center[2]*start[2])                         )) -
                ( radius*radius );

    //cerr << "c: " << c << endl;


    GLfloat sq = sqrt( (b*b) - (4*a*c) );
    if(isnan(sq))
      return -1.0;

    if(sq == 0)
      return (-b)/(2*a);

    GLfloat t_pos = (-b + sq ) / (2*a);
    GLfloat t_neg = (-b - sq ) / (2*a);

    //cerr << "tPos: " << t_pos << endl;
    //cerr << "tNeg: " << t_neg << endl;
    // move nan to -1

    if(isnan(t_pos))
      t_pos = -1.0;

    if(isnan(t_neg))
      t_neg = -1.0;



//     // return the lowest positive number
//     // any negative value indicates non-intersection
//     if(t_pos > 0 && t_neg > 0) {
//       	if(t_pos < t_neg)
// 	  return t_pos;
// 	else
// 	  return t_neg;
//     } else if(t_pos > 0) {
//       return t_pos;
//     } else if(t_neg > 0) {
//       return t_neg;
//     } else
//       return -1.0;

    // return the lowest positive number
    // any negative value indicates non-intersection
    if(t_pos > 0 && t_neg > 0) {
      	if(t_pos < t_neg)
	  return t_pos;
	else
	  return t_neg;
    } else if(t_pos < 0) {
      if(t_neg < 0)
	return -1.0;
      else
	return t_neg;
    } else // This next line is wrong, but when I change it, it breaks.
      return t_neg;
 }





// "accessor" methods
// copy values for various colors into dest

inline void Sphere::getAmbientColor(GLfloat dest[3])
{

  copy3(ambient_color,dest);
}



inline void Sphere::getSpecularColor(GLfloat dest[3])
{
  copy3(specular_color,dest);
}



inline void Sphere::getDiffuseColor(GLfloat dest[3])
{
  copy3(diffuse_color, dest);
}



inline void Sphere::getRefractColor(GLfloat dest[3])
{
  copy3(refract_color, dest);
}










/* main and helper functions
int main()
{

  GLfloat black[3] = {0.0, 0.0, 0.0};
  GLfloat center[3] = {1.0, 1.0, 1.0};

  Sphere mysphere(black, black, black, black,
		  0.25, 0.25, 0.25, 0.25,
		  0.0,
		  center, 7.0);


  GLfloat dest[3] = {0.0, 0.0, 0.0};

  cout << "Is a light source?" << endl;
  cout << mysphere.isLightSource() << endl;

  cout << "Ambient Light: " << endl;
  mysphere.getAmbientColor(dest);
  print3(dest);

  cout << "Diffuse Constant: "
       << mysphere.getDiffuseK()
       << endl;

  cout << "Refract Index: "
       << mysphere.getRefractIndex()
       << endl;


  GLfloat start[3] = {9.0, 0.0, 0.0};
  GLfloat slope[3] = {-0.5, 1.0, 0.5};

  cout << "t value of intersection with line: " << endl
       << "Pos: " << endl;
  print3(start);
  cout << "Slope: " << endl;
  print3(slope);
  GLfloat t = mysphere.intersect(start, slope);
  cout << "t = " << t
       << endl;

  GLfloat point[3];
  point[0] = (slope[0]*t) + start[0];
  point[1] = (slope[1]*t) + start[1];
  point[2] = (slope[2]*t) + start[2];

  cout << "...which is at point: "
       << "x= " << point[0]
       << "y= " << point[1]
       << "z= " << point[2]
       << endl;

  cout << "Normal at this point is: ";

  mysphere.getNormal(point, dest);

  print3(dest);


  return 0;
}

*/
