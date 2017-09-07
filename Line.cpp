#include "Line.h"

Line::Line(GLfloat initCubeWidth)
	: Tetronimo(initCubeWidth)
{
	for(int i = -1; i < 3; i++)
	{
		xOff.push_back(i);
		yOff.push_back(0);
		zOff.push_back(0);
	}
}

Line::Line()
{
	for(int i = -1; i < 3; i++)
	{
		xOff.push_back(i);
		yOff.push_back(0);
		zOff.push_back(0);
	}
}


Line::~Line(void)
{
}
