#pragma once
#include "disk.h"
#include "i2.h"

class Othello{
private:
	Disk disk[8][8];
	int num_disk[2];

	void updateDisk();
	void reverseLine(bool color,I2 r,I2 d);
	void reverse(bool color,I2 position);
	void turn_disk(bool color, I2 r);
	bool checkLine(bool color,I2 r,I2 d);
	bool checkPutable(bool color,I2 position);

public:
	void put_disk(bool color, I2 r);

	I2 judge();
	bool getColor(I2 r);
	bool isOnboard(I2 r);
	bool isPutable(bool color, I2 r);
	bool isAnyPutable(bool color);
	void draw_disks(bool turn);
	Othello();
};
