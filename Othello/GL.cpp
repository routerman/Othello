#include "GL.hpp"



void GL::DrawPoint(float size, int x, int y)
{
	glPointSize((GLfloat)size);
	glBegin(GL_POINTS);
	glVertex2i((GLint)x, (GLint)y);
	glEnd();
}


void GL::DrawLine(int width, int x1, int y1, int x2, int y2)
{
	glLineWidth((GLint)width);
	glBegin(GL_LINES);
	glVertex2i((GLint)x1,(GLint)y1);
	glVertex2i((GLint)x2,(GLint)y2);
	glEnd();
}
void GL::DrawString(int x, int y, char *s)
{
	glRasterPos2f(x, y);
    
	//for(; *s != '/0'; s++){
    //for(; *s != '\n'; s++){
    for(unsigned int i=0; i < strlen(s) ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s);
        s++;
	}
}
//石を描く関数
void GL::Drawstone(int x, int y){
	GLint x1, y1;
	glBegin(GL_POLYGON);
	for(int i=0; i<18; i++){
		x1=x+28*sin(M_PI*i/9);
		y1=y+28*cos(M_PI*i/9);
		glVertex2d((GLint)x1,(GLint)y1);
	}
	glEnd();
}
//置ける場所を示す関数
void GL::Drawsquare( int x, int y){
	glBegin(GL_POLYGON);
	glVertex2i((GLint)x,(GLint)y);
	glVertex2i((GLint)x+60,(GLint)y);
	glVertex2i((GLint)x+60,(GLint)y+60);
	glVertex2i((GLint)x,(GLint)y+60);
	glEnd();
}
/*
//アナログ時計を描く関数
void DrawWatch(int x,int y,float t){
	GLint x1, y1, i;
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0; i<360; i+=20){
		x1=x+80*sin(M_PI*i/180);
		y1=y+80*cos(M_PI*i/180);
		glVertex2d((GLint)x1,(GLint)y1);
	}
	glEnd();
    
	glColor3f(0,0,0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(x,y);
	glVertex2f(x+70*sin(t*3.14/30),y-70*cos(t*3.14/30));
	glEnd();
    
}
*/