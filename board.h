#pragma once
#include "gl.h"
#include "i2.h"
#include "button.h"

class Board{
	
	//disk<map>
public:
	Button reset,undo,play;
	Button player[2];
    void button_proc(int &stat,I2 cursor);
    void draw(unsigned time1);
};
