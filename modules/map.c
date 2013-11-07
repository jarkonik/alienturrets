#include <GL/glut.h>



struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;



void cube(float size,int *texture);

void Map(char ** map,int * texture)
{
			
 
int i,j,k;
		
	//Draw labirynth
		for (j=0;j<=48;j++)
		{	
			for (i=0;i<=48;i++)
			{	
				if (map[j][i]==1)
				{
					glPushMatrix();
					glTranslated(i*3.3-75,0,j*3.3-75);
				
					cube(3.3,texture);
					glPopMatrix();
				}
			}
		}

	//Draw artifact
	const GLfloat white[4] = { 1.f, 1.f, 1.f, 1.f };
	const GLfloat gold[4] = { 255, 255, 0, 1.f };
	glPushMatrix();
	glTranslated(80.1,0,80.1);
	glMaterialfv( GL_FRONT, GL_DIFFUSE,gold );
	glutSolidSphere(1.2,10,10);
	glMaterialfv( GL_FRONT, GL_DIFFUSE,white );
	glPopMatrix();
				
	//Draw Skybox	
    	glPushMatrix();
	
		glBindTexture(GL_TEXTURE_2D, texture[0]);         
		glBegin(GL_QUADS);
			 glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-300,-300,-300);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(300,-300,-300);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(300,300,-300);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-300,300,-300);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[0]);        
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-300,-300,300);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(300,-300,300);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(300,300,300);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-300,300,300);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[0]);        
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(300,-300,-300);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(300,-300,300);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(300,300,300);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(300,300,-300);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[0]);        
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-300,-300,-300);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-300,-300,300);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-300,300,300);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-300,300,-300);
		glEnd();
		
		//Floor
		glBindTexture(GL_TEXTURE_2D, texture[1]);     
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-75,-1.5,-75);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(83.4,-1.5,-75);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(83.4,-1.5,83.4);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-75,-1.5,83.4);
		glEnd();
	
    	glPopMatrix();

    
}
