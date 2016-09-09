#pragma once
#include "gl.h"
#include "i2.h"
class Disk{
	I2 position;
	bool onboard;			//既に置いてあるかどうか
	bool color;			//色
	bool putable[2];

public:
	void place(bool color){
		onboard=true;
		putable[0]=putable[1]=false;
		this->color=color;
	}
	void draw(bool turn){
			if( onboard ){
				if( color )glColor3f(1,1,1);
				else glColor3f(0,0,0);
				GL::DrawCircle(90+60*position.x,90+60*position.y);
			}
			if( putable[turn] ){
				glColor3f(0,1,0.1);
				GL::DrawSquare(60+60*position.x,60+60*position.y);
			}
	}
	void checkPutable(bool color){
		if( isOnboard() )putable[color]=false;
		else{
			for(int i=-1;i<=1;i++){
				for(int j=-1;j<=1;j++){
					I2 direction(i,j);
					//putable[color]|=line(color,position,direction);
				}
			}
		}
	}
	bool isPutable(bool color){return this->putable[color];}
	void setPutable(bool color,bool state){putable[color]=state;}
	bool isOnboard(){return this->onboard;}
	void setOnboard(bool onboard){this->onboard=onboard;}
	bool getColor(){return this->color;}
	void setColor(bool color){this->color=color;}
	void init_postion(int x, int y){
		this->position.x=x;
		this->position.y=y;
	}
	Disk(){
		onboard=false;
	}
};
