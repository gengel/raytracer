/* Assignment 4 - CS 357

   In case you can't tell, it's four spheres.  One is a "mirror sphere."
   The entire scene is surrounded by two mirrors, one behind the viewer 
   and one out in the distance.

   My traceRay function is a bit messy.  However, it should be decipherable.
   My class structure for traceable objects is, I believe, self-explanatory.

   I think I did everything.
   
   Also, there are some misc source files in this directory, not all of 
   which are used here.  Ignore them.  The important files are this one, 
   Sphere.*, TraceObject.*, ar3.*, and Wall.*


 *  Ray-Tracing
 *  Woo-hoo!
 * 
 */

#include "Sphere.H"  
#include "Wall.H"

#define X 800
#define Y 800

#define viewX X/2
#define viewY Y/2
#define viewZ -1000

#define OBJECTS 3
#define LIGHTS 1

// ray-trace return vals
#define NOTHING 0
#define LIGHT 1
#define OBJECT 2

#define DEBUG false
#define DEBUG2 false

#define RECURSE 12
#define MIN_WEIGHT 0.01

GLfloat image[X][Y][3];
GLfloat RED[3] = {1.0, 0.1, 0.1};
GLfloat BLUE[3] = {0.0, 0.0, 1.0};
GLfloat GREEN[3] = {0.0, 1.0, 0.0};
GLfloat BLACK[3] = {0.0, 0.0, 0.0};
GLfloat WHITE[3] = {1.0, 1.0, 1.0};
GLfloat CYAN[3] = {0.0, 1.0, 1.0};

GLfloat SOURCE_POINT[3] = {0, 0, 0};
GLfloat SOURCE_RADIUS = 80.0;
/*
GLfloat SOURCE2_POINT[3] = {1000, 200, 80};
GLfloat SOURCE2_RADIUS = 40.0;
*/
int traceRay(GLfloat start[3], GLfloat slope[3],
	     TraceObject* objects[OBJECTS],
	     GLfloat lights[LIGHTS][3],
	     GLfloat color_dest[3], 
	     int level, GLfloat weight, bool doColor);




// create the scene!
void renderScene()
{
  //array for objects in scene
  TraceObject* objects[OBJECTS];
  GLfloat lights[LIGHTS][3];

  // create object
  Sphere* myLightSource = new Sphere(WHITE, WHITE, WHITE, WHITE,
				     0.7, 0.5, 0.0, 1.0,
				     0.0, 
				     SOURCE_POINT, 
				     SOURCE_RADIUS);


  /* Sphere* myLightSource2 = new Sphere(WHITE, WHITE, WHITE, WHITE,
				      1.0, 0.0, 0.0, 0.0,
				      0.0,
				      SOURCE2_POINT, 
				      SOURCE2_RADIUS);
  */			     
  myLightSource->flipLight();
  //myLightSource2->flipLight();

  copy3(SOURCE_POINT,lights[0]);
  //  copy3(SOURCE2_POINT,lights[1]);


  GLfloat point[3] = { 400, 400, 400 };
  Sphere* myRedSphere = new Sphere(RED, RED, WHITE, WHITE,
				   0.1, 0.9, 0.0, 0.1,
				   0.0, 
				   point, 100.0);
  
  GLfloat point2[3] = { 600, 600,  600 };
  Sphere* myBlueSphere = new Sphere(BLUE, BLUE, WHITE, WHITE,
				    0.1, 0.9, 0.0, 0.1,
				    0.0, 
				    point2, 150.0);
  /*
  GLfloat point3[3] = { 775, 300, 150 };
  Sphere* myWhiteSphere = new Sphere(CYAN, CYAN, WHITE, WHITE,
				     0.1, 0.9, 0.0, 0.3,
				     0.0,
				     point3, 350.0);
  */
  /*
  Wall* myWall= new Wall(WHITE, WHITE, WHITE, WHITE,
			 0.0, 0.1, 0.0, 0.85,
			 0.0, 900.0, true);

  Wall* myOtherWall = new Wall(WHITE, WHITE, WHITE, WHITE,
			  0.0, 0.1, 0.0, 0.85,
			  0.0, -1001.0, false);

  
  GLfloat point4[4] = { 95, 590, 200 };
  
  Sphere* myMirrorBall = new Sphere(WHITE, WHITE, WHITE, WHITE,
				    0.02, 0.25, 0.0, 1.0,
				    0.0,
				    point4, 160.0);
  
  */
  // add to array
  objects[0] = myLightSource;
  objects[1] = myRedSphere;
  objects[2] = myBlueSphere;
  // objects[3] = myWhiteSphere;
  
  // objects[4] = myWall;
  //objects[5] = myMirrorBall;
  //objects[6] = myOtherWall;
  //objects[4] = myLightSource2;
  // Calculate ray from viewer to each point on pixel grid


  for(int i = 0; i < X; i++)
    {
      if( i % 8 == 0)
	cerr << ".";

      for(int j = 0; j < Y; j++)
	{
	  GLfloat start[3] = { viewX, viewY, viewZ };
	  GLfloat slope[3] = { (i-viewX), (j-viewY), (0-viewZ) };
	  unit3(slope,slope);

	  traceRay(start, slope, objects, lights, image[j][i], 
		   RECURSE, 1.0, true);
	  #if DEBUG
	    cout << "x: " << i << "   y: " << j << endl;
	  #endif
	  
	}
      
      //cerr << "pppppp" <<endl;
    }
  cerr << endl;


}






