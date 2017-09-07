#include <stdlib.h>
#include <Windows.h>
#include <GL/glut.h>
#include <time.h>
#include "GameSpace.h"

#include "Tetronimo.h"
#include "Line.h"
#include "Lpiece.h"
#include "S.h"
#include "square.h"
#include "T.h"
#include "zS.h"
#include "zS3.h"
#include "zS5.h"

#include "SOIL.h"

#include <MMsystem.h>

#pragma comment(lib, "Winmm.lib")

bool* keyStates = new bool[256];//store the key states
int gameState = 0;
GLfloat z = 0.0f;
GLfloat cubeWidth = .25f;
GLfloat xPos = 0.0f;
GLfloat yPos = 0.0f;
GameSpace* gamespace;
Tetronimo* tet;
bool gameover = false;
int initSpeed = 1000;
int	speed = 1000;
int score = 0;
int totalLines = 0;
bool sound = false;

void keyOperations (void) {

}

void drawTetronimo()
{
	tet->setXYZ(xPos, yPos, z);
	std::vector<int> box = tet->boundingBox();
	if(box[0] < -2)
		xPos += (-2-box[0]);
	if(box[1] < -2)
		yPos += (-2-box[1]);
	if(box[2] < 0)
		z += (0-box[2]);
	if(box[3] > 2)
		xPos += (2-box[3]);
	if(box[4] > 2)
		yPos += (2-box[4]);
	if(box[5] > 11)
		z += (11-box[5]);
	tet->setXYZ(xPos, yPos, z);
	tet->draw();
}

void titleText (void) {
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0,0,-1.0f);
	GLuint tex_2d = SOIL_load_OGL_texture
	(
		"3D Title Screen.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-.615, -.58, 0);

		glTexCoord2f(0, 1);
		glVertex3f(-.615, .58, 0);

		glTexCoord2f(1, 1);
		glVertex3f(.615, .58, 0);

		glTexCoord2f(1, 0);
		glVertex3f(.615, -.58, 0);
	glEnd();
	glDeleteTextures(1, &tex_2d);
}

void displayOptions (void) {
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0,0,-1.0f);
	GLuint tex_2d;
	char* filename;
	switch(initSpeed)
	{
	case 1000:
		{
			if(sound)
				filename = "3D Options EON.png";
			else // off
				filename = "3D Options EOFF.png";
		}
		break;
	case 800:
		{
			if(sound)
				filename = "3D Options MON.png";
			else
				filename = "3D Options MOFF.png";
		}
		break;
	case 600:
		{
			if(sound)
				filename = "3D Options HON.png";
			else
				filename = "3D Options HOFF.png";
		}
		break;
	}
	tex_2d = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-.615, -.58, 0);

		glTexCoord2f(0, 1);
		glVertex3f(-.615, .58, 0);

		glTexCoord2f(1, 1);
		glVertex3f(.615, .58, 0);

		glTexCoord2f(1, 0);
		glVertex3f(.615, -.58, 0);
	glEnd();
	glDeleteTextures(1, &tex_2d);
}

void displayInstructions (void) {
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0,0,-1.0f);
	GLuint tex_2d = SOIL_load_OGL_texture
	(
		"New3DInstruct.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-.615, -.58, 0);

		glTexCoord2f(0, 1);
		glVertex3f(-.615, .58, 0);

		glTexCoord2f(1, 1);
		glVertex3f(.615, .58, 0);

		glTexCoord2f(1, 0);
		glVertex3f(.615, -.58, 0);
	glEnd();
	glDeleteTextures(1, &tex_2d);
}
void gameOverScreen()
{
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0,0,-1.0f);
	GLuint tex_2d = SOIL_load_OGL_texture
	(
		"GameOver.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-.615, -.58, 0);

		glTexCoord2f(0, 1);
		glVertex3f(-.615, .58, 0);

		glTexCoord2f(1, 1);
		glVertex3f(.615, .58, 0);

		glTexCoord2f(1, 0);
		glVertex3f(.615, -.58, 0);
	glEnd();
	glDeleteTextures(1, &tex_2d);
}

