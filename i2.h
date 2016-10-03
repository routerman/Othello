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
	I2 operator+(I2 a){
		a.x = this->x + a.x;
		a.y = this->y + a.y;
		return a;
	}
	void operator+=(I2 a){
		this->x+=a.x;
		this->y+=a.y;
	}
};
