#pragma once
#include "machine.h"
#include "disk.h"
#include "i2.h"

#define BLACK false
#define WHITE true


/* Routermanの思考を埋め込んだコンピュータ(厨二www) */
class Routerman : public Machine{
	int weight[8][8];
public:
	bool corner_flag(Othello tmp, I2 test);
	void select();
	int score(Othello tmp, I2 test);
	Routerman(bool color);
};
