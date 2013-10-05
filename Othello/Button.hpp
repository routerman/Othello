#pragma once
#include "I2.hpp"
#include "GL.hpp"

class Button{
	bool flag;
	bool active;
	int left,right,top,bottom;
	float r,g,b;
	string label[3];
	int num_label;
public:
	void drow(){	
		glColor3f(r,g,b);
		glBegin(GL_POLYGON);
			glVertex2i((GLint)left ,(GLint)top);
			glVertex2i((GLint)right,(GLint)top);
			glVertex2i((GLint)right,(GLint)bottom);
			glVertex2i((GLint)left ,(GLint)bottom);
		glEnd();
		if(active)glColor3f(r+0.1,g+0.1,b+0.1);
		else glColor3f(r-0.1,g-0.1,b-0.1);
		glBegin(GL_POLYGON);
			glVertex2i((GLint)left+5 ,(GLint)top+5);
			glVertex2i((GLint)right-5,(GLint)top+5);
			glVertex2i((GLint)right-5,(GLint)bottom-5);
			glVertex2i((GLint)left+5 ,(GLint)bottom-5);
		glEnd();
		glColor3f(1-r,1-g,1-b);
		GL::DrawString(left+10,(bottom+top)/2,label[num_label]);
	}
	void setstring(string a,string b,string c){
		this->label[0]=a;
		this->label[1]=b;
		this->label[2]=c;
	}
	void set(int left,int right,int top,int bottom,float r,float g,float b){
		this->left=left;
		this->right=right;
		this->top=top;
		this->bottom=bottom;
		this->r=r;
		this->g=g;
		this->b=b;
	}
	void selectLabel(int num){if( num>=0 && num<=2)this->num_label=num;}
	bool isPushed(I2 cursor){
		if( cursor.x<left || cursor.x>right  )return false;
		if( cursor.y<top  || cursor.y>bottom )return false;
		active=!active;
		return true;
	}
	Button(){
		num_label=0;
	}
};