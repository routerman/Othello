#pragma once
#include "GL.hpp"
#include "I2.hpp"

class Board{
	
	//disk<map>
public:
	void drow(unsigned time1){
		/* オセロライン */
		glColor3f(0,0,0);
		for(int i=1;i<=9;i++){
			GL::DrawLine(2,60*i,60,60*i,540);//縦
			GL::DrawLine(2,60,60*i,540,60*i);//横
		}
		GL::DrawPoint(8,180,180);
		GL::DrawPoint(8,180,420);
		GL::DrawPoint(8,420,180);
		GL::DrawPoint(8,420,420);
		/* ガジェット */
		//Line
		glLineWidth(7);
		glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2i(570,0);  
		glColor3f(1,1,1);
		glVertex2i(570,600);
		glEnd();
		//時計
		GL::DrawWatch(700,100,time1/60);  

	}
};