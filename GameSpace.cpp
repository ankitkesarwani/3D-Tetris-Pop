#include "GameSpace.h"
#include <GL/glut.h>
#include "SOIL.h"
#include "Tetris_Utils.h"
#include "Tetronimo.h"

GameSpace::GameSpace(void)
{
	width = 5;
	length = 5;
	height = 12;
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < length; j++)
		{
			for(int k = 0; k < height; k++)
			{
				filled.push_back(0);
			}
		}
	}
	glEnable( GL_TEXTURE_2D );

}

void GameSpace::draw(GLfloat cubeWidth)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	int count = 0;
	glTranslatef(0.0, 0.0, -1.0f);
	for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			if( count % 2)
				glColor3f(0.0f, 0.0f, 0.0f);
			else
				glColor3f(0.0f, 0.2f, 0.2f);
			count++;
			glBegin(GL_QUADS);
				glVertex3f(-(cubeWidth * 2.5) + cubeWidth*j, -(cubeWidth * 2.5), 0.0 - cubeWidth*i);
				glVertex3f(-(cubeWidth * 2.5) + cubeWidth*j, -(cubeWidth * 2.5), -cubeWidth - cubeWidth*i);
				glVertex3f(-(cubeWidth * 1.5) + cubeWidth*j, -(cubeWidth * 2.5), -cubeWidth - cubeWidth*i);
				glVertex3f(-(cubeWidth * 1.5) + cubeWidth*j, -(cubeWidth * 2.5), 0.0 - cubeWidth*i);
			glEnd();
		}
		count++;
		for(int j = 0; j < 5; j++)
		{
			if( count % 2)
				glColor3f(0.0f, 0.0f, 0.0f);
			else
				glColor3f(0.0, 0.2f, 0.2f);
			count++;
			glBegin(GL_QUADS);
				glVertex3f(-(cubeWidth * 2.5), -(cubeWidth * 2.5) + cubeWidth*j, 0.0 - cubeWidth*i);
				glVertex3f(-(cubeWidth * 2.5), -(cubeWidth * 2.5) + cubeWidth*j, -cubeWidth - cubeWidth*i);
				glVertex3f(-(cubeWidth * 2.5), -(cubeWidth * 1.5) + cubeWidth*j, -cubeWidth - cubeWidth*i);
				glVertex3f(-(cubeWidth * 2.5), -(cubeWidth * 1.5) + cubeWidth*j, 0.0 - cubeWidth*i);
			glEnd();
		}
		count++;
		for(int j = 0; j < 5; j++)
		{
			if( count % 2)
				glColor3f(0.0f, 0.0f, 0.0f);
			else
				glColor3f(0.0, 0.2f, 0.2f);
			count++;
			glBegin(GL_QUADS);
				glVertex3f(-(cubeWidth * 2.5) + cubeWidth*j, (cubeWidth * 2.5), 0.0 - cubeWidth*i);
				glVertex3f(-(cubeWidth * 2.5) + cubeWidth*j, (cubeWidth * 2.5), -cubeWidth - cubeWidth*i);
				glVertex3f(-(cubeWidth * 1.5) + cubeWidth*j, (cubeWidth * 2.5), -cubeWidth - cubeWidth*i);
				glVertex3f(-(cubeWidth * 1.5) + cubeWidth*j, (cubeWidth * 2.5), 0.0 - cubeWidth*i);
			glEnd();
		}
		count++;
		for(int j = 0; j < 5; j++)
		{
			if( count % 2)
				glColor3f(0.0f, 0.0f, 0.0f);
			else
				glColor3f(0.0, 0.2f, 0.2f);
			count++;
			glBegin(GL_QUADS);
				glVertex3f((cubeWidth * 2.5), -(cubeWidth * 2.5) + cubeWidth*j, 0.0 - cubeWidth*i);
				glVertex3f((cubeWidth * 2.5), -(cubeWidth * 2.5) + cubeWidth*j, -cubeWidth - cubeWidth*i);
				glVertex3f((cubeWidth * 2.5), -(cubeWidth * 1.5) + cubeWidth*j, -cubeWidth - cubeWidth*i);
				glVertex3f((cubeWidth * 2.5), -(cubeWidth * 1.5) + cubeWidth*j, 0.0 - cubeWidth*i);
			glEnd();
		}
	}
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			if( count % 2)
				glColor3f(0.0f, 0.0f, 0.0f);
			else
				glColor3f(0.0, 0.2f, 0.2f);
			count++;
			glBegin(GL_QUADS);
				glVertex3f(-(cubeWidth * 2.5) + cubeWidth*i, -(cubeWidth * 2.5) + cubeWidth*j, -12*cubeWidth);
				glVertex3f(-(cubeWidth * 1.5) + cubeWidth*i, -(cubeWidth * 2.5) + cubeWidth*j, -12*cubeWidth);
				glVertex3f(-(cubeWidth * 1.5) + cubeWidth*i, -(cubeWidth * 1.5) + cubeWidth*j, -12*cubeWidth);
				glVertex3f(-(cubeWidth * 2.5) + cubeWidth*i, -(cubeWidth * 1.5) + cubeWidth*j, -12*cubeWidth);
			glEnd();
		}
	}
	GLuint tex_2d = SOIL_load_OGL_texture
		(
			"cube-border.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
		);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	for(int k = 11; k >= 0; k--)
	{
		for(int dist = length/2 + width/2; dist >=0; dist--)
		{
			for(int i = 0; i < width; i++)
			{
				for(int j = 0; j < length; j++)
				{

					int index = i + j * length + k * length * width;

					if(filled[index] && (abs(width/2 - i) + abs(length/2 - j)) == dist)
					{
						glLoadIdentity();
						glTranslatef((i-2)*cubeWidth, (j-2)*cubeWidth, -1.0-0.5*cubeWidth-k*cubeWidth);
						switch (k)
						{
						case 0:
							glColor3f(1.0, 0.0, 0);
							break;
						case 1:
							glColor3f(0.5, 0.0, 0.9);
							break;
						case 2:
							glColor3f(0.9, 0.5, 0);
							break;
						case 3:
							glColor3f(0.9, 0.9, 0.0);
							break;
						case 4:
							glColor3f(0.0, 0.5, 0.9);
							break;
						case 5:
							glColor3f(0.2, 0.6, 0.4);
							break;
						case 6:
							glColor3f(0.2, 0.1, 0.0);
							break;
						case 7:
							glColor3f(0.9, 0.0, 0.5);
							break;
						case 8:
							glColor3f(0.9, 0.5, 0.9);
							break;
						case 9:
							glColor3f(0.5, 0.5, 0.9);
							break;
						case 10:
							glColor3f(0.5, 0.9, 0.0);
							break;
						case 11:
							glColor3f(0.5, 0.9, 0.9);
							break;

						}

						drawCube(cubeWidth, i, j, tex_2d);

					}
				}
			}
		}
	}
	glDeleteTextures(1, &tex_2d);
}


 GameSpace::~GameSpace(void)
{
}

