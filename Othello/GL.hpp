#pragma once
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <GL/glut.h>
#define M_PI 3.1415

/////////////////
/* DisplayŠÖ” */
/////////////////
using namespace std;

class GL{
	int waittime;
	int time;
	static int width;
	static int height;
	//int key;
	//bool D3;
public:
	static void CreateWindow(int left,int right,int bottom,int top,const char *name){
		glutInitWindowPosition(0, 0);
		if(top-bottom>0){
			glutInitWindowSize(right-left,top-bottom);
		}else{
			glutInitWindowSize(right-left,bottom-top);
		}
		glutCreateWindow(name);
		gluOrtho2D(left,right,bottom,top);
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);//cursor
	}

	static void display();
	static void timer(int dt);
	static void mouse(int cx,int cy);
	static void mousebotton(int state ,int button, int cx,int cy);
	static void key(unsigned char k, int x, int y);
	static void init();
	//parts
	static void DrawPoint(float size, int x, int y);
	static void DrawLine(int width, int x1, int y1, int x2, int y2);
	static void DrawString(int x, int y, char *s);
	static void Drawstone(int x, int y);
	static void Drawsquare( int x, int y);
	
	static void DrawWatch(int x,int y,float t);
	GL(){}
};
