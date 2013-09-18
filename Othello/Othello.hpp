#pragma once
#include "GL.hpp"
#include "Board.hpp"
#include "Disk.hpp"
#include "Machine.hpp"

#define BLACK false
#define WHITE true

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

class Othello : public GL{
	/* ëÄçÏïœêî */
	Mode mode;
	Stat stat;
	unsigned int mx;
	unsigned int my;
	unsigned int w;
	unsigned int b;
	unsigned int preY;
	unsigned int preX;

	unsigned int time1;
	unsigned int time2;

	bool debug;
	bool turn;	//false:BLACK true:WHITE
	Disk disk[8][8];
	Disk f;
	Machine c;
	Board board;
public:
	void init();
	void mousebotton(int state ,int button, int cx,int cy);
	void mouse(int cx,int cy);
	void key(unsigned char k, int x, int y);
	void timer(int dt);
	void display();

	bool line(bool color,signed int y,signed int x,signed int dy,signed int dx);
	void reverse(bool color,signed int cy ,signed int cx);
	bool CanPut(bool color);
	Othello(){
		time1=time2=0;
		stat=READY;
		mode=P2M;
		debug=false;
		turn=false;
	}
};