int GameSpace::getSpace(int x, int y, int z)
{
	int index = x + y * length + z * length * width;
	return filled[index];
}

int GameSpace::isOccupied(Tetronimo* tet)
{
	int occupied = 0;
	for(int i = 0; i < 4; i++)
	{
		int xtemp = tet->getX() + tet->getXOff()[i] + 2;
		int ytemp = tet->getY() + tet->getYOff()[i] + 2;
		int ztemp = tet->getZ() + tet->getZOff()[i];
		int index = xtemp + ytemp * length + ztemp * length * width;
		if(index < 0 || index > 4+4*5 + 11*25 || filled[index])
			occupied = 1;
	}
	return occupied;
}

void GameSpace::setSpace(int x, int y, int z, int value)
{
	int index = x + y * length + z * length * width;
	filled[index] = value;
}

void GameSpace::setSpaces(Tetronimo* tet, int value)
{
	for(int i = 0; i < 4; i++)
	{
		int x = tet->getX() + tet->getXOff()[i] + 2;
		int y = tet->getY() + tet->getYOff()[i] + 2;
		int z = tet->getZ() + tet->getZOff()[i];
		int index = x + y * length + z * length * width;
		filled[index] = value;
	}
}

int GameSpace::checkAndClear()
{
	int linesCleared = 0;
	for(int i = 0; i < 12; i++)
	{
		if(check(i))
		{
			linesCleared++;
			for(int k = 0; k < width; k++)
			{
				for(int l = 0; l < length; l++)
				{
					for(int j = i; j > 0; j--)
					{
						int index = k + l * length + j * length * width;
						int oneUp = k + l * length + (j-1) * length * width;
						filled[index] = filled[oneUp];
					}
					filled[k + l * length] = 0;
				}
			}
		}
	}
	return linesCleared;
}

bool GameSpace::check(int level)
{
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < width; j++)
		{
			int index = i + j * length + level * length * width;
			if(!filled[index])
				return false;
		}
	}
	return true;
}

void GameSpace::resetSpace()
{
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < length; j++)
		{
			for(int k = 0; k < height; k++)
			{
				int index = i + j * length + k * length * width;
				filled[index] = 0;
			}
		}
	}
}
