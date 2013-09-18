#pragma once
#include "GL.hpp"
#include "I2.hpp"

class Board{
	//disk<map>
public:
	void drow(int mode,int stat){
		/* ƒIƒZƒƒ‰ƒCƒ“ */
		glColor3f(0,0,0);
		for(int i=1;i<=9;i++){
			GL::DrawLine(2,60*i,60,60*i,540);//c
			GL::DrawLine(2,60,60*i,540,60*i);//‰¡
		}
		GL::DrawPoint(8,180,180);
		GL::DrawPoint(8,180,420);
		GL::DrawPoint(8,420,180);
		GL::DrawPoint(8,420,420);
		
		GL::DrawString(580,500,"p:POSE");
		GL::DrawString(580,530,"backspace:BACK");
		GL::DrawString(580,560,"m:PLAYMODE");
		GL::DrawString(580,590,"esc:EXIT");
    
		glLineWidth(7);
		glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2i(570,0);
    
		glColor3f(1,1,1);
		glVertex2i(570,600);
		glEnd();


		if( mode==P2M || mode==P2P )GL::DrawString(600,410,"1PYOU");
		else GL::DrawString(600,410,"1PCOM");
		if( mode==M2P || mode==P2P )GL::DrawString(600,440,"2PYOU");
		else GL::DrawString(600,440,"2PCOM");
		if(stat==POSE)GL::DrawString(600,300,"POSE");
		    
		GL::DrawWatch(700,100,0);
	}
};