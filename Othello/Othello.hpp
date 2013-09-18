#include "GL.hpp"
#include "Board.hpp"
#include "Stone.hpp"
#include "Machine.hpp"

#define STAT_READY 0
#define STAT_PLAY 1
#define STAT_POSE 2
#define STAT_WAIT 3
#define STAT_TURN 4
#define STAT_THINK 5
#define STAT_END 6
#define STAT_GAMEOVER 7

#define MODE_YOUYOU 1
#define MODE_YOUCOM 2
#define MODE_COMYOU 3
#define MODE_COMCOM 4

#define BLACK false
#define WHITE true


class Othello : public GL{
	/* ëÄçÏïœêî */
	unsigned int mx;
	unsigned int my;
	unsigned int w;
	unsigned int b;
	unsigned int preY;
	unsigned int preX;

	unsigned int time1;
	unsigned int time2;

	unsigned int stat;
	unsigned int player;
	bool debug;
	bool turn;	//false:BLACK true:WHITE


	stone s[8][8];
	stone f;
	machine c;
public:
	void InitGame();
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
		stat=STAT_READY;
		player=MODE_YOUCOM;
		debug=false;
		turn=false;
	}
};