#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

void cube(float size,int *texture)
{		
	srand(time(NULL));	
	float d=size/2;
			glBindTexture(GL_TEXTURE_2D, texture[2]); 
				
			//Front
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-d,-d,-d);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(d,-d,-d);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(d,d,-d);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-d,d,-d);
			glEnd();
			
			//Back
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-d,-d,d);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(d,-d,d);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(d,d,d);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-d,d,d);
			glEnd();

			//Left
			glBegin(GL_QUADS);
			 glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-d,-d,d);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-d,-d,-d);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-d,d,-d);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-d,d,d);
			glEnd();

			//Right
			glBegin(GL_QUADS);

			 glTexCoord2f(0.0f, 0.0f);
			glVertex3f(d,-d,d);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(d,-d,-d);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(d,d,-d);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(d,d,d);
			glEnd();
/*
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

			glBegin(GL_QUADS);
			 glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-300,-300,-300);
			
         		 glTexCoord2f(1.0f, 0.0f);
			glVertex3f(300,-300,-300);

			 glTexCoord2f(1.0f, 1.0f);
			glVertex3f(300,300,-300);

			 glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-300,300,-300);
			glEnd();*/


}