// start is a point in space
// slope is slope(s) of ray
// level is used for a check on recursion
// color_dest[3] is "return val"
// 
int traceRay(GLfloat start[3], GLfloat slope[3],
	     TraceObject* objects[OBJECTS],
	     GLfloat lights[LIGHTS][3],
	     GLfloat color_dest[3], 
	     int level, GLfloat weight, bool doColor)
{
  GLfloat result[3] = {0.0, 0.0, 0.0};

  if(level == 0)
    {
      copy3(result,color_dest);
      return NOTHING;
    }
  level--;

  if(weight < MIN_WEIGHT)
    {
      copy3(result, color_dest);
      return NOTHING;
    }


  
  // first, find t for each object 
  GLfloat t_vals[OBJECTS];

  for(int i = 0; i< OBJECTS; i++)
    t_vals[i] = objects[i]->intersect(start, slope);

  
  

  // now, find lowest positive num
  GLfloat minval = 9999999;
  int min = -1;
  int i = 0;
  for(i = 0; i < OBJECTS; i++ )
    {
      if( t_vals[i] < minval && t_vals[i] > 0)
	{
	  minval = t_vals[i];
	  min = i;
	}
    }

  // if min = -1, we found NO object
  if(min < 0)
    {
      copy3(BLACK, color_dest);
      return NOTHING;
    }
  else
    {
      cerr << "Found object at t: " << minval << endl;
    }

  //cerr << "We hit SOMETHING..." << endl;
  
  // otherwise, object is object at min
  TraceObject* closest = objects[min];

  // if object is a light source, we're white!
  if(closest->isLightSource())
    {

      closest->getAmbientColor(color_dest);
      scale3(color_dest, closest->getAmbientK(), color_dest);
      return LIGHT;
    }

  if(!doColor)
    {
      return OBJECT;
    }

  // otherwise, regular old object
  // so let's do some calculatin!

  // ambient calc

  GLfloat amb[3];
  closest->getAmbientColor(amb);

  scale3(amb, closest->getAmbientK(), amb);
  add3(amb, result, result);

  
  
  // 
  // get Normal at point
  GLfloat N[3];

  GLfloat point[3];

  for(int i = 0; i<3; i++)
    point[i] = start[i] + (minval * slope[i]);
  
  closest->getNormal(point,N);

  // point now is point of intersection
  // N is normal vector at point

  // diffusen calc
  GLfloat diff[3] = {0.0, 0.0, 0.0};

  for(int i = 0; i< LIGHTS; i++)
    {
      
      GLfloat currLight[3];
      copy3(lights[i],currLight);
      //GLfloat currLight[3] = lights[i];

      GLfloat L[3];
      GLfloat newpoint[3];
      for(int i = 0; i<3; i++)
	{
	  L[i] = currLight[i] - point[i];
	  newpoint[i] = point[i] + L[i]*0.001;
	}


      GLfloat Ip[3];
    
      int x = traceRay(newpoint,L,objects,lights,Ip,1,1,false);
      //cerr << x << endl;
      if(  x== LIGHT )
	{
	  #if DEBUG
	    {
	      cout << "Doing diffuse calc...";
	      cout << "Light found at: " << endl;
	      print3(currLight);
	      cout << "Intersection point: " << endl;
	      print3(point);
	      
	      cout << "Vector from point to light: " << endl;
	      print3(L);
	      

	    }
	  
	  #endif

	  unit3(L,L);

	  GLfloat dot = dot3(L,N);
	  
	  #if DEBUG
	    {
	      cout << "L as a unit vector: " << endl;
	      print3(L);

	      cout << "N as a unit vector: " << endl;
	      print3(N);

	      cout << "Dot product of L and N is: " 
		   << dot << endl;
	    }
	  #endif

	    //don't let this affect things if light doesn't hit
	  if(dot > 0 && dot < 1)
	    {

	      GLfloat color[3];
	      closest->getDiffuseColor(color);
	  
	      scale3(color,dot,color);
	      mult3(color,Ip,color);

	      add3(diff, color, diff);
	    }
	  
	  #if DEBUG
	    {
	      cout << "Done diffuse calc" << endl;
	      cout << "Diffuse is: " << endl;
	      print3(diff);
	    }
	  #endif
	}
    }

  scale3(diff, closest->getDiffuseK(), diff);
  add3(diff, result, result);


  /*// specular light
  
  GLfloat spec_k = closest->getSpecularK();
  if(spec_k > 0)
    {
      GLfloat spec_Ip[3];

      // specular direction
      GLfloat R[3];
      GLfloat V[3];

      V[0] = start[0] - point[0];
      V[1] = start[1] - point[1];
      V[2] = start[2] - point[2];

 

      unit3(V,V);

      GLfloat Rdot = dot3(N,V) * 2;
      
      scale3(N,Rdot,R);

      sub3(R,V,R);

     GLfloat spec_point[3];
     for(int i = 0; i < 3; i++)
       spec_point[i] = point[i] + (R[i] * 0.001); 

     traceRay(spec_point,R,objects,lights,spec_Ip,level,(weight*spec_k),true);
      
     scale3(spec_Ip,spec_k,spec_Ip);

     add3(result,spec_Ip,result);


    }
  */

  // check for color > 1.0

  for(int i = 0; i < 3; i++)
    if(result[i] > 1.0)
      result[i] = 1.0;


  // equiv to "return"
  copy3(result, color_dest);
  return OBJECT;
} 







void display() {
  

  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(45, 45);
  glDrawPixels(X, Y, GL_RGB, GL_FLOAT, image);
  glFlush();
}

void reshape(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLfloat)X, 0.0, (GLfloat)Y );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, w, h);
}

void init() {
  glClearColor(0.0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLfloat)X, 0.0, (GLfloat)Y );

}


int main(int argc, char** argv) {

  renderScene();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(900, 900);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Greg's Fun With Rays");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}


