#pragma once
#include <vector>
#include <GL/glut.h>

class Tetronimo
{
public:
	Tetronimo(void);
	Tetronimo(GLfloat initCubeWidth);
	~Tetronimo(void);
	void draw();
	void rotateX();
	void rotateY();
	void rotateZ();
	std::vector<int> boundingBox();
	void setXYZ(int xNew, int yNew, int zNew);
	int getX();
	int getY();
	int getZ();
	std::vector<int> getXOff();
	std::vector<int> getYOff();
	std::vector<int> getZOff();
protected:
	int x, y, z;
	std::vector<int> xOff, yOff, zOff;
	GLfloat cubeWidth;
};
