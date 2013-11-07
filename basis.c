
#include <GL/glut.h>
#include <math.h>

#include "gamepipeline.h"


char ** map;
float xpos=-72,ypos=0,zpos=-72,xrot=0,yrot=0,zrot=0;
int texture[10];
int hp=100;
Bullet bullets[1000];
Turret turrets[100];
int mousex,mousey;
int wwidth=640,wheight=480;
char stats[50];

void render(void);
void keyboard (unsigned char key, int x, int y);
void settings (void);
void reshape (int w, int h);
int  PlayerCollision(int direction);
void mouse (int x, int y);
void mouseclick(int button, int state, int x, int y);
void turretfire(int t);

void window_pos( GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
   GLfloat fx, fy;

   /* Push current matrix mode and viewport attributes */
   glPushAttrib( GL_TRANSFORM_BIT | GL_VIEWPORT_BIT );

   /* Setup projection parameters */
   glMatrixMode( GL_PROJECTION );
   glPushMatrix();
   glLoadIdentity();
   glMatrixMode( GL_MODELVIEW );
   glPushMatrix();
   glLoadIdentity();

   glDepthRange( z, z );
   glViewport( (int) x - 1, (int) y - 1, 2, 2 );

   /* set the raster (window) position */
   fx = x - (int) x;
   fy = y - (int) y;
   glRasterPos4f( fx, fy, 0.0, w );

   /* restore matrices, viewport and matrix mode */
   glPopMatrix();
   glMatrixMode( GL_PROJECTION );
   glPopMatrix();

   glPopAttrib();
}



int main(int argc, char **argv) {
	
	int i,j;

	//Set all bullets to nonfired status.
	for (i=0;i<1000;i++) bullets[i].fired=0;

	//Set all turrets to nonexisting status
	for (i=0;i<100;i++) turrets[i].existing=0;


	//Allocate array for storing a map and fill with 0
	map = malloc(49 * sizeof(char*));
	for (i=0;i<=48;i++) 
	{	
		map[i]=malloc(49* sizeof(char));
		for (j=0;j<=48;j++) 	
		{

		map[i][j]=0;
		}
	}

	//Generate map(labirynth with turrets)
	MapGen(map,turrets);


	// GLUT and window init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(wwidth,wheight);
	glutCreateWindow("Game");

	//Callbacks
	glutDisplayFunc(render);
	glutKeyboardFunc (keyboard); 
  	glutIdleFunc(render);
	glutReshapeFunc (reshape);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mouseclick);
	glutTimerFunc(1,turretfire,0);

	//Load textures
	LoadGLTextures(texture);
	 settings(); 
	
	//Fullscreen
	glutFullScreen();


	//Into the GLUT loop
	glutMainLoop();


	return 0;

}

void settings (void) {
		glMatrixMode (GL_MODELVIEW);		
	glEnable(GL_TEXTURE_2D);	
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
        glEnable (GL_DEPTH_TEST); //settings the depth testing
    	glShadeModel (GL_SMOOTH); //set the shader to smooth shade
	glutSetCursor(GLUT_CURSOR_NONE);
	
	
     
	glEnable (GL_LIGHTING); //enabling the lighting
	GLfloat LightAmbient[] = { 1.f, 1.0f, 1.0f, 1.0f };   // white ambient light at half intensity (rgba) 
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //super bright, full intensity diffuse light.
	GLfloat LightPosition[] = { 0, 100, 0, 1.0 }; //position of light (x, y, z, (position of light))
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);  // add lighting. (ambient)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);  // add lighting. (diffuse).
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); // set light position.
	glEnable(GL_LIGHT1); //enable light



}

void reshape (int w, int h) 
{
    wwidth=w;
    wheight=h;
    //Function called in case of window reshape
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
    glMatrixMode (GL_MODELVIEW);

}



void render (void) {
    glClearColor (0.0,0.0,0.0,1.0); //Clear the screen 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear buffers

    glLoadIdentity();  //Load identity matrix for player(camera)
    glRotatef(xrot,1.0,0.0,0.0); //Rotate player(camera) on x axis
    glRotatef(yrot,0.0,1.0,0.0);  //Rotate player(camera) on y axis
    glTranslated(-xpos,-ypos,-zpos); //Translatate player(camera)

   

	

	
    Map(map,texture); //Load map(labirynth and skybox, and bind textures to them)


    WorldMove(bullets,map,turrets,xpos,ypos,zpos,&hp); //Draw turrets and bullets

	//Print stats
	window_pos(0,wheight-20,0,wwidth);

	sprintf(stats,"Hp: %d",hp);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, stats);

	//Return if dead
	if (hp<=0)
	{
		printf("Game over- you are dead!");
		exit(0);
	}

	//Return if won
	if (xpos>75 && zpos>75)
	{
		printf("Congratulations!");
		exit(0);
	}

	//If in starting area - print instructions
	if ((xpos<-60) && (zpos<-60))
	{
			window_pos(0,wheight/2,0,wwidth);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "You are now in a starting area.");
			window_pos(0,wheight/2-20,0,wwidth);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "You have to find a golden artifact ,");
			window_pos(0,wheight/2-40,0,wwidth);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "which is hidden on the other side of labirynth.");
			window_pos(0,wheight/2-60,0,wwidth);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Good luck and beware of alien turrets!");
			window_pos(0,wheight/2-80,0,wwidth);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Movement- WSAD, Fire - LMB");
	}
	



    glutSwapBuffers(); //Swap buffers

}

