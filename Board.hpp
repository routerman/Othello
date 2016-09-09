#pragma once
#include "GL.hpp"
#include "I2.hpp"
#include "Button.hpp"

class Board{
	
	//disk<map>
public:
	Button reset,undo,play;
	Button player[2];
    void button_proc(int &stat,I2 cursor);
    void drow(unsigned time1);
};
