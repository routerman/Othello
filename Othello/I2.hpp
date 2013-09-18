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


//#define P2P 0
//#define P2M 1
//#define M2P 2
//#define M2M 3

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