void mouse (int x, int y)
{


	int xchange=x-wwidth/2;

	if (xchange!=0) 
	{
		yrot+=xchange/8;

		glutWarpPointer(wwidth/2,wheight/2);

	}
}

void mouseclick(int button, int state, int x, int y)
{
int i;
	if (button==GLUT_LEFT_BUTTON)
	{
		for (i=0;i<1000;i++)
		{
			if (bullets[i].fired==0)
			{
				bullets[i].player=1;
				bullets[i].fired=1;
				bullets[i].xpos=xpos;
				bullets[i].ypos=ypos;
				bullets[i].zpos=zpos;
				bullets[i].xrot=xrot;
				bullets[i].yrot=yrot;
				bullets[i].zrot=zrot;
			
			break;
			
			}
		}
		
	}
}

void turretfire(int t)
{
int i,j;
for (j=0;j<100;j++)
	{
		if (turrets[j].existing==1)
		{
			for (i=0;i<1000;i++)
			{
				if (bullets[i].fired==0)
				{	
						bullets[i].player=0;
						bullets[i].fired=1;
						bullets[i].xpos=turrets[j].xpos;
						bullets[i].ypos=turrets[j].ypos+1;
						bullets[i].zpos=turrets[j].zpos;
						bullets[i].xrot=-turrets[j].xrot+180;
						bullets[i].yrot=-turrets[j].yrot+180;
						bullets[i].zrot=-turrets[j].zrot+180;
						float xrotrad, yrotrad;
							yrotrad = ( bullets[i].yrot / 180 * 3.141592654f);
				       		    xrotrad = ( bullets[i].xrot / 180 * 3.141592654f);
						    bullets[i].xpos += sin(yrotrad)*2;
			 		       	    bullets[i].zpos -= cos(yrotrad)*2;
						    bullets[i].ypos -= sin(xrotrad)*2;
						break;
			
				}
			}
		}
	}
	glutTimerFunc(2000,turretfire,0);

}

void keyboard (unsigned char key, int x, int y) {

	int i,j;
 

/*  if (key==113) //q - look up (for testing)
    {
    xrot += 2;
    if (xrot >360) xrot -= 360;
    }

    if (key==122) //z - look down(for testing)
    {
    xrot -= 2;
    if (xrot < -360) xrot += 360;
    }*/


    if (key==119) //w - go forward
    { 
   float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos += sin(yrotrad)/4;
    zpos -= cos(yrotrad)/4;
    ypos -= sin(xrotrad)/4;
    PlayerCollision(key);
    }

    if (key==115) //s - go backward
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= sin(yrotrad)/4;
    zpos += cos(yrotrad)/4 ;
    ypos += sin(xrotrad)/4;
    PlayerCollision(key);

    }

    if (key==100) //d turn right
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos += cos(yrotrad)/4;
    zpos += sin(yrotrad)/4;
    PlayerCollision(key);



    }

    if (key==97) //a turn left
    {
	    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= cos(yrotrad)/4;
    zpos -= sin(yrotrad)/4;
    PlayerCollision(key);
    }

}

int PlayerCollision(int direction)
{
int i,j;
		//check distance of all cubes to player
		for (j=(int)((int)(zpos+75)/3.3);j<=(int)((int)(zpos+75)/3.3)+1;j++)
		{	
			for (i=(int)((int)(xpos+75)/3.3);i<=(int)((int)(xpos+75)/3.3)+1;i++)
			{	
				if (map[j][i]==1)
				{
					if (sqrt(pow(i*3.3-75-xpos,2)+pow(0-ypos,2)+pow(j*3.3-75-zpos,2))<=2.5) //if distance to cube is lesser than 2.5
					{
						
						float xrotrad, yrotrad;
						if (direction==119)
						{
						 //If key pressed was 'w' reverse the motion
						  	 yrotrad = (yrot / 180 * 3.141592654f);
						   	 xrotrad = (xrot / 180 * 3.141592654f);
						    	xpos -= sin(yrotrad)/4;
						    	zpos += cos(yrotrad)/4;
						   	 ypos += sin(xrotrad)/4;
						}
						if (direction==115)
						{
						//If key pressed was 's' reverse the motion
							    yrotrad = (yrot / 180 * 3.141592654f);
							    xrotrad = (xrot / 180 * 3.141592654f);	
							    xpos += sin(yrotrad)/4;
							    zpos -= cos(yrotrad)/4;
							    ypos -= sin(xrotrad)/4;
						}
						if (direction==100)
						{
							      yrotrad = (yrot / 180 * 3.141592654f);
							    xrotrad = (xrot / 180 * 3.141592654f);	
							  xpos -= cos(yrotrad)/4;
							  zpos -= sin(yrotrad)/4;
						//If key pressed was 'd' reverse the motion
						}
						if (direction==97)
						{	    yrotrad = (yrot / 180 * 3.141592654f);
							    xrotrad = (xrot / 180 * 3.141592654f);	
							  xpos += cos(yrotrad)/4;
							  zpos += sin(yrotrad)/4;
						//If key pressed was 'a' reverse the motion
						}
						 return 1;
					
					}
			
				}
			}
		}
return 0;
}