void newTetronimo()
{
	int piece = rand() % 8;
	switch(piece)
	{
	case 0:
		tet = new Line();
		break;
	case 1:
		tet = new Lpiece();
		break;
	case 2:
		tet = new Spiece();
		break;
	case 3:
		tet = new Square();
		break;
	case 4:
		tet = new Tpiece();
		break;
	case 5:
		tet = new zS5piece();
		break;
	case 6:
		tet = new zS3piece();
		break;
	case 7:
		tet = new zSpiece();
		break;
	}
}

void display (void) {

	int i, linesCleared;
	char message[100];
	switch (gameState)
	{
	case 0:
		titleText();
		break;
	case 1:
		linesCleared = gamespace->checkAndClear();
		score += 100 * linesCleared;
		totalLines += linesCleared;
		speed = initSpeed - 100 * (int)(totalLines/10);
		gamespace->draw(cubeWidth);

		drawTetronimo();
		itoa(score, message, 10);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -1.0);
		glRasterPos2f(0.5, 0.5);
		for (i=0; i < 9; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
			message[i] = ' ';
		}
		itoa(totalLines, message, 10);
		glRasterPos2f(-0.5, 0.5);
		for (i=0; i < 9; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
		}
		break;
	case 2:
		gameOverScreen();
		break;
	case 3:
		break;
	case 4:
		displayOptions();
		break;
	case 5:
		displayInstructions();
		break;
	}
	glFlush();
}

void reshape (int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);

}

void keyPressed (unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		tet->rotateX();
		if(gamespace->isOccupied(tet))
		{
			tet->rotateX();
			tet->rotateX();
			tet->rotateX();
		}
		break;
	case 'w':
		tet->rotateY();
		if(gamespace->isOccupied(tet))
		{
			tet->rotateY();
			tet->rotateY();
			tet->rotateY();
		}
		break;
	case 'e':
		tet->rotateZ();
		if(gamespace->isOccupied(tet))
		{
			tet->rotateZ();
			tet->rotateZ();
			tet->rotateZ();
		}
		break;
	case 'a':
		tet->rotateX();
		tet->rotateX();
		tet->rotateX();
		if(gamespace->isOccupied(tet))
		{
			tet->rotateX();
		}
		break;
	case 's':
		tet->rotateY();
		tet->rotateY();
		tet->rotateY();
		if(gamespace->isOccupied(tet))
		{
			tet->rotateY();
		}
		break;
	case 'd':
		tet->rotateZ();
		tet->rotateZ();
		tet->rotateZ();
		if(gamespace->isOccupied(tet))
		{
			tet->rotateZ();
		}
		break;
	case ' ':
		while(z <= 11 && !gamespace->isOccupied(tet))
		{
			z++;
			score += 2;
			tet->setXYZ(xPos, yPos, z);
			glutPostRedisplay();
		}
		if(z <= 0)
		{
			gameState = 2;
		}
		else
		{
			tet->setXYZ(xPos, yPos, z-1);
			gamespace->setSpaces(tet, 1);
			tet->~Tetronimo();
			newTetronimo();
			xPos = 0; yPos = 0; z = 0;
			tet->setXYZ(xPos, yPos, z);
		}
		break;
	case 'n':
		if(gameState == 0)
			gameState = 1;
		else
			gameState = 0;
		break;
	case 'p':
		if(gameState == 1)
			gameState = 3;
		else if(gameState == 3)
			gameState = 1;
		break;
	case 27:
		exit(0);
		break;
	case 'i':
		if(gameState == 5)
			gameState = 0;
		else
			gameState = 5;
		break;
	case 'o':
		if(gameState == 4)
			gameState = 0;
		else
			gameState = 4;
		break;
	}
	tet->setXYZ(xPos, yPos, z);
	std::vector<int> box = tet->boundingBox();
	if(box[0] < -2)
		xPos += (-2-box[0]);
	if(box[1] < -2)
		yPos += (-2-box[1]);
	if(box[2] < 0)
		z += (0-box[2]);
	if(box[3] > 2)
		xPos += (2-box[3]);
	if(box[4] > 2)
		yPos += (2-box[4]);
	if(box[5] > 11)
		z += (11-box[5]);
	tet->setXYZ(xPos, yPos, z);
	glutPostRedisplay();
}

