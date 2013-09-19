#pragma once
#include "Routerman.hpp"
#include "Agent.hpp"
#include "GL.hpp"
#include "Board.hpp"
#include "Disk.hpp"
#include "I2.hpp"


class Othello : public GL{
	Routerman routerman;
	Agent agent;


	Board board;
	Mode mode;
	Stat stat;
	I2 cursor;
	I2 before;
	//bool debug;
	bool turn;	//false:BLACK true:WHITE
	int num_disk[2];
	unsigned int time1,time2;
	stringstream message;

public:
	Disk disk[8][8];
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
	Othello();
	Othello(Disk disk[][8]);
};