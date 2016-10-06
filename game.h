#pragma once
#include "routerman.h"
#include "agent.h"
#include "button.h"
#include "i2.h"
#include "gl.h"
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

	Button reset_button;
	Button undo_button;
	Button play_button;
	Button player_button[2];

	Machine *machine[2];
	int stat;
	PlayerMode player_mode[2];

	I2 cursor_square;
	I2 before_square[2];

	bool turn;	//false:BLACK true:WHITE
	I2 result;

	unsigned int global_time,sub_time;
	stringstream message;
protected:

public:
	void mouse_click(int state ,int button, I2 point);
	void mouse_motion(I2 point);
	void key(unsigned char k, int x, int y);
	void timer(int dt);
	void display();

	I2 cursor_adjust(I2 point);
	void reshape(GLsizei width, GLsizei height);
	void undo();
	void proc();
	void result_message();
	Game();
};

extern Game *game;