void specialPressed (int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
		yPos += 1;
		if(gamespace->isOccupied(tet))
			yPos -=1;
		tet->setXYZ(xPos, yPos, z);
		break;
	case GLUT_KEY_DOWN:
		yPos -= 1;
		if(gamespace->isOccupied(tet))
			yPos +=1;
		tet->setXYZ(xPos, yPos, z);
		break;
	case GLUT_KEY_LEFT:
		xPos -= 1;
		if(gamespace->isOccupied(tet))
			xPos +=1;
		tet->setXYZ(xPos, yPos, z);
		break;
	case GLUT_KEY_RIGHT:
		xPos += 1;
		if(gamespace->isOccupied(tet))
			xPos -=1;
		tet->setXYZ(xPos, yPos, z);
		break;


	}
	tet->setXYZ(xPos, yPos, z);
	std::vector<int> box = tet->boundingBox();
	if(box[0] < -2)
		xPos += (-2-box[0]);
	if(box[1] < -2)
		yPos += (-2-box[1]);
	if(box[2] < 0)
		z += (0-box[2]);
	if(box[3] > 2)
		xPos += (2-box[3]);
	if(box[4] > 2)
		yPos += (2-box[4]);
	if(box[5] > 11)
		z += (11-box[5]);
	tet->setXYZ(xPos, yPos, z);
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
	if(gameState == 0 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(150 <= x && x <= 725 && 255 <= y && y <= 337)
		{
			score = 0;
			totalLines = 0;
			xPos = yPos = z = 0;
			newTetronimo();
			gamespace->resetSpace();
			gameState = 1;
		}
		if(150 <= x && x <= 725 && 375 <= y && y <= 460)
		{
			gameState = 5;
		}
		if(150 <= x && x <= 725 && 500 <= y && y <= 580)
		{
			gameState = 4;
		}

	}
	else if(gameState == 4 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(505 <= y && y <= 570 && 379 <= x && x <= 505)
		{
			sound = true;
			PlaySound(TEXT("Tetris.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);

		}
		else if(505 <= y && y <= 570 && 549 <= x && x <= 676)
		{
			sound = false;
			PlaySound(0, 0, 0);
		}
		else if(337 <= y && y <= 404 && 366 <= x && x <= 502)
		{
			initSpeed = 1000;
		}
		else if(337 <= y && y <= 404 && 526 <= x && x <= 663)
		{
			initSpeed = 800;
		}
		else if(337 <= y && y <= 404 && 676 <= x && x <= 813)
		{
			initSpeed = 600;
		}
		else if(668 <= y && y <= 729 && 692 <= x && x <= 818)
		{
			gameState = 0;
		}
	}
	else if(gameState == 5 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(643 <= x && x <= 832 && 672 <= y && y <= 742)
		{
			gameState = 0;
		}
	}

	glutPostRedisplay();
}

void Timer(int value)
{
	switch (gameState)
	{
	case 0:
		break;
	case 1:
		tet->setXYZ(xPos, yPos, z);
		std::vector<int> box = tet->boundingBox();
		if(box[0] < -2)
			xPos += (-2-box[0]);
		if(box[1] < -2)
			yPos += (-2-box[1]);
		if(box[2] < 0)
			z += (0-box[2]);
		if(box[3] > 2)
			xPos += (2-box[3]);
		if(box[4] > 2)
			yPos += (2-box[4]);
		if(box[5] > 11)
			z += (11-box[5]);

		z++;
		score += 1;
		tet->setXYZ(xPos, yPos, z);
		if(z > 11 || gamespace->isOccupied(tet))
		{
			if(z <= 1)
				gameState = 2;
			tet->setXYZ(xPos, yPos, z-1);
			gamespace->setSpaces(tet, 1);
			tet->~Tetronimo();
			newTetronimo();
			xPos = 0; yPos = 0; z = 0;
			tet->setXYZ(xPos, yPos, z);
		}
		glutPostRedisplay();
		break;
	}
	glutTimerFunc(speed, Timer, value);
}

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE);
	glutInitWindowSize (850, 800);
	glutInitWindowPosition (200, 50);
	glutCreateWindow ("3D Tetris");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIgnoreKeyRepeat(true);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialPressed);
	glutMouseFunc(mouseClick);
	glutTimerFunc(speed,Timer,0);
	gamespace = new GameSpace();
	newTetronimo();
	if(sound)
		PlaySound(TEXT("Tetris.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	else
		PlaySound(0, 0, 0);
	srand(time(NULL));
	glutMainLoop();
}
