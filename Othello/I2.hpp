#pragma once
class I2{
public:
	int x,y;
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
