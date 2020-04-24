/*
 * texture.c
 *
 *	Introduction au texturage
 */

#include <stdlib.h>
#include <stdio.h>

// for mac osx
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
// only for windows
#ifdef _WIN32
#include <windows.h>
#endif
// for windows and linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "pnm_io.h"

int angle_x=45, angle_y=-45;
float distance = 8;
GLuint texture, texture2;

// place the camera
void place_camera () {
	glTranslatef (0, 0, -distance);
	glRotatef (angle_x, 1, 0, 0);
	glRotatef (angle_y, 0, 1, 0);
}


//load the texture from file
GLuint load_texture (char * ppm_file)
{
	GLuint texture;
	im_color * image = NULL;

	//**********************************
	// generate and bind the texture
	//**********************************



	//**********************************
	// set the texture parameter for the repetition (clamp)
	//**********************************


	//**********************************
	// set the texture parameter for the interpolation (nearest pixel)
	//**********************************


	//**********************************
	// load the texture from file, see load_ppm
	//**********************************


	//**********************************
	// load the texture in opengl from "image"
	//**********************************



	return texture;
}

// draw the room as a cube
void glRoom (GLdouble size)
{
	GLdouble v = size/2;
	//**********************************
	// load the brick texture using load_texture and store it in texture2
	//**********************************


	//**********************************
	// bind the texture2
	//**********************************


	//**********************************
	// enable opengl texturing
	//**********************************


	glBegin (GL_QUADS);
		glNormal3f ( 0,  0, 1);
		//**********************************
		// BEFORE EACH vertex set the texture coordinates
		//**********************************
		glVertex3f (-v, -v, -v);
		glVertex3f ( v, -v, -v);
		glVertex3f ( v,  v, -v);
		glVertex3f (-v,  v, -v);

		glNormal3f ( 0,  0, -1);
		glVertex3f ( v, -v, v);
		glVertex3f (-v, -v, v);
		glVertex3f (-v,  v, v);
		glVertex3f ( v,  v, v);

		glNormal3f ( -1, 0,  0);
		glVertex3f ( v, -v, -v);
		glVertex3f ( v, -v,  v);
		glVertex3f ( v,  v,  v);
		glVertex3f ( v,  v, -v);

		glNormal3f ( 1,  0,  0);
		glVertex3f (-v, -v,  v);
		glVertex3f (-v, -v, -v);
		glVertex3f (-v,  v, -v);
		glVertex3f (-v,  v,  v);

		glNormal3f ( 0, -1,  0);
		glVertex3f (-v,  v, -v);
		glVertex3f ( v,  v, -v);
		glVertex3f ( v,  v,  v);
		glVertex3f (-v,  v,  v);

		glNormal3f ( 0,  1,  0);
		glVertex3f (-v, -v, -v);
		glVertex3f (-v, -v,  v);
		glVertex3f ( v, -v,  v);
		glVertex3f ( v, -v, -v);
	glEnd();
	//**********************************
	// disable opengl texturing
	//**********************************

}




/* Draw a box visibile from inside */
void place_background () {
	glPushMatrix();
		glScalef (15, 15, 15);
		glRoom (1.0);
	glPopMatrix ();
}


/*
 *OpenGL initialization
 */
void init () {
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);

	// les normales unitaires
	//glEnable (GL_RESCALE_NORMAL);
	glEnable (GL_NORMALIZE);

	//**********************************
	// load the wood texture in texture
	//**********************************


	//**********************************
	// enable texture
	//**********************************


	//**********************************
	// enable cull face
	//**********************************


	//**********************************
	// enable depht test
	//**********************************

}



void display ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//place the camera
	place_camera ();

	// draw the background
	glColor3f (1.0, 1.0, 1.0);
	place_background();

	//**********************************
	// bind the texture in texture (the wood texture)
	//**********************************

	//**********************************
	// enable texturing
	//**********************************


	//**********************************
	// draw a simple square face of unitary size centered in (0,0,0)
	//**********************************

		//**********************************
		// Before declaring each vertex give also the texture coordinates
		//**********************************


	//**********************************
	// disable texturing
	//**********************************


	glutSwapBuffers ();
}

/*
 *	@brief Callback for window size change
 *	@param[in] w new width of the window
 *	@param[in] h new height of the window
 */
void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (60, (GLfloat)w/(GLfloat)h, 0.1, 50);
}


/*
 * Callback for special keys
 */
#define DELTA_ANGLE_X	5
#define DELTA_ANGLE_Y	5
#define DELTA_DISTANCE	0.3
#define DISTANCE_MIN	0.0
void special (int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			angle_x = (angle_x + DELTA_ANGLE_X) % 360;
		break;
		case GLUT_KEY_DOWN:
			angle_x = (angle_x - DELTA_ANGLE_X) % 360;
		break;
		case GLUT_KEY_LEFT:
			angle_y = (angle_y + DELTA_ANGLE_Y) % 360;
		break;
		case GLUT_KEY_RIGHT:
			angle_y = (angle_y - DELTA_ANGLE_Y) % 360;
		break;
		case GLUT_KEY_PAGE_DOWN:
			distance += DELTA_DISTANCE;
		break;
		case GLUT_KEY_PAGE_UP:
			distance -= (distance>DISTANCE_MIN)? DELTA_DISTANCE: 0.0;
		break;
		default: break;
	}
	glutPostRedisplay();
}
/*
 * Callback for keys
 */
void keyboard (unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
		case 27: // [ESC]
			exit(0);
		break;
		default:
        break;
	}
}



int main (int argc, char **argv) {

	glutInit (&argc,argv);
	// Double buffer, rgb color and z-buffer activated
	glutInitDisplayMode (GLUT_DOUBLE |
			GLUT_RGB | GLUT_DEPTH);

	// main windows
	glutInitWindowSize (640,480);
	glutInitWindowPosition (50,50);
	glutCreateWindow ("OpenG Texture");

	// set callbacks
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);

	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);

	init();

	glutMainLoop();
	exit (0);
}
