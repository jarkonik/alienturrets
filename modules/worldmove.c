#include <math.h>
#include <GL/glut.h>

struct Bullet {
    float xpos;
    float ypos;
    float zpos;
    float xrot;
    float yrot;
    float zrot;
    int fired;
    int player;
};
typedef struct Bullet Bullet;

struct Turret {
    float xpos;
    float ypos;
    float zpos;
    float xrot;
    float yrot;
    float zrot;
    int existing;
};
typedef struct Turret Turret;

void WorldMove(Bullet * bullets,char ** map,Turret * turrets,float xpos,float ypos,float zpos,int *hp)
{	

					const GLfloat blue[4] = { .3f, .3f, 1.f, 1.f };
					const GLfloat white[4] = { 1.f, 1.f, 1.f, 1.f };
					const GLfloat green[4] = { 0, 204, 0, 1.f };
					const GLfloat red[4] = { 204,0 , 0, 1.f };
int i,j,k;



		//Draw turrets
		for (i=0;i<100;i++)
		{
			if (turrets[i].existing==1)
			{
					
					glPushMatrix();
				
					
					glTranslated(turrets[i].xpos,turrets[i].ypos,turrets[i].zpos);
					
					//Target player
					float x,z,c,angle;
					
					x=xpos-turrets[i].xpos;
					z=zpos-turrets[i].zpos;
					c=sqrt(pow(x,2)+pow(z,2));
					angle=asin(x/c)/3.14*180;
					if (angle<0) angle=-angle;
				
				
					
					if ((x>=0) && (z>=0)) angle=180-angle;
					if ((x<0) && (z>=0)) angle=180+angle;
					if ((x<0) && (z<0)) angle=360-angle;
					turrets[i].yrot=180;
					turrets[i].yrot-=angle;
					
					
					//End targeting					


	
				
					glMaterialfv( GL_FRONT, GL_DIFFUSE,blue );
					
					glutSolidCube(1.4);
					
					
					
					glTranslated(0,1,0);
		
					glutSolidSphere(1.2,10,10);	
					glPushMatrix();
					glRotatef(turrets[i].yrot,0,1.0,0.0);
					glMaterialfv( GL_FRONT, GL_DIFFUSE, green );
					glutSolidCone(0.6,2.3,10,10);
					glPopMatrix();
					glPopMatrix();
					glMaterialfv( GL_FRONT, GL_DIFFUSE, white );
			}
		}

	
	//Draw bullets
	for (i=0;i<1000;i++)
	{
		if (bullets[i].fired==1)
		{
				    //Check for collisions with closest cubes and destroy bullet if collides
				    for (j=(int)((int)(bullets[i].zpos+75)/3.3);j<=(int)((int)(bullets[i].zpos+75)/3.3)+1;j++)
		        	    {	
				
					for (k=(int)((int)(bullets[i].xpos+75)/3.3);k<=(int)((int)(bullets[i].xpos+75)/3.3)+1;k++)
					{	
						
						if (map[j][k]==1)
						{
							if (sqrt(pow(k*3.3-75-bullets[i].xpos,2)+pow(0-bullets[i].ypos,2)+pow(j*3.3-75-bullets[i].zpos,2))<=2.3) //if distance to cube is lesser than 2.3
							{
								bullets[i].fired=0;
							}
						}
					}
				    }

				   //Check for collisions with player and if collides substract hp and destroy bullet
				   if ((bullets[i].player==0) && (sqrt(pow(xpos-bullets[i].xpos,2)+pow(ypos-bullets[i].ypos,2)+pow(zpos-bullets[i].zpos,2))<=1.0)) //if distance to player is lesser than 1.0
							{
							
								(*hp)--;
								bullets[i].fired=0;
							}

				    //Check for collisions with turrets and destroy turret and bullet if collides
				    for (j=0;j<100;j++)
				    {
					if (turrets[j].existing==1)
					{
				
						if (sqrt(pow(turrets[j].xpos-bullets[i].xpos,2)+pow(turrets[j].ypos-bullets[i].ypos,2)+pow(turrets[j].zpos-bullets[i].zpos,2))<=2.0) //if distance to turret is lesser than 2.5
							{
								turrets[j].existing=0;
								bullets[i].fired=0;
							}
					}					
				    }

				    //Move bullet
		   		    float xrotrad, yrotrad;
				    yrotrad = ( bullets[i].yrot / 180 * 3.141592654f);
		       		    xrotrad = ( bullets[i].xrot / 180 * 3.141592654f);
			            bullets[i].xpos += sin(yrotrad)*2;
	 		       	    bullets[i].zpos -= cos(yrotrad)*2;
				    bullets[i].ypos -= sin(xrotrad)*2;

					//Translate and draw bullet
					glPushMatrix();
					glTranslated(bullets[i].xpos,bullets[i].ypos,bullets[i].zpos);
					glMaterialfv( GL_FRONT, GL_DIFFUSE, red );
					glutSolidSphere(0.1,10,10);
					glMaterialfv( GL_FRONT, GL_DIFFUSE, white );
					glPopMatrix();
		}
					
	}
}
