#pragma once
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glut.h>
#define M_PI 3.1415

/*
reshape‘Î‰ž
private‰»
*/
using namespace std;

class GL{
protected:
	int waittime;
	int time;
	int width;
	int height;
	int calib;
	double ration;
	static string title;
	//int key;
	//bool D3;
public:
	void CreateWindow(int left,int right,int bottom,int top,const char *name);
	//static void display();
	//static void timer(int dt);
	//static void mouse(int cx,int cy);
	//static void mousebotton(int state ,int button, int cx,int cy);
	//static void key(unsigned char k, int x, int y);
	//static void init();
	//parts
	static void DrawPoint(float size, int x, int y);
	static void DrawLine(int width, int x1, int y1, int x2, int y2);
	static void DrawString(int x, int y, string s);
	static void DrawCircle(int x, int y);
	static void DrawSquare( int x, int y);
	static void DrawWatch(int x,int y,float t);
	GL(){}
};
