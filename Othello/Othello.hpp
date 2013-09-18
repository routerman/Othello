#pragma once
#include "GL.hpp"
#include "Board.hpp"
#include "Disk.hpp"
#include "Machine.hpp"
#include "I2.hpp"


class Othello : public GL{
	/* ëÄçÏïœêî */
	Mode mode;
	Stat stat;
	Disk disk[8][8];
	Disk f;
	Machine machine[2];
	Board board;
	I2 cursor;
	I2 before;

	unsigned int num_disk[2];
	unsigned int time1,time2;

	bool debug;
	bool turn;	//false:BLACK true:WHITE
public:
	void init();
	void mousebotton(int state ,int button, int cx,int cy);
	void mouse(int cx,int cy);
	void key(unsigned char k, int x, int y);
	void timer(int dt);
	void display();

	void procedure();
	bool line(bool color,int x,int y,int dx,int dy);
	void reverse(bool color,int cy ,int cx);
	bool CanPut(bool color);
	Othello(){}
};