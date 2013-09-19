#pragma once
#include "Machine.hpp"
#include "GL.hpp"
#include "Board.hpp"
#include "Disk.hpp"
#include "I2.hpp"


class Othello : public GL{
	Machine machine[2];
	Board board;
	Mode mode;
	Stat stat;
	I2 cursor;
	I2 before;
	//bool debug;
	bool turn;	//false:BLACK true:WHITE
	int num_disk[2];
	unsigned int time1,time2;
public:
	Disk disk[8][8];
	void cpdisk(Disk disk[][8]){
		for(int m=0;m<8;m++){
			for(int n=0;n<8;n++){
				this->disk[m][n]=disk[m][n];
			}
		}
	}
	void init();
	void mousebotton(int state ,int button, int cx,int cy);
	void mouse(int cx,int cy);
	void key(unsigned char k, int x, int y);
	void timer(int dt);
	void display();

	void Proc();
	bool line(bool color,int x,int y,int dx,int dy);
	void reverse(bool color,int cy ,int cx);
	bool CanPut(bool color);
	Othello(){}
};