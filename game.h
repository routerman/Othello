#pragma once
#include "routerman.h"
#include "agent.h"
#include "gl.h"
#include "board.h"
#include "button.h"
#include "i2.h"
#include "othello.h"
#include <vector>

enum Stat{
	READY,
	PLAY,
	PAUSE,
	WAIT,
	TURN,
	THINK,
	END,
	GAMEOVER
};

enum PlayerMode{
	HUMAN,
	AGENT,
	ROUTERMAN,
};

class Game : public GL{
    int width,height;
    Othello *othello;
	vector<Othello> history;

	Board board;
	Machine *machine[2];
	int stat;
	PlayerMode player_mode[2];

	I2 cursor;
	I2 cursor_square;
	I2 before_square[2];

	bool turn;	//false:BLACK true:WHITE
	int num_disk[2];
	unsigned int time1,subtime;
	stringstream message;
	Disk before_disk[8][8][2];
protected:

public:
	void cursor_adjust(int cx,int cy){
		//cursor_square.set(cursor.x/(60*ration)-1,cursor.y/(60*ration)-1);		

		cursor.x=cx/ration;
		cursor.y=cy/ration-calib;
	}
	void mousebotton(int state ,int button, int cx,int cy);
	void mouse(int cx,int cy);
	void key(unsigned char k, int x, int y);
	void timer(int dt);
	void display();
	void reshape(GLsizei width, GLsizei height){
		this->width=width;
		this->height=height;
		if( width > height*4/3 ){
			ration=(double)height/600;
			glViewport( 0, 0, height*4/3, height );
		}else{
			ration=(double)width/800;
			calib=height-600*ration;
			glViewport( 0, 0, width, width*3/4 );
		}
	}
	void save(){
		this->history.push_back(*this->othello);
	}
	void undo(){
		if(this->history.size() > 1){
			this->history.pop_back();
		   *this->othello = this->history.back();
			this->history.pop_back();
		}
	}
	void Proc();
	Game();
};

extern Game *game;
