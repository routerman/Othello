#pragma once
#include "GL.hpp"
#include "I2.hpp"

class Board{
	//disk<map>
public:
	void drow(int mode,int stat,int cpu,unsigned time1){
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
		//stat
		if(stat==POSE )GL::DrawString(600,250,"POSE");
		else if(stat==READY )GL::DrawString(600,250,"READY");
		//対戦モード
		glColor3f(0,0,0);
		if( mode==P2M || mode==P2P )GL::DrawString(600,300,"1P YOU");
		else GL::DrawString(600,300,"1P COM");
		if( mode==M2P || mode==P2P )GL::DrawString(600,330,"2P YOU");
		else GL::DrawString(600,330,"2P COM");
		//コンピュータ
		if(cpu!=NON){
			if(mode==P2M){
				glColor3f(1,1,1);
				if(cpu==ROUTERMAN)GL::DrawString(600,400,"ROUTERMAN");
				else GL::DrawString(600,430,"AGENT");
			}else if(mode==M2P){
				glColor3f(0,0,0);
				if(cpu==ROUTERMAN)GL::DrawString(600,400,"ROUTERMAN");
				else GL::DrawString(600,430,"AGENT");		
			}else if(mode==M2M){
				glColor3f(0,0,0);
				if(cpu==R2A){
					glColor3f(0,0,0);
					GL::DrawString(600,400,"ROUTERMAN");
					glColor3f(1,1,1);
					GL::DrawString(600,430,"AGENT");
				}else if(cpu==A2R){
					glColor3f(0,0,0);
					GL::DrawString(600,400,"AGENT");
					glColor3f(1,1,1);
					GL::DrawString(600,430,"ROUTERMAN");
				}
			}
		}

		//キーマニュアル
		GL::DrawString(580,500,"p:POSE");
		GL::DrawString(580,530,"backspace:BACK");
		GL::DrawString(580,560,"m:PLAYMODE");
		GL::DrawString(580,590,"esc:EXIT");
	}
};