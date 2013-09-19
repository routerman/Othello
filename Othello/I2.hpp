#pragma once
class I2{
public:
	int x,y;
	void set(int x,int y){
		this->x=x;
		this->y=y;
	}
	I2(){
		this->x=0;
		this->y=0;
	}
	I2(int x,int y){
		this->x=x;
		this->y=y;
	}
	bool isOnboard(){
		if( x<0 || x>7 )return false;
		if( y<0 || y>7 )return false;
		return true;
	}
};

enum Mode{
	P2P,
	P2M,
	M2P,
	M2M,
};


enum Stat{
	READY,
	PLAY,
	POSE,
	WAIT,
	TURN,
	THINK,
	END,
	GAMEOVER
};


enum Cpu{
	NON,
	AGENT,
	ROUTERMAN,
	A2R,
	R2A
};