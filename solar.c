#include <sys/times.h>
#include <SDL.h>
#include "GL/gl.h"
#include "GL/vgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define	WINDOW_WIDTH	700
#define WINDOW_HEIGHT	700

/* Re-introduce 32-bit word encoding of 32-bit RGBA values */
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367

#ifndef M_PI
#  define M_PI 3.14159265
#endif

SDL_Surface *sdlSurface;
VGL_Surface glSurface;

int width0 = WINDOW_WIDTH;
int height0 = WINDOW_HEIGHT;

float radius = 0;
float cnt = 0.0;

void init(void)
{
	GLfloat rad,angle = 0.0;
	GLint i;
	glNormal3f(0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0, 1.0, 1.0, 0);
	glPointSize(5);
	glBegin( GL_POINTS );
	glVertex2f(0, 0);
	glEnd();
	glColor4f(0, 1.0, 0, 0);
	for (rad = 0; rad < 1; rad = rad + 0.15)
	{
		glBegin( GL_LINE_LOOP );
		for (i = 0; i < 100; i++)
		{
			angle = ((2.0 * i * M_PI) / 100);
			glVertex2f(rad*sin(angle), rad*cos(angle));
		}
		glEnd();
	}
	glColor4f(1.0, 1.0, 1.0, 0);
	glBegin( GL_LINE_LOOP );
	for (i = 0; i < 100; i++)
	{
		angle = 2.0* i * M_PI / 100;
		glVertex2f(radius*cos(angle), radius*sin(angle));		
	}
	glEnd();
}

void display(void)
{
	init();
	if (radius < 0.9)
		radius = radius + 0.04;
	else radius = 0;
	if ((radius >= 0.4)&&(radius < 0.5)) cnt = 10;
	if (cnt > 0.0)
	{
		glPointSize(cnt);
		glBegin( GL_POINTS );
		glColor4f(1.0, 1.0, 1.0, 0);
		glVertex2f(0.4*cos(2.0 * 20 *M_PI / 100),0.4*sin(2.0 * 20 *M_PI / 100));
		glEnd();
		cnt = cnt - 1.0;
	}
	vglSwapBuffers(sdlSurface, glSurface); //переключение с vgl поверхности на sdl
}

int main(int argc, char* argv[]) 
{
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);
	vglInitialize();

	sdlSurface = SDL_SetVideoMode(width0, height0, 0, SDL_ANYFORMAT);
	glSurface = vglCreateSurface(width0, height0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
	vglMakeCurrent(glSurface, glSurface);

	init();
	display();

	for (;;) {
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)  break;
		display();
	}
	return 0;
}